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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.27.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.27.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/danilmalyshev/Desktop/MyProgect/Chess

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/danilmalyshev/Desktop/MyProgect/Chess

# Include any dependencies generated for this target.
include CMakeFiles/Chess.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Chess.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Chess.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Chess.dir/flags.make

CMakeFiles/Chess.dir/src/main.cpp.o: CMakeFiles/Chess.dir/flags.make
CMakeFiles/Chess.dir/src/main.cpp.o: src/main.cpp
CMakeFiles/Chess.dir/src/main.cpp.o: CMakeFiles/Chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/danilmalyshev/Desktop/MyProgect/Chess/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Chess.dir/src/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Chess.dir/src/main.cpp.o -MF CMakeFiles/Chess.dir/src/main.cpp.o.d -o CMakeFiles/Chess.dir/src/main.cpp.o -c /Users/danilmalyshev/Desktop/MyProgect/Chess/src/main.cpp

CMakeFiles/Chess.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Chess.dir/src/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/danilmalyshev/Desktop/MyProgect/Chess/src/main.cpp > CMakeFiles/Chess.dir/src/main.cpp.i

CMakeFiles/Chess.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Chess.dir/src/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/danilmalyshev/Desktop/MyProgect/Chess/src/main.cpp -o CMakeFiles/Chess.dir/src/main.cpp.s

CMakeFiles/Chess.dir/src/Logic.cpp.o: CMakeFiles/Chess.dir/flags.make
CMakeFiles/Chess.dir/src/Logic.cpp.o: src/Logic.cpp
CMakeFiles/Chess.dir/src/Logic.cpp.o: CMakeFiles/Chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/danilmalyshev/Desktop/MyProgect/Chess/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Chess.dir/src/Logic.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Chess.dir/src/Logic.cpp.o -MF CMakeFiles/Chess.dir/src/Logic.cpp.o.d -o CMakeFiles/Chess.dir/src/Logic.cpp.o -c /Users/danilmalyshev/Desktop/MyProgect/Chess/src/Logic.cpp

CMakeFiles/Chess.dir/src/Logic.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Chess.dir/src/Logic.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/danilmalyshev/Desktop/MyProgect/Chess/src/Logic.cpp > CMakeFiles/Chess.dir/src/Logic.cpp.i

CMakeFiles/Chess.dir/src/Logic.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Chess.dir/src/Logic.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/danilmalyshev/Desktop/MyProgect/Chess/src/Logic.cpp -o CMakeFiles/Chess.dir/src/Logic.cpp.s

CMakeFiles/Chess.dir/src/Figures/Figure.cpp.o: CMakeFiles/Chess.dir/flags.make
CMakeFiles/Chess.dir/src/Figures/Figure.cpp.o: src/Figures/Figure.cpp
CMakeFiles/Chess.dir/src/Figures/Figure.cpp.o: CMakeFiles/Chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/danilmalyshev/Desktop/MyProgect/Chess/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Chess.dir/src/Figures/Figure.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Chess.dir/src/Figures/Figure.cpp.o -MF CMakeFiles/Chess.dir/src/Figures/Figure.cpp.o.d -o CMakeFiles/Chess.dir/src/Figures/Figure.cpp.o -c /Users/danilmalyshev/Desktop/MyProgect/Chess/src/Figures/Figure.cpp

CMakeFiles/Chess.dir/src/Figures/Figure.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Chess.dir/src/Figures/Figure.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/danilmalyshev/Desktop/MyProgect/Chess/src/Figures/Figure.cpp > CMakeFiles/Chess.dir/src/Figures/Figure.cpp.i

CMakeFiles/Chess.dir/src/Figures/Figure.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Chess.dir/src/Figures/Figure.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/danilmalyshev/Desktop/MyProgect/Chess/src/Figures/Figure.cpp -o CMakeFiles/Chess.dir/src/Figures/Figure.cpp.s

CMakeFiles/Chess.dir/src/Windows/MainMenu.cpp.o: CMakeFiles/Chess.dir/flags.make
CMakeFiles/Chess.dir/src/Windows/MainMenu.cpp.o: src/Windows/MainMenu.cpp
CMakeFiles/Chess.dir/src/Windows/MainMenu.cpp.o: CMakeFiles/Chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/danilmalyshev/Desktop/MyProgect/Chess/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Chess.dir/src/Windows/MainMenu.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Chess.dir/src/Windows/MainMenu.cpp.o -MF CMakeFiles/Chess.dir/src/Windows/MainMenu.cpp.o.d -o CMakeFiles/Chess.dir/src/Windows/MainMenu.cpp.o -c /Users/danilmalyshev/Desktop/MyProgect/Chess/src/Windows/MainMenu.cpp

CMakeFiles/Chess.dir/src/Windows/MainMenu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Chess.dir/src/Windows/MainMenu.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/danilmalyshev/Desktop/MyProgect/Chess/src/Windows/MainMenu.cpp > CMakeFiles/Chess.dir/src/Windows/MainMenu.cpp.i

CMakeFiles/Chess.dir/src/Windows/MainMenu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Chess.dir/src/Windows/MainMenu.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/danilmalyshev/Desktop/MyProgect/Chess/src/Windows/MainMenu.cpp -o CMakeFiles/Chess.dir/src/Windows/MainMenu.cpp.s

CMakeFiles/Chess.dir/src/Windows/PlayMenu.cpp.o: CMakeFiles/Chess.dir/flags.make
CMakeFiles/Chess.dir/src/Windows/PlayMenu.cpp.o: src/Windows/PlayMenu.cpp
CMakeFiles/Chess.dir/src/Windows/PlayMenu.cpp.o: CMakeFiles/Chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/danilmalyshev/Desktop/MyProgect/Chess/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Chess.dir/src/Windows/PlayMenu.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Chess.dir/src/Windows/PlayMenu.cpp.o -MF CMakeFiles/Chess.dir/src/Windows/PlayMenu.cpp.o.d -o CMakeFiles/Chess.dir/src/Windows/PlayMenu.cpp.o -c /Users/danilmalyshev/Desktop/MyProgect/Chess/src/Windows/PlayMenu.cpp

CMakeFiles/Chess.dir/src/Windows/PlayMenu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Chess.dir/src/Windows/PlayMenu.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/danilmalyshev/Desktop/MyProgect/Chess/src/Windows/PlayMenu.cpp > CMakeFiles/Chess.dir/src/Windows/PlayMenu.cpp.i

CMakeFiles/Chess.dir/src/Windows/PlayMenu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Chess.dir/src/Windows/PlayMenu.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/danilmalyshev/Desktop/MyProgect/Chess/src/Windows/PlayMenu.cpp -o CMakeFiles/Chess.dir/src/Windows/PlayMenu.cpp.s

CMakeFiles/Chess.dir/src/Windows/Setting.cpp.o: CMakeFiles/Chess.dir/flags.make
CMakeFiles/Chess.dir/src/Windows/Setting.cpp.o: src/Windows/Setting.cpp
CMakeFiles/Chess.dir/src/Windows/Setting.cpp.o: CMakeFiles/Chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/danilmalyshev/Desktop/MyProgect/Chess/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Chess.dir/src/Windows/Setting.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Chess.dir/src/Windows/Setting.cpp.o -MF CMakeFiles/Chess.dir/src/Windows/Setting.cpp.o.d -o CMakeFiles/Chess.dir/src/Windows/Setting.cpp.o -c /Users/danilmalyshev/Desktop/MyProgect/Chess/src/Windows/Setting.cpp

CMakeFiles/Chess.dir/src/Windows/Setting.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Chess.dir/src/Windows/Setting.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/danilmalyshev/Desktop/MyProgect/Chess/src/Windows/Setting.cpp > CMakeFiles/Chess.dir/src/Windows/Setting.cpp.i

CMakeFiles/Chess.dir/src/Windows/Setting.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Chess.dir/src/Windows/Setting.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/danilmalyshev/Desktop/MyProgect/Chess/src/Windows/Setting.cpp -o CMakeFiles/Chess.dir/src/Windows/Setting.cpp.s

CMakeFiles/Chess.dir/src/Windows/TypeGame.cpp.o: CMakeFiles/Chess.dir/flags.make
CMakeFiles/Chess.dir/src/Windows/TypeGame.cpp.o: src/Windows/TypeGame.cpp
CMakeFiles/Chess.dir/src/Windows/TypeGame.cpp.o: CMakeFiles/Chess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/danilmalyshev/Desktop/MyProgect/Chess/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Chess.dir/src/Windows/TypeGame.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Chess.dir/src/Windows/TypeGame.cpp.o -MF CMakeFiles/Chess.dir/src/Windows/TypeGame.cpp.o.d -o CMakeFiles/Chess.dir/src/Windows/TypeGame.cpp.o -c /Users/danilmalyshev/Desktop/MyProgect/Chess/src/Windows/TypeGame.cpp

CMakeFiles/Chess.dir/src/Windows/TypeGame.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Chess.dir/src/Windows/TypeGame.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/danilmalyshev/Desktop/MyProgect/Chess/src/Windows/TypeGame.cpp > CMakeFiles/Chess.dir/src/Windows/TypeGame.cpp.i

CMakeFiles/Chess.dir/src/Windows/TypeGame.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Chess.dir/src/Windows/TypeGame.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/danilmalyshev/Desktop/MyProgect/Chess/src/Windows/TypeGame.cpp -o CMakeFiles/Chess.dir/src/Windows/TypeGame.cpp.s

# Object files for target Chess
Chess_OBJECTS = \
"CMakeFiles/Chess.dir/src/main.cpp.o" \
"CMakeFiles/Chess.dir/src/Logic.cpp.o" \
"CMakeFiles/Chess.dir/src/Figures/Figure.cpp.o" \
"CMakeFiles/Chess.dir/src/Windows/MainMenu.cpp.o" \
"CMakeFiles/Chess.dir/src/Windows/PlayMenu.cpp.o" \
"CMakeFiles/Chess.dir/src/Windows/Setting.cpp.o" \
"CMakeFiles/Chess.dir/src/Windows/TypeGame.cpp.o"

# External object files for target Chess
Chess_EXTERNAL_OBJECTS =

Chess: CMakeFiles/Chess.dir/src/main.cpp.o
Chess: CMakeFiles/Chess.dir/src/Logic.cpp.o
Chess: CMakeFiles/Chess.dir/src/Figures/Figure.cpp.o
Chess: CMakeFiles/Chess.dir/src/Windows/MainMenu.cpp.o
Chess: CMakeFiles/Chess.dir/src/Windows/PlayMenu.cpp.o
Chess: CMakeFiles/Chess.dir/src/Windows/Setting.cpp.o
Chess: CMakeFiles/Chess.dir/src/Windows/TypeGame.cpp.o
Chess: CMakeFiles/Chess.dir/build.make
Chess: /opt/homebrew/lib/libsfml-graphics.2.6.1.dylib
Chess: /opt/homebrew/lib/libsfml-audio.2.6.1.dylib
Chess: /opt/homebrew/lib/libsfml-network.2.6.1.dylib
Chess: /opt/homebrew/lib/libglfw.3.3.dylib
Chess: /opt/homebrew/lib/libsfml-window.2.6.1.dylib
Chess: /opt/homebrew/lib/libsfml-system.2.6.1.dylib
Chess: CMakeFiles/Chess.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/danilmalyshev/Desktop/MyProgect/Chess/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable Chess"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Chess.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Chess.dir/build: Chess
.PHONY : CMakeFiles/Chess.dir/build

CMakeFiles/Chess.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Chess.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Chess.dir/clean

CMakeFiles/Chess.dir/depend:
	cd /Users/danilmalyshev/Desktop/MyProgect/Chess && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/danilmalyshev/Desktop/MyProgect/Chess /Users/danilmalyshev/Desktop/MyProgect/Chess /Users/danilmalyshev/Desktop/MyProgect/Chess /Users/danilmalyshev/Desktop/MyProgect/Chess /Users/danilmalyshev/Desktop/MyProgect/Chess/CMakeFiles/Chess.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Chess.dir/depend
