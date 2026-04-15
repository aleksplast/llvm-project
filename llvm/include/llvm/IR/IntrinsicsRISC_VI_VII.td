let TargetPrefix = "riscvivii" in {  // All intrinsics start with "llvm.riscvivii.".

 def int_riscvivii_putpixel: ClangBuiltin<"screen_put_pixel">,
   Intrinsic<[], [llvm_i32_ty, llvm_i32_ty, llvm_i32_ty], [IntrNoMem, IntrHasSideEffects]>;

 def int_riscvivii_flush: ClangBuiltin<"screen_flush">,
   Intrinsic<[], [], [IntrNoMem, IntrHasSideEffects]>;

 } // TargetPrefix = "riscvivii"
