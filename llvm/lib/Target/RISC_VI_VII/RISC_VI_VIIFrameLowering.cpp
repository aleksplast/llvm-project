#include "RISC_VI_VIIFrameLowering.h"
#include "RISC_VI_VII.h"
#include "RISC_VI_VIIInstrInfo.h"
#include "RISC_VI_VIISubtarget.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"

using namespace llvm;

void RISC_VI_VIIFrameLowering::emitPrologue(MachineFunction &MF,
                                             MachineBasicBlock &MBB) const {
  int FrameSize = (int)MF.getFrameInfo().getStackSize();
  if (FrameSize == 0)
    return;

  const RISC_VI_VIIInstrInfo *TII =
      static_cast<const RISC_VI_VIIInstrInfo *>(MF.getSubtarget().getInstrInfo());
  MachineBasicBlock::iterator MBBI = MBB.begin();

  BuildMI(MBB, MBBI, DebugLoc(), TII->get(RISC_VI_VII::ADDi),
          RISC_VI_VII::TUNG_TUNG_TUNG_SAHUR)
      .addReg(RISC_VI_VII::TUNG_TUNG_TUNG_SAHUR)
      .addImm(-FrameSize);
}

void RISC_VI_VIIFrameLowering::emitEpilogue(MachineFunction &MF,
                                             MachineBasicBlock &MBB) const {
  int FrameSize = (int)MF.getFrameInfo().getStackSize();
  if (FrameSize == 0)
    return;

  const RISC_VI_VIIInstrInfo *TII =
      static_cast<const RISC_VI_VIIInstrInfo *>(MF.getSubtarget().getInstrInfo());
  MachineBasicBlock::iterator MBBI = MBB.getLastNonDebugInstr();

  BuildMI(MBB, MBBI, DebugLoc(), TII->get(RISC_VI_VII::ADDi),
          RISC_VI_VII::TUNG_TUNG_TUNG_SAHUR)
      .addReg(RISC_VI_VII::TUNG_TUNG_TUNG_SAHUR)
      .addImm(FrameSize);
}

MachineBasicBlock::iterator
RISC_VI_VIIFrameLowering::eliminateCallFramePseudoInstr(
    MachineFunction &, MachineBasicBlock &MBB,
    MachineBasicBlock::iterator MI) const {
  return MBB.erase(MI);
}

StackOffset
RISC_VI_VIIFrameLowering::getFrameIndexReference(const MachineFunction &MF,
                                                  int FI,
                                                  Register &FrameReg) const {
  FrameReg = RISC_VI_VII::TUNG_TUNG_TUNG_SAHUR;
  const MachineFrameInfo &MFI = MF.getFrameInfo();
  return StackOffset::getFixed(MFI.getObjectOffset(FI) +
                               (int64_t)MFI.getStackSize());
}
