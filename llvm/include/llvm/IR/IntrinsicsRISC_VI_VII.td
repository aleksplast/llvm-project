let TargetPrefix = "riscvivii" in {  // All intrinsics start with "llvm.riscvivii.".

 def int_riscvivii_putpixel:
   Intrinsic<[], [llvm_i32_ty, llvm_i32_ty, llvm_i32_ty], [IntrNoMem, IntrHasSideEffects]>;

 def int_riscvivii_flush:
   Intrinsic<[], [], [IntrNoMem, IntrHasSideEffects]>;

 def int_riscvivii_simrand:
   Intrinsic<[], [llvm_i32_ty], [IntrNoMem, IntrHasSideEffects]>;

 } // TargetPrefix = "riscvivii"
