#ifndef LLVM_LIB_TARGET_RISC_VI_VII_RISC_VI_VIIFRAMELOWERING_H
#define LLVM_LIB_TARGET_RISC_VI_VII_RISC_VI_VIIFRAMELOWERING_H

#include "RISC_VI_VII.h"
#include "llvm/CodeGen/TargetFrameLowering.h"

namespace llvm {

class RISC_VI_VIIFrameLowering : public TargetFrameLowering {
public:
  explicit RISC_VI_VIIFrameLowering()
      : TargetFrameLowering(TargetFrameLowering::StackGrowsDown, Align(4), 0) {
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
};

} // namespace llvm

#endif // LLVM_LIB_TARGET_RISC_VI_VII_RISC_VI_VIIFRAMELOWERING_H
