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
CMAKE_SOURCE_DIR = /Users/junsi/Desktop/VE281/project/p4/proj4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/junsi/Desktop/VE281/project/p4/proj4/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/proj4.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/proj4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/proj4.dir/flags.make

CMakeFiles/proj4.dir/main.cpp.o: CMakeFiles/proj4.dir/flags.make
CMakeFiles/proj4.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/junsi/Desktop/VE281/project/p4/proj4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/proj4.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/proj4.dir/main.cpp.o -c /Users/junsi/Desktop/VE281/project/p4/proj4/main.cpp

CMakeFiles/proj4.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proj4.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/junsi/Desktop/VE281/project/p4/proj4/main.cpp > CMakeFiles/proj4.dir/main.cpp.i

CMakeFiles/proj4.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proj4.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/junsi/Desktop/VE281/project/p4/proj4/main.cpp -o CMakeFiles/proj4.dir/main.cpp.s

# Object files for target proj4
proj4_OBJECTS = \
"CMakeFiles/proj4.dir/main.cpp.o"

# External object files for target proj4
proj4_EXTERNAL_OBJECTS =

proj4: CMakeFiles/proj4.dir/main.cpp.o
proj4: CMakeFiles/proj4.dir/build.make
proj4: CMakeFiles/proj4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/junsi/Desktop/VE281/project/p4/proj4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable proj4"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/proj4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/proj4.dir/build: proj4

.PHONY : CMakeFiles/proj4.dir/build

CMakeFiles/proj4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/proj4.dir/cmake_clean.cmake
.PHONY : CMakeFiles/proj4.dir/clean

CMakeFiles/proj4.dir/depend:
	cd /Users/junsi/Desktop/VE281/project/p4/proj4/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/junsi/Desktop/VE281/project/p4/proj4 /Users/junsi/Desktop/VE281/project/p4/proj4 /Users/junsi/Desktop/VE281/project/p4/proj4/cmake-build-debug /Users/junsi/Desktop/VE281/project/p4/proj4/cmake-build-debug /Users/junsi/Desktop/VE281/project/p4/proj4/cmake-build-debug/CMakeFiles/proj4.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/proj4.dir/depend

