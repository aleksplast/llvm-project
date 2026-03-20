#include "RISC_VI_VIIMCAsmInfo.h"
#include "RISC_VI_VII.h"

using namespace llvm;

RISC_VI_VIIELFMCAsmInfo::RISC_VI_VIIELFMCAsmInfo(const Triple &TT) {
  RISC_VI_VII_DUMP_MAGENTA
  SupportsDebugInformation = false;
  Data16bitsDirective = "\t.short\t";
  Data32bitsDirective = "\t.word\t";
  Data64bitsDirective = nullptr;
  ZeroDirective = "\t.space\t";
  CommentString = ";";

  UsesELFSectionDirectiveForBSS = false;
  AllowAtInName = true;
  HiddenVisibilityAttr = MCSA_Invalid;
  HiddenDeclarationVisibilityAttr = MCSA_Invalid;
  ProtectedVisibilityAttr = MCSA_Invalid;

  ExceptionsType = ExceptionHandling::None;
}
