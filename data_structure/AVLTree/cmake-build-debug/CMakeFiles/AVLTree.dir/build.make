# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\CLion 2020.3.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\CLion 2020.3.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Daer\data_structure\AVLTree

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Daer\data_structure\AVLTree\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/AVLTree.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/AVLTree.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AVLTree.dir/flags.make

CMakeFiles/AVLTree.dir/main.c.obj: CMakeFiles/AVLTree.dir/flags.make
CMakeFiles/AVLTree.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Daer\data_structure\AVLTree\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/AVLTree.dir/main.c.obj"
	D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\AVLTree.dir\main.c.obj   -c D:\Daer\data_structure\AVLTree\main.c

CMakeFiles/AVLTree.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/AVLTree.dir/main.c.i"
	D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Daer\data_structure\AVLTree\main.c > CMakeFiles\AVLTree.dir\main.c.i

CMakeFiles/AVLTree.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/AVLTree.dir/main.c.s"
	D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Daer\data_structure\AVLTree\main.c -o CMakeFiles\AVLTree.dir\main.c.s

CMakeFiles/AVLTree.dir/AVLTree.c.obj: CMakeFiles/AVLTree.dir/flags.make
CMakeFiles/AVLTree.dir/AVLTree.c.obj: ../AVLTree.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Daer\data_structure\AVLTree\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/AVLTree.dir/AVLTree.c.obj"
	D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\AVLTree.dir\AVLTree.c.obj   -c D:\Daer\data_structure\AVLTree\AVLTree.c

CMakeFiles/AVLTree.dir/AVLTree.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/AVLTree.dir/AVLTree.c.i"
	D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Daer\data_structure\AVLTree\AVLTree.c > CMakeFiles\AVLTree.dir\AVLTree.c.i

CMakeFiles/AVLTree.dir/AVLTree.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/AVLTree.dir/AVLTree.c.s"
	D:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Daer\data_structure\AVLTree\AVLTree.c -o CMakeFiles\AVLTree.dir\AVLTree.c.s

# Object files for target AVLTree
AVLTree_OBJECTS = \
"CMakeFiles/AVLTree.dir/main.c.obj" \
"CMakeFiles/AVLTree.dir/AVLTree.c.obj"

# External object files for target AVLTree
AVLTree_EXTERNAL_OBJECTS =

AVLTree.exe: CMakeFiles/AVLTree.dir/main.c.obj
AVLTree.exe: CMakeFiles/AVLTree.dir/AVLTree.c.obj
AVLTree.exe: CMakeFiles/AVLTree.dir/build.make
AVLTree.exe: CMakeFiles/AVLTree.dir/linklibs.rsp
AVLTree.exe: CMakeFiles/AVLTree.dir/objects1.rsp
AVLTree.exe: CMakeFiles/AVLTree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Daer\data_structure\AVLTree\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable AVLTree.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\AVLTree.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AVLTree.dir/build: AVLTree.exe

.PHONY : CMakeFiles/AVLTree.dir/build

CMakeFiles/AVLTree.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\AVLTree.dir\cmake_clean.cmake
.PHONY : CMakeFiles/AVLTree.dir/clean

CMakeFiles/AVLTree.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Daer\data_structure\AVLTree D:\Daer\data_structure\AVLTree D:\Daer\data_structure\AVLTree\cmake-build-debug D:\Daer\data_structure\AVLTree\cmake-build-debug D:\Daer\data_structure\AVLTree\cmake-build-debug\CMakeFiles\AVLTree.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AVLTree.dir/depend

