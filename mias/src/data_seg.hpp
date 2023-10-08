#pragma once
#include "table.hpp"
#include <map>
#include <spdlog/spdlog.h>

namespace mias {

class DataSegParser {

public:
  DataSegParser() = default;

  void Reset();

  void Parse(const std::vector<std::string> &clean_input);

  enum class CommandType { kEmpty, kVar, kSpace, kAlign, kEnd, kData, kError };

private:
  CommandType GetNextCommandType() const;

  void RunVarDefinitionCommand();

  void RunDataDefinitionCommand();

  void RunSpaceCommand();

  void RunAlignCommand();

  void RunVarDefinition(std::string name);

  void RunAlign(int n);

public:
  DmemDesc Describe() const;

private:
  std::vector<std::string> input_str_;

  std::vector<uint8_t> dmem_;

  std::map<std::string, size_t> addr_name_;

  size_t index_{0};
  bool is_align_{false};
  bool is_next_align_{false};
  int align_n_{0};
  int next_align_n_{0};

public:
  const std::vector<uint8_t> &GetDmem() const noexcept { return dmem_; }
};

} // namespace mias
