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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dev/app/cpp_basic

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dev/app/cpp_basic/build

# Include any dependencies generated for this target.
include timer/CMakeFiles/pulse.dir/depend.make

# Include the progress variables for this target.
include timer/CMakeFiles/pulse.dir/progress.make

# Include the compile flags for this target's objects.
include timer/CMakeFiles/pulse.dir/flags.make

timer/CMakeFiles/pulse.dir/pulse.cpp.o: timer/CMakeFiles/pulse.dir/flags.make
timer/CMakeFiles/pulse.dir/pulse.cpp.o: ../timer/pulse.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dev/app/cpp_basic/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object timer/CMakeFiles/pulse.dir/pulse.cpp.o"
	cd /home/dev/app/cpp_basic/build/timer && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pulse.dir/pulse.cpp.o -c /home/dev/app/cpp_basic/timer/pulse.cpp

timer/CMakeFiles/pulse.dir/pulse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pulse.dir/pulse.cpp.i"
	cd /home/dev/app/cpp_basic/build/timer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dev/app/cpp_basic/timer/pulse.cpp > CMakeFiles/pulse.dir/pulse.cpp.i

timer/CMakeFiles/pulse.dir/pulse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pulse.dir/pulse.cpp.s"
	cd /home/dev/app/cpp_basic/build/timer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dev/app/cpp_basic/timer/pulse.cpp -o CMakeFiles/pulse.dir/pulse.cpp.s

# Object files for target pulse
pulse_OBJECTS = \
"CMakeFiles/pulse.dir/pulse.cpp.o"

# External object files for target pulse
pulse_EXTERNAL_OBJECTS =

timer/pulse: timer/CMakeFiles/pulse.dir/pulse.cpp.o
timer/pulse: timer/CMakeFiles/pulse.dir/build.make
timer/pulse: timer/CMakeFiles/pulse.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dev/app/cpp_basic/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable pulse"
	cd /home/dev/app/cpp_basic/build/timer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pulse.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
timer/CMakeFiles/pulse.dir/build: timer/pulse

.PHONY : timer/CMakeFiles/pulse.dir/build

timer/CMakeFiles/pulse.dir/clean:
	cd /home/dev/app/cpp_basic/build/timer && $(CMAKE_COMMAND) -P CMakeFiles/pulse.dir/cmake_clean.cmake
.PHONY : timer/CMakeFiles/pulse.dir/clean

timer/CMakeFiles/pulse.dir/depend:
	cd /home/dev/app/cpp_basic/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dev/app/cpp_basic /home/dev/app/cpp_basic/timer /home/dev/app/cpp_basic/build /home/dev/app/cpp_basic/build/timer /home/dev/app/cpp_basic/build/timer/CMakeFiles/pulse.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : timer/CMakeFiles/pulse.dir/depend
