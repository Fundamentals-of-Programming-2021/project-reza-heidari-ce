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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/mnt/c/sharif/c how to program/project"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/sharif/c how to program/project/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/project.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/project.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/project.dir/flags.make

CMakeFiles/project.dir/main.c.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/main.c.o: ../main.c
CMakeFiles/project.dir/main.c.o: CMakeFiles/project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/sharif/c how to program/project/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/project.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/project.dir/main.c.o -MF CMakeFiles/project.dir/main.c.o.d -o CMakeFiles/project.dir/main.c.o -c "/mnt/c/sharif/c how to program/project/main.c"

CMakeFiles/project.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/project.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/mnt/c/sharif/c how to program/project/main.c" > CMakeFiles/project.dir/main.c.i

CMakeFiles/project.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/project.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/mnt/c/sharif/c how to program/project/main.c" -o CMakeFiles/project.dir/main.c.s

CMakeFiles/project.dir/username_menu.c.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/username_menu.c.o: ../username_menu.c
CMakeFiles/project.dir/username_menu.c.o: CMakeFiles/project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/sharif/c how to program/project/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/project.dir/username_menu.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/project.dir/username_menu.c.o -MF CMakeFiles/project.dir/username_menu.c.o.d -o CMakeFiles/project.dir/username_menu.c.o -c "/mnt/c/sharif/c how to program/project/username_menu.c"

CMakeFiles/project.dir/username_menu.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/project.dir/username_menu.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/mnt/c/sharif/c how to program/project/username_menu.c" > CMakeFiles/project.dir/username_menu.c.i

CMakeFiles/project.dir/username_menu.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/project.dir/username_menu.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/mnt/c/sharif/c how to program/project/username_menu.c" -o CMakeFiles/project.dir/username_menu.c.s

CMakeFiles/project.dir/game_map.c.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/game_map.c.o: ../game_map.c
CMakeFiles/project.dir/game_map.c.o: CMakeFiles/project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/sharif/c how to program/project/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/project.dir/game_map.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/project.dir/game_map.c.o -MF CMakeFiles/project.dir/game_map.c.o.d -o CMakeFiles/project.dir/game_map.c.o -c "/mnt/c/sharif/c how to program/project/game_map.c"

CMakeFiles/project.dir/game_map.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/project.dir/game_map.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/mnt/c/sharif/c how to program/project/game_map.c" > CMakeFiles/project.dir/game_map.c.i

CMakeFiles/project.dir/game_map.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/project.dir/game_map.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/mnt/c/sharif/c how to program/project/game_map.c" -o CMakeFiles/project.dir/game_map.c.s

# Object files for target project
project_OBJECTS = \
"CMakeFiles/project.dir/main.c.o" \
"CMakeFiles/project.dir/username_menu.c.o" \
"CMakeFiles/project.dir/game_map.c.o"

# External object files for target project
project_EXTERNAL_OBJECTS =

project: CMakeFiles/project.dir/main.c.o
project: CMakeFiles/project.dir/username_menu.c.o
project: CMakeFiles/project.dir/game_map.c.o
project: CMakeFiles/project.dir/build.make
project: CMakeFiles/project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/sharif/c how to program/project/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/project.dir/build: project
.PHONY : CMakeFiles/project.dir/build

CMakeFiles/project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/project.dir/clean

CMakeFiles/project.dir/depend:
	cd "/mnt/c/sharif/c how to program/project/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/sharif/c how to program/project" "/mnt/c/sharif/c how to program/project" "/mnt/c/sharif/c how to program/project/cmake-build-debug" "/mnt/c/sharif/c how to program/project/cmake-build-debug" "/mnt/c/sharif/c how to program/project/cmake-build-debug/CMakeFiles/project.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/project.dir/depend

