# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/rguyard/acharn/mmocode/serveurfin

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rguyard/acharn/mmocode/serveurfin

# Include any dependencies generated for this target.
include CMakeFiles/serveur.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/serveur.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/serveur.dir/flags.make

CMakeFiles/serveur.dir/mainServeurV4.cpp.o: CMakeFiles/serveur.dir/flags.make
CMakeFiles/serveur.dir/mainServeurV4.cpp.o: mainServeurV4.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rguyard/acharn/mmocode/serveurfin/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/serveur.dir/mainServeurV4.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/serveur.dir/mainServeurV4.cpp.o -c mainServeurV4.cpp

CMakeFiles/serveur.dir/mainServeurV4.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/serveur.dir/mainServeurV4.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E mainServeurV4.cpp > CMakeFiles/serveur.dir/mainServeurV4.cpp.i

CMakeFiles/serveur.dir/mainServeurV4.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/serveur.dir/mainServeurV4.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S mainServeurV4.cpp -o CMakeFiles/serveur.dir/mainServeurV4.cpp.s

CMakeFiles/serveur.dir/mainServeurV4.cpp.o.requires:
.PHONY : CMakeFiles/serveur.dir/mainServeurV4.cpp.o.requires

CMakeFiles/serveur.dir/mainServeurV4.cpp.o.provides: CMakeFiles/serveur.dir/mainServeurV4.cpp.o.requires
	$(MAKE) -f CMakeFiles/serveur.dir/build.make CMakeFiles/serveur.dir/mainServeurV4.cpp.o.provides.build
.PHONY : CMakeFiles/serveur.dir/mainServeurV4.cpp.o.provides

CMakeFiles/serveur.dir/mainServeurV4.cpp.o.provides.build: CMakeFiles/serveur.dir/mainServeurV4.cpp.o

CMakeFiles/serveur.dir/ServeurV4.cpp.o: CMakeFiles/serveur.dir/flags.make
CMakeFiles/serveur.dir/ServeurV4.cpp.o: ServeurV4.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rguyard/acharn/mmocode/serveurfin/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/serveur.dir/ServeurV4.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/serveur.dir/ServeurV4.cpp.o -c ServeurV4.cpp

CMakeFiles/serveur.dir/ServeurV4.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/serveur.dir/ServeurV4.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E ServeurV4.cpp > CMakeFiles/serveur.dir/ServeurV4.cpp.i

CMakeFiles/serveur.dir/ServeurV4.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/serveur.dir/ServeurV4.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S ServeurV4.cpp -o CMakeFiles/serveur.dir/ServeurV4.cpp.s

CMakeFiles/serveur.dir/ServeurV4.cpp.o.requires:
.PHONY : CMakeFiles/serveur.dir/ServeurV4.cpp.o.requires

CMakeFiles/serveur.dir/ServeurV4.cpp.o.provides: CMakeFiles/serveur.dir/ServeurV4.cpp.o.requires
	$(MAKE) -f CMakeFiles/serveur.dir/build.make CMakeFiles/serveur.dir/ServeurV4.cpp.o.provides.build
.PHONY : CMakeFiles/serveur.dir/ServeurV4.cpp.o.provides

CMakeFiles/serveur.dir/ServeurV4.cpp.o.provides.build: CMakeFiles/serveur.dir/ServeurV4.cpp.o

CMakeFiles/serveur.dir/Sauvegarde.cpp.o: CMakeFiles/serveur.dir/flags.make
CMakeFiles/serveur.dir/Sauvegarde.cpp.o: Sauvegarde.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rguyard/acharn/mmocode/serveurfin/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/serveur.dir/Sauvegarde.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/serveur.dir/Sauvegarde.cpp.o -c Sauvegarde.cpp

CMakeFiles/serveur.dir/Sauvegarde.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/serveur.dir/Sauvegarde.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E Sauvegarde.cpp > CMakeFiles/serveur.dir/Sauvegarde.cpp.i

CMakeFiles/serveur.dir/Sauvegarde.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/serveur.dir/Sauvegarde.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S Sauvegarde.cpp -o CMakeFiles/serveur.dir/Sauvegarde.cpp.s

CMakeFiles/serveur.dir/Sauvegarde.cpp.o.requires:
.PHONY : CMakeFiles/serveur.dir/Sauvegarde.cpp.o.requires

CMakeFiles/serveur.dir/Sauvegarde.cpp.o.provides: CMakeFiles/serveur.dir/Sauvegarde.cpp.o.requires
	$(MAKE) -f CMakeFiles/serveur.dir/build.make CMakeFiles/serveur.dir/Sauvegarde.cpp.o.provides.build
.PHONY : CMakeFiles/serveur.dir/Sauvegarde.cpp.o.provides

CMakeFiles/serveur.dir/Sauvegarde.cpp.o.provides.build: CMakeFiles/serveur.dir/Sauvegarde.cpp.o

# Object files for target serveur
serveur_OBJECTS = \
"CMakeFiles/serveur.dir/mainServeurV4.cpp.o" \
"CMakeFiles/serveur.dir/ServeurV4.cpp.o" \
"CMakeFiles/serveur.dir/Sauvegarde.cpp.o"

# External object files for target serveur
serveur_EXTERNAL_OBJECTS =

serveur: CMakeFiles/serveur.dir/mainServeurV4.cpp.o
serveur: CMakeFiles/serveur.dir/ServeurV4.cpp.o
serveur: CMakeFiles/serveur.dir/Sauvegarde.cpp.o
serveur: CMakeFiles/serveur.dir/build.make
serveur: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
serveur: /usr/lib/x86_64-linux-gnu/libboost_thread.so
serveur: /usr/lib/x86_64-linux-gnu/libpthread.so
serveur: CMakeFiles/serveur.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable serveur"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/serveur.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/serveur.dir/build: serveur
.PHONY : CMakeFiles/serveur.dir/build

CMakeFiles/serveur.dir/requires: CMakeFiles/serveur.dir/mainServeurV4.cpp.o.requires
CMakeFiles/serveur.dir/requires: CMakeFiles/serveur.dir/ServeurV4.cpp.o.requires
CMakeFiles/serveur.dir/requires: CMakeFiles/serveur.dir/Sauvegarde.cpp.o.requires
.PHONY : CMakeFiles/serveur.dir/requires

CMakeFiles/serveur.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/serveur.dir/cmake_clean.cmake
.PHONY : CMakeFiles/serveur.dir/clean

CMakeFiles/serveur.dir/depend:
	cd /home/rguyard/acharn/mmocode/serveurfin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rguyard/acharn/mmocode/serveurfin /home/rguyard/acharn/mmocode/serveurfin /home/rguyard/acharn/mmocode/serveurfin /home/rguyard/acharn/mmocode/serveurfin /home/rguyard/acharn/mmocode/serveurfin/CMakeFiles/serveur.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/serveur.dir/depend

