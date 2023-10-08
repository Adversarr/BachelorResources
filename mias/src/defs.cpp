#include "defs.hpp"
#include <spdlog/spdlog.h>

namespace mias {

InstrDesc InstrDesc::Add(uint32_t rs, uint32_t rt, uint32_t rd) {
  InstrDesc desc;
  desc.opcode = 0b000000;
  desc.shamt = 0b00000;
  desc.func = 0b100000;
  desc.type = Instr::kAdd;
  desc.rs = rs;
  desc.rt = rt;
  desc.rd = rd;
  return desc;
}

InstrDesc InstrDesc::Addu(uint32_t rs, uint32_t rt, uint32_t rd) {
  InstrDesc desc;
  desc.type = Instr::kAddu;
  desc.opcode = 0b000000;
  desc.shamt = 0b00000;
  desc.func = 0b100001;
  desc.rs = rs;
  desc.rt = rt;
  desc.rd = rd;
  return desc;
}

InstrDesc InstrDesc::Sub(uint32_t rs, uint32_t rt, uint32_t rd) {
  InstrDesc desc;
  desc.type = Instr::kSub;
  desc.opcode = 0b000000;
  desc.shamt = 0b00000;
  desc.func = 0b100010;
  desc.rs = rs;
  desc.rt = rt;
  desc.rd = rd;
  return desc;
}

InstrDesc InstrDesc::Subu(uint32_t rs, uint32_t rt, uint32_t rd) {
  InstrDesc desc;
  desc.type = Instr::kSubu;
  desc.opcode = 0b000000;
  desc.shamt = 0b00000;
  desc.func = 0b100011;
  desc.rs = rs;
  desc.rt = rt;
  desc.rd = rd;
  return desc;
}

InstrDesc InstrDesc::And(uint32_t rs, uint32_t rt, uint32_t rd) {
  InstrDesc desc;
  desc.type = Instr::kAnd;
  desc.opcode = 0b000000;
  desc.shamt = 0b00000;
  desc.func = 0b100100;
  desc.rs = rs;
  desc.rt = rt;
  desc.rd = rd;
  return desc;
}

InstrDesc InstrDesc::Mult(uint32_t rs, uint32_t rt) {
  InstrDesc desc;
  desc.type = Instr::kMult;
  desc.opcode = 0b000000;
  desc.shamt = 0b00000;
  desc.func = 0b011000;
  desc.rd = 0;
  desc.rs = rs;
  desc.rt = rt;
  return desc;
}

InstrDesc InstrDesc::Multu(uint32_t rs, uint32_t rt) {
  InstrDesc desc;
  desc.type = Instr::kMultu;
  desc.opcode = 0b000000;
  desc.shamt = 0b00000;
  desc.func = 0b011001;
  desc.rd = 0;
  desc.rs = rs;
  desc.rt = rt;
  return desc;
}

InstrDesc InstrDesc::Div(uint32_t rs, uint32_t rt) {
  InstrDesc desc;
  desc.type = Instr::kDiv;
  desc.opcode = 0b000000;
  desc.shamt = 0b00000;
  desc.func = 0b011010;
  desc.rd = 0;
  desc.rs = rs;
  desc.rt = rt;
  return desc;
}

InstrDesc InstrDesc::Divu(uint32_t rs, uint32_t rt) {
  InstrDesc desc;
  desc.type = Instr::kDivu;
  desc.opcode = 0b000000;
  desc.shamt = 0b00000;
  desc.func = 0b011011;
  desc.rd = 0;
  desc.rs = rs;
  desc.rt = rt;
  return desc;
}

InstrDesc InstrDesc::Mfhi(uint32_t rd) {
  InstrDesc desc;
  desc.type = Instr::kMfhi;
  desc.opcode = 0b000000;
  desc.shamt = 0b00000;
  desc.func = 0b010000;
  desc.rd = 0;
  desc.rd = rd;
  return desc;
}

InstrDesc InstrDesc::Mflo(uint32_t rd) {
  InstrDesc desc;
  desc.type = Instr::kMflo;
  desc.opcode = 0b000000;
  desc.shamt = 0b00000;
  desc.func = 0b010010;
  desc.rd = 0;
  desc.rd = rd;
  return desc;
}

InstrDesc InstrDesc::Mthi(uint32_t rs) {
  InstrDesc desc;
  desc.type = Instr::kMthi;
  desc.opcode = 0b000000;
  desc.shamt = 0b00000;
  desc.func = 0b010001;
  desc.rs = rs;
  return desc;
}

InstrDesc InstrDesc::Mtlo(uint32_t rs) {
  InstrDesc desc;
  desc.type = Instr::kMtlo;
  desc.opcode = 0b000000;
  desc.shamt = 0b00000;
  desc.func = 0b010011;
  desc.rs = rs;
  return desc;
}

InstrDesc InstrDesc::Mfc0(uint32_t rt, uint32_t rd, uint32_t sel) {
  InstrDesc desc;
  desc.type = Instr::kMfc0;
  desc.opcode = 0b000000;
  desc.rs = 0b00100;
  desc.func = (0b111 & sel);
  desc.rt = rt;
  desc.rd = rd;
  return desc;
}

InstrDesc InstrDesc::Mtc0(uint32_t rt, uint32_t rd, uint32_t sel) {
  InstrDesc desc;
  desc.type = Instr::kMtc0;
  desc.opcode = 0b010000;
  desc.rs = 0b00100;
  desc.func = (0b111 & sel);
  desc.rt = rt;
  desc.rd = rd;
  return desc;
}

InstrDesc InstrDesc::Or(uint32_t rs, uint32_t rt, uint32_t rd) {
  InstrDesc desc;
  desc.type = Instr::kOr;
  desc.opcode = 0b000000;
  desc.func = 0b100101;
  desc.rs = rs;
  desc.rt = rt;
  desc.rd = rd;
  return desc;
}

InstrDesc InstrDesc::Xor(uint32_t rs, uint32_t rt, uint32_t rd) {
  InstrDesc desc;
  desc.type = Instr::kXor;
  desc.opcode = 0b000000;
  desc.func = 0b100110;
  desc.rs = rs;
  desc.rt = rt;
  desc.rd = rd;
  return desc;
}

InstrDesc InstrDesc::Nor(uint32_t rs, uint32_t rt, uint32_t rd) {
  InstrDesc desc;
  desc.type = Instr::kNor;
  desc.opcode = 0b000000;
  desc.func = 0b100111;
  desc.rs = rs;
  desc.rt = rt;
  desc.rd = rd;
  return desc;
}

InstrDesc InstrDesc::Slt(uint32_t rs, uint32_t rt, uint32_t rd) {
  InstrDesc desc;
  desc.type = Instr::kSlt;
  desc.func = 0b101010;
  desc.rs = rs;
  desc.rt = rt;
  desc.rd = rd;
  return desc;
}

InstrDesc InstrDesc::Sltu(uint32_t rs, uint32_t rt, uint32_t rd) {
  InstrDesc desc;
  desc.type = Instr::kSltu;
  desc.func = 0b101011;
  desc.rs = rs;
  desc.rt = rt;
  desc.rd = rd;
  return desc;
}

InstrDesc InstrDesc::Sll(uint32_t rt, uint32_t rd, uint32_t shamt) {
  InstrDesc desc;
  desc.type = Instr::kSll;
  desc.rs = 0;
  desc.func = 0; 
  desc.rt = rt;
  desc.rd = rd;
  desc.shamt = shamt;
  return desc;
}

InstrDesc InstrDesc::Srl(uint32_t rt, uint32_t rd, uint32_t shamt) {
  InstrDesc desc;
  desc.type = Instr::kSrl;
  desc.func = 0b000010;
  desc.rt = rt;
  desc.rd = rd;
  desc.shamt = shamt;
  return desc;
}

InstrDesc InstrDesc::Sra(uint32_t rt, uint32_t rd, uint32_t shamt) {
  InstrDesc desc;
  desc.type = Instr::kSra;
  desc.func = 0b000011;
  desc.rt = rt;
  desc.rd = rd;
  desc.shamt = shamt;
  return desc;
}

InstrDesc InstrDesc::Sllv(uint32_t rs, uint32_t rt, uint32_t rd) {
  InstrDesc desc;
  desc.type = Instr::kSllv;
  desc.func = 0b000100;
  desc.rt = rt;
  desc.rd = rd;
  desc.rs = rs;
  return desc;
}

InstrDesc InstrDesc::Srlv(uint32_t rs, uint32_t rt, uint32_t rd) {
  InstrDesc desc;
  desc.type = Instr::kSrlv;
  desc.func = 0b000110;
  desc.rt = rt;
  desc.rd = rd;
  desc.rs = rs;
  return desc;
}

InstrDesc InstrDesc::Srav(uint32_t rs, uint32_t rt, uint32_t rd) {
  InstrDesc desc;
  desc.type = Instr::kSrav;
  desc.func = 0b000111;
  desc.rt = rt;
  desc.rd = rd;
  desc.rs = rs;
  return desc;
}

InstrDesc InstrDesc::Jr(uint32_t rs) {
  InstrDesc desc;
  desc.type = Instr::kJr;
  desc.func = 0b001000;
  desc.rs = rs;
  return desc;
}

InstrDesc InstrDesc::Jalr(uint32_t rs, uint32_t rd) {
  InstrDesc desc;
  desc.type = Instr::kJalr;
  desc.func = 0b001001;
  desc.rd = rd;
  desc.rs = rs;
  return desc;
}

InstrDesc InstrDesc::Break(uint32_t code) {
  InstrDesc desc;
  desc.type = Instr::kBreak;
  desc.func = 001101;
  desc.code = code;
  return desc;
}

InstrDesc InstrDesc::Syscall(uint32_t code) {
  InstrDesc desc;
  desc.type = Instr::kSyscall;
  desc.code = code;
  desc.func = 0b001100;
  return desc;
}

InstrDesc InstrDesc::Eret() {
  InstrDesc desc;
  desc.type = Instr::kEret;
  desc.func = 0b011000;
  desc.code = 1 << 19;
  return desc;
}

InstrDesc InstrDesc::Addi(uint32_t rs, uint32_t rt, uint32_t imm) {
  InstrDesc desc;
  desc.type = Instr::kAddi;
  desc.opcode = 0b001000;
  desc.rt = rt;
  desc.rs = rs;
  desc.immediate = imm;
  return desc;
}

InstrDesc InstrDesc::Addiu(uint32_t rs, uint32_t rt, uint32_t imm) {
  InstrDesc desc;
  desc.type = Instr::kAddiu;
  desc.opcode = 0b001001;
  desc.rt = rt;
  desc.rs = rs;
  desc.immediate = imm;
  return desc;
}

InstrDesc InstrDesc::Andi(uint32_t rs, uint32_t rt, uint32_t imm) {
  InstrDesc desc;
  desc.opcode = 0b001100;
  desc.type = Instr::kAndi;
  desc.rt = rt;
  desc.rs = rs;
  desc.immediate = imm;
  return desc;
}

InstrDesc InstrDesc::Ori(uint32_t rs, uint32_t rt, uint32_t imm) {
  InstrDesc desc;
  desc.type = Instr::kOri;
  desc.opcode = 0b001101;
  desc.rt = rt;
  desc.rs = rs;
  desc.immediate = imm;
  return desc;
}

InstrDesc InstrDesc::Xori(uint32_t rs, uint32_t rt, uint32_t imm) {
  InstrDesc desc;
  desc.type = Instr::kXori;
  desc.opcode = 0b001110;
  desc.rt = rt;
  desc.rs = rs;
  desc.immediate = imm;
  return desc;
}

InstrDesc InstrDesc::Lui(uint32_t rs, uint32_t rt, uint32_t imm) {
  InstrDesc desc;
  desc.type = Instr::kLui;
  desc.opcode = 0b001111;
  desc.rt = rt;
  desc.rs = rs;
  desc.immediate = imm;
  return desc;
}

InstrDesc InstrDesc::Lb(uint32_t rs, uint32_t rt, uint32_t offset) {
  InstrDesc desc;
  desc.type = Instr::kLb;
  desc.opcode = 0b100000;
  desc.rt = rt;
  desc.rs = rs;
  desc.immediate = offset;
  return desc;
}

InstrDesc InstrDesc::Lbu(uint32_t rs, uint32_t rt, uint32_t offset) {
  InstrDesc desc;
  desc.type = Instr::kLbu;
  desc.opcode = 0b100100;
  desc.rt = rt;
  desc.rs = rs;
  desc.immediate = offset;
  return desc;
}

InstrDesc InstrDesc::Lh(uint32_t rs, uint32_t rt, uint32_t offset) {
  InstrDesc desc;
  desc.type = Instr::kLh;
  desc.opcode = 0b100101;
  desc.rt = rt;
  desc.rs = rs;
  desc.immediate = offset;
  return desc;
}

InstrDesc InstrDesc::Lhu(uint32_t rs, uint32_t rt, uint32_t offset) {
  InstrDesc desc;
  desc.type = Instr::kLhu;
  desc.opcode = 0b101000;
  desc.rt = rt;
  desc.rs = rs;
  desc.immediate = offset;
  return desc;
}

InstrDesc InstrDesc::Sb(uint32_t rs, uint32_t rt, uint32_t offset) {
  InstrDesc desc;
  desc.type = Instr::kSb;
  desc.opcode = 0b101000;
  desc.rt = rt;
  desc.rs = rs;
  desc.immediate = offset;
  return desc;
}

InstrDesc InstrDesc::Sh(uint32_t rs, uint32_t rt, uint32_t offset) {
  InstrDesc desc;
  desc.type = Instr::kSh;
  desc.opcode = 0b101001;
  desc.rt = rt;
  desc.rs = rs;
  desc.immediate = offset;
  return desc;
}

InstrDesc InstrDesc::Lw(uint32_t rs, uint32_t rt, uint32_t offset) {
  InstrDesc desc;
  desc.type = Instr::kLw;
  desc.opcode = 0b100011;
  desc.rt = rt;
  desc.rs = rs;
  desc.immediate = offset;
  return desc;
}

InstrDesc InstrDesc::Sw(uint32_t rs, uint32_t rt, uint32_t offset) {
  InstrDesc desc;
  desc.type = Instr::kSw;
  desc.opcode = 0b101011;
  desc.rt = rt;
  desc.rs = rs;
  desc.immediate = offset;
  return desc;
}

InstrDesc InstrDesc::Beq(uint32_t rs, uint32_t rt, uint32_t offset) {
  InstrDesc desc;
  desc.type = Instr::kBeq;
  desc.opcode = 0b000100;
  desc.rt = rt;
  desc.rs = rs;
  desc.immediate = offset;
  return desc;
}

InstrDesc InstrDesc::Bne(uint32_t rs, uint32_t rt, uint32_t offset) {
  InstrDesc desc;
  desc.type = Instr::kBne;
  desc.opcode = 0b000101;
  desc.rt = rt;
  desc.rs = rs;
  desc.immediate = offset;
  return desc;
}

InstrDesc InstrDesc::Bgtz(uint32_t rs, uint32_t rt, uint32_t offset){
  InstrDesc desc;
  desc.type = Instr::kBgtz;
  desc.opcode = 0b000111;
  desc.rs = rs;
  desc.rt = rt;
  desc.immediate = offset;
  return desc;
}
InstrDesc InstrDesc::Bgez(uint32_t rs, uint32_t rt, uint32_t offset) {
  InstrDesc desc;
  desc.type = Instr::kBgez;
  desc.opcode = 0b000001;
  desc.rt = rt;
  desc.rs = rs;
  desc.immediate = offset;
  return desc;
}

InstrDesc InstrDesc::Blez(uint32_t rs, uint32_t rt, uint32_t offset) {
  InstrDesc desc;
  desc.type = Instr::kBlez;
  desc.opcode = 0b000110;
  desc.rt = rt;
  desc.rs = rs;
  desc.immediate = offset;
  return desc;
}

InstrDesc InstrDesc::Bltz(uint32_t rs, uint32_t rt, uint32_t offset) {
  InstrDesc desc;
  desc.type = Instr::kBltz;
  desc.opcode = 0b000001;
  desc.rt = rt;
  desc.rs = rs;
  desc.immediate = offset;
  return desc;
}

InstrDesc InstrDesc::Bgezal(uint32_t rs, uint32_t rt, uint32_t offset) {
  InstrDesc desc;
  desc.type = Instr::kBgezal;
  desc.opcode = 0b000001;
  desc.rt = rt;
  desc.rs = rs;
  desc.immediate = offset;
  return desc;
}

InstrDesc InstrDesc::Bltzal(uint32_t rs, uint32_t rt, uint32_t offset) {
  InstrDesc desc;
  desc.type = Instr::kBltzal;
  desc.opcode = 0b000001;
  desc.rt = rt;
  desc.rs = rs;
  desc.immediate = offset;
  return desc;
}

InstrDesc InstrDesc::Slti(uint32_t rs, uint32_t rt, uint32_t imm) {
  InstrDesc desc;
  desc.opcode = 0b001010;
  desc.type = Instr::kSlti;
  desc.rt = rt;
  desc.rs = rs;
  desc.immediate = imm;
  return desc;
}

InstrDesc InstrDesc::Sltiu(uint32_t rs, uint32_t rt, uint32_t imm) {
  InstrDesc desc;
  desc.type = Instr::kSltiu;
  desc.opcode = 0b001011;
  desc.rt = rt;
  desc.rs = rs;
  desc.immediate = imm;
  return desc;
}

InstrDesc InstrDesc::J(uint32_t addr) {
  InstrDesc desc;
  desc.opcode = 0b000010;
  desc.type = Instr::kJ;
  desc.address = addr;
  return desc;
}

InstrDesc InstrDesc::Jal(uint32_t addr) {
  InstrDesc desc;
  desc.opcode = 0b000011;
  desc.type = Instr::kJal;
  desc.address = addr;
  return desc;
}

InstrDesc InstrDesc::Nop() {
  InstrDesc desc;
  return desc;
}

} // namespace mias
