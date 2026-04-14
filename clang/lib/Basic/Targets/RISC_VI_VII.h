#ifndef LLVM_CLANG_LIB_BASIC_TARGETS_RISC_VI_VII_H
#define LLVM_CLANG_LIB_BASIC_TARGETS_RISC_VI_VII_H
#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/TargetOptions.h"
#include "llvm/Support/Compiler.h"
#include "llvm/TargetParser/Triple.h"
namespace clang {
namespace targets {

class LLVM_LIBRARY_VISIBILITY RISC_VI_VIITargetInfo : public TargetInfo {
public:
  RISC_VI_VIITargetInfo(const llvm::Triple &Triple, const TargetOptions &Opts)
      : TargetInfo(Triple) {
    NoAsmVariants = true;
    LongLongAlign = 32;
    SuitableAlign = 32;
    DoubleAlign = LongDoubleAlign = 32;
    SizeType = UnsignedInt;
    PtrDiffType = SignedInt;
    IntPtrType = SignedInt;
    WCharType = UnsignedChar;
    WIntType = UnsignedInt;
    resetDataLayout("e-m:e-p:32:32-i8:8:32-i16:16:32-i64:64-n32");
  }

  void getTargetDefines(const LangOptions &Opts,
                        MacroBuilder &Builder) const override;

  ArrayRef<Builtin::Info> getTargetBuiltins() const override;

  BuiltinVaListKind getBuiltinVaListKind() const override {
    return TargetInfo::VoidPtrBuiltinVaList;
  }

  std::string_view getClobbers() const override { return ""; }

  ArrayRef<const char *> getGCCRegNames() const override {
    static const char *const GCCRegNames[] = {
        "TRALALERO_TRALALA", "BOMBARDIRO_CROCODILO", "TUNG_TUNG_TUNG_SAHUR", "BALLERINA_CAPPUCCINA", "CAPPUCINO_ASSASINO",
        "BOMBOMBINI_GUSINI", "LIRILI_LARILA", "FRIGO_CAMELO", "BONECA_AMBALABU", "BRR_BRR_PATAPIM", "TRIPPI_TROPPI",
        "TROPPA_TRIPPA", "CHIMPANZINI_BANANINI", "BOBRITO_BANDITO", "LA_VACA_SATURNA_SATURNITA", "TRULIMERA_TRULICINA"};
    return llvm::ArrayRef(GCCRegNames);
  }

  ArrayRef<TargetInfo::GCCRegAlias> getGCCRegAliases() const override {
    return std::nullopt;
  }

  bool validateAsmConstraint(const char *&Name,
                             TargetInfo::ConstraintInfo &Info) const override {
    return false;
  }
};
} // namespace targets
} // namespace clang
#endif // LLVM_CLANG_LIB_BASIC_TARGETS_RISC_VI_VII_H
