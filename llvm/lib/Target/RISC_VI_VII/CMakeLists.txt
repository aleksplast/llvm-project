add_llvm_component_group(RISC_VI_VII)

set(LLVM_TARGET_DEFINITIONS RISC_VI_VII.td)

tablegen(LLVM RISC_VI_VIIGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM RISC_VI_VIIGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM RISC_VI_VIIGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM RISC_VI_VIIGenMCPseudoLowering.inc -gen-pseudo-lowering)
tablegen(LLVM RISC_VI_VIIGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM RISC_VI_VIIGenCallingConv.inc -gen-callingconv)
tablegen(LLVM RISC_VI_VIIGenAsmWriter.inc -gen-asm-writer)

add_public_tablegen_target(RISC_VI_VIICommonTableGen)

add_llvm_target(RISC_VI_VIICodeGen
  RISC_VI_VIITargetMachine.cpp
  RISC_VI_VIIRegisterInfo.cpp
  RISC_VI_VIIInstrInfo.cpp
  RISC_VI_VIISubtarget.cpp
  RISC_VI_VIIAsmPrinter.cpp
  RISC_VI_VIIISelDagToDag.cpp
  RISC_VI_VIIISelLowering.cpp
  RISC_VI_VIIMCInstLower.cpp

  LINK_COMPONENTS
  CodeGen
  Core
  Support
  Target
  RISC_VI_VIIInfo
  AsmPrinter
  SelectionDAG

  ADD_TO_COMPONENT
  RISC_VI_VII
  )

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
