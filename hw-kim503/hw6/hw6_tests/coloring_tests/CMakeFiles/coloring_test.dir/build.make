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
CMAKE_SOURCE_DIR = /home/cs104/cs104/hw-kim503/hw6/hw6_tests

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cs104/cs104/hw-kim503/hw6/hw6_tests

# Include any dependencies generated for this target.
include coloring_tests/CMakeFiles/coloring_test.dir/depend.make

# Include the progress variables for this target.
include coloring_tests/CMakeFiles/coloring_test.dir/progress.make

# Include the compile flags for this target's objects.
include coloring_tests/CMakeFiles/coloring_test.dir/flags.make

coloring_tests/CMakeFiles/coloring_test.dir/coloring_tests.cpp.o: coloring_tests/CMakeFiles/coloring_test.dir/flags.make
coloring_tests/CMakeFiles/coloring_test.dir/coloring_tests.cpp.o: coloring_tests/coloring_tests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cs104/cs104/hw-kim503/hw6/hw6_tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object coloring_tests/CMakeFiles/coloring_test.dir/coloring_tests.cpp.o"
	cd /home/cs104/cs104/hw-kim503/hw6/hw6_tests/coloring_tests && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/coloring_test.dir/coloring_tests.cpp.o -c /home/cs104/cs104/hw-kim503/hw6/hw6_tests/coloring_tests/coloring_tests.cpp

coloring_tests/CMakeFiles/coloring_test.dir/coloring_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/coloring_test.dir/coloring_tests.cpp.i"
	cd /home/cs104/cs104/hw-kim503/hw6/hw6_tests/coloring_tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cs104/cs104/hw-kim503/hw6/hw6_tests/coloring_tests/coloring_tests.cpp > CMakeFiles/coloring_test.dir/coloring_tests.cpp.i

coloring_tests/CMakeFiles/coloring_test.dir/coloring_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/coloring_test.dir/coloring_tests.cpp.s"
	cd /home/cs104/cs104/hw-kim503/hw6/hw6_tests/coloring_tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cs104/cs104/hw-kim503/hw6/hw6_tests/coloring_tests/coloring_tests.cpp -o CMakeFiles/coloring_test.dir/coloring_tests.cpp.s

coloring_tests/CMakeFiles/coloring_test.dir/coloring_tests.cpp.o.requires:

.PHONY : coloring_tests/CMakeFiles/coloring_test.dir/coloring_tests.cpp.o.requires

coloring_tests/CMakeFiles/coloring_test.dir/coloring_tests.cpp.o.provides: coloring_tests/CMakeFiles/coloring_test.dir/coloring_tests.cpp.o.requires
	$(MAKE) -f coloring_tests/CMakeFiles/coloring_test.dir/build.make coloring_tests/CMakeFiles/coloring_test.dir/coloring_tests.cpp.o.provides.build
.PHONY : coloring_tests/CMakeFiles/coloring_test.dir/coloring_tests.cpp.o.provides

coloring_tests/CMakeFiles/coloring_test.dir/coloring_tests.cpp.o.provides.build: coloring_tests/CMakeFiles/coloring_test.dir/coloring_tests.cpp.o


coloring_tests/CMakeFiles/coloring_test.dir/coloring_checker.cpp.o: coloring_tests/CMakeFiles/coloring_test.dir/flags.make
coloring_tests/CMakeFiles/coloring_test.dir/coloring_checker.cpp.o: coloring_tests/coloring_checker.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cs104/cs104/hw-kim503/hw6/hw6_tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object coloring_tests/CMakeFiles/coloring_test.dir/coloring_checker.cpp.o"
	cd /home/cs104/cs104/hw-kim503/hw6/hw6_tests/coloring_tests && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/coloring_test.dir/coloring_checker.cpp.o -c /home/cs104/cs104/hw-kim503/hw6/hw6_tests/coloring_tests/coloring_checker.cpp

coloring_tests/CMakeFiles/coloring_test.dir/coloring_checker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/coloring_test.dir/coloring_checker.cpp.i"
	cd /home/cs104/cs104/hw-kim503/hw6/hw6_tests/coloring_tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cs104/cs104/hw-kim503/hw6/hw6_tests/coloring_tests/coloring_checker.cpp > CMakeFiles/coloring_test.dir/coloring_checker.cpp.i

coloring_tests/CMakeFiles/coloring_test.dir/coloring_checker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/coloring_test.dir/coloring_checker.cpp.s"
	cd /home/cs104/cs104/hw-kim503/hw6/hw6_tests/coloring_tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cs104/cs104/hw-kim503/hw6/hw6_tests/coloring_tests/coloring_checker.cpp -o CMakeFiles/coloring_test.dir/coloring_checker.cpp.s

coloring_tests/CMakeFiles/coloring_test.dir/coloring_checker.cpp.o.requires:

.PHONY : coloring_tests/CMakeFiles/coloring_test.dir/coloring_checker.cpp.o.requires

coloring_tests/CMakeFiles/coloring_test.dir/coloring_checker.cpp.o.provides: coloring_tests/CMakeFiles/coloring_test.dir/coloring_checker.cpp.o.requires
	$(MAKE) -f coloring_tests/CMakeFiles/coloring_test.dir/build.make coloring_tests/CMakeFiles/coloring_test.dir/coloring_checker.cpp.o.provides.build
.PHONY : coloring_tests/CMakeFiles/coloring_test.dir/coloring_checker.cpp.o.provides

coloring_tests/CMakeFiles/coloring_test.dir/coloring_checker.cpp.o.provides.build: coloring_tests/CMakeFiles/coloring_test.dir/coloring_checker.cpp.o


# Object files for target coloring_test
coloring_test_OBJECTS = \
"CMakeFiles/coloring_test.dir/coloring_tests.cpp.o" \
"CMakeFiles/coloring_test.dir/coloring_checker.cpp.o"

# External object files for target coloring_test
coloring_test_EXTERNAL_OBJECTS =

coloring_tests/coloring_test: coloring_tests/CMakeFiles/coloring_test.dir/coloring_tests.cpp.o
coloring_tests/coloring_test: coloring_tests/CMakeFiles/coloring_test.dir/coloring_checker.cpp.o
coloring_tests/coloring_test: coloring_tests/CMakeFiles/coloring_test.dir/build.make
coloring_tests/coloring_test: testing_utils/libtesting_utils.a
coloring_tests/coloring_test: /usr/lib/libgtest.a
coloring_tests/coloring_test: testing_utils/kwsys/libkwsys.a
coloring_tests/coloring_test: testing_utils/libperf/libperf.a
coloring_tests/coloring_test: /usr/lib/libgtest_main.a
coloring_tests/coloring_test: coloring_tests/CMakeFiles/coloring_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cs104/cs104/hw-kim503/hw6/hw6_tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable coloring_test"
	cd /home/cs104/cs104/hw-kim503/hw6/hw6_tests/coloring_tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/coloring_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
coloring_tests/CMakeFiles/coloring_test.dir/build: coloring_tests/coloring_test

.PHONY : coloring_tests/CMakeFiles/coloring_test.dir/build

coloring_tests/CMakeFiles/coloring_test.dir/requires: coloring_tests/CMakeFiles/coloring_test.dir/coloring_tests.cpp.o.requires
coloring_tests/CMakeFiles/coloring_test.dir/requires: coloring_tests/CMakeFiles/coloring_test.dir/coloring_checker.cpp.o.requires

.PHONY : coloring_tests/CMakeFiles/coloring_test.dir/requires

coloring_tests/CMakeFiles/coloring_test.dir/clean:
	cd /home/cs104/cs104/hw-kim503/hw6/hw6_tests/coloring_tests && $(CMAKE_COMMAND) -P CMakeFiles/coloring_test.dir/cmake_clean.cmake
.PHONY : coloring_tests/CMakeFiles/coloring_test.dir/clean

coloring_tests/CMakeFiles/coloring_test.dir/depend:
	cd /home/cs104/cs104/hw-kim503/hw6/hw6_tests && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cs104/cs104/hw-kim503/hw6/hw6_tests /home/cs104/cs104/hw-kim503/hw6/hw6_tests/coloring_tests /home/cs104/cs104/hw-kim503/hw6/hw6_tests /home/cs104/cs104/hw-kim503/hw6/hw6_tests/coloring_tests /home/cs104/cs104/hw-kim503/hw6/hw6_tests/coloring_tests/CMakeFiles/coloring_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : coloring_tests/CMakeFiles/coloring_test.dir/depend

