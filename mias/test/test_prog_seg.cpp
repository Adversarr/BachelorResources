#include <doctest/doctest.h>
#include "prog_seg.hpp"
#include <spdlog/spdlog.h>
TEST_CASE("Prog Seg") {
  spdlog::set_level(spdlog::level::debug);
  mias::ProgSegParser parser;
  mias::DmemDesc dmem;
  dmem.variables.insert({"buf0", 0});
  parser.SetDmemDesc(dmem);
  std::vector<std::string> asm_in{
    "start:",
    "add $1, $2, $3",
    "end:",
    "bne $1, $2,  start",
    "lw $1, buf0($2)"
    // "jr $31"
  };


  parser.Parse(asm_in);
}
