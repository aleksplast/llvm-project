#include "RISC_VI_VII.h"
#include "clang/Basic/Builtins.h"
#include "clang/Basic/MacroBuilder.h"

using namespace clang;
using namespace clang::targets;

void RISC_VI_VIITargetInfo::getTargetDefines(const LangOptions &Opts,
                                     MacroBuilder &Builder) const {
  Builder.defineMacro("__riscvivii__");
}

ArrayRef<Builtin::Info> RISC_VI_VIITargetInfo::getTargetBuiltins() const {
  return std::nullopt;
}
