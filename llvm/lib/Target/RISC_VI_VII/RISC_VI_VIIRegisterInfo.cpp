#include "RISC_VI_VIIRegisterInfo.h"
#include "RISC_VI_VII.h"
#include "RISC_VI_VIIFrameLowering.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

using namespace llvm;

#define GET_REGINFO_TARGET_DESC
#include "RISC_VI_VIIGenRegisterInfo.inc"

RISC_VI_VIIRegisterInfo::RISC_VI_VIIRegisterInfo() : RISC_VI_VIIGenRegisterInfo(RISC_VI_VII::SIX0) {
  RISC_VI_VII_DUMP_GREEN
}
