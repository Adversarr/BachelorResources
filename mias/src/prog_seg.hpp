#pragma once

#include <map>
#include <vector>
#include <string>
#include "table.hpp"
namespace mias {

class ProgSegParser {
public:
  void SetDmemDesc(const DmemDesc& desc);

  void Parse(const std::vector<std::string> &clean_input);

  PmemDesc Describe();

public:
  std::vector<uint32_t> GenerateOutput() const;

private:
  void MarkAllFlags();

  void GenerateBinary();
  void AddFlag(std::string name);

  std::vector<std::string> input_str_;
  std::vector<std::string> instr_str_;
  std::vector<uint32_t> instr_binary_;
  size_t index_{0};
  std::map<std::string, std::size_t> flags_;
  DmemDesc dmem_desc_;
};

} // namespace details
