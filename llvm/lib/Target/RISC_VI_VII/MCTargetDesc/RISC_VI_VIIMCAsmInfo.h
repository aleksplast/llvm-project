#ifndef LLVM_LIB_TARGET_RISC_VI_VII_MCTARGETDESC_RISC_VI_VIIMCASMINFO_H
#define LLVM_LIB_TARGET_RISC_VI_VII_MCTARGETDESC_RISC_VI_VIIMCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {

class Triple;

class RISC_VI_VIIELFMCAsmInfo : public MCAsmInfoELF {
public:
  explicit RISC_VI_VIIELFMCAsmInfo(const Triple &TheTriple);
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_RISC_VI_VII_MCTARGETDESC_RISC_VI_VIIMCASMINFO_H
