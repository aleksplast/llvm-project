#ifndef LLVM_LIB_TARGET_RISC_VI_VII_RISC_VI_VIIINSTRINFO_H
#define LLVM_LIB_TARGET_RISC_VI_VII_RISC_VI_VIIINSTRINFO_H

#include "RISC_VI_VIIRegisterInfo.h"
#include "MCTargetDesc/RISC_VI_VIIInfo.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "RISC_VI_VIIGenInstrInfo.inc"

namespace llvm {

class RISC_VI_VIISubtarget;

class RISC_VI_VIIInstrInfo : public RISC_VI_VIIGenInstrInfo {
public:
  RISC_VI_VIIInstrInfo();

};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_RISC_VI_VII_RISC_VI_VIIINSTRINFO_H
