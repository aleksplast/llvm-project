add_llvm_component_group(RISC_VI_VII)

add_llvm_target(RISC_VI_VIICodeGen
  RISC_VI_VIITargetMachine.cpp

  LINK_COMPONENTS
  CodeGen
  Core
  Support
  Target
  RISC_VI_VIIInfo

  ADD_TO_COMPONENT
  RISC_VI_VII
  )

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
