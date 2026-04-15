//===----------------------------------------------------------------------===//
 // This describes the calling conventions for RISC_VI_VII architecture.
 //===----------------------------------------------------------------------===//

 //===----------------------------------------------------------------------===//
 // RISC_VI_VII Return Value Calling Convention
 //===----------------------------------------------------------------------===//
 def RetCC_RISC_VI_VII : CallingConv<[
   // i32 return values
   CCIfType<[i32, i64], CCAssignToReg<[TRALALERO_TRALALA, BOMBARDIRO_CROCODILO, BALLERINA_CAPPUCCINA, CAPPUCINO_ASSASINO]>>,

   // Integer values get stored in stack slots that are 4 bytes in
   // size and 4-byte aligned.
   CCIfType<[i64], CCAssignToStack<8, 4>>,
   CCIfType<[i32], CCAssignToStack<4, 4>>
 ]>;

 //===----------------------------------------------------------------------===//
 // RISC_VI_VII Argument Calling Conventions
 //===----------------------------------------------------------------------===//
 def CC_RISC_VI_VII : CallingConv<[
   // Promote i8/i16 arguments to i32.
   CCIfType<[i8, i16], CCPromoteToType<i32>>,

   // The first 4 integer arguments are passed in integer registers.
   CCIfType<[i32, i64], CCAssignToReg<[TRALALERO_TRALALA, BOMBARDIRO_CROCODILO, BALLERINA_CAPPUCCINA, CAPPUCINO_ASSASINO]>>,

   // Integer values get stored in stack slots that are 4 bytes in
   // size and 4-byte aligned.
   CCIfType<[i64], CCAssignToStack<8, 4>>,
   CCIfType<[i32], CCAssignToStack<4, 4>>
 ]>;

 def CSR_RISC_VI_VII : CalleeSavedRegs<(add BOMBOMBINI_GUSINI, LIRILI_LARILA, FRIGO_CAMELO, TUNG_TUNG_TUNG_SAHUR, BONECA_AMBALABU, TRIPPI_TROPPI, TROPPA_TRIPPA)>;
