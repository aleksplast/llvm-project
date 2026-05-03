//===----------------------------------------------------------------------===//
//  Describe RISC_VI_VII instructions format
//
//  CPU INSTRUCTION FORMATS (64-bit)
//
//  [63:56] opcode  [55:52] r1  [51:48] r2  [47:32] padding  [31:0] r3_imm
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
  let Inst{31-0}  = r3_imm;

  let OutOperandList = outs;
  let InOperandList  = ins;
  let AsmString   = asmstr;
  let Pattern     = pattern;
}

// Pseudo instructions format
class RISC_VI_VIIPseudoInst<dag outs, dag ins, string asmstr, list<dag> pattern>
   : RISC_VI_VIIInst<0, outs, ins, asmstr, pattern> {
  let isPseudo = 1;
  let isCodeGenOnly = 1;
}
