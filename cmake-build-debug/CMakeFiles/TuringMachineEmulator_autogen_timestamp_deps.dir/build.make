# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/lev/.local/share/JetBrains/Toolbox/apps/clion-nova/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /home/lev/.local/share/JetBrains/Toolbox/apps/clion-nova/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lev/CLionProjects/TuringMachineEmulator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lev/CLionProjects/TuringMachineEmulator/cmake-build-debug

# Utility rule file for TuringMachineEmulator_autogen_timestamp_deps.

# Include any custom commands dependencies for this target.
include CMakeFiles/TuringMachineEmulator_autogen_timestamp_deps.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/TuringMachineEmulator_autogen_timestamp_deps.dir/progress.make

CMakeFiles/TuringMachineEmulator_autogen_timestamp_deps: /usr/lib/qt6/moc
CMakeFiles/TuringMachineEmulator_autogen_timestamp_deps: /usr/lib/qt6/uic
CMakeFiles/TuringMachineEmulator_autogen_timestamp_deps: /usr/lib/libQt6Widgets.so.6.6.2

TuringMachineEmulator_autogen_timestamp_deps: CMakeFiles/TuringMachineEmulator_autogen_timestamp_deps
TuringMachineEmulator_autogen_timestamp_deps: CMakeFiles/TuringMachineEmulator_autogen_timestamp_deps.dir/build.make
.PHONY : TuringMachineEmulator_autogen_timestamp_deps

# Rule to build all files generated by this target.
CMakeFiles/TuringMachineEmulator_autogen_timestamp_deps.dir/build: TuringMachineEmulator_autogen_timestamp_deps
.PHONY : CMakeFiles/TuringMachineEmulator_autogen_timestamp_deps.dir/build

CMakeFiles/TuringMachineEmulator_autogen_timestamp_deps.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TuringMachineEmulator_autogen_timestamp_deps.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TuringMachineEmulator_autogen_timestamp_deps.dir/clean

CMakeFiles/TuringMachineEmulator_autogen_timestamp_deps.dir/depend:
	cd /home/lev/CLionProjects/TuringMachineEmulator/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lev/CLionProjects/TuringMachineEmulator /home/lev/CLionProjects/TuringMachineEmulator /home/lev/CLionProjects/TuringMachineEmulator/cmake-build-debug /home/lev/CLionProjects/TuringMachineEmulator/cmake-build-debug /home/lev/CLionProjects/TuringMachineEmulator/cmake-build-debug/CMakeFiles/TuringMachineEmulator_autogen_timestamp_deps.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/TuringMachineEmulator_autogen_timestamp_deps.dir/depend

