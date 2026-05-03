#ifndef LLVM_LIB_TARGET_RISC_VI_VII_RISC_VI_VIIFRAMELOWERING_H
#define LLVM_LIB_TARGET_RISC_VI_VII_RISC_VI_VIIFRAMELOWERING_H

#include "RISC_VI_VII.h"
#include "llvm/CodeGen/TargetFrameLowering.h"

namespace llvm {
class RISC_VI_VIISubtarget;

class RISC_VI_VIIFrameLowering : public TargetFrameLowering {
public:
  RISC_VI_VIIFrameLowering(const RISC_VI_VIISubtarget &STI)
      : TargetFrameLowering(TargetFrameLowering::StackGrowsDown, Align(4), 0),
        STI(STI) {
    RISC_VI_VII_DUMP_GREEN
  }

  void emitPrologue(MachineFunction &MF,
                    MachineBasicBlock &MBB) const override;
  void emitEpilogue(MachineFunction &MF,
                    MachineBasicBlock &MBB) const override;

  StackOffset getFrameIndexReference(const MachineFunction &MF, int FI,
                                     Register &FrameReg) const override;

  MachineBasicBlock::iterator
  eliminateCallFramePseudoInstr(MachineFunction &MF, MachineBasicBlock &MBB,
                                MachineBasicBlock::iterator MI) const override;

  bool hasFPImpl(const MachineFunction &MF) const override { return false; }

private:
  const RISC_VI_VIISubtarget &STI;
};

} // namespace llvm

#endif // LLVM_LIB_TARGET_RISC_VI_VII_RISC_VI_VIIFRAMELOWERING_H
