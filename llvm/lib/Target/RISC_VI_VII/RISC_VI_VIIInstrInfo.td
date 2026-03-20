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
  let EncoderMethod = "getImmOpValue";
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

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, isCall = 1, isBranch = 1, isTerminator = 1 in
def BR : RISC_VI_VIIInst<0x0, (outs), (ins GPR:$rs1), "BR $rs1",
                  [(brind GPR:$rs1)]>;

let isBarrier = 1, isReturn = 1, isTerminator = 1 in
def PseudoRET : RISC_VI_VIIPseudoInst<(outs), (ins), "# PseudoRET",
                [(risc_vi_vii_ret)]>,
                PseudoInstExpansion<(BR SIX7)>;

// movli
let isAsCheapAsAMove = 1, isCodeGenOnly = 1, isReMaterializable = 1 in
def MOVLI : RISC_VI_VIIInst<0x0, (outs GPR:$rd), (ins simm16:$imm),
                     "MOVli $rd $imm",
                     [(set GPR:$rd, simm16:$imm)]>;
