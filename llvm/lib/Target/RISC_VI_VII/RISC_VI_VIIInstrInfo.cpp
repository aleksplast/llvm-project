#include "RISC_VI_VIIInstrInfo.h"
#include "RISC_VI_VII.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineMemOperand.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

#define GET_INSTRINFO_CTOR_DTOR
#include "RISC_VI_VIIGenInstrInfo.inc"

#define DEBUG_TYPE "RISC_VI_VII-inst-info"

RISC_VI_VIIInstrInfo::RISC_VI_VIIInstrInfo()
    : RISC_VI_VIIGenInstrInfo(RISC_VI_VII::ADJCALLSTACKDOWN,
                              RISC_VI_VII::ADJCALLSTACKUP) { RISC_VI_VII_DUMP_GREEN }

void RISC_VI_VIIInstrInfo::copyPhysReg(MachineBasicBlock &MBB,
                               MachineBasicBlock::iterator MBBI,
                               const DebugLoc &DL, MCRegister DstReg,
                               MCRegister SrcReg, bool KillSrc,
                               bool RenamableDest, bool RenamableSrc) const {
  if (RISC_VI_VII::GPRRegClass.contains(DstReg, SrcReg)) {
    BuildMI(MBB, MBBI, DL, get(RISC_VI_VII::MOV), DstReg)
        .addReg(SrcReg, getKillRegState(KillSrc));
    return;
  }
  llvm_unreachable("can't copyPhysReg");
}

#include "RISC_VI_VIIInstrInfo.h"
#include "RISC_VI_VIIRegisterInfo.h"

void RISC_VI_VIIInstrInfo::storeRegToStackSlot(
      MachineBasicBlock &MBB, MachineBasicBlock::iterator MI, Register SrcReg,
      bool IsKill, int FrameIndex, const TargetRegisterClass *RC,
      const TargetRegisterInfo *TRI, Register VReg,
      MachineInstr::MIFlag Flags) const {
  DebugLoc DL = MI->getDebugLoc();
  BuildMI(MBB, MI, DL, get(RISC_VI_VII::SW))
      .addReg(SrcReg, getKillRegState(IsKill))
      .addFrameIndex(FrameIndex)
      .addImm(0);
}

void RISC_VI_VIIInstrInfo::loadRegFromStackSlot(
      MachineBasicBlock &MBB, MachineBasicBlock::iterator MI, Register DestReg,
      int FrameIndex, const TargetRegisterClass *RC,
      const TargetRegisterInfo *TRI, Register VReg,
      MachineInstr::MIFlag Flags) const {
  DebugLoc DL = MI->getDebugLoc();
  BuildMI(MBB, MI, DL, get(RISC_VI_VII::LW))
      .addReg(DestReg, RegState::Define)
      .addFrameIndex(FrameIndex)
      .addImm(0);
}
