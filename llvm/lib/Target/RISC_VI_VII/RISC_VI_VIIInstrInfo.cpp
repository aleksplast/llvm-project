#include "RISC_VI_VIIInstrInfo.h"
#include "RISC_VI_VII.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineMemOperand.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

#define GET_INSTRINFO_CTOR_DTOR
#include "RISC_VI_VIIGenInstrInfo.inc"

#define DEBUG_TYPE "RISC_VI_VII-inst-info"

RISC_VI_VIIInstrInfo::RISC_VI_VIIInstrInfo() : RISC_VI_VIIGenInstrInfo() { RISC_VI_VII_DUMP_GREEN }
