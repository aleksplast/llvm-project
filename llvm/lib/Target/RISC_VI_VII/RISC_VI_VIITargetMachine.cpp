#include "RISC_VI_VIITargetMachine.h"
#include "RISC_VI_VII.h"
#include "TargetInfo/RISC_VI_VIITargetInfo.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/MC/TargetRegistry.h"
#include <optional>

using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeRISC_VI_VIITarget() {
  // Register the target.
  RISC_VI_VII_DUMP_CYAN
  RegisterTargetMachine<RISC_VI_VIITargetMachine> A(getTheRISC_VI_VIITarget());
}

RISC_VI_VIITargetMachine::RISC_VI_VIITargetMachine(const Target &T, const Triple &TT,
                                   StringRef CPU, StringRef FS,
                                   const TargetOptions &Options,
                                   std::optional<Reloc::Model> RM,
                                   std::optional<CodeModel::Model> CM,
                                   CodeGenOptLevel OL, bool JIT)
    : CodeGenTargetMachineImpl(
          T, "e-m:e-p:32:32-i8:8:32-i16:16:32-i64:64-n32", TT, CPU, FS, Options,
          Reloc::Static, getEffectiveCodeModel(CM, CodeModel::Small), OL) {
  RISC_VI_VII_DUMP_CYAN
  initAsmInfo();
}


namespace {

/// RISC_VI_VII Code Generator Pass Configuration Options.
class RISC_VI_VIIPassConfig : public TargetPassConfig {
public:
  RISC_VI_VIIPassConfig(RISC_VI_VIITargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  bool addInstSelector() override {
    RISC_VI_VII_DUMP_CYAN
    return false;
  }
};

} // end anonymous namespace

TargetPassConfig *RISC_VI_VIITargetMachine::createPassConfig(PassManagerBase &PM) {
  RISC_VI_VII_DUMP_CYAN
  return new RISC_VI_VIIPassConfig(*this, PM);
}
