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
CMAKE_SOURCE_DIR = "/mnt/2BC7DF4C492DF2D1/Files/Study/Datalogi 2/DH2323/Labb 2/RayTracing"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/2BC7DF4C492DF2D1/Files/Study/Datalogi 2/DH2323/Labb 2/RayTracing"

# Include any dependencies generated for this target.
include CMakeFiles/SecondLab.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SecondLab.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SecondLab.dir/flags.make

CMakeFiles/SecondLab.dir/skeleton.cpp.o: CMakeFiles/SecondLab.dir/flags.make
CMakeFiles/SecondLab.dir/skeleton.cpp.o: skeleton.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/2BC7DF4C492DF2D1/Files/Study/Datalogi 2/DH2323/Labb 2/RayTracing/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SecondLab.dir/skeleton.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SecondLab.dir/skeleton.cpp.o -c "/mnt/2BC7DF4C492DF2D1/Files/Study/Datalogi 2/DH2323/Labb 2/RayTracing/skeleton.cpp"

CMakeFiles/SecondLab.dir/skeleton.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SecondLab.dir/skeleton.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/2BC7DF4C492DF2D1/Files/Study/Datalogi 2/DH2323/Labb 2/RayTracing/skeleton.cpp" > CMakeFiles/SecondLab.dir/skeleton.cpp.i

CMakeFiles/SecondLab.dir/skeleton.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SecondLab.dir/skeleton.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/2BC7DF4C492DF2D1/Files/Study/Datalogi 2/DH2323/Labb 2/RayTracing/skeleton.cpp" -o CMakeFiles/SecondLab.dir/skeleton.cpp.s

CMakeFiles/SecondLab.dir/skeleton.cpp.o.requires:

.PHONY : CMakeFiles/SecondLab.dir/skeleton.cpp.o.requires

CMakeFiles/SecondLab.dir/skeleton.cpp.o.provides: CMakeFiles/SecondLab.dir/skeleton.cpp.o.requires
	$(MAKE) -f CMakeFiles/SecondLab.dir/build.make CMakeFiles/SecondLab.dir/skeleton.cpp.o.provides.build
.PHONY : CMakeFiles/SecondLab.dir/skeleton.cpp.o.provides

CMakeFiles/SecondLab.dir/skeleton.cpp.o.provides.build: CMakeFiles/SecondLab.dir/skeleton.cpp.o


# Object files for target SecondLab
SecondLab_OBJECTS = \
"CMakeFiles/SecondLab.dir/skeleton.cpp.o"

# External object files for target SecondLab
SecondLab_EXTERNAL_OBJECTS =

SecondLab: CMakeFiles/SecondLab.dir/skeleton.cpp.o
SecondLab: CMakeFiles/SecondLab.dir/build.make
SecondLab: /usr/lib/x86_64-linux-gnu/libSDLmain.a
SecondLab: /usr/lib/x86_64-linux-gnu/libSDL.so
SecondLab: CMakeFiles/SecondLab.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/2BC7DF4C492DF2D1/Files/Study/Datalogi 2/DH2323/Labb 2/RayTracing/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable SecondLab"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SecondLab.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SecondLab.dir/build: SecondLab

.PHONY : CMakeFiles/SecondLab.dir/build

CMakeFiles/SecondLab.dir/requires: CMakeFiles/SecondLab.dir/skeleton.cpp.o.requires

.PHONY : CMakeFiles/SecondLab.dir/requires

CMakeFiles/SecondLab.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SecondLab.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SecondLab.dir/clean

CMakeFiles/SecondLab.dir/depend:
	cd "/mnt/2BC7DF4C492DF2D1/Files/Study/Datalogi 2/DH2323/Labb 2/RayTracing" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/2BC7DF4C492DF2D1/Files/Study/Datalogi 2/DH2323/Labb 2/RayTracing" "/mnt/2BC7DF4C492DF2D1/Files/Study/Datalogi 2/DH2323/Labb 2/RayTracing" "/mnt/2BC7DF4C492DF2D1/Files/Study/Datalogi 2/DH2323/Labb 2/RayTracing" "/mnt/2BC7DF4C492DF2D1/Files/Study/Datalogi 2/DH2323/Labb 2/RayTracing" "/mnt/2BC7DF4C492DF2D1/Files/Study/Datalogi 2/DH2323/Labb 2/RayTracing/CMakeFiles/SecondLab.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/SecondLab.dir/depend

