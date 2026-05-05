#ifndef LLVM_LIB_TARGET_RISC_VI_VII_MCTARGETDESC_RISC_VI_VIIFIXUPKINDS_H
#define LLVM_LIB_TARGET_RISC_VI_VII_MCTARGETDESC_RISC_VI_VIIFIXUPKINDS_H

#include "llvm/MC/MCFixup.h"

namespace llvm {
namespace RISC_VI_VII {
enum Fixups {
  fixup_RISC_VI_VII_PC32 = FirstTargetFixupKind,
  // Marker
  LastTargetFixupKind,
  NumTargetFixupKinds = LastTargetFixupKind - FirstTargetFixupKind
};
} // namespace RISC_VI_VII
} // namespace llvm

#endif
