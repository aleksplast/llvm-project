#include "MCTargetDesc/RISC_VI_VIIInfo.h"
#include "RISC_VI_VII.h"
#include "RISC_VI_VIIMCAsmInfo.h"
#include "RISC_VI_VIIInstPrinter.h"
#include "TargetInfo/RISC_VI_VIITargetInfo.h"
#include "llvm/MC/MCDwarf.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

#define GET_INSTRINFO_MC_DESC
#include "RISC_VI_VIIGenInstrInfo.inc"

#define GET_REGINFO_MC_DESC
#include "RISC_VI_VIIGenRegisterInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "RISC_VI_VIIGenSubtargetInfo.inc"

static MCRegisterInfo *createRISC_VI_VIIMCRegisterInfo(const Triple &TT) {
  RISC_VI_VII_DUMP_MAGENTA
  MCRegisterInfo *X = new MCRegisterInfo();
  InitRISC_VI_VIIMCRegisterInfo(X, RISC_VI_VII::TRALALERO_TRALALA);
  return X;
}

static MCInstrInfo *createRISC_VI_VIIMCInstrInfo() {
  RISC_VI_VII_DUMP_MAGENTA
  MCInstrInfo *X = new MCInstrInfo();
  InitRISC_VI_VIIMCInstrInfo(X);
  return X;
}

static MCSubtargetInfo *createRISC_VI_VIIMCSubtargetInfo(const Triple &TT,
                                                 StringRef CPU, StringRef FS) {
  RISC_VI_VII_DUMP_MAGENTA
  return createRISC_VI_VIIMCSubtargetInfoImpl(TT, CPU, /*TuneCPU*/ CPU, FS);
}

static MCAsmInfo *createRISC_VI_VIIMCAsmInfo(const MCRegisterInfo &MRI,
                                     const Triple &TT,
                                     const MCTargetOptions &Options) {
  RISC_VI_VII_DUMP_MAGENTA
  MCAsmInfo *MAI = new RISC_VI_VIIELFMCAsmInfo(TT);
  unsigned SP = MRI.getDwarfRegNum(RISC_VI_VII::BOMBARDIRO_CROCODILO, true);
  MCCFIInstruction Inst = MCCFIInstruction::cfiDefCfa(nullptr, SP, 0);
  MAI->addInitialFrameState(Inst);
  return MAI;
}

static MCInstPrinter *createRISC_VI_VIIMCInstPrinter(const Triple &T,
                                             unsigned SyntaxVariant,
                                             const MCAsmInfo &MAI,
                                             const MCInstrInfo &MII,
                                             const MCRegisterInfo &MRI) {
  RISC_VI_VII_DUMP_MAGENTA
  return new RISC_VI_VIIInstPrinter(MAI, MII, MRI);
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeRISC_VI_VIITargetMC() {
  RISC_VI_VII_DUMP_MAGENTA
  Target &TheRISC_VI_VIITarget = getTheRISC_VI_VIITarget();
  RegisterMCAsmInfoFn X(TheRISC_VI_VIITarget, createRISC_VI_VIIMCAsmInfo);
  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheRISC_VI_VIITarget, createRISC_VI_VIIMCRegisterInfo);
  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheRISC_VI_VIITarget, createRISC_VI_VIIMCInstrInfo);
  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheRISC_VI_VIITarget,
                                          createRISC_VI_VIIMCSubtargetInfo);
  // Register the MCInstPrinter
  TargetRegistry::RegisterMCInstPrinter(TheRISC_VI_VIITarget, createRISC_VI_VIIMCInstPrinter);
}
