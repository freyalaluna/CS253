# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /s/bach/n/under/fturner/cs253/HW2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /s/bach/n/under/fturner/cs253/HW2

# Utility rule file for hw2.tar.

# Include any custom commands dependencies for this target.
include CMakeFiles/hw2.tar.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/hw2.tar.dir/progress.make

CMakeFiles/hw2.tar:
	tar -cf hw2.tar *.cc *.h CMakeLists.txt

hw2.tar: CMakeFiles/hw2.tar
hw2.tar: CMakeFiles/hw2.tar.dir/build.make
.PHONY : hw2.tar

# Rule to build all files generated by this target.
CMakeFiles/hw2.tar.dir/build: hw2.tar
.PHONY : CMakeFiles/hw2.tar.dir/build

CMakeFiles/hw2.tar.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hw2.tar.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hw2.tar.dir/clean

CMakeFiles/hw2.tar.dir/depend:
	cd /s/bach/n/under/fturner/cs253/HW2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /s/bach/n/under/fturner/cs253/HW2 /s/bach/n/under/fturner/cs253/HW2 /s/bach/n/under/fturner/cs253/HW2 /s/bach/n/under/fturner/cs253/HW2 /s/bach/n/under/fturner/cs253/HW2/CMakeFiles/hw2.tar.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hw2.tar.dir/depend

