include "llvm/Target/Target.td"
include "RISC_VI_VIIRegisterInfo.td"
include "RISC_VI_VIIInstrInfo.td"

def RISC_VI_VIIInstrInfo : InstrInfo;
def RISC_VI_VII : Target {
  let InstructionSet = RISC_VI_VIIInstrInfo;
}
