#include "../RISC_VI_VII.h"
#include "llvm/Support/raw_ostream.h"

// We need to define this function for linking succeed
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeRISC_VI_VIITargetMC() { RISC_VI_VII_DUMP_MAGENTA }
