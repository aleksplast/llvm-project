#include "RISC_VI_VIISelectionDAGInfo.h"
#include "RISC_VI_VIIISelLowering.h"
#include "llvm/CodeGen/SelectionDAG.h"

using namespace llvm;

SDValue RISC_VI_VIISelectionDAGInfo::EmitTargetCodeForMemset(
    SelectionDAG &DAG, const SDLoc &dl, SDValue Chain, SDValue Dst,
    SDValue Val, SDValue Size, Align Alignment, bool isVolatile,
    bool AlwaysInline, MachinePointerInfo DstPtrInfo) const {
  SDValue FillVal = DAG.getNode(ISD::ZERO_EXTEND, dl, MVT::i32, Val);
  if (Size.getValueType() != MVT::i32)
    Size = DAG.getNode(ISD::TRUNCATE, dl, MVT::i32, Size);
  SDValue Ops[] = {Chain, Dst, FillVal, Size};
  return DAG.getNode(RISC_VI_VIIISD::MEMSET, dl, MVT::Other, Ops);
}

SDValue RISC_VI_VIISelectionDAGInfo::EmitTargetCodeForMemcpy(
    SelectionDAG &DAG, const SDLoc &dl, SDValue Chain, SDValue Dst,
    SDValue Src, SDValue Size, Align Alignment, bool isVolatile,
    bool AlwaysInline, MachinePointerInfo DstPtrInfo,
    MachinePointerInfo SrcPtrInfo) const {
  SDValue Ops[] = {Chain, Dst, Src, Size};
  return DAG.getNode(RISC_VI_VIIISD::MEMCPY, dl, MVT::Other, Ops);
}
