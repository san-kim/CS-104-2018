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
include CMakeFiles/first_memtest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/first_memtest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/first_memtest.dir/flags.make

CMakeFiles/first_memtest.dir/home/cs104/cs104/hw-kim503/hw1/first_memtest.cpp.o: CMakeFiles/first_memtest.dir/flags.make
CMakeFiles/first_memtest.dir/home/cs104/cs104/hw-kim503/hw1/first_memtest.cpp.o: /home/cs104/cs104/hw-kim503/hw1/first_memtest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cs104/cs104/hw-kim503/hw1/hw1_tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/first_memtest.dir/home/cs104/cs104/hw-kim503/hw1/first_memtest.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/first_memtest.dir/home/cs104/cs104/hw-kim503/hw1/first_memtest.cpp.o -c /home/cs104/cs104/hw-kim503/hw1/first_memtest.cpp

CMakeFiles/first_memtest.dir/home/cs104/cs104/hw-kim503/hw1/first_memtest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/first_memtest.dir/home/cs104/cs104/hw-kim503/hw1/first_memtest.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cs104/cs104/hw-kim503/hw1/first_memtest.cpp > CMakeFiles/first_memtest.dir/home/cs104/cs104/hw-kim503/hw1/first_memtest.cpp.i

CMakeFiles/first_memtest.dir/home/cs104/cs104/hw-kim503/hw1/first_memtest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/first_memtest.dir/home/cs104/cs104/hw-kim503/hw1/first_memtest.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cs104/cs104/hw-kim503/hw1/first_memtest.cpp -o CMakeFiles/first_memtest.dir/home/cs104/cs104/hw-kim503/hw1/first_memtest.cpp.s

CMakeFiles/first_memtest.dir/home/cs104/cs104/hw-kim503/hw1/first_memtest.cpp.o.requires:

.PHONY : CMakeFiles/first_memtest.dir/home/cs104/cs104/hw-kim503/hw1/first_memtest.cpp.o.requires

CMakeFiles/first_memtest.dir/home/cs104/cs104/hw-kim503/hw1/first_memtest.cpp.o.provides: CMakeFiles/first_memtest.dir/home/cs104/cs104/hw-kim503/hw1/first_memtest.cpp.o.requires
	$(MAKE) -f CMakeFiles/first_memtest.dir/build.make CMakeFiles/first_memtest.dir/home/cs104/cs104/hw-kim503/hw1/first_memtest.cpp.o.provides.build
.PHONY : CMakeFiles/first_memtest.dir/home/cs104/cs104/hw-kim503/hw1/first_memtest.cpp.o.provides

CMakeFiles/first_memtest.dir/home/cs104/cs104/hw-kim503/hw1/first_memtest.cpp.o.provides.build: CMakeFiles/first_memtest.dir/home/cs104/cs104/hw-kim503/hw1/first_memtest.cpp.o


# Object files for target first_memtest
first_memtest_OBJECTS = \
"CMakeFiles/first_memtest.dir/home/cs104/cs104/hw-kim503/hw1/first_memtest.cpp.o"

# External object files for target first_memtest
first_memtest_EXTERNAL_OBJECTS =

first_memtest: CMakeFiles/first_memtest.dir/home/cs104/cs104/hw-kim503/hw1/first_memtest.cpp.o
first_memtest: CMakeFiles/first_memtest.dir/build.make
first_memtest: libhw1_simple_char_manager.a
first_memtest: CMakeFiles/first_memtest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cs104/cs104/hw-kim503/hw1/hw1_tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable first_memtest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/first_memtest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/first_memtest.dir/build: first_memtest

.PHONY : CMakeFiles/first_memtest.dir/build

CMakeFiles/first_memtest.dir/requires: CMakeFiles/first_memtest.dir/home/cs104/cs104/hw-kim503/hw1/first_memtest.cpp.o.requires

.PHONY : CMakeFiles/first_memtest.dir/requires

CMakeFiles/first_memtest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/first_memtest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/first_memtest.dir/clean

CMakeFiles/first_memtest.dir/depend:
	cd /home/cs104/cs104/hw-kim503/hw1/hw1_tests && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cs104/cs104/hw-kim503/hw1/hw1_tests /home/cs104/cs104/hw-kim503/hw1/hw1_tests /home/cs104/cs104/hw-kim503/hw1/hw1_tests /home/cs104/cs104/hw-kim503/hw1/hw1_tests /home/cs104/cs104/hw-kim503/hw1/hw1_tests/CMakeFiles/first_memtest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/first_memtest.dir/depend

