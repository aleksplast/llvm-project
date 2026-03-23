#include "RISC_VI_VIISubtarget.h"
#include "RISC_VI_VII.h"
#include "llvm/Target/TargetMachine.h"

using namespace llvm;

#define DEBUG_TYPE "RISC_VI_VII-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "RISC_VI_VIIGenSubtargetInfo.inc"

RISC_VI_VIISubtarget::RISC_VI_VIISubtarget(const Triple &TT, const std::string &CPU,
                           const std::string &FS, const TargetMachine &TM)
    : RISC_VI_VIIGenSubtargetInfo(TT, CPU, /*TuneCPU=*/CPU, FS), TLInfo(TM, *this),
      FrameLowering(*this) {
  RISC_VI_VII_DUMP_CYAN
}
