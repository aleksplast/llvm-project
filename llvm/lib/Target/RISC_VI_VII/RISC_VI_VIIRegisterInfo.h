#ifndef LLVM_LIB_TARGET_RISC_VI_VII_RISC_VI_VIIREGISTERINFO_H
#define LLVM_LIB_TARGET_RISC_VI_VII_RISC_VI_VIIREGISTERINFO_H

#define GET_REGINFO_HEADER
#include "RISC_VI_VIIGenRegisterInfo.inc"

namespace llvm {

struct RISC_VI_VIIRegisterInfo : public RISC_VI_VIIGenRegisterInfo {
public:
  RISC_VI_VIIRegisterInfo();
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_RISC_VI_VII_RISC_VI_VIIREGISTERINFO_H
