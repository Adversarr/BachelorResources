#include "data_seg.hpp"
#include "utils.hpp"
#include <iomanip>
#include <map>
#include <regex>
#include <spdlog/spdlog.h>
#include <sstream>

namespace mias {

static void throw_error() {
  throw std::runtime_error("Data Segment Runtime Error");
}

static std::pair<std::vector<char>, int> get_string(std::string str) {
  std::vector<char> retval;
  int i = 1;
  bool is_last_backslash = false;
  while (i != str.length()) {
    char c = str[i];
    if (is_last_backslash) {
      // NOTE: Only support \0 \\ \"
      if ('0' != c || c != '\\' || c != '"') {
        spdlog::error("Unrecognized Reinterprete char '{}'", c);
        throw_error();
      }

      retval.push_back(c);

      is_last_backslash = false;
    } else {
      if (c == '\\') {
        is_last_backslash = true;
      } else if (c == '"') {
        break;
      } else {
        retval.push_back(c);
      }
    }

    i += 1;
  }

  if ('"' != str[i]) {
    spdlog::error("Untermintated Ascii String = {}", str);
    throw_error();
  }

  return std::make_pair(retval, i);
}

static std::vector<char> interprete_strings(std::string data_str,
                                            bool append_zero) {
  std::vector<char> retval;
  spdlog::debug("Interpreting(str) {}", data_str);
  auto start = find_first_nws(data_str);
  if (start == data_str.length()) {
    spdlog::error("Expect: '\"'");
    throw_error();
  }
  while (start != data_str.length()) {
    auto [s, end] = get_string(data_str.substr(start));
    std::move(s.begin(), s.end(), std::back_inserter(retval));
    if (append_zero) {
      retval.push_back('\0');
    }

    auto comma = find_first_nws(data_str, start + end + 1);
    if (comma != data_str.length()) {
      if (data_str[comma] != ',') {
        spdlog::error("Expect ','");
        throw_error();
      }
      start = find_first(data_str, '"', comma + 1);
    } else {
      break;
    }
  }

  return retval;
}

static std::vector<uint32_t> interprete_integers(std::string data_str) {
  std::vector<uint32_t> retval;
  spdlog::debug("Interpreting {}", data_str);
  // 1. Get first not ws
  auto start = find_first_nws(data_str);
  while (start != data_str.length()) {
    auto i = start;
    while (i < data_str.length()) {
      char c = data_str[i];
      if (!(isxdigit(c) || c == 'x')) {
        break;
      }
      i += 1;
    }
    auto num = data_str.substr(start, i - start);
    auto num_i = mias::atoi(num);
    spdlog::debug("Num str = {}, Num Interprete = {}", num, num_i);

    // Process string like 6:3
    bool is_grouped = false;
    if (i < data_str.length()) {
      if (data_str[i] == ':') {
        is_grouped = true;
      }
    }
    int group_num = 1;
    if (is_grouped) {
      std::istringstream iss(data_str.substr(i + 1));
      iss >> std::setbase(10) >> group_num;
    }

    for (int i = 0; i < group_num; ++i) {
      retval.push_back(num_i);
    }

    auto comma = find_first(data_str, ',', i);
    if (comma == data_str.length()) {
      break;
    } else {
      start = find_first_nws(data_str, comma + 1);
    }
  }
  return retval;
}

void DataSegParser::Parse(const std::vector<std::string> &clean_input) {
  // Reset();
  input_str_ = clean_input;

  auto cmd_type = GetNextCommandType();
  while (cmd_type != CommandType::kEnd) {
    spdlog::debug("[D] parsing {}, type = {}", input_str_[index_],
                  (int)cmd_type);

    switch (cmd_type) {
    case CommandType::kAlign:
      RunAlignCommand();
      break;
    case CommandType::kSpace:
      RunSpaceCommand();
      break;
    case CommandType::kVar:
      RunVarDefinitionCommand();
      break;
    case CommandType::kData:
      RunDataDefinitionCommand();
      break;
    case CommandType::kEmpty:
    case CommandType::kEnd:
      break;

    default:
      throw std::runtime_error("Error Command Type.");
    }

    index_ += 1;
    cmd_type = GetNextCommandType();
  }

  spdlog::info("[D] Done.");
}

void DataSegParser::RunVarDefinitionCommand() {
  auto cmd = input_str_[index_];
  // remove all the spaces.
  int i = 0;
  while (std::isspace(cmd[i])) {
    i += 1;
    if (i >= cmd.length()) {
      spdlog::error("Expect: Var Name");
      throw_error();
    }
  }

  auto vname_begin = i;
  while (cmd[i] != ':') {
    i += 1;
    if (i >= cmd.length()) {
      spdlog::error("Expect: ':'");
      throw_error();
    }
  }
  auto vname_end = i;
  std::string vname = cmd.substr(vname_begin, i - vname_begin);
  RunVarDefinition(vname);
}

void DataSegParser::RunVarDefinition(std::string name) {
  if (addr_name_.find(name) != addr_name_.end()) {
    spdlog::error("name = {}", name);
    throw_error();
  }

  if (is_align_) {
    int fill_zero_count = dmem_.size() % align_n_;
    for (int i = 0; i < fill_zero_count; ++i) {
      dmem_.push_back(0);
    }
    spdlog::info("Align variable, filled {} zero(s).", fill_zero_count);
  }

  is_align_ = is_next_align_;
  align_n_ = next_align_n_;
  is_next_align_ = false;

  addr_name_.insert({name, dmem_.size()});
  spdlog::info("[D] Variable: {}, Address: {}, Align = {}, AlignValid? = {}",
               name, dmem_.size(), align_n_, is_align_);
}

void DataSegParser::RunDataDefinitionCommand() {
  auto cmd = input_str_[index_];
  auto space_position = find_first_ws(cmd);
  auto dtype = strtolower(cmd.substr(0, space_position));
  spdlog::debug("Got dtype = {}", dtype);
  auto remaining_begin = find_first_nws(cmd, space_position);
  if (dtype == ".ascii") {
    auto ascii = interprete_strings(cmd.substr(remaining_begin), false);
    for (auto c : ascii) {
      spdlog::debug("Ascii: c = {}", (int)c);
      dmem_.push_back(static_cast<uint8_t>(c));
    }
  } else if (dtype == ".asciiz") {
    auto ascii = interprete_strings(cmd.substr(remaining_begin), true);
    for (auto c : ascii) {
      spdlog::debug("Asciiz: c = {}", (int)c);
      dmem_.push_back(static_cast<uint8_t>(c));
    }
  } else {
    if (dtype == ".float" || dtype == ".double") {
      spdlog::error("Minisys does not support floating operation.");
      throw_error();
    }
    auto segment = interprete_integers(cmd.substr(remaining_begin));
    if (dtype == ".word") {
      for (auto ui : segment) {
        dmem_.push_back(static_cast<uint8_t>(ui >> 24));
        dmem_.push_back(static_cast<uint8_t>(ui >> 16));
        dmem_.push_back(static_cast<uint8_t>(ui >> 8));
        dmem_.push_back(static_cast<uint8_t>(ui));
      }
    } else if (dtype == ".half") {
      for (auto ui : segment) {
        if (ui > 0xFFFF) {
          spdlog::error(
              "Data type '.half' has value greater than 0xFFFF, value is {}",
              ui);
          throw_error();
        }
        dmem_.push_back(static_cast<uint8_t>(ui >> 8));
        dmem_.push_back(static_cast<uint8_t>(ui));
      }
    } else if (dtype == ".byte") {
      for (auto ui : segment) {
        if (ui > 0xFF) {
          spdlog::error(
              "Data type '.byte' has value greater than 0xFF, value is {}", ui);
          throw_error();
        }
        dmem_.push_back(static_cast<uint8_t>(ui));
      }
    }
  }
}

void DataSegParser::RunAlignCommand() {
  auto cmd = input_str_[index_];
  int dot_position = find_first_nws(cmd);

  if (cmd.substr(dot_position + 1, 5) != "align") {
    spdlog::error("Expect: 'align', Got: {} {}", dot_position,
                  cmd.substr(dot_position + 1, 5));
    throw_error();
  }

  std::istringstream s(cmd.substr(dot_position + 6));

  int n;
  s >> n;
  if (n <= 1) {
    spdlog::error("Align: n should greater than 1");
    throw_error();
  }

  RunAlign(n * 2);
}

void DataSegParser::RunAlign(int n) {
  spdlog::info("[D] Align next variable, n * 2 = {}", n);
  next_align_n_ = n;
  is_next_align_ = true;
}

void DataSegParser::RunSpaceCommand() {
  auto cmd = input_str_[index_];
  cmd = strtolower(cmd);
  if (cmd.substr(0, 6) != ".space") {
    spdlog::error("Expect: '.space'");
  }

  auto n = atoi(cmd.substr(6));
  if (n <= 0) {
    spdlog::error("Space command with n <= 0: n = {}", n);
    throw_error();
  } else {
    std::fill_n(std::back_inserter(dmem_), n, 0);
    spdlog::info("Fill {} zero bytes", n);
  }
}

DataSegParser::CommandType DataSegParser::GetNextCommandType() const {
  if (index_ >= input_str_.size()) {
    return CommandType::kEnd;
  }

  auto cmd = input_str_[index_];
  if (std::isalpha(cmd.front())) {
    return CommandType::kVar;
  }

  if (cmd.front() == '.') {
    if (cmd.length() < 5) {
      spdlog::error("Expect: 'align', 'byte', 'half', 'word', 'float', "
                    "'double', 'ascii', 'asciiz', 'space'.");
      throw_error();
    }

    auto first3 = strtolower(cmd.substr(1, 3));
    if (first3 == "ali") {
      return CommandType::kAlign;
    } else if (first3 == "spa") {
      return CommandType::kSpace;
    } else {
      return CommandType::kData;
    }
  }

  return CommandType::kError;
}

inline static uint32_t compose(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
  uint32_t v;
  uint8_t *p = reinterpret_cast<uint8_t *>(&v);
  p[3] = a;
  p[2] = b;
  p[1] = c;
  p[0] = d;
  return v;
}

DmemDesc DataSegParser::Describe() const {
  DmemDesc desc;
  desc.variables = addr_name_;
  for (int i = 0; i * 4 < dmem_.size(); ++i) {
    desc.dmem_value.push_back(compose(dmem_[i * 4], dmem_[i * 4 + 1],
                                      dmem_[i * 4 + 2], dmem_[i * 4 + 3]));
  }
  return desc;
}

} // namespace mias
