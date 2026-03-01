#include "RISC_VI_VIITargetInfo.h"
#include "../RISC_VI_VII.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

Target &llvm::getTheRISC_VI_VIITarget() {
  RISC_VI_VII_DUMP_YELLOW
  static Target TheRISC_VI_VIITarget;
  return TheRISC_VI_VIITarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeRISC_VI_VIITargetInfo() {
  RISC_VI_VII_DUMP_YELLOW
  RegisterTarget<Triple::riscvivii> X(getTheRISC_VI_VIITarget(), "RISC_VI_VII",
                                "Brainrot target for LLVM course", "RISC_VI_VII");
}
