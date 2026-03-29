add_llvm_component_library(LLVMRISC_VI_VIIDesc
  RISC_VI_VIIMCTargetDesc.cpp
  RISC_VI_VIIMCAsmInfo.cpp
  RISC_VI_VIIInstPrinter.cpp
  RISC_VI_VIIMCCodeEmitter.cpp

  LINK_COMPONENTS
  MC
  Support
  RISC_VI_VIIInfo

  ADD_TO_COMPONENT
  RISC_VI_VII
 )
