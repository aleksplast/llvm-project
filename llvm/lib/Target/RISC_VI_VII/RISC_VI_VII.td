include "llvm/Target/Target.td"
include "RISC_VI_VIIRegisterInfo.td"
include "RISC_VI_VIIInstrInfo.td"

class Proc<string Name, list<SubtargetFeature> Features>
 : Processor<Name, NoItineraries, Features>;

def : Proc<"generic", []>;

def RISC_VI_VIIInstrInfo : InstrInfo;
def RISC_VI_VII : Target {
  let InstructionSet = RISC_VI_VIIInstrInfo;
}
