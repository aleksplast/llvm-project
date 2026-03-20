#include "MCTargetDesc/RISC_VI_VIIInfo.h"
#include "RISC_VI_VII.h"
#include "TargetInfo/RISC_VI_VIITargetInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define GET_INSTRINFO_MC_DESC
#include "RISC_VI_VIIGenInstrInfo.inc"

#define GET_REGINFO_MC_DESC
#include "RISC_VI_VIIGenRegisterInfo.inc"

static MCRegisterInfo *createRISC_VI_VIIMCRegisterInfo(const Triple &TT) {
  RISC_VI_VII_DUMP_MAGENTA
  MCRegisterInfo *X = new MCRegisterInfo();
  InitRISC_VI_VIIMCRegisterInfo(X, RISC_VI_VII::SIX0);
  return X;
}

static MCInstrInfo *createRISC_VI_VIIMCInstrInfo() {
  RISC_VI_VII_DUMP_MAGENTA
  MCInstrInfo *X = new MCInstrInfo();
  InitRISC_VI_VIIMCInstrInfo(X);
  return X;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeRISC_VI_VIITargetMC() {
  RISC_VI_VII_DUMP_MAGENTA
  Target &TheRISC_VI_VIITarget = getTheRISC_VI_VIITarget();
  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheRISC_VI_VIITarget, createRISC_VI_VIIMCRegisterInfo);
  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheRISC_VI_VIITarget, createRISC_VI_VIIMCInstrInfo);
}
