#ifndef LLVM_LIB_TARGET_RISC_VI_VII_RISC_VI_VIIREGISTERINFO_H
#define LLVM_LIB_TARGET_RISC_VI_VII_RISC_VI_VIIREGISTERINFO_H

#define GET_REGINFO_HEADER
#include "RISC_VI_VIIGenRegisterInfo.inc"

namespace llvm {

class TargetInstrInfo;
class SimSubtarget;

struct RISC_VI_VIIRegisterInfo : public RISC_VI_VIIGenRegisterInfo {
public:
  RISC_VI_VIIRegisterInfo();

  const MCPhysReg *getCalleeSavedRegs(const MachineFunction *MF) const override;

  const uint32_t *getCallPreservedMask(const MachineFunction &MF,
                                       CallingConv::ID CC) const override;

  BitVector getReservedRegs(const MachineFunction &MF) const override;

  bool requiresRegisterScavenging(const MachineFunction &MF) const override;

  bool eliminateFrameIndex(MachineBasicBlock::iterator II, int SPAdj,
                           unsigned FIOperandNum,
                           RegScavenger *RS = nullptr) const override;

  // Debug information queries.
  Register getFrameRegister(const MachineFunction &MF) const override;
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_RISC_VI_VII_RISC_VI_VIIREGISTERINFO_H
