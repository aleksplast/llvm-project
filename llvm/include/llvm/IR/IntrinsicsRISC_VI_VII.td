let TargetPrefix = "riscvivii" in {  // All intrinsics start with "llvm.riscvivii.".

 def int_riscvivii_putpixel: ClangBuiltin<"screenPutPixel">,
   Intrinsic<[], [llvm_i32_ty, llvm_i32_ty, llvm_i32_ty], [IntrNoMem, IntrHasSideEffects]>;

 def int_riscvivii_flush: ClangBuiltin<"screenFlush">,
   Intrinsic<[], [], [IntrNoMem, IntrHasSideEffects]>;

 def int_riscvivii_simrand: ClangBuiltin<"simRand">,
   Intrinsic<[], [llvm_i32_ty], [IntrNoMem, IntrHasSideEffects]>;

 } // TargetPrefix = "riscvivii"
