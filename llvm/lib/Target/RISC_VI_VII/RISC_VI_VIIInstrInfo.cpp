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

bool RISC_VI_VIIInstrInfo::analyzeBranch(MachineBasicBlock &MBB,
                                          MachineBasicBlock *&TBB,
                                          MachineBasicBlock *&FBB,
                                          SmallVectorImpl<MachineOperand> &Cond,
                                          bool AllowModify) const {
  TBB = FBB = nullptr;
  Cond.clear();

  MachineBasicBlock::iterator I = MBB.end();
  while (I != MBB.begin()) {
    --I;
    if (I->isDebugInstr())
      continue;
    if (!I->isTerminator())
      break;

    unsigned Opc = I->getOpcode();
    if (Opc == RISC_VI_VII::B) {
      TBB = I->getOperand(0).getMBB();
    } else if (Opc == RISC_VI_VII::BR_COND) {
      FBB = TBB;
      TBB = I->getOperand(1).getMBB();
      Cond.push_back(I->getOperand(0));
    } else {
      return true; // unknown terminator
    }
  }
  return false;
}

unsigned RISC_VI_VIIInstrInfo::insertBranch(MachineBasicBlock &MBB,
                                             MachineBasicBlock *TBB,
                                             MachineBasicBlock *FBB,
                                             ArrayRef<MachineOperand> Cond,
                                             const DebugLoc &DL,
                                             int *BytesAdded) const {
  assert(TBB && "insertBranch must not be told to insert a fallthrough");
  assert(Cond.size() <= 1);

  if (Cond.empty()) {
    BuildMI(&MBB, DL, get(RISC_VI_VII::B)).addMBB(TBB);
    if (BytesAdded) *BytesAdded = 8;
    return 1;
  }

  BuildMI(&MBB, DL, get(RISC_VI_VII::BR_COND)).add(Cond[0]).addMBB(TBB);
  if (!FBB) {
    if (BytesAdded) *BytesAdded = 8;
    return 1;
  }

  BuildMI(&MBB, DL, get(RISC_VI_VII::B)).addMBB(FBB);
  if (BytesAdded) *BytesAdded = 16;
  return 2;
}

unsigned RISC_VI_VIIInstrInfo::removeBranch(MachineBasicBlock &MBB,
                                             int *BytesRemoved) const {
  MachineBasicBlock::iterator I = MBB.end();
  unsigned Count = 0;

  while (I != MBB.begin()) {
    --I;
    if (I->isDebugInstr())
      continue;
    unsigned Opc = I->getOpcode();
    if (Opc != RISC_VI_VII::B && Opc != RISC_VI_VII::BR_COND)
      break;
    I->eraseFromParent();
    I = MBB.end();
    ++Count;
  }

  if (BytesRemoved) *BytesRemoved = Count * 8;
  return Count;
}
