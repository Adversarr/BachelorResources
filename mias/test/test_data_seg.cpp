#include <data_seg.hpp>
#include <doctest/doctest.h>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

TEST_CASE("dataseg_01") {
  std::vector<std::string> asm_content = {
      ".align  \t 8",      
      "buf:",
      ".word 2:3",
      "buf2:",
      ".byte  3,8,87, 21",
      ".word 0x34a,15",
      ".ascii \"123\"",
      ".asciiz \"123\", \"234\"",
      ".space 3"};
  try {
    mias::DataSegParser parser;
    parser.Parse(asm_content);
    std::cerr << "Dmem Vector = " << std::endl;
    int i = 0;
    std::cerr << std::setfill('0') << std::hex;
    for (auto u8 : parser.GetDmem()) {
      if ((i & 0x3) == 0) {
        std::cerr << "0x" << std::setw(8) << 
          std::hex << i << ":";
      }
      std::cerr << std::setw(2) << (int)u8;
      i += 1;
      if ((i & 0x3) == 0) {
        std::cerr << std::endl;
      }
    }
    std::cerr << std::endl;
  } catch (std::runtime_error &rte) {
    CHECK(false);
  }
}
