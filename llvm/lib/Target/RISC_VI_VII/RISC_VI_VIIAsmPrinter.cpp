
#include "MCTargetDesc/RISC_VI_VIIInstPrinter.h"
#include "RISC_VI_VII.h"
#include "RISC_VI_VIISubtarget.h"
#include "RISC_VI_VIITargetMachine.h"
#include "TargetInfo/RISC_VI_VIITargetInfo.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineConstantPool.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define DEBUG_TYPE "asm-printer"

namespace {

class RISC_VI_VIIAsmPrinter : public AsmPrinter {
  const MCSubtargetInfo *STI;

public:
  explicit RISC_VI_VIIAsmPrinter(TargetMachine &TM,
                         std::unique_ptr<MCStreamer> Streamer)
      : AsmPrinter(TM, std::move(Streamer)), STI(TM.getMCSubtargetInfo()) {
    RISC_VI_VII_DUMP_GREEN
  }

  void emitInstruction(const MachineInstr *MI) override;

  StringRef getPassName() const override { return "RISC_VI_VII Assembly Printer"; }

  bool lowerPseudoInstExpansion(const MachineInstr *MI, MCInst &Inst);
};

} // end anonymous namespace

// RISC_VI_VIIple pseudo-instructions have their lowering (with expansion to real
// instructions) auto-generated.
#include "RISC_VI_VIIGenMCPseudoLowering.inc"

void RISC_VI_VIIAsmPrinter::emitInstruction(const MachineInstr *MI) {
  RISC_VI_VII_DUMP_GREEN
  // Do any auto-generated pseudo lowerings.
  if (MCInst OutInst; lowerPseudoInstExpansion(MI, OutInst)) {
    EmitToStreamer(*OutStreamer, OutInst);
    return;
  }
}

// Force static initialization.
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeRISC_VI_VIIAsmPrinter() {
  RegisterAsmPrinter<RISC_VI_VIIAsmPrinter> X(getTheRISC_VI_VIITarget());
}
