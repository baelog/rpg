# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_SOURCE_DIR = /home/florent/rpg

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/florent/rpg/build

# Include any dependencies generated for this target.
include CMakeFiles/rpg.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/rpg.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/rpg.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rpg.dir/flags.make

CMakeFiles/rpg.dir/main.c.o: CMakeFiles/rpg.dir/flags.make
CMakeFiles/rpg.dir/main.c.o: /home/florent/rpg/main.c
CMakeFiles/rpg.dir/main.c.o: CMakeFiles/rpg.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/florent/rpg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/rpg.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/rpg.dir/main.c.o -MF CMakeFiles/rpg.dir/main.c.o.d -o CMakeFiles/rpg.dir/main.c.o -c /home/florent/rpg/main.c

CMakeFiles/rpg.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/rpg.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/florent/rpg/main.c > CMakeFiles/rpg.dir/main.c.i

CMakeFiles/rpg.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/rpg.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/florent/rpg/main.c -o CMakeFiles/rpg.dir/main.c.s

CMakeFiles/rpg.dir/yaml.c.o: CMakeFiles/rpg.dir/flags.make
CMakeFiles/rpg.dir/yaml.c.o: /home/florent/rpg/yaml.c
CMakeFiles/rpg.dir/yaml.c.o: CMakeFiles/rpg.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/florent/rpg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/rpg.dir/yaml.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/rpg.dir/yaml.c.o -MF CMakeFiles/rpg.dir/yaml.c.o.d -o CMakeFiles/rpg.dir/yaml.c.o -c /home/florent/rpg/yaml.c

CMakeFiles/rpg.dir/yaml.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/rpg.dir/yaml.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/florent/rpg/yaml.c > CMakeFiles/rpg.dir/yaml.c.i

CMakeFiles/rpg.dir/yaml.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/rpg.dir/yaml.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/florent/rpg/yaml.c -o CMakeFiles/rpg.dir/yaml.c.s

CMakeFiles/rpg.dir/read.c.o: CMakeFiles/rpg.dir/flags.make
CMakeFiles/rpg.dir/read.c.o: /home/florent/rpg/read.c
CMakeFiles/rpg.dir/read.c.o: CMakeFiles/rpg.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/florent/rpg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/rpg.dir/read.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/rpg.dir/read.c.o -MF CMakeFiles/rpg.dir/read.c.o.d -o CMakeFiles/rpg.dir/read.c.o -c /home/florent/rpg/read.c

CMakeFiles/rpg.dir/read.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/rpg.dir/read.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/florent/rpg/read.c > CMakeFiles/rpg.dir/read.c.i

CMakeFiles/rpg.dir/read.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/rpg.dir/read.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/florent/rpg/read.c -o CMakeFiles/rpg.dir/read.c.s

CMakeFiles/rpg.dir/map.c.o: CMakeFiles/rpg.dir/flags.make
CMakeFiles/rpg.dir/map.c.o: /home/florent/rpg/map.c
CMakeFiles/rpg.dir/map.c.o: CMakeFiles/rpg.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/florent/rpg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/rpg.dir/map.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/rpg.dir/map.c.o -MF CMakeFiles/rpg.dir/map.c.o.d -o CMakeFiles/rpg.dir/map.c.o -c /home/florent/rpg/map.c

CMakeFiles/rpg.dir/map.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/rpg.dir/map.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/florent/rpg/map.c > CMakeFiles/rpg.dir/map.c.i

CMakeFiles/rpg.dir/map.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/rpg.dir/map.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/florent/rpg/map.c -o CMakeFiles/rpg.dir/map.c.s

CMakeFiles/rpg.dir/map/ground.c.o: CMakeFiles/rpg.dir/flags.make
CMakeFiles/rpg.dir/map/ground.c.o: /home/florent/rpg/map/ground.c
CMakeFiles/rpg.dir/map/ground.c.o: CMakeFiles/rpg.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/florent/rpg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/rpg.dir/map/ground.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/rpg.dir/map/ground.c.o -MF CMakeFiles/rpg.dir/map/ground.c.o.d -o CMakeFiles/rpg.dir/map/ground.c.o -c /home/florent/rpg/map/ground.c

CMakeFiles/rpg.dir/map/ground.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/rpg.dir/map/ground.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/florent/rpg/map/ground.c > CMakeFiles/rpg.dir/map/ground.c.i

CMakeFiles/rpg.dir/map/ground.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/rpg.dir/map/ground.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/florent/rpg/map/ground.c -o CMakeFiles/rpg.dir/map/ground.c.s

CMakeFiles/rpg.dir/map/wall.c.o: CMakeFiles/rpg.dir/flags.make
CMakeFiles/rpg.dir/map/wall.c.o: /home/florent/rpg/map/wall.c
CMakeFiles/rpg.dir/map/wall.c.o: CMakeFiles/rpg.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/florent/rpg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/rpg.dir/map/wall.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/rpg.dir/map/wall.c.o -MF CMakeFiles/rpg.dir/map/wall.c.o.d -o CMakeFiles/rpg.dir/map/wall.c.o -c /home/florent/rpg/map/wall.c

CMakeFiles/rpg.dir/map/wall.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/rpg.dir/map/wall.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/florent/rpg/map/wall.c > CMakeFiles/rpg.dir/map/wall.c.i

CMakeFiles/rpg.dir/map/wall.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/rpg.dir/map/wall.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/florent/rpg/map/wall.c -o CMakeFiles/rpg.dir/map/wall.c.s

# Object files for target rpg
rpg_OBJECTS = \
"CMakeFiles/rpg.dir/main.c.o" \
"CMakeFiles/rpg.dir/yaml.c.o" \
"CMakeFiles/rpg.dir/read.c.o" \
"CMakeFiles/rpg.dir/map.c.o" \
"CMakeFiles/rpg.dir/map/ground.c.o" \
"CMakeFiles/rpg.dir/map/wall.c.o"

# External object files for target rpg
rpg_EXTERNAL_OBJECTS =

rpg: CMakeFiles/rpg.dir/main.c.o
rpg: CMakeFiles/rpg.dir/yaml.c.o
rpg: CMakeFiles/rpg.dir/read.c.o
rpg: CMakeFiles/rpg.dir/map.c.o
rpg: CMakeFiles/rpg.dir/map/ground.c.o
rpg: CMakeFiles/rpg.dir/map/wall.c.o
rpg: CMakeFiles/rpg.dir/build.make
rpg: CMakeFiles/rpg.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/florent/rpg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable rpg"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rpg.dir/link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold "Copying assets to build directory..."
	/usr/bin/cmake -E copy_directory /home/florent/rpg/assets /home/florent/rpg/build/assets

# Rule to build all files generated by this target.
CMakeFiles/rpg.dir/build: rpg
.PHONY : CMakeFiles/rpg.dir/build

CMakeFiles/rpg.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rpg.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rpg.dir/clean

CMakeFiles/rpg.dir/depend:
	cd /home/florent/rpg/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/florent/rpg /home/florent/rpg /home/florent/rpg/build /home/florent/rpg/build /home/florent/rpg/build/CMakeFiles/rpg.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/rpg.dir/depend

