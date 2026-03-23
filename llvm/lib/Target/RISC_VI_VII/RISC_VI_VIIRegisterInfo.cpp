#include "RISC_VI_VIIRegisterInfo.h"
#include "RISC_VI_VII.h"
#include "RISC_VI_VIIFrameLowering.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

using namespace llvm;

#define GET_REGINFO_TARGET_DESC
#include "RISC_VI_VIIGenRegisterInfo.inc"

RISC_VI_VIIRegisterInfo::RISC_VI_VIIRegisterInfo() : RISC_VI_VIIGenRegisterInfo(RISC_VI_VII::TRALALERO_TRALALA) {
  RISC_VI_VII_DUMP_GREEN
}
const MCPhysReg *
RISC_VI_VIIRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  RISC_VI_VII_DUMP_GREEN
  return CSR_RISC_VI_VII_SaveList;
}

BitVector RISC_VI_VIIRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  RISC_VI_VII_DUMP_GREEN
  RISC_VI_VIIFrameLowering const *TFI = getFrameLowering(MF);

  BitVector Reserved(getNumRegs());
  Reserved.set(RISC_VI_VII::BRR_BRR_PATAPIM);

  if (TFI->hasFP(MF)) {
    Reserved.set(RISC_VI_VII::LIRILI_LARILA);
  }
  return Reserved;
}

bool RISC_VI_VIIRegisterInfo::requiresRegisterScavenging(
    const MachineFunction &MF) const {
  return false;
}

bool RISC_VI_VIIRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                          int SPAdj, unsigned FIOperandNum,
                                          RegScavenger *RS) const {
  RISC_VI_VII_DUMP_GREEN
  assert(SPAdj == 0 && "Unexpected non-zero SPAdj value");

  MachineInstr &MI = *II;
  MachineFunction &MF = *MI.getParent()->getParent();
  DebugLoc DL = MI.getDebugLoc();

  int FrameIndex = MI.getOperand(FIOperandNum).getIndex();
  Register FrameReg;
  int Offset = getFrameLowering(MF)
                   ->getFrameIndexReference(MF, FrameIndex, FrameReg)
                   .getFixed();
  Offset += MI.getOperand(FIOperandNum + 1).getImm();

  if (!isInt<16>(Offset)) {
    llvm_unreachable("");
  }

  MI.getOperand(FIOperandNum).ChangeToRegister(FrameReg, false, false, false);
  MI.getOperand(FIOperandNum + 1).ChangeToImmediate(Offset);
  return false;
}

Register RISC_VI_VIIRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  RISC_VI_VII_DUMP_GREEN
  const TargetFrameLowering *TFI = getFrameLowering(MF);
  return TFI->hasFP(MF) ? RISC_VI_VII::LIRILI_LARILA : RISC_VI_VII::BRR_BRR_PATAPIM;
}

const uint32_t *
RISC_VI_VIIRegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                      CallingConv::ID CC) const {
  RISC_VI_VII_DUMP_GREEN
  return CSR_RISC_VI_VII_RegMask;
}
