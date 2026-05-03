//===----------------------------------------------------------------------===//
// RISC_VI_VII profiles and nodes
//===----------------------------------------------------------------------===//

def risc_vi_vii_ret      : SDNode<"RISC_VI_VIIISD::RET", SDTNone,
                            [SDNPHasChain, SDNPOptInGlue, SDNPVariadic]>;

def SDT_RISC_VI_VIIBrCC  : SDTypeProfile<0, 2, [SDTCisVT<0, i32>,
                                                 SDTCisVT<1, OtherVT>]>;
def risc_vi_vii_brcc     : SDNode<"RISC_VI_VIIISD::BR_CC", SDT_RISC_VI_VIIBrCC,
                            [SDNPHasChain]>;

//===----------------------------------------------------------------------===//
// Instruction format superclass
//===----------------------------------------------------------------------===//

include "RISC_VI_VIIInstrFormats.td"

//===----------------------------------------------------------------------===//
// RISC_VI_VII Operand, Complex Patterns and Transformations Definitions.
//===----------------------------------------------------------------------===//

class SImmAsmOperand<int width> : AsmOperandClass {
  let Name = "SImm" # width;
  let RenderMethod = "addImmOperands";
  let DiagnosticType = !strconcat("Invalid", Name);
}

def btarget32 : Operand<OtherVT> {
  let ParserMatchClass = SImmAsmOperand<32>;
  let PrintMethod = "printBranchOperand";
  let EncoderMethod = "getBranchTarget32OpValue";
  let DecoderMethod = "decodeSImmOperand<32>";
  let MCOperandPredicate = [{
    int64_t Imm;
    if (MCOp.evaluateAsConstantImm(Imm))
      return isInt<32>(Imm);
    return MCOp.isBareSymbolRef();
  }];
  let OperandType = "OPERAND_PCREL";
}

def simm32 : Operand<i32>, ImmLeaf<i32, [{ return true; }]> {
  let ParserMatchClass = SImmAsmOperand<32>;
  let EncoderMethod = "getSImm32OpValue";
  let DecoderMethod = "decodeSImmOperand<32>";
  let MCOperandPredicate = [{
    int64_t Imm;
    if (MCOp.evaluateAsConstantImm(Imm))
      return isInt<32>(Imm);
    return MCOp.isBareSymbolRef();
  }];
  let OperandType = "OPERAND_SIMM32";
  let OperandNamespace = "RISC_VI_VIIOp";
}

//===----------------------------------------------------------------------===//
// RISC_VI_VII Instructions
//===----------------------------------------------------------------------===//

// Unconditional direct branch
let isBarrier = 1, isBranch = 1, isTerminator = 1, r1 = 0, r2 = 0 in
def B : RISC_VI_VIIInst<0xB0, (outs), (ins btarget32:$r3_imm), "B $r3_imm",
                [(br bb:$r3_imm)]>;

// Conditional branch: branch to target if $r1 != 0
let isBranch = 1, isTerminator = 1, r2 = 0 in
def BR_COND : RISC_VI_VIIInst<0x21, (outs), (ins GPR:$r1, btarget32:$r3_imm),
                      "BR_COND $r1 $r3_imm",
                      [(risc_vi_vii_brcc GPR:$r1, bb:$r3_imm)]>;

// Indirect branch (to register)
let hasSideEffects = 0, mayLoad = 0, mayStore = 0, isCall = 1, isBranch = 1, isTerminator = 1, r2 = 0, r3_imm = 0 in
def BR : RISC_VI_VIIInst<0x52, (outs), (ins GPR:$r1), "BR $r1",
                  [(brind GPR:$r1)]>;

let isBarrier = 1, isReturn = 1, isTerminator = 1 in
def PseudoRET : RISC_VI_VIIPseudoInst<(outs), (ins), "# PseudoRET",
                [(risc_vi_vii_ret)]>,
                PseudoInstExpansion<(BR BRR_BRR_PATAPIM)>;

// addi
let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in
def ADDi : RISC_VI_VIIInst<0x40, (outs GPR:$r1), (ins GPR:$r2, simm32:$r3_imm),
           "ADDi $r1 $r2 $r3_imm",
           [(set GPR:$r1, (add GPR:$r2, simm32:$r3_imm))]>;

// sremi
let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in
def SREMi : RISC_VI_VIIInst<0x50, (outs GPR:$r1), (ins GPR:$r2, simm32:$r3_imm),
           "SREMi $r1 $r2 $r3_imm",
           [(set GPR:$r1, (srem GPR:$r2, simm32:$r3_imm))]>;

// andi
let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in
def ANDi : RISC_VI_VIIInst<0x60, (outs GPR:$r1), (ins GPR:$r2, simm32:$r3_imm),
           "ANDi $r1 $r2 $r3_imm",
           [(set GPR:$r1, (and GPR:$r2, simm32:$r3_imm))]>;

// movi
let isAsCheapAsAMove = 1, isCodeGenOnly = 1, isReMaterializable = 1, r2 = 0 in
def MOVI : RISC_VI_VIIInst<0x67, (outs GPR:$r1), (ins simm32:$r3_imm),
                     "MOVi $r1 $r3_imm",
                     [(set GPR:$r1, simm32:$r3_imm)]>;

// mov
let isAsCheapAsAMove = 1, isCodeGenOnly = 1, isReMaterializable = 1, r3_imm = 0 in
def MOV : RISC_VI_VIIInst<0x66, (outs GPR:$r1), (ins GPR:$r2),
          "MOV $r1 $r2",
          []>;

let Constraints = "$r2 = $rs_out", hasSideEffects = 1, mayLoad = 0, mayStore = 0 in
def INC_EQ : RISC_VI_VIIInst<0x90, (outs GPR:$r1, GPR:$rs_out), (ins GPR:$r2, simm32:$r3_imm), "INC_EQ $r1 $r2 $r3_imm", []>;

let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in
def ADD : RISC_VI_VIIInst<0x41, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3_imm),
    "ADD $r1 $r2 $r3_imm",
    [(set GPR:$r1, (add GPR:$r2, GPR:$r3_imm))]>;

let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in
def MUL : RISC_VI_VIIInst<0x42, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3_imm),
    "MUL $r1 $r2 $r3_imm",
    [(set GPR:$r1, (mul GPR:$r2, GPR:$r3_imm))]>;

let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in
def SHL : RISC_VI_VIIInst<0x43, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3_imm),
    "SHL $r1 $r2 $r3_imm",
    [(set GPR:$r1, (shl GPR:$r2, GPR:$r3_imm))]>;

let mayLoad = 1, hasSideEffects = 0 in
def LW : RISC_VI_VIIInst<0x10, (outs GPR:$r1), (ins GPR:$r2, simm32:$r3_imm),
    "LW $r1 $r2 $r3_imm",
    [(set GPR:$r1, (load (add GPR:$r2, simm32:$r3_imm)))]>;

let mayStore = 1, hasSideEffects = 0 in
def SW : RISC_VI_VIIInst<0x11, (outs), (ins GPR:$r1, GPR:$r2, simm32:$r3_imm),
    "SW $r1 $r2 $r3_imm",
    [(store (i32 GPR:$r1), (add GPR:$r2, simm32:$r3_imm))]>;

def : Pat<(i32 (load GPR:$r2)), (LW GPR:$r2, 0)>;
def : Pat<(store (i32 GPR:$r1), GPR:$r2), (SW GPR:$r1, GPR:$r2, 0)>;

// flush
let r1 = 0, r2 = 0, r3_imm = 0 in
def SCREEN_FLUSH : RISC_VI_VIIInst<0xFF, (outs), (ins), "SCREEN_FLUSH", [(int_riscvivii_flush)]>;

// putpixel
def SCREEN_PUT_PIXEL : RISC_VI_VIIInst<0xEE, (outs), (ins GPR:$r1, GPR:$r2, GPR:$r3_imm),
                      "SCREEN_PUT_PIXEL $r1 $r2 $r3_imm", [(int_riscvivii_putpixel GPR:$r1, GPR:$r2, GPR:$r3_imm)]>;

//===----------------------------------------------------------------------===//
// Comparison instructions produce 0 or 1 in destination register
//===----------------------------------------------------------------------===//

let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in {

// Signed comparisons (reg-reg)
def CMP_EQ  : RISC_VI_VIIInst<0x30, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3_imm),
                "CMP_EQ $r1 $r2 $r3_imm",
                [(set GPR:$r1, (seteq  GPR:$r2, GPR:$r3_imm))]>;
def CMP_NE  : RISC_VI_VIIInst<0x31, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3_imm),
                "CMP_NE $r1 $r2 $r3_imm",
                [(set GPR:$r1, (setne  GPR:$r2, GPR:$r3_imm))]>;
def CMP_LT  : RISC_VI_VIIInst<0x32, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3_imm),
                "CMP_LT $r1 $r2 $r3_imm",
                [(set GPR:$r1, (setlt  GPR:$r2, GPR:$r3_imm))]>;
def CMP_GT  : RISC_VI_VIIInst<0x33, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3_imm),
                "CMP_GT $r1 $r2 $r3_imm",
                [(set GPR:$r1, (setgt  GPR:$r2, GPR:$r3_imm))]>;
def CMP_LE  : RISC_VI_VIIInst<0x34, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3_imm),
                "CMP_LE $r1 $r2 $r3_imm",
                [(set GPR:$r1, (setle  GPR:$r2, GPR:$r3_imm))]>;
def CMP_GE  : RISC_VI_VIIInst<0x35, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3_imm),
                "CMP_GE $r1 $r2 $r3_imm",
                [(set GPR:$r1, (setge  GPR:$r2, GPR:$r3_imm))]>;

// Unsigned comparisons (reg-reg)
def CMP_ULT : RISC_VI_VIIInst<0x36, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3_imm),
                "CMP_ULT $r1 $r2 $r3_imm",
                [(set GPR:$r1, (setult GPR:$r2, GPR:$r3_imm))]>;
def CMP_UGT : RISC_VI_VIIInst<0x37, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3_imm),
                "CMP_UGT $r1 $r2 $r3_imm",
                [(set GPR:$r1, (setugt GPR:$r2, GPR:$r3_imm))]>;
def CMP_ULE : RISC_VI_VIIInst<0x38, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3_imm),
                "CMP_ULE $r1 $r2 $r3_imm",
                [(set GPR:$r1, (setule GPR:$r2, GPR:$r3_imm))]>;
def CMP_UGE : RISC_VI_VIIInst<0x39, (outs GPR:$r1), (ins GPR:$r2, GPR:$r3_imm),
                "CMP_UGE $r1 $r2 $r3_imm",
                [(set GPR:$r1, (setuge GPR:$r2, GPR:$r3_imm))]>;

} // hasSideEffects = 0
