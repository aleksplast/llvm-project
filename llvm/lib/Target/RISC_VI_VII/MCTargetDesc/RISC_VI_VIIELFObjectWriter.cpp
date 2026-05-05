#include "MCTargetDesc/RISC_VI_VIIMCTargetDesc.h"
#include "MCTargetDesc/RISC_VI_VIIFixupKinds.h"
#include "RISC_VI_VII.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCValue.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

namespace {
class RISC_VI_VIIELFObjectWriter : public MCELFObjectTargetWriter {
public:
  RISC_VI_VIIELFObjectWriter(bool Is64Bit, uint8_t OSABI)
      : MCELFObjectTargetWriter(Is64Bit, OSABI, ELF::EM_RISC_VI_VII,
                                /*HasRelocationAddend*/ true) {}

  ~RISC_VI_VIIELFObjectWriter() override = default;

protected:
  unsigned getRelocType(MCContext &Ctx, const MCValue &Target,
                        const MCFixup &Fixup, bool IsPCRel) const override;

  bool needsRelocateWithSymbol(const MCValue &Val, const MCSymbol &Sym,
                               unsigned Type) const override;
};
} // namespace

unsigned RISC_VI_VIIELFObjectWriter::getRelocType(MCContext &Ctx, const MCValue &Target,
                                          const MCFixup &Fixup,
                                          bool IsPCRel) const {
  MCFixupKind Kind = Fixup.getKind();
  if (Kind >= FirstLiteralRelocationKind)
    return Kind - FirstLiteralRelocationKind;

  switch (unsigned(Kind)) {
  case RISC_VI_VII::fixup_RISC_VI_VII_PC32:
    return 1;
  default:
    llvm_unreachable("Unimplemented fixup -> relocation");
  }
}

bool RISC_VI_VIIELFObjectWriter::needsRelocateWithSymbol(const MCValue &,
                                                 const MCSymbol &,
                                                 unsigned Type) const {
  return false;
}

std::unique_ptr<MCObjectTargetWriter>
llvm::createRISC_VI_VIIELFObjectWriter(bool Is64Bit, uint8_t OSABI) {
  return std::make_unique<RISC_VI_VIIELFObjectWriter>(Is64Bit, OSABI);
}
