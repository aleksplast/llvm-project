#ifndef LLVM_LIB_TARGET_RISC_VI_VII_MCTARGETDESC_RISC_VI_VIIINFO_H
#define LLVM_LIB_TARGET_RISC_VI_VII_MCTARGETDESC_RISC_VI_VIIINFO_H

#include "llvm/MC/MCInstrDesc.h"

namespace llvm {

namespace RISC_VI_VIIOp {
enum OperandType : unsigned {
  OPERAND_SIMM16 = MCOI::OPERAND_FIRST_TARGET,
  OPERAND_SIMM32,
};
} // namespace RISC_VI_VIIOp

} // end namespace llvm

#endif
