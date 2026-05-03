#include "MCTargetDesc/RISC_VI_VIIMCTargetDesc.h"
#include "RISC_VI_VII.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCFixup.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCObjectFileInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/Endian.h"
#include "llvm/Support/EndianStream.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/TargetParser/SubtargetFeature.h"
#include <cassert>
#include <cstdint>

using namespace llvm;

#define DEBUG_TYPE "mccodeemitter"

STATISTIC(MCNumEmitted, "Number of MC instructions emitted");

namespace {

class RISC_VI_VIIMCCodeEmitter : public MCCodeEmitter {
  MCContext &Ctx;

public:
  RISC_VI_VIIMCCodeEmitter(const MCInstrInfo &, MCContext &ctx) : Ctx(ctx) {}
  RISC_VI_VIIMCCodeEmitter(const RISC_VI_VIIMCCodeEmitter &) = delete;
  RISC_VI_VIIMCCodeEmitter &operator=(const RISC_VI_VIIMCCodeEmitter &) = delete;
  ~RISC_VI_VIIMCCodeEmitter() override = default;

  void encodeInstruction(const MCInst &MI, SmallVectorImpl<char> &CB,
                         SmallVectorImpl<MCFixup> &Fixups,
                         const MCSubtargetInfo &STI) const override;

  uint64_t getBinaryCodeForInstr(const MCInst &MI,
                                 SmallVectorImpl<MCFixup> &Fixups,
                                 const MCSubtargetInfo &STI) const;

  unsigned getMachineOpValue(const MCInst &MI, const MCOperand &MO,
                             SmallVectorImpl<MCFixup> &Fixups,
                             const MCSubtargetInfo &STI) const;

  uint64_t encodeR3Imm(const MCInst &MI, unsigned OpIdx,
                       SmallVectorImpl<MCFixup> &Fixups,
                       const MCSubtargetInfo &STI, bool IsSymbol) const;
};

} // end anonymous namespace

uint64_t RISC_VI_VIIMCCodeEmitter::encodeR3Imm(const MCInst &MI, unsigned OpIdx,
    SmallVectorImpl<MCFixup> &Fixups,
    const MCSubtargetInfo &STI, bool IsSymbol) const {
  const MCOperand &MO = MI.getOperand(OpIdx);
  if (MO.isReg())
    return Ctx.getRegisterInfo()->getEncodingValue(MO.getReg()) & 0xFFFFFFFFULL;
  if (MO.isImm())
    return static_cast<uint64_t>(MO.getImm()) & 0xFFFFFFFFULL;
  if (MO.isExpr()) {
    Fixups.push_back(MCFixup::create(
        0, MO.getExpr(),
        MCFixupKind(FirstLiteralRelocationKind + 1), MI.getLoc()));
    return 0;
  }
  llvm_unreachable("Unexpected operand type for r3_imm");
}

void RISC_VI_VIIMCCodeEmitter::encodeInstruction(const MCInst &MI,
                                         SmallVectorImpl<char> &CB,
                                         SmallVectorImpl<MCFixup> &Fixups,
                                         const MCSubtargetInfo &STI) const {
  uint64_t Bits = getBinaryCodeForInstr(MI, Fixups, STI);

  unsigned Op = MI.getOpcode();
  uint64_t R3 = 0;

  if (Op == RISC_VI_VII::ADD    || Op == RISC_VI_VII::MUL    ||
      Op == RISC_VI_VII::SHL    || Op == RISC_VI_VII::OR     ||
      Op == RISC_VI_VII::AND    || Op == RISC_VI_VII::CMP_EQ ||
      Op == RISC_VI_VII::CMP_NE || Op == RISC_VI_VII::CMP_LT ||
      Op == RISC_VI_VII::CMP_GT || Op == RISC_VI_VII::CMP_LE ||
      Op == RISC_VI_VII::CMP_GE || Op == RISC_VI_VII::CMP_ULT||
      Op == RISC_VI_VII::CMP_UGT|| Op == RISC_VI_VII::CMP_ULE||
      Op == RISC_VI_VII::CMP_UGE|| Op == RISC_VI_VII::SCREEN_PUT_PIXEL)
    R3 = encodeR3Imm(MI, 2, Fixups, STI, false);
  else if (Op == RISC_VI_VII::ADDi  || Op == RISC_VI_VII::SREMi ||
           Op == RISC_VI_VII::ANDi  || Op == RISC_VI_VII::XORi  ||
           Op == RISC_VI_VII::LW    || Op == RISC_VI_VII::SW)
    R3 = encodeR3Imm(MI, 2, Fixups, STI, true);
  else if (Op == RISC_VI_VII::MOVI)
    R3 = encodeR3Imm(MI, 1, Fixups, STI, true);
  else if (Op == RISC_VI_VII::INC_EQ)
    R3 = encodeR3Imm(MI, 3, Fixups, STI, true);
  else if (Op == RISC_VI_VII::B)
    R3 = encodeR3Imm(MI, 0, Fixups, STI, true);
  else if (Op == RISC_VI_VII::CALL)
    R3 = encodeR3Imm(MI, 0, Fixups, STI, true);
  else if (Op == RISC_VI_VII::BR_COND)
    R3 = encodeR3Imm(MI, 1, Fixups, STI, true);
  Bits |= R3;

  support::endian::write(CB, Bits, llvm::endianness::little);
  ++MCNumEmitted;
}

unsigned RISC_VI_VIIMCCodeEmitter::getMachineOpValue(const MCInst &MI,
                                             const MCOperand &MO,
                                             SmallVectorImpl<MCFixup> &Fixups,
                                             const MCSubtargetInfo &STI) const {
  if (MO.isReg())
    return Ctx.getRegisterInfo()->getEncodingValue(MO.getReg());

  if (MO.isImm())
    return MO.getImm();

  assert(MO.isExpr());
  const MCExpr *Expr = MO.getExpr();

  int64_t Res;
  if (Expr->evaluateAsAbsolute(Res))
    return Res;

  llvm_unreachable("Unhandled expression!");
  return 0;
}


#include "RISC_VI_VIIGenMCCodeEmitter.inc"

MCCodeEmitter *llvm::createRISC_VI_VIIMCCodeEmitter(const MCInstrInfo &MCII,
                                            MCContext &Ctx) {
  return new RISC_VI_VIIMCCodeEmitter(MCII, Ctx);
}
