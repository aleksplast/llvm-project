//===----------------------------------------------------------------------===//
//
// This file declares RISC_VI_VII-specific per-machine-function information.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_RISC_VI_VII_RISC_VI_VIIMACHINEFUNCTIONINFO_H
#define LLVM_LIB_TARGET_RISC_VI_VII_RISC_VI_VIIMACHINEFUNCTIONINFO_H

#include "llvm/CodeGen/MachineFunction.h"
#include <vector>

namespace llvm {

/// RISC_VI_VIIFunctionInfo - This class is derived from MachineFunction private
/// RISC_VI_VII target-specific information for each MachineFunction.
class RISC_VI_VIIFunctionInfo : public MachineFunctionInfo {
  virtual void anchor();

  bool ReturnStackOffsetSet = false;
  unsigned ReturnStackOffset = -1U;

  /// FrameIndex for start of varargs area
  int VarArgsFrameIndex = 0;
  /// Size of the save area used for varargs
  int VarArgsSaveSize = 0;
  /// Size of stack frame to save callee saved registers
  unsigned CalleeSavedStackSize = 0;

public:
  RISC_VI_VIIFunctionInfo() {}
  explicit RISC_VI_VIIFunctionInfo(MachineFunction &MF) {}
  ~RISC_VI_VIIFunctionInfo() {}

  void setVarArgsFrameIndex(int Off) { VarArgsFrameIndex = Off; }
  int getVarArgsFrameIndex() const { return VarArgsFrameIndex; }

  void setVarArgsSaveSize(int Size) { VarArgsSaveSize = Size; }
  int getVarArgsSaveSize() const { return VarArgsSaveSize; }

  unsigned getCalleeSavedStackSize() const { return CalleeSavedStackSize; }
  void setCalleeSavedStackSize(unsigned Size) { CalleeSavedStackSize = Size; }

  void setReturnStackOffset(unsigned Off) {
    assert(!ReturnStackOffsetSet && "Return stack offset set twice");
    ReturnStackOffset = Off;
    ReturnStackOffsetSet = true;
  }

  unsigned getReturnStackOffset() const {
    assert(ReturnStackOffsetSet && "Return stack offset not set");
    return ReturnStackOffset;
  }
};
} // end namespace llvm

#endif // LLVM_LIB_TARGET_RISC_VI_VII_RISC_VI_VIIMACHINEFUNCTIONINFO_H
