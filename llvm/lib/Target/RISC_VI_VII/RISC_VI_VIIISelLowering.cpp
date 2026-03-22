#include "RISC_VI_VIIISelLowering.h"
#include "RISC_VI_VII.h"
#include "RISC_VI_VIIRegisterInfo.h"
#include "RISC_VI_VIISubtarget.h"
#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/CodeGen/MachineFunction.h"

#define DEBUG_TYPE "RISC_VI_VII-lower"

using namespace llvm;

RISC_VI_VIITargetLowering::RISC_VI_VIITargetLowering(const TargetMachine &TM,
                                     const RISC_VI_VIISubtarget &STI)
    : TargetLowering(TM), STI(STI) {
  RISC_VI_VII_DUMP_RED
  addRegisterClass(MVT::i32, &RISC_VI_VII::GPRRegClass);
}

const char *RISC_VI_VIITargetLowering::getTargetNodeName(unsigned Opcode) const {
  RISC_VI_VII_DUMP_RED
  switch (Opcode) {
  case RISC_VI_VIIISD::CALL:
    return "RISC_VI_VIIISD::CALL";
  case RISC_VI_VIIISD::RET:
    return "RISC_VI_VIIISD::RET";
  }
  return nullptr;
}
