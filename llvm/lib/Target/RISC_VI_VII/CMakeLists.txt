add_llvm_component_group(RISC_VI_VII)

set(LLVM_TARGET_DEFINITIONS RISC_VI_VII.td)

tablegen(LLVM RISC_VI_VIIGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM RISC_VI_VIIGenInstrInfo.inc -gen-instr-info)

add_public_tablegen_target(RISC_VI_VIICommonTableGen)

add_llvm_target(RISC_VI_VIICodeGen
  RISC_VI_VIITargetMachine.cpp
  RISC_VI_VIIRegisterInfo.cpp
  RISC_VI_VIIInstrInfo.cpp

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
