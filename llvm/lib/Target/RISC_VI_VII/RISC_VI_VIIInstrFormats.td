//===----------------------------------------------------------------------===//
//  Describe RISC_VI_VII instructions format
//
//  CPU INSTRUCTION FORMATS (64-bit)
//
//  [63:56] opcode  [55:52] r1  [51:48] r2  [47:32] padding  [31:0] r3/imm
//
//===----------------------------------------------------------------------===//

// Generic RISC_VI_VII Format
class RISC_VI_VIIInst<bits<8> op, dag outs, dag ins, string asmstr, list<dag> pattern>: Instruction
{
  // Inst and Size: for tablegen(... -gen-emitter) and
  // tablegen(... -gen-disassembler) in CMakeLists.txt
  let Namespace = "RISC_VI_VII";
  let DecoderNamespace = "RISC_VI_VII";
  let Size = 8;

  field bits<64> Inst;

  bits<8>  Opcode = op;
  bits<4>  r1;
  bits<4>  r2;
  bits<32> r3_imm = 0;

  let Inst{63-56} = Opcode;
  let Inst{55-52} = r1;
  let Inst{51-48} = r2;
  let Inst{47-32} = 0;
  let Inst{31-0}  = 0;  // Subclasses override this for their operand types

  let OutOperandList = outs;
  let InOperandList  = ins;
  let AsmString   = asmstr;
  let Pattern     = pattern;
}

// R-type: third operand is a register (4-bit encoding in bits 3:0)
class RISC_VI_VIIInstR<bits<8> op, dag outs, dag ins, string asmstr, list<dag> pattern>
    : RISC_VI_VIIInst<op, outs, ins, asmstr, pattern> {
  bits<4> r3_reg;
  let Inst{3-0} = r3_reg;
}

// I-type: third operand is a 32-bit signed immediate
class RISC_VI_VIIInstI<bits<8> op, dag outs, dag ins, string asmstr, list<dag> pattern>
    : RISC_VI_VIIInst<op, outs, ins, asmstr, pattern> {
  bits<32> imm32;
  let Inst{31-0} = imm32;
}

// B-type: third operand is a 32-bit branch/call target
class RISC_VI_VIIInstB<bits<8> op, dag outs, dag ins, string asmstr, list<dag> pattern>
    : RISC_VI_VIIInst<op, outs, ins, asmstr, pattern> {
  bits<32> btarget;
  let Inst{31-0} = btarget;
}

// Pseudo instructions format
class RISC_VI_VIIPseudoInst<dag outs, dag ins, string asmstr, list<dag> pattern>
   : RISC_VI_VIIInst<0, outs, ins, asmstr, pattern> {
  let isPseudo = 1;
  let isCodeGenOnly = 1;
}
