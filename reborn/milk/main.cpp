#include <cxxopts.hpp>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <regex>
#include <set>
#include <string_view>

using InputFileData = std::vector<std::string>;
std::vector<std::string> input_file_paths;
std::vector<InputFileData> input_file_data;

bool verbose = false;
bool has_bios = false;

bool sort = false;

std::string output_file_path;

struct FlagMatch {
  bool is_valid = false;
  size_t start = 0, end = 0;
};
struct Anchor {
  uint32_t document_id;
  uint32_t line;
  FlagMatch match;
  std::string mapped_name;
};

struct {
  std::multimap<std::string, Anchor> flags;
  std::set<std::string> flag_remap;
} output_descriptor;

void run();

int main(int argc, char **argv) {
  cxxopts::Options opts("milk", "MInisys LinKer");
  opts.add_options()("d", "flags without dot will be ignored when linking.",
                     cxxopts::value<std::string>()->default_value("1"));
  opts.add_options()("o", "Output Asm File, 1 for stdout.",
                     cxxopts::value<std::string>()->default_value("1"));
  opts.add_options()("v", "Enable verbose mode",
                     cxxopts::value<bool>()->default_value("false"));
  opts.add_options()("s", "sort output",
                     cxxopts::value<bool>()->default_value("false"));
  opts.add_options()("h,help", "Print usage");
  opts.add_options()(
      "b", "Bios file (special). take the first input as BIOS program",
      cxxopts::value<bool>()->default_value("false"));
  auto option = opts.parse(argc, argv);

  if (option.count("h") > 0) {
    std::cout << opts.help() << std::endl;
    return EXIT_SUCCESS;
  }

  input_file_paths = option.unmatched();
  verbose = option["v"].as<bool>();
  has_bios = option["b"].as<bool>();
  sort = option["s"].as<bool>();
  run();
  return EXIT_SUCCESS;
}
void read_files();

void mark_flags();

void run_remap();

void generate_output();

void run() {
  read_files();
  mark_flags();
  run_remap();
  generate_output();
}

FlagMatch get_flag_in_line(const std::string &line) {
  std::regex flag_regex("\\b(.+):", std::regex::ECMAScript);
  std::smatch base_match;
  if (!std::regex_search(line, base_match, flag_regex)) {
    return {false, 0, 0};
  }

  if (base_match.size() == 0) {
    return {false, 0, 0};
  } else if (base_match.size() != 2) {
    return {false, 0, 0};
  }

  auto ssmatch = base_match[1];
  std::string matched = ssmatch.str();
  FlagMatch match;
  match.is_valid = true;
  match.start = std::distance(line.begin(), ssmatch.first);
  match.end = ssmatch.length() + match.start;
  if (verbose) {
    std::cerr << "Log: found flag " << std::quoted(matched) << " in line "
              << std::quoted(line) << std::endl;
    std::cerr << "Log: Flag informathion: (" << match.start << ", " << match.end
              << ")" << std::endl;
  }
  return match;
}

InputFileData read_file(const std::string &path) {
  std::ifstream file(path);
  std::vector<std::string> data;
  if (!file) {
    std::cerr << "Error: cannot open file " << std::quoted(path) << std::endl;
    exit(EXIT_FAILURE);
  }
  while (file.good()) {
    std::string s;
    std::getline(file, s);
    if (file.fail() && !file.eof()) {
      std::cerr << "File read operation failed." << std::endl;
      exit(EXIT_FAILURE);
    }
    data.push_back(s);
  }
  return data;
}

void read_files() {
  for (const auto &path : input_file_paths) {
    auto data = read_file(path);
    input_file_data.push_back(data);

    if (verbose) {
      std::cerr << "File " << std::quoted(path)
                << " loaded. #line = " << data.size() << std::endl;
    }
  }
  if (has_bios) {
    if (verbose) {
      std::cerr << "Bios loaded as file#0." << std::endl;
    }
  }
}

void mark_flags() {
  size_t document_id = 0;
  for (const auto &data : input_file_data) {
    size_t line_id = 0;
    for (const auto &line : data) {
      auto match = get_flag_in_line(line);
      if (match.is_valid) {
        Anchor anchor;
        anchor.document_id = document_id;
        anchor.line = line_id;
        anchor.match = match;
        auto flag = line.substr(match.start, match.end - match.start);
        output_descriptor.flags.emplace(flag, anchor);
      }

      line_id += 1;
    }
    document_id += 1;
  }
}

std::string try_emplace_flag(std::string flag_name, std::string mapped_name,
                             uint32_t document_id, uint32_t line_id) {
  if (output_descriptor.flag_remap.find(mapped_name) !=
      output_descriptor.flag_remap.end()) {
    if (verbose) {
      std::cerr << "Try mapped name " << std::quoted(mapped_name)
                << " already in use." << std::endl;
    }
    return try_emplace_flag(flag_name,
                            mapped_name + std::to_string(document_id) +
                                std::to_string(line_id),
                            document_id, line_id);
  }
  output_descriptor.flag_remap.insert(flag_name);
  return mapped_name;
}

void run_remap() {
  auto &flags = output_descriptor.flags;
  auto &remap = output_descriptor.flag_remap;
  for (auto &[k, v] : flags) {
    auto mapped_name = try_emplace_flag(k, k, v.document_id, v.line);
    v.mapped_name = mapped_name;
    auto &line = input_file_data[v.document_id][v.line];
    line.replace(v.match.start, v.match.end - v.match.start, mapped_name);
    if (verbose) {
      std::cerr << "Mapping " << std::quoted(k) << "->"
                << std::quoted(mapped_name) << " (" << line << ")" << std::endl;
    }
  }
}

std::string str_tolower(std::string s) {
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c) { return std::tolower(c); } // correct
  );
  return s;
}

void do_map(std::string &s, uint32_t document_id) {
  std::regex word("\\b[0-9A-Za-z_\\.]+\\b",
                  std::regex::ECMAScript | std::regex::icase);
  auto words_begin = std::sregex_iterator(s.begin(), s.end(), word);
  auto words_end = std::sregex_iterator();
  for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
    std::smatch match = *i;
    std::string match_str = match.str();
    if (output_descriptor.flags.find(match_str) !=
        output_descriptor.flags.end()) {
      auto [b, e] = output_descriptor.flags.equal_range(match_str);
      for (auto i = b; i != e; ++i) {
        if (i->second.document_id == document_id) {
          if (verbose) {
            std::cerr << "Found flag in " << std::quoted(s) << "Will map to"
                      << std::quoted(i->second.mapped_name) << std::endl;
          }
          s.replace(match.position(), match.length(), i->second.mapped_name);
          break;
        }
      }
    }
  }
}

void generate_output() {
  enum State { kData, kText, kNone } state;
  InputFileData data, text;

  for (size_t i = 0; i < input_file_data.size(); ++i) {
    auto &doc = input_file_data[i];
    bool found_bios_user_pg_begin = false;
    state = kNone;
    for (auto line : doc) {
      if (has_bios && str_tolower(line) == "user_program_begin:" && i == 0) {
        if (verbose) {
          std::cerr << "Found user program begin in BIOS" << std::endl;
        }

        found_bios_user_pg_begin = true;
        break;
      }
      do_map(line, i);
      if (sort) {
        if (str_tolower(line).find(".data") != std::string::npos) {
          state = kData;
        } else if (::str_tolower(line).find(".text") != std::string::npos) {
          state = kText;
        }
        if (state == kData) {
          data.push_back(line);
        } else if (state == kText) {
          text.push_back(line);
        }
      } else {
        std::cout << line << std::endl;
      }
    }

    if (found_bios_user_pg_begin) {
      if (sort) {
        text.push_back("user_program_begin:");
        text.push_back("\tnop");
        text.push_back("\tnop");
        text.push_back("\tnop");
      } else {
        std::cout << "user_program_begin:" << std::endl;
        std::cout << "\tnop" << std::endl;
        std::cout << "\tnop" << std::endl;
        std::cout << "\tnop" << std::endl;
      }
    }
  }

  if (sort) {
    for (const auto &line : data) {
      std::cout << line << std::endl;
    }
    for (const auto &line : text) {
      std::cout << line << std::endl;
    }
  }
}
