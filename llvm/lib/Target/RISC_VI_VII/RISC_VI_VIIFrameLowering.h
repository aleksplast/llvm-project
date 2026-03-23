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

  /// emitProlog/emitEpilog - These methods insert prolog and epilog code into
  /// the function.
  void emitPrologue(MachineFunction &MF,
                    MachineBasicBlock &MBB) const override {}
  void emitEpilogue(MachineFunction &MF,
                    MachineBasicBlock &MBB) const override {}

  /// hasFP - Return true if the specified function should have a dedicated
  /// frame pointer register. For most targets this is true only if the function
  /// has variable sized allocas or if frame pointer elimination is disabled.
  bool hasFPImpl(const MachineFunction &MF) const override { return false; }

  private:
  const RISC_VI_VIISubtarget &STI;
};

} // namespace llvm

#endif // LLVM_LIB_TARGET_RISC_VI_VII_RISC_VI_VIIFRAMELOWERING_H
