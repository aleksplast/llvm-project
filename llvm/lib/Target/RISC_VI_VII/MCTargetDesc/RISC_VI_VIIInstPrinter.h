#ifndef LLVM_LIB_TARGET_RISC_VI_VII_INSTPRINTER_RISC_VI_VIIINSTPRINTER_H
#define LLVM_LIB_TARGET_RISC_VI_VII_INSTPRINTER_RISC_VI_VIIINSTPRINTER_H

#include "llvm/MC/MCInstPrinter.h"
#include "llvm/MC/MCRegister.h"

namespace llvm {

class RISC_VI_VIIInstPrinter : public MCInstPrinter {
public:
  RISC_VI_VIIInstPrinter(const MCAsmInfo &MAI, const MCInstrInfo &MII,
                 const MCRegisterInfo &MRI)
      : MCInstPrinter(MAI, MII, MRI) {}

  std::pair<const char *, uint64_t>
  getMnemonic(const MCInst &MI) const override {}

  // Override MCInstPrinter.
  void printRegName(raw_ostream &O, MCRegister Reg) override {}
  void printInst(const MCInst *MI, uint64_t Address, StringRef Annot,
                 const MCSubtargetInfo &STI, raw_ostream &O) override {}
};
} // end namespace llvm

#endif // LLVM_LIB_TARGET_RISC_VI_VII_INSTPRINTER_RISC_VI_VIIINSTPRINTER_H
