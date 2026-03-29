#ifndef LLVM_LIB_TARGET_RISC_VI_VII_MCTARGETDESC_RISC_VI_VIIMCTARGETDESC_H
#define LLVM_LIB_TARGET_RISC_VI_VII_MCTARGETDESC_RISC_VI_VIIMCTARGETDESC_H

// Defines symbolic names for RISC_VI_VII registers.  This defines a mapping from
// register name to register number.
//
#define GET_REGINFO_ENUM
#include "RISC_VI_VIIGenRegisterInfo.inc"

// Defines symbolic names for the RISC_VI_VII instructions.
#define GET_INSTRINFO_ENUM
#include "RISC_VI_VIIGenInstrInfo.inc"

namespace llvm {
class MCCodeEmitter;
class MCContext;
class MCInstrInfo;
class MCAsmBackend;
class MCObjectTargetWriter;
class MCRegisterInfo;
class MCSubtargetInfo;
class MCTargetOptions;
class Target;

MCCodeEmitter *createRISC_VI_VIIMCCodeEmitter(const MCInstrInfo &MCII, MCContext &Ctx);
MCAsmBackend *createRISC_VI_VIIAsmBackend(const Target &T, const MCSubtargetInfo &STI,
                                  const MCRegisterInfo &MRI,
                                  const MCTargetOptions &Options);
} // namespace llvm


#endif // LLVM_LIB_TARGET_RISC_VI_VII_MCTARGETDESC_RISC_VI_VIIMCTARGETDESC_H
