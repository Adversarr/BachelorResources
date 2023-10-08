#pragma once
#include <cstdint>
#include <optional>
#include <string>

namespace mias {

enum class Instr {
  kAdd,
  kAddu,
  kSub,
  kSubu,
  kAnd,
  kOr,
  kXor,
  kNor,
  kSlt,
  kSltu,
  kSllv,
  kSrlv,
  kSrav,

  kAddi,
  kAddiu,
  kAndi,
  kOri,
  kXori,
  kSlti,
  kSltiu,

  kMult,
  kMultu,
  kDiv,
  kDivu,
  kMfc0,
  kMtc0,
  kJalr,

  kBgez,
  kBgtz,
  kBlez,
  kBltz,
  kBgezal,
  kBltzal,

  kLb,
  kLbu,
  kLh,
  kLhu,
  kSb,
  kSh,
  kLw,
  kSw,

  kJ,
  kJal,

  kSyscall,

  kSll,
  kSrl,
  kSra,
  kBne,
  kBeq,
  kLui,
  kMfhi,
  kMflo,
  kMthi,
  kMtlo,
  kJr,
  kBreak,
  kEret,
  kJl,
  kJle,
  kJg,
  kJge,
  kNop
};

struct InstrDesc {
  Instr type;
  uint32_t opcode;
  // Rtype
  uint32_t rs, rt, rd;
  uint32_t shamt;
  uint32_t func;
  uint32_t code;

  // Itype
  uint32_t immediate;

  // Jtype
  uint32_t address;

  // optional, flag.
  std::optional<std::string> flag;

  InstrDesc()
      : type(Instr::kNop), opcode(0), rs(0), rt(0), rd(0), shamt(0), func(0),
        code(0), immediate(0), address(0), flag(std::nullopt) {}

  static InstrDesc Add(uint32_t rs, uint32_t rt, uint32_t rd);
  static InstrDesc Addu(uint32_t rs, uint32_t rt, uint32_t rd);
  static InstrDesc Sub(uint32_t rs, uint32_t rt, uint32_t rd);
  static InstrDesc Subu(uint32_t rs, uint32_t rt, uint32_t rd);
  static InstrDesc And(uint32_t rs, uint32_t rt, uint32_t rd);
  static InstrDesc Mult(uint32_t rs, uint32_t rt);
  static InstrDesc Multu(uint32_t rs, uint32_t rt);
  static InstrDesc Div(uint32_t rs, uint32_t rt);
  static InstrDesc Divu(uint32_t rs, uint32_t rt);
  static InstrDesc Mfhi(uint32_t rd);
  static InstrDesc Mflo(uint32_t rd);
  static InstrDesc Mthi(uint32_t rs);
  static InstrDesc Mtlo(uint32_t rs);
  static InstrDesc Mfc0(uint32_t rt, uint32_t rd, uint32_t sel);
  static InstrDesc Mtc0(uint32_t rt, uint32_t rd, uint32_t sel);
  static InstrDesc Or(uint32_t rs, uint32_t rt, uint32_t rd);
  static InstrDesc Xor(uint32_t rs, uint32_t rt, uint32_t rd);
  static InstrDesc Nor(uint32_t rs, uint32_t rt, uint32_t rd);
  static InstrDesc Slt(uint32_t rs, uint32_t rt, uint32_t rd);
  static InstrDesc Sltu(uint32_t rs, uint32_t rt, uint32_t rd);
  static InstrDesc Sll(uint32_t rt, uint32_t rd, uint32_t shamt);
  static InstrDesc Srl(uint32_t rt, uint32_t rd, uint32_t shamt);
  static InstrDesc Sra(uint32_t rt, uint32_t rd, uint32_t shamt);
  static InstrDesc Sllv(uint32_t rs, uint32_t rt, uint32_t rd);
  static InstrDesc Srlv(uint32_t rs, uint32_t rt, uint32_t rd);
  static InstrDesc Srav(uint32_t rs, uint32_t rt, uint32_t rd);
  static InstrDesc Jr(uint32_t rs);
  static InstrDesc Jalr(uint32_t rs, uint32_t rd);
  static InstrDesc Break(uint32_t code);
  static InstrDesc Syscall(uint32_t code);
  static InstrDesc Eret();

  static InstrDesc Addi(uint32_t rs, uint32_t rt, uint32_t imm);
  static InstrDesc Addiu(uint32_t rs, uint32_t rt, uint32_t imm);
  static InstrDesc Andi(uint32_t rs, uint32_t rt, uint32_t imm);
  static InstrDesc Ori(uint32_t rs, uint32_t rt, uint32_t imm);
  static InstrDesc Xori(uint32_t rs, uint32_t rt, uint32_t imm);
  static InstrDesc Lui(uint32_t rs, uint32_t rt, uint32_t imm);

  static InstrDesc Lb(uint32_t rs, uint32_t rt, uint32_t offset);
  static InstrDesc Lbu(uint32_t rs, uint32_t rt, uint32_t offset);
  static InstrDesc Lh(uint32_t rs, uint32_t rt, uint32_t offset);
  static InstrDesc Lhu(uint32_t rs, uint32_t rt, uint32_t offset);
  static InstrDesc Sb(uint32_t rs, uint32_t rt, uint32_t offset);
  static InstrDesc Sh(uint32_t rs, uint32_t rt, uint32_t offset);
  static InstrDesc Lw(uint32_t rs, uint32_t rt, uint32_t offset);
  static InstrDesc Sw(uint32_t rs, uint32_t rt, uint32_t offset);
  static InstrDesc Beq(uint32_t rs, uint32_t rt, uint32_t offset);
  static InstrDesc Bne(uint32_t rs, uint32_t rt, uint32_t offset);
  static InstrDesc Bgez(uint32_t rs, uint32_t rt, uint32_t offset);
  static InstrDesc Bgtz(uint32_t rs, uint32_t rt, uint32_t offset);
  static InstrDesc Blez(uint32_t rs, uint32_t rt, uint32_t offset);
  static InstrDesc Bltz(uint32_t rs, uint32_t rt, uint32_t offset);
  static InstrDesc Bgezal(uint32_t rs, uint32_t rt, uint32_t offset);
  static InstrDesc Bltzal(uint32_t rs, uint32_t rt, uint32_t offset);

  static InstrDesc Slti(uint32_t rs, uint32_t rt, uint32_t imm);
  static InstrDesc Sltiu(uint32_t rs, uint32_t rt, uint32_t imm);
  static InstrDesc J(uint32_t addr);
  static InstrDesc Jal(uint32_t addr);
  static InstrDesc Nop();
};


} // namespace mias
