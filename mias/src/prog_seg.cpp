#include "prog_seg.hpp"
#include "defs.hpp"
#include "spdlog/spdlog.h"
#include "utils.hpp"
#include <algorithm>
#include <iostream>
#include <magic_enum.hpp>
#include <string>
#include <string_view>
#include <variant>

namespace mias {

uint32_t to_binary(InstrDesc desc) {
  desc.opcode &= 0b111111;
  desc.rs &= 0b11111;
  desc.rt &= 0b11111;
  desc.rd &= 0b11111;
  desc.immediate &= 0xFFFF;
  desc.shamt &= 0b11111;
  desc.func &= 0b111111;

  switch (desc.type) {
  case Instr::kAdd:
  case Instr::kAddu:
  case Instr::kSub:
  case Instr::kSubu:
  case Instr::kAnd:
  case Instr::kOr:
  case Instr::kXor:
  case Instr::kNor:
  case Instr::kSlt:
  case Instr::kSltu:
  case Instr::kSllv:
  case Instr::kSrlv:
  case Instr::kSrav:
    return (desc.opcode << 26) | (desc.rs << 21) | (desc.rt << 16) |
           (desc.rd << 11) | (desc.shamt << 6) | desc.func;

  case Instr::kAddi:
  case Instr::kAddiu:
  case Instr::kAndi:
  case Instr::kOri:
  case Instr::kXori:
  case Instr::kSlti:
  case Instr::kSltiu:
    return desc.opcode << 26 | desc.rs << 21 | desc.rt << 16 | desc.immediate;
  case Instr::kMult:
  case Instr::kMultu:
  case Instr::kDiv:
  case Instr::kDivu:
  case Instr::kMfc0:
  case Instr::kMtc0:
  case Instr::kJalr:
    return (desc.opcode << 26) | (desc.rs << 21) | (desc.rt << 16) |
           (desc.rd << 11) | (desc.shamt << 6) | desc.func;
  case Instr::kBgez:
  case Instr::kBgtz:
  case Instr::kBlez:
  case Instr::kBltz:
  case Instr::kBgezal:
  case Instr::kBltzal:
    return (desc.opcode << 26) | (desc.rs << 21) | (desc.rt << 16) |
           desc.immediate;

  case Instr::kLb:
  case Instr::kLbu:
  case Instr::kLh:
  case Instr::kLhu:
  case Instr::kSb:
  case Instr::kSh:
  case Instr::kLw:
  case Instr::kSw:
  case Instr::kBne:
  case Instr::kBeq:
    return (desc.opcode << 26) | (desc.rs << 21) | (desc.rt << 16) |
           desc.immediate;

  case Instr::kJ:
  case Instr::kJal:
    return (desc.opcode << 26) | desc.address;

  case Instr::kSyscall:
  case Instr::kEret:
    return (desc.opcode << 26) | (desc.code << 6) | desc.func;
  case Instr::kLui:
    return (desc.opcode << 26) | (desc.rt << 16) | desc.immediate;

  case Instr::kSll:
  case Instr::kSrl:
  case Instr::kSra:
  case Instr::kMfhi:
  case Instr::kMflo:
  case Instr::kMthi:
  case Instr::kMtlo:
  case Instr::kJr:
  case Instr::kJl:
  case Instr::kJle:
  case Instr::kJg:
  case Instr::kJge:
  case Instr::kNop:
    return (desc.opcode << 26) | (desc.rs << 21) | (desc.rt << 16) |
           (desc.rd << 11) | (desc.shamt << 6) | desc.func;

  case Instr::kBreak:
    return (desc.opcode << 26) | (desc.code << 6) | desc.func;
  default:
    spdlog::error("Not Implemented Error");
    throw std::runtime_error("Not Implemented Error");
  };
}

uint32_t interprete_immediate(std::string imm) { return mias::atoi(imm); }

uint32_t interprete_register(std::string str) {
  // TODO:
  // $0 -> 0
  // $s0 -> ?
  // support $num for now.
  auto beg = find_first_nws(str);
  auto end = find_first_ws(str, beg);

  auto real = str.substr(beg, end - beg);
  uint32_t retval = 0;
  if (real[0] != '$') {
    spdlog::error("Expect '$' for register. got {}", real);
    throw std::runtime_error("Interprete Register Error");
  } else {
    if (real == "$zero") {
      return 0;
    } else if (real == "$at") {
      return 1;
    } else if (real == "$v0") {
      return 2;
    } else if (real == "$v1") {
      return 3;
    } else if (real == "$k0") {
      return 26;
    } else if (real == "$k1") {
      return 27;
    } else if (real == "$gp") {
      return 28;
    } else if (real == "$sp") {
      return 29;
    } else if (real == "$fp") {
      return 30;
    } else if (real == "$ra") {
      return 31;
    } else if (std::isdigit(real[1])) {
      retval = mias::atoi(real.substr(1));
    } else if (real[1] =='a') {
      return real[2] - '0' + 4;
    } else if (real[1] == 't') {
      auto id = real[2] - '0';
      if (id < 8) {
        return id + 8;
      } else {
        return id + 16;
      }
    } else if (real[1] == 's') {
      spdlog::warn("Got {}, return {}", real, real[2] != '8' ? (real[2] - '0' + 16) : 30);
      return real[2] != '8' ? (real[2] - '0' + 16) : 30;
    } else {
      spdlog::info("Except Register Name, got {}", real);
      throw std::runtime_error("Prog Seg Error");
    }
  }
  return retval;
}

std::variant<std::string, uint32_t> interprete_offset(std::string off) {
  if (std::isdigit(off.front()) || off.front() == '-') {
    return mias::atoi(off);
  } else if (std::isalpha(off.front())) {
    return off;
  } else {
    spdlog::error("Expect: alpha or digit, got {}", off);
    throw std::runtime_error("Interprete Offset Error.");
  }
  return {(uint32_t)0};
}

std::pair<std::variant<std::string, uint32_t>, uint32_t>
interprete_register_with_offset(std::string str) {
  auto lbrace = str.find('(');
  auto rbrace = str.find(')');
  if (lbrace >= rbrace) {
    spdlog::error("Expect '('");
    throw std::runtime_error("Data Segment Error");
  } else if (rbrace == str.length()) {
    spdlog::error("Expect: ')'");
    throw std::runtime_error("Data Segment Error");
  }
  auto off = str.substr(0, lbrace);
  auto reg = str.substr(lbrace + 1, rbrace - lbrace - 1);
  return std::make_pair(interprete_offset(off), interprete_register(reg));
}

InstrDesc from_string(std::string str) {
  auto space = find_first_ws(str);
  auto instr_name = strtolower(str.substr(0, space));
  auto remaining = str.substr(space);
  std::string output;
  std::copy_if(remaining.begin(), remaining.end(), std::back_inserter(output),
               [](char x) { return !std::isspace(x); });
  std::swap(output, remaining);

  spdlog::info("[P] Got Instr: {}, Full Instr = {}", instr_name, str);
  // TODO: Impl for each instruction! Parse the instr string here.
  // You can suppose the instr has:
  // 1. no spaces before the instr
  // 2. no comment after the instr.
  if (instr_name == "add") {
    auto params = split(remaining, ',');
    auto rd = interprete_register(params[0]);
    auto rs = interprete_register(params[1]);
    auto rt = interprete_register(params[2]);
    return InstrDesc::Add(rs, rt, rd);
  } else if (instr_name == "addu") {
    auto params = split(remaining, ',');
    auto rd = interprete_register(params[0]);
    auto rs = interprete_register(params[1]);
    auto rt = interprete_register(params[2]);
    return InstrDesc::Addu(rs, rt, rd);
  } else if (instr_name == "sub") {
    auto params = split(remaining, ',');
    auto rd = interprete_register(params[0]);
    auto rs = interprete_register(params[1]);
    auto rt = interprete_register(params[2]);
    return InstrDesc::Sub(rs, rt, rd);
  } else if (instr_name == "subu") {
    auto params = split(remaining, ',');
    auto rd = interprete_register(params[0]);
    auto rs = interprete_register(params[1]);
    auto rt = interprete_register(params[2]);
    return InstrDesc::Subu(rs, rt, rd);
  } else if (instr_name == "and") {
    auto params = split(remaining, ',');
    auto rd = interprete_register(params[0]);
    auto rs = interprete_register(params[1]);
    auto rt = interprete_register(params[2]);
    return InstrDesc::And(rs, rt, rd);
  } else if (instr_name == "or") {
    auto params = split(remaining, ',');
    auto rd = interprete_register(params[0]);
    auto rs = interprete_register(params[1]);
    auto rt = interprete_register(params[2]);
    return InstrDesc::Or(rs, rt, rd);
  } else if (instr_name == "xor") {
    auto params = split(remaining, ',');
    auto rd = interprete_register(params[0]);
    auto rs = interprete_register(params[1]);
    auto rt = interprete_register(params[2]);
    return InstrDesc::Xor(rs, rt, rd);
  } else if (instr_name == "nor") {
    auto params = split(remaining, ',');
    auto rd = interprete_register(params[0]);
    auto rs = interprete_register(params[1]);
    auto rt = interprete_register(params[2]);
    return InstrDesc::Nor(rs, rt, rd);
  } else if (instr_name == "slt") {
    auto params = split(remaining, ',');
    auto rd = interprete_register(params[0]);
    auto rs = interprete_register(params[1]);
    auto rt = interprete_register(params[2]);
    return InstrDesc::Slt(rs, rt, rd);
  } else if (instr_name == "sltu") {
    auto params = split(remaining, ',');
    auto rd = interprete_register(params[0]);
    auto rs = interprete_register(params[1]);
    auto rt = interprete_register(params[2]);
    return InstrDesc::Sltu(rs, rt, rd);
  } else if (instr_name == "sllv") {
    auto params = split(remaining, ',');
    auto rd = interprete_register(params[0]);
    auto rs = interprete_register(params[2]);
    auto rt = interprete_register(params[1]);
    return InstrDesc::Sllv(rs, rt, rd);
  } else if (instr_name == "srlv") {
    auto params = split(remaining, ',');
    auto rd = interprete_register(params[0]);
    auto rs = interprete_register(params[2]);
    auto rt = interprete_register(params[1]);
    return InstrDesc::Srlv(rs, rt, rd);
  } else if (instr_name == "srav") {
    auto params = split(remaining, ',');
    auto rd = interprete_register(params[0]);
    auto rs = interprete_register(params[2]);
    auto rt = interprete_register(params[1]);
    return InstrDesc::Srav(rs, rt, rd);
  } else if (instr_name == "mult") {
    auto params = split(remaining, ',');
    auto rs = interprete_register(params[0]);
    auto rt = interprete_register(params[1]);
    return InstrDesc::Mult(rs, rt);
  } else if (instr_name == "multu") {
    auto params = split(remaining, ',');
    auto rs = interprete_register(params[0]);
    auto rt = interprete_register(params[1]);
    return InstrDesc::Multu(rs, rt);
  } else if (instr_name == "div") {
    auto params = split(remaining, ',');
    auto rs = interprete_register(params[0]);
    auto rt = interprete_register(params[1]);
    return InstrDesc::Div(rs, rt);
  } else if (instr_name == "divu") {
    auto params = split(remaining, ',');
    auto rs = interprete_register(params[0]);
    auto rt = interprete_register(params[1]);
    return InstrDesc::Divu(rs, rt);
  } else if (instr_name == "mfhi") {
    auto rd = interprete_register(remaining);
    return InstrDesc::Mfhi(rd);
  } else if (instr_name == "mflo") {
    auto rd = interprete_register(remaining);
    return InstrDesc::Mflo(rd);
  } else if (instr_name == "mthi") {
    auto rs = interprete_register(remaining);
    return InstrDesc::Mthi(rs);
  } else if (instr_name == "mtlo") {
    auto rs = interprete_register(remaining);
    return InstrDesc::Mtlo(rs);
  } else if (instr_name == "mfc0") {
    auto params = split(remaining, ',');
    auto rs = interprete_register(params[0]);
    auto rt = interprete_register(params[1]);
    auto sel = interprete_immediate(params[2]);
    return InstrDesc::Mfc0(rs, rt, sel);
  } else if (instr_name == "mtc0") {
    auto params = split(remaining, ',');
    auto rs = interprete_register(params[0]);
    auto rt = interprete_register(params[1]);
    auto sel = interprete_immediate(params[2]);
    return InstrDesc::Mtc0(rs, rt, sel);
  } else if (instr_name == "srl") {
    auto params = split(remaining, ',');
    auto rd = interprete_register(params[0]);
    auto rt = interprete_register(params[1]);
    auto shamt = interprete_immediate(params[2]);
    return InstrDesc::Srl(rt, rd, shamt);
  } else if (instr_name == "sll") {
    auto params = split(remaining, ',');
    auto rd = interprete_register(params[0]);
    auto rt = interprete_register(params[1]);
    auto shamt = interprete_immediate(params[2]);
    return InstrDesc::Sll(rt, rd, shamt);
  } else if (instr_name == "sra") {
    auto params = split(remaining, ',');
    auto rd = interprete_register(params[0]);
    auto rt = interprete_register(params[1]);
    auto shamt = interprete_immediate(params[2]);
    return InstrDesc::Sra(rt, rd, shamt);
  } else if (instr_name == "jr") {
    auto rs = interprete_register(remaining);
    return InstrDesc::Jr(rs);
  } else if (instr_name == "jalr") {
    auto params = split(remaining, ',');
    auto rd = interprete_register(params[0]);
    auto rs = interprete_register(params[1]);
    return InstrDesc::Jalr(rs, rd);
  } else if (instr_name == "break") {
    auto code = interprete_immediate(remaining);
    return InstrDesc::Break(code);
  } else if (instr_name == "syscall") {
    auto code = interprete_immediate(remaining);
    return InstrDesc::Syscall(code);
  } else if (instr_name == "eret") {
    return InstrDesc::Eret();
  } else if (instr_name == "addi") {
    auto param = split(remaining, ',');
    auto rt = interprete_register(param[0]);
    auto rs = interprete_register(param[1]);
    auto imm = interprete_immediate(param[2]);
    return InstrDesc::Addi(rs, rt, imm);
  } else if (instr_name == "addiu") {
    auto param = split(remaining, ',');
    auto rt = interprete_register(param[0]);
    auto rs = interprete_register(param[1]);
    auto imm = interprete_immediate(param[2]);
    return InstrDesc::Addiu(rs, rt, imm);
  } else if (instr_name == "andi") {
    auto param = split(remaining, ',');
    auto rt = interprete_register(param[0]);
    auto rs = interprete_register(param[1]);
    auto imm = interprete_immediate(param[2]);
    return InstrDesc::Andi(rs, rt, imm);
  } else if (instr_name == "ori") {
    auto param = split(remaining, ',');
    auto rt = interprete_register(param[0]);
    auto rs = interprete_register(param[1]);
    auto imm = interprete_immediate(param[2]);
    return InstrDesc::Ori(rs, rt, imm);
  } else if (instr_name == "xori") {
    auto param = split(remaining, ',');
    auto rt = interprete_register(param[0]);
    auto rs = interprete_register(param[1]);
    auto imm = interprete_immediate(param[2]);
    return InstrDesc::Xori(rs, rt, imm);
  } else if (instr_name == "lui") {
    auto param = split(remaining, ',');
    auto rt = interprete_register(param[0]);
    auto imm = interprete_immediate(param[1]);
    return InstrDesc::Lui(0, rt, imm);
  } else if (instr_name == "lb") {
    auto param = split(remaining, ',');
    auto rt = interprete_register(param[0]);
    auto [off, rs] = interprete_register_with_offset(param[1]);
    auto idesc = InstrDesc::Lb(rs, rt, 0);
    if (std::holds_alternative<uint32_t>(off)) {
      idesc.immediate = std::get<uint32_t>(off);
    } else {
      idesc.flag = std::get<std::string>(off);
    }
    return idesc;
  } else if (instr_name == "lbu") {
    auto param = split(remaining, ',');
    auto rt = interprete_register(param[0]);
    auto [off, rs] = interprete_register_with_offset(param[1]);
    auto idesc = InstrDesc::Lbu(rs, rt, 0);
    if (std::holds_alternative<uint32_t>(off)) {
      idesc.immediate = std::get<uint32_t>(off);
    } else {
      idesc.flag = std::get<std::string>(off);
    }
    return idesc;
  } else if (instr_name == "lh") {
    auto param = split(remaining, ',');
    auto rt = interprete_register(param[0]);
    auto [off, rs] = interprete_register_with_offset(param[1]);
    auto idesc = InstrDesc::Lh(rs, rt, 0);
    if (std::holds_alternative<uint32_t>(off)) {
      idesc.immediate = std::get<uint32_t>(off);
    } else {
      idesc.flag = std::get<std::string>(off);
    }
    return idesc;
  } else if (instr_name == "lhu") {
    auto param = split(remaining, ',');
    auto rt = interprete_register(param[0]);
    auto [off, rs] = interprete_register_with_offset(param[1]);
    auto idesc = InstrDesc::Lhu(rs, rt, 0);
    if (std::holds_alternative<uint32_t>(off)) {
      idesc.immediate = std::get<uint32_t>(off);
    } else {
      idesc.flag = std::get<std::string>(off);
    }
    return idesc;
  } else if (instr_name == "sb") {
    auto param = split(remaining, ',');
    auto rt = interprete_register(param[0]);
    auto [off, rs] = interprete_register_with_offset(param[1]);
    auto idesc = InstrDesc::Sb(rs, rt, 0);
    if (std::holds_alternative<uint32_t>(off)) {
      idesc.immediate = std::get<uint32_t>(off);
    } else {
      idesc.flag = std::get<std::string>(off);
    }
    return idesc;
  } else if (instr_name == "sh") {
    auto param = split(remaining, ',');
    auto rt = interprete_register(param[0]);
    auto [off, rs] = interprete_register_with_offset(param[1]);
    auto idesc = InstrDesc::Sh(rs, rt, 0);
    if (std::holds_alternative<uint32_t>(off)) {
      idesc.immediate = std::get<uint32_t>(off);
    } else {
      idesc.flag = std::get<std::string>(off);
    }
    return idesc;
  } else if (instr_name == "lw") {
    auto param = split(remaining, ',');
    auto rt = interprete_register(param[0]);
    auto [off, rs] = interprete_register_with_offset(param[1]);
    auto idesc = InstrDesc::Lw(rs, rt, 0);
    if (std::holds_alternative<uint32_t>(off)) {
      idesc.immediate = std::get<uint32_t>(off);
    } else {
      idesc.flag = std::get<std::string>(off);
    }
    return idesc;
  } else if (instr_name == "sw") {
    auto param = split(remaining, ',');
    auto rt = interprete_register(param[0]);
    auto [off, rs] = interprete_register_with_offset(param[1]);
    auto idesc = InstrDesc::Sw(rs, rt, 0);
    if (std::holds_alternative<uint32_t>(off)) {
      idesc.immediate = std::get<uint32_t>(off);
    } else {
      idesc.flag = std::get<std::string>(off);
    }
    return idesc;
  } else if (instr_name == "beq") {
    auto param = split(remaining, ',');
    auto rt = interprete_register(param[1]);
    auto rs = interprete_register(param[0]);
    auto off = interprete_offset(param[2]);
    auto idesc = InstrDesc::Beq(rs, rt, 0);
    if (std::holds_alternative<uint32_t>(off)) {
      idesc.immediate = std::get<uint32_t>(off);
    } else {
      idesc.flag = std::get<std::string>(off);
    }
    return idesc;
  } else if (instr_name == "bne") {
    auto param = split(remaining, ',');
    auto rt = interprete_register(param[1]);
    auto rs = interprete_register(param[0]);
    auto off = interprete_offset(param[2]);
    auto idesc = InstrDesc::Bne(rs, rt, 0);
    if (std::holds_alternative<uint32_t>(off)) {
      idesc.immediate = std::get<uint32_t>(off);
    } else {
      idesc.flag = std::get<std::string>(off);
    }
    return idesc;
  } else if (instr_name == "bgez") {
    auto param = split(remaining, ',');
    auto rs = interprete_register(param[0]);
    auto off = interprete_offset(param[1]);
    auto idesc = InstrDesc::Bgez(rs, 1, 0);
    if (std::holds_alternative<uint32_t>(off)) {
      idesc.immediate = std::get<uint32_t>(off);
    } else {
      idesc.flag = std::get<std::string>(off);
    }
    return idesc;
  } else if (instr_name == "bgtz") {
    auto param = split(remaining, ',');
    auto rs = interprete_register(param[0]);
    auto off = interprete_offset(param[1]);
    auto idesc = InstrDesc::Bgtz(rs, 0, 0);
    if (std::holds_alternative<uint32_t>(off)) {
      idesc.immediate = std::get<uint32_t>(off);
    } else {
      idesc.flag = std::get<std::string>(off);
    }
    return idesc;
  } else if (instr_name == "blez") {
    auto param = split(remaining, ',');
    auto rs = interprete_register(param[0]);
    auto off = interprete_offset(param[1]);
    auto idesc = InstrDesc::Blez(rs, 0, 0);
    if (std::holds_alternative<uint32_t>(off)) {
      idesc.immediate = std::get<uint32_t>(off);
    } else {
      idesc.flag = std::get<std::string>(off);
    }
    return idesc;
  } else if (instr_name == "bltz") {
    auto param = split(remaining, ',');
    auto rs = interprete_register(param[0]);
    auto off = interprete_offset(param[1]);
    auto idesc = InstrDesc::Bltz(rs, 0, 0);
    if (std::holds_alternative<uint32_t>(off)) {
      idesc.immediate = std::get<uint32_t>(off);
    } else {
      idesc.flag = std::get<std::string>(off);
    }
    return idesc;
  } else if (instr_name == "bgezal") {
    auto param = split(remaining, ',');
    auto rs = interprete_register(param[0]);
    auto off = interprete_offset(param[1]);
    auto idesc = InstrDesc::Bgezal(rs, 0b10001, 0);
    if (std::holds_alternative<uint32_t>(off)) {
      idesc.immediate = std::get<uint32_t>(off);
    } else {
      idesc.flag = std::get<std::string>(off);
    }
    return idesc;
  } else if (instr_name == "bltzal") {
    auto param = split(remaining, ',');
    auto rs = interprete_register(param[0]);
    auto off = interprete_offset(param[1]);
    auto idesc = InstrDesc::Bltzal(rs, 0b10000, 0);
    if (std::holds_alternative<uint32_t>(off)) {
      idesc.immediate = std::get<uint32_t>(off);
    } else {
      idesc.flag = std::get<std::string>(off);
    }
    return idesc;
  } else if (instr_name == "slti") {
    auto param = split(remaining, ',');
    auto rt = interprete_register(param[0]);
    auto rs = interprete_register(param[1]);
    auto imm = interprete_immediate(param[2]);
    return InstrDesc::Slti(rs, rt, imm);
  } else if (instr_name == "sltiu") {
    auto param = split(remaining, ',');
    auto rt = interprete_register(param[0]);
    auto imm = interprete_immediate(param[2]);
    auto rs = interprete_register(param[1]);
    return InstrDesc::Sltiu(rs, rt, imm);
  } else if (instr_name == "j") {
    auto imm = interprete_offset(remaining);
    auto instr = InstrDesc::J(0);
    if (std::holds_alternative<uint32_t>(imm)) {
      instr.address = std::get<uint32_t>(imm);
    } else {
      instr.flag = std::get<std::string>(imm);
    }
    return instr;
  } else if (instr_name == "jal") {
    auto imm = interprete_offset(remaining);
    auto instr = InstrDesc::Jal(0);
    if (std::holds_alternative<uint32_t>(imm)) {
      instr.address = std::get<uint32_t>(imm);
    } else {
      instr.flag = std::get<std::string>(imm);
    }
    return instr;
  } else if (instr_name == "nop") {
    return InstrDesc::Nop();
  }
  spdlog::error("Not Implemented Error.");
  throw std::runtime_error("Not Implemented Error");
}

enum class InstrAccessType { kNone, kGoto, kDmem };

static InstrAccessType get_iat(InstrDesc desc) {
  switch (desc.type) {
  case Instr::kLb:
  case Instr::kLbu:
  case Instr::kLh:
  case Instr::kLhu:
  case Instr::kSb:
  case Instr::kSh:
  case Instr::kLw:
  case Instr::kSw:
    return InstrAccessType::kDmem;
  case Instr::kBne:
  case Instr::kBeq:
  case Instr::kBgez:
  case Instr::kBgtz:
  case Instr::kBlez:
  case Instr::kBltz:
  case Instr::kBgezal:
  case Instr::kBltzal:
  case Instr::kJ:
  case Instr::kJal:
    return InstrAccessType::kGoto;
  default:
    return InstrAccessType::kNone;
  }
}

void ProgSegParser::Parse(const std::vector<std::string> &clean_input) {
  input_str_ = clean_input;
  MarkAllFlags();
  GenerateBinary();
}

void ProgSegParser::SetDmemDesc(const DmemDesc &desc) { dmem_desc_ = desc; }

void ProgSegParser::MarkAllFlags() {
  for (const auto &instr : input_str_) {
    if (instr.find(':') != std::string::npos) {
      // instr is flag
      auto pos = instr.find(':');
      auto flag = instr.substr(0, pos);
      AddFlag(flag);
    } else {
      instr_str_.push_back(instr);
      spdlog::debug("[P] Add Instr: {}", instr);
    }
  }
}

void ProgSegParser::AddFlag(std::string name) {
  if (flags_.find(name) == flags_.end()) {
    spdlog::debug("[P] Add Flag {}, global offset = {:#010x}", name,
                  instr_str_.size());
    flags_.emplace(name, instr_str_.size());
  } else {
    spdlog::error("Prog Seg: Flags redefinition. {}", name);
    throw std::runtime_error("Prog Seg Error");
  }
}

void ProgSegParser::GenerateBinary() {
  for (auto instr : instr_str_) {
    auto idesc = from_string(instr);
    uint32_t binary = 0;
    auto iat = get_iat(idesc);
    if (iat == InstrAccessType::kDmem) {
      // Accessing Data Memory
      if (idesc.flag) {
        // has flag, -> find in dmem
        if (auto it = dmem_desc_.variables.find(idesc.flag.value());
            it != dmem_desc_.variables.end()) {
          // found.
          spdlog::info("[P] Found dmem flag: {} : {}", it->first, it->second);
          idesc.immediate = static_cast<uint32_t>(it->second);
        } else {
          spdlog::error("Prog Seg: Unknown Flag {}", idesc.flag.value());
          throw std::runtime_error("Prog Seg Error");
        }
      }
    } else if (iat == InstrAccessType::kGoto) {
      // Accessing Program Counter
      uint32_t offset;
      if (idesc.flag) {
        if (auto it = flags_.find(idesc.flag.value()); it != flags_.end()) {
          offset = it->second;
          spdlog::info(
              "[P] Found flag {}, global index = {:#010x}, offset = {:#010x}",
              it->first, it->second, offset);
        } else {
          spdlog::error("Prog Seg: Flag {} not defined.", idesc.flag.value());
          throw std::runtime_error("Prog Seg Error");
        }
        if (idesc.type == Instr::kJ || idesc.type == Instr::kJal) {
          idesc.address = offset;
        } else {
          idesc.immediate =
              offset - static_cast<uint32_t>(instr_binary_.size()) - 1;
        }
      }
    }
    binary = to_binary(idesc);
    spdlog::info("Instr: {}, type = {}, bc = {:#010x}", instr,
                 magic_enum::enum_name(idesc.type), binary);
    instr_binary_.push_back(binary);
  }
}

PmemDesc ProgSegParser::Describe() {
  PmemDesc desc;
  desc.flags = flags_;
  desc.binary_instrs = instr_binary_;
  return desc;
}

} // namespace mias
