# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/junsi/Desktop/VE281/project/p1/proj1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/junsi/Desktop/VE281/project/p1/proj1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/proj1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/proj1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/proj1.dir/flags.make

CMakeFiles/proj1.dir/main.cpp.o: CMakeFiles/proj1.dir/flags.make
CMakeFiles/proj1.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/junsi/Desktop/VE281/project/p1/proj1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/proj1.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/proj1.dir/main.cpp.o -c /Users/junsi/Desktop/VE281/project/p1/proj1/main.cpp

CMakeFiles/proj1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proj1.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/junsi/Desktop/VE281/project/p1/proj1/main.cpp > CMakeFiles/proj1.dir/main.cpp.i

CMakeFiles/proj1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proj1.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/junsi/Desktop/VE281/project/p1/proj1/main.cpp -o CMakeFiles/proj1.dir/main.cpp.s

# Object files for target proj1
proj1_OBJECTS = \
"CMakeFiles/proj1.dir/main.cpp.o"

# External object files for target proj1
proj1_EXTERNAL_OBJECTS =

proj1: CMakeFiles/proj1.dir/main.cpp.o
proj1: CMakeFiles/proj1.dir/build.make
proj1: CMakeFiles/proj1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/junsi/Desktop/VE281/project/p1/proj1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable proj1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/proj1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/proj1.dir/build: proj1

.PHONY : CMakeFiles/proj1.dir/build

CMakeFiles/proj1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/proj1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/proj1.dir/clean

CMakeFiles/proj1.dir/depend:
	cd /Users/junsi/Desktop/VE281/project/p1/proj1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/junsi/Desktop/VE281/project/p1/proj1 /Users/junsi/Desktop/VE281/project/p1/proj1 /Users/junsi/Desktop/VE281/project/p1/proj1/cmake-build-debug /Users/junsi/Desktop/VE281/project/p1/proj1/cmake-build-debug /Users/junsi/Desktop/VE281/project/p1/proj1/cmake-build-debug/CMakeFiles/proj1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/proj1.dir/depend

