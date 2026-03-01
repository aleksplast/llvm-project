add_llvm_component_library(LLVMRISC_VI_VIIInfo
  RISC_VI_VIITargetInfo.cpp

  LINK_COMPONENTS
  MC
  Support

  ADD_TO_COMPONENT
  RISC_VI_VII
  )
