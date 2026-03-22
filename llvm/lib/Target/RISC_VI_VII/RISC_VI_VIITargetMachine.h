#ifndef LLVM_LIB_TARGET_RISC_VI_VII_RISC_VI_VIITARGETMACHINE_H
#define LLVM_LIB_TARGET_RISC_VI_VII_RISC_VI_VIITARGETMACHINE_H

#include "llvm/CodeGen/CodeGenTargetMachineImpl.h"
#include "RISC_VI_VIISubtarget.h"
#include <optional>

namespace llvm {
extern Target TheRISC_VI_VIITarget;

class RISC_VI_VIITargetMachine : public CodeGenTargetMachineImpl {
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  RISC_VI_VIISubtarget Subtarget;

public:
  RISC_VI_VIITargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                   StringRef FS, const TargetOptions &Options,
                   std::optional<Reloc::Model> RM,
                   std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                   bool JIT);
  const RISC_VI_VIISubtarget *getSubtargetImpl(const Function &) const override {
    RISC_VI_VII_DUMP_CYAN
    return &Subtarget;
  }
  // Pass Pipeline Configuration
  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;
  TargetLoweringObjectFile *getObjFileLowering() const override;
};
} // end namespace llvm

#endif // LLVM_LIB_TARGET_RISC_VI_VII_RISC_VI_VIITARGETMACHINE_H
