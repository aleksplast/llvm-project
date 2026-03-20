// RISC_VI_VII Register file declaration
class RISC_VI_VIIReg<bits<16> Enc, string n> : Register<n>{
    let HWEncoding = Enc;
    let Namespace = "RISC_VI_VII";
}

// Registers
foreach I = 0-15 in {
    def SIX#I : RISC_VI_VIIReg<I, "six"#I>;
}

// Classes
def GPR : RegisterClass<"RISC_VI_VII", [i32], 32, (add
  SIX0, SIX1, SIX2, SIX3, SIX4, SIX5, SIX6, SIX7, SIX8, SIX9, SIX10, SIX11, SIX12, SIX13, SIX14, SIX15)>;
