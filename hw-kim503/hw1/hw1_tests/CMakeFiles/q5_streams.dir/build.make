# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/cs104/cs104/hw-kim503/hw1/hw1_tests

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cs104/cs104/hw-kim503/hw1/hw1_tests

# Include any dependencies generated for this target.
include CMakeFiles/q5_streams.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/q5_streams.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/q5_streams.dir/flags.make

CMakeFiles/q5_streams.dir/home/cs104/cs104/hw-kim503/hw1/hw1q5.cpp.o: CMakeFiles/q5_streams.dir/flags.make
CMakeFiles/q5_streams.dir/home/cs104/cs104/hw-kim503/hw1/hw1q5.cpp.o: /home/cs104/cs104/hw-kim503/hw1/hw1q5.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cs104/cs104/hw-kim503/hw1/hw1_tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/q5_streams.dir/home/cs104/cs104/hw-kim503/hw1/hw1q5.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/q5_streams.dir/home/cs104/cs104/hw-kim503/hw1/hw1q5.cpp.o -c /home/cs104/cs104/hw-kim503/hw1/hw1q5.cpp

CMakeFiles/q5_streams.dir/home/cs104/cs104/hw-kim503/hw1/hw1q5.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/q5_streams.dir/home/cs104/cs104/hw-kim503/hw1/hw1q5.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cs104/cs104/hw-kim503/hw1/hw1q5.cpp > CMakeFiles/q5_streams.dir/home/cs104/cs104/hw-kim503/hw1/hw1q5.cpp.i

CMakeFiles/q5_streams.dir/home/cs104/cs104/hw-kim503/hw1/hw1q5.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/q5_streams.dir/home/cs104/cs104/hw-kim503/hw1/hw1q5.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cs104/cs104/hw-kim503/hw1/hw1q5.cpp -o CMakeFiles/q5_streams.dir/home/cs104/cs104/hw-kim503/hw1/hw1q5.cpp.s

CMakeFiles/q5_streams.dir/home/cs104/cs104/hw-kim503/hw1/hw1q5.cpp.o.requires:

.PHONY : CMakeFiles/q5_streams.dir/home/cs104/cs104/hw-kim503/hw1/hw1q5.cpp.o.requires

CMakeFiles/q5_streams.dir/home/cs104/cs104/hw-kim503/hw1/hw1q5.cpp.o.provides: CMakeFiles/q5_streams.dir/home/cs104/cs104/hw-kim503/hw1/hw1q5.cpp.o.requires
	$(MAKE) -f CMakeFiles/q5_streams.dir/build.make CMakeFiles/q5_streams.dir/home/cs104/cs104/hw-kim503/hw1/hw1q5.cpp.o.provides.build
.PHONY : CMakeFiles/q5_streams.dir/home/cs104/cs104/hw-kim503/hw1/hw1q5.cpp.o.provides

CMakeFiles/q5_streams.dir/home/cs104/cs104/hw-kim503/hw1/hw1q5.cpp.o.provides.build: CMakeFiles/q5_streams.dir/home/cs104/cs104/hw-kim503/hw1/hw1q5.cpp.o


# Object files for target q5_streams
q5_streams_OBJECTS = \
"CMakeFiles/q5_streams.dir/home/cs104/cs104/hw-kim503/hw1/hw1q5.cpp.o"

# External object files for target q5_streams
q5_streams_EXTERNAL_OBJECTS =

q5_streams: CMakeFiles/q5_streams.dir/home/cs104/cs104/hw-kim503/hw1/hw1q5.cpp.o
q5_streams: CMakeFiles/q5_streams.dir/build.make
q5_streams: CMakeFiles/q5_streams.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cs104/cs104/hw-kim503/hw1/hw1_tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable q5_streams"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/q5_streams.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/q5_streams.dir/build: q5_streams

.PHONY : CMakeFiles/q5_streams.dir/build

CMakeFiles/q5_streams.dir/requires: CMakeFiles/q5_streams.dir/home/cs104/cs104/hw-kim503/hw1/hw1q5.cpp.o.requires

.PHONY : CMakeFiles/q5_streams.dir/requires

CMakeFiles/q5_streams.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/q5_streams.dir/cmake_clean.cmake
.PHONY : CMakeFiles/q5_streams.dir/clean

CMakeFiles/q5_streams.dir/depend:
	cd /home/cs104/cs104/hw-kim503/hw1/hw1_tests && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cs104/cs104/hw-kim503/hw1/hw1_tests /home/cs104/cs104/hw-kim503/hw1/hw1_tests /home/cs104/cs104/hw-kim503/hw1/hw1_tests /home/cs104/cs104/hw-kim503/hw1/hw1_tests /home/cs104/cs104/hw-kim503/hw1/hw1_tests/CMakeFiles/q5_streams.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/q5_streams.dir/depend
