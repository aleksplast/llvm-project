//===----------------------------------------------------------------------===//
// RISC_VI_VII profiles and nodes
//===----------------------------------------------------------------------===//

def risc_vi_vii_ret      : SDNode<"RISC_VI_VIIISD::RET", SDTNone,
                            [SDNPHasChain, SDNPOptInGlue, SDNPVariadic]>;

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

def simm16 : Operand<i32>, ImmLeaf<i32, [{return isInt<16>(Imm);}]> {
  let ParserMatchClass = SImmAsmOperand<16>;
  let EncoderMethod = "getSImm16OpValue";
  let DecoderMethod = "decodeSImmOperand<16>";
  let MCOperandPredicate = [{
    int64_t Imm;
    if (MCOp.evaluateAsConstantImm(Imm))
      return isInt<16>(Imm);
    return MCOp.isBareSymbolRef();
  }];
  let OperandType = "OPERAND_SIMM16";
  let OperandNamespace = "RISC_VI_VIIOp";
}

//===----------------------------------------------------------------------===//
// RISC_VI_VII Instructions
//===----------------------------------------------------------------------===//

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, isCall = 1, isBranch = 1, isTerminator = 1, r2 = 0, r3_imm = 0 in
def BR : RISC_VI_VIIInst<0x52, (outs), (ins GPR:$r1), "BR $r1",
                  [(brind GPR:$r1)]>;

let isBarrier = 1, isReturn = 1, isTerminator = 1 in
def PseudoRET : RISC_VI_VIIPseudoInst<(outs), (ins), "# PseudoRET",
                [(risc_vi_vii_ret)]>,
                PseudoInstExpansion<(BR TUNG_TUNG_TUNG_SAHUR)>;

// movli
let isAsCheapAsAMove = 1, isCodeGenOnly = 1, isReMaterializable = 1, r2 = 0 in
def MOVI : RISC_VI_VIIInst<0x67, (outs GPR:$r1), (ins simm16:$r3_imm),
                     "MOVi $r1 $r3_imm",
                     [(set GPR:$r1, simm16:$r3_imm)]>;

// flush
let r1 = 0, r2 = 0, r3_imm = 0 in
def SCREEN_FLUSH : RISC_VI_VIIInst<0xFF, (outs), (ins), "FLUSH", [(int_riscvivii_flush)]>;

// putpixel
def SCREEN_PUT_PIXEL : RISC_VI_VIIInst<0xEE, (outs), (ins GPR:$r1, GPR:$r2, GPR:$r3_imm),
                      "SCREEN_PUT_PIXEL $r1 $r2 $r3_imm", [(int_riscvivii_putpixel GPR:$r1, GPR:$r2, GPR:$r3_imm)]>;

// simrand
let r2 = 0, r3_imm = 0 in
def SIM_RAND : RISC_VI_VIIInst<0xDD, (outs), (ins GPR:$r1),
                      "SIM_RAND $r1", [(int_riscvivii_simrand GPR:$r1)]>;
