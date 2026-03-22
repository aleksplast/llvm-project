#ifndef LLVM_LIB_TARGET_RISC_VI_VII_RISC_VI_VIIISELLOWERING_H
#define LLVM_LIB_TARGET_RISC_VI_VII_RISC_VI_VIIISELLOWERING_H

#include "RISC_VI_VII.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/CodeGen/TargetLowering.h"

namespace llvm {

class RISC_VI_VIISubtarget;
class RISC_VI_VIITargetMachine;

namespace RISC_VI_VIIISD {

enum NodeType : unsigned {
  // Start the numbering where the builtin ops and target ops leave off.
  FIRST_NUMBER = ISD::BUILTIN_OP_END,
  RET,
  CALL,
  BR_CC,
};

} // namespace RISC_VI_VIIISD

} // end namespace llvm

#endif // LLVM_LIB_TARGET_RISC_VI_VII_RISC_VI_VIIISELLOWERING_H
