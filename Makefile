# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/simon/git/vncpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/simon/git/vncpp

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/simon/git/vncpp/CMakeFiles /Users/simon/git/vncpp/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/simon/git/vncpp/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named main

# Build rule for target.
main: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 main
.PHONY : main

# fast build rule for target.
main/fast:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/build
.PHONY : main/fast

src/gateway/bybit/BybitGateway.o: src/gateway/bybit/BybitGateway.cpp.o

.PHONY : src/gateway/bybit/BybitGateway.o

# target to build an object file
src/gateway/bybit/BybitGateway.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/gateway/bybit/BybitGateway.cpp.o
.PHONY : src/gateway/bybit/BybitGateway.cpp.o

src/gateway/bybit/BybitGateway.i: src/gateway/bybit/BybitGateway.cpp.i

.PHONY : src/gateway/bybit/BybitGateway.i

# target to preprocess a source file
src/gateway/bybit/BybitGateway.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/gateway/bybit/BybitGateway.cpp.i
.PHONY : src/gateway/bybit/BybitGateway.cpp.i

src/gateway/bybit/BybitGateway.s: src/gateway/bybit/BybitGateway.cpp.s

.PHONY : src/gateway/bybit/BybitGateway.s

# target to generate assembly for a file
src/gateway/bybit/BybitGateway.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/gateway/bybit/BybitGateway.cpp.s
.PHONY : src/gateway/bybit/BybitGateway.cpp.s

src/main.o: src/main.cpp.o

.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i

.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s

.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

src/trader/RestClient.o: src/trader/RestClient.cpp.o

.PHONY : src/trader/RestClient.o

# target to build an object file
src/trader/RestClient.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/trader/RestClient.cpp.o
.PHONY : src/trader/RestClient.cpp.o

src/trader/RestClient.i: src/trader/RestClient.cpp.i

.PHONY : src/trader/RestClient.i

# target to preprocess a source file
src/trader/RestClient.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/trader/RestClient.cpp.i
.PHONY : src/trader/RestClient.cpp.i

src/trader/RestClient.s: src/trader/RestClient.cpp.s

.PHONY : src/trader/RestClient.s

# target to generate assembly for a file
src/trader/RestClient.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/trader/RestClient.cpp.s
.PHONY : src/trader/RestClient.cpp.s

src/trader/http/connection.o: src/trader/http/connection.cpp.o

.PHONY : src/trader/http/connection.o

# target to build an object file
src/trader/http/connection.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/trader/http/connection.cpp.o
.PHONY : src/trader/http/connection.cpp.o

src/trader/http/connection.i: src/trader/http/connection.cpp.i

.PHONY : src/trader/http/connection.i

# target to preprocess a source file
src/trader/http/connection.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/trader/http/connection.cpp.i
.PHONY : src/trader/http/connection.cpp.i

src/trader/http/connection.s: src/trader/http/connection.cpp.s

.PHONY : src/trader/http/connection.s

# target to generate assembly for a file
src/trader/http/connection.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/trader/http/connection.cpp.s
.PHONY : src/trader/http/connection.cpp.s

test/test_threadpool/main.o: test/test_threadpool/main.cpp.o

.PHONY : test/test_threadpool/main.o

# target to build an object file
test/test_threadpool/main.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/test/test_threadpool/main.cpp.o
.PHONY : test/test_threadpool/main.cpp.o

test/test_threadpool/main.i: test/test_threadpool/main.cpp.i

.PHONY : test/test_threadpool/main.i

# target to preprocess a source file
test/test_threadpool/main.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/test/test_threadpool/main.cpp.i
.PHONY : test/test_threadpool/main.cpp.i

test/test_threadpool/main.s: test/test_threadpool/main.cpp.s

.PHONY : test/test_threadpool/main.s

# target to generate assembly for a file
test/test_threadpool/main.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/test/test_threadpool/main.cpp.s
.PHONY : test/test_threadpool/main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... main"
	@echo "... src/gateway/bybit/BybitGateway.o"
	@echo "... src/gateway/bybit/BybitGateway.i"
	@echo "... src/gateway/bybit/BybitGateway.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/trader/RestClient.o"
	@echo "... src/trader/RestClient.i"
	@echo "... src/trader/RestClient.s"
	@echo "... src/trader/http/connection.o"
	@echo "... src/trader/http/connection.i"
	@echo "... src/trader/http/connection.s"
	@echo "... test/test_threadpool/main.o"
	@echo "... test/test_threadpool/main.i"
	@echo "... test/test_threadpool/main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

