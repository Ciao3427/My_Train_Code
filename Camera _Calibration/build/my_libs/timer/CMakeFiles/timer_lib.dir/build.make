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
CMAKE_SOURCE_DIR = "/home/ciao/桌面/CODE/考核与学习/Camera _Calibration"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/ciao/桌面/CODE/考核与学习/Camera _Calibration/build"

# Include any dependencies generated for this target.
include my_libs/timer/CMakeFiles/timer_lib.dir/depend.make

# Include the progress variables for this target.
include my_libs/timer/CMakeFiles/timer_lib.dir/progress.make

# Include the compile flags for this target's objects.
include my_libs/timer/CMakeFiles/timer_lib.dir/flags.make

my_libs/timer/CMakeFiles/timer_lib.dir/timer.cpp.o: my_libs/timer/CMakeFiles/timer_lib.dir/flags.make
my_libs/timer/CMakeFiles/timer_lib.dir/timer.cpp.o: ../my_libs/timer/timer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/ciao/桌面/CODE/考核与学习/Camera _Calibration/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object my_libs/timer/CMakeFiles/timer_lib.dir/timer.cpp.o"
	cd "/home/ciao/桌面/CODE/考核与学习/Camera _Calibration/build/my_libs/timer" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/timer_lib.dir/timer.cpp.o -c "/home/ciao/桌面/CODE/考核与学习/Camera _Calibration/my_libs/timer/timer.cpp"

my_libs/timer/CMakeFiles/timer_lib.dir/timer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/timer_lib.dir/timer.cpp.i"
	cd "/home/ciao/桌面/CODE/考核与学习/Camera _Calibration/build/my_libs/timer" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/ciao/桌面/CODE/考核与学习/Camera _Calibration/my_libs/timer/timer.cpp" > CMakeFiles/timer_lib.dir/timer.cpp.i

my_libs/timer/CMakeFiles/timer_lib.dir/timer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/timer_lib.dir/timer.cpp.s"
	cd "/home/ciao/桌面/CODE/考核与学习/Camera _Calibration/build/my_libs/timer" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/ciao/桌面/CODE/考核与学习/Camera _Calibration/my_libs/timer/timer.cpp" -o CMakeFiles/timer_lib.dir/timer.cpp.s

# Object files for target timer_lib
timer_lib_OBJECTS = \
"CMakeFiles/timer_lib.dir/timer.cpp.o"

# External object files for target timer_lib
timer_lib_EXTERNAL_OBJECTS =

my_libs/timer/libtimer_lib.so: my_libs/timer/CMakeFiles/timer_lib.dir/timer.cpp.o
my_libs/timer/libtimer_lib.so: my_libs/timer/CMakeFiles/timer_lib.dir/build.make
my_libs/timer/libtimer_lib.so: /usr/local/lib/libfmt.so.8.1.1
my_libs/timer/libtimer_lib.so: my_libs/timer/CMakeFiles/timer_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/ciao/桌面/CODE/考核与学习/Camera _Calibration/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libtimer_lib.so"
	cd "/home/ciao/桌面/CODE/考核与学习/Camera _Calibration/build/my_libs/timer" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/timer_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
my_libs/timer/CMakeFiles/timer_lib.dir/build: my_libs/timer/libtimer_lib.so

.PHONY : my_libs/timer/CMakeFiles/timer_lib.dir/build

my_libs/timer/CMakeFiles/timer_lib.dir/clean:
	cd "/home/ciao/桌面/CODE/考核与学习/Camera _Calibration/build/my_libs/timer" && $(CMAKE_COMMAND) -P CMakeFiles/timer_lib.dir/cmake_clean.cmake
.PHONY : my_libs/timer/CMakeFiles/timer_lib.dir/clean

my_libs/timer/CMakeFiles/timer_lib.dir/depend:
	cd "/home/ciao/桌面/CODE/考核与学习/Camera _Calibration/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/ciao/桌面/CODE/考核与学习/Camera _Calibration" "/home/ciao/桌面/CODE/考核与学习/Camera _Calibration/my_libs/timer" "/home/ciao/桌面/CODE/考核与学习/Camera _Calibration/build" "/home/ciao/桌面/CODE/考核与学习/Camera _Calibration/build/my_libs/timer" "/home/ciao/桌面/CODE/考核与学习/Camera _Calibration/build/my_libs/timer/CMakeFiles/timer_lib.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : my_libs/timer/CMakeFiles/timer_lib.dir/depend

