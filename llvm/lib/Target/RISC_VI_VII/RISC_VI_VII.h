#ifndef LLVM_LIB_TARGET_RISC_VI_VII_RISC_VI_VII_H
#define LLVM_LIB_TARGET_RISC_VI_VII_RISC_VI_VII_H

#include "MCTargetDesc/RISC_VI_VIIMCTargetDesc.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"

#define RISC_VI_VII_DUMP(Color)                                                        \
  {                                                                            \
    llvm::errs().changeColor(Color)                                            \
        << __func__ << "\n\t\t" << __FILE__ << ":" << __LINE__ << "\n";        \
    llvm::errs().changeColor(llvm::raw_ostream::WHITE);                        \
  }
// #define RISC_VI_VII_DUMP(Color) {}

#define RISC_VI_VII_DUMP_RED RISC_VI_VII_DUMP(llvm::raw_ostream::RED)
#define RISC_VI_VII_DUMP_GREEN RISC_VI_VII_DUMP(llvm::raw_ostream::GREEN)
#define RISC_VI_VII_DUMP_YELLOW RISC_VI_VII_DUMP(llvm::raw_ostream::YELLOW)
#define RISC_VI_VII_DUMP_CYAN RISC_VI_VII_DUMP(llvm::raw_ostream::CYAN)
#define RISC_VI_VII_DUMP_MAGENTA RISC_VI_VII_DUMP(llvm::raw_ostream::MAGENTA)
#define RISC_VI_VII_DUMP_WHITE RISC_VI_VII_DUMP(llvm::raw_ostream::WHITE)

namespace llvm {
class RISC_VI_VIITargetMachine;
class FunctionPass;

FunctionPass *createRISC_VI_VIIISelDag(RISC_VI_VIITargetMachine &TM, CodeGenOptLevel OptLevel);

} // namespace llvm

#endif // LLVM_LIB_TARGET_RISC_VI_VII_RISC_VI_VII_H
