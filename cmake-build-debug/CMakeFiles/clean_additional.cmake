# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/TuringMachineEmulator_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/TuringMachineEmulator_autogen.dir/ParseCache.txt"
  "TuringMachineEmulator_autogen"
  )
endif()
