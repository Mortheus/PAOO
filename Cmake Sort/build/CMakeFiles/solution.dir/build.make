# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /mnt/c/Drew/PAOO/PAOO

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Drew/PAOO/PAOO/build

# Include any dependencies generated for this target.
include CMakeFiles/solution.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/solution.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/solution.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/solution.dir/flags.make

CMakeFiles/solution.dir/sortare.cpp.o: CMakeFiles/solution.dir/flags.make
CMakeFiles/solution.dir/sortare.cpp.o: ../sortare.cpp
CMakeFiles/solution.dir/sortare.cpp.o: CMakeFiles/solution.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Drew/PAOO/PAOO/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/solution.dir/sortare.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/solution.dir/sortare.cpp.o -MF CMakeFiles/solution.dir/sortare.cpp.o.d -o CMakeFiles/solution.dir/sortare.cpp.o -c /mnt/c/Drew/PAOO/PAOO/sortare.cpp

CMakeFiles/solution.dir/sortare.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/solution.dir/sortare.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Drew/PAOO/PAOO/sortare.cpp > CMakeFiles/solution.dir/sortare.cpp.i

CMakeFiles/solution.dir/sortare.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/solution.dir/sortare.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Drew/PAOO/PAOO/sortare.cpp -o CMakeFiles/solution.dir/sortare.cpp.s

# Object files for target solution
solution_OBJECTS = \
"CMakeFiles/solution.dir/sortare.cpp.o"

# External object files for target solution
solution_EXTERNAL_OBJECTS =

solution: CMakeFiles/solution.dir/sortare.cpp.o
solution: CMakeFiles/solution.dir/build.make
solution: CMakeFiles/solution.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Drew/PAOO/PAOO/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable solution"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/solution.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/solution.dir/build: solution
.PHONY : CMakeFiles/solution.dir/build

CMakeFiles/solution.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/solution.dir/cmake_clean.cmake
.PHONY : CMakeFiles/solution.dir/clean

CMakeFiles/solution.dir/depend:
	cd /mnt/c/Drew/PAOO/PAOO/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Drew/PAOO/PAOO /mnt/c/Drew/PAOO/PAOO /mnt/c/Drew/PAOO/PAOO/build /mnt/c/Drew/PAOO/PAOO/build /mnt/c/Drew/PAOO/PAOO/build/CMakeFiles/solution.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/solution.dir/depend

