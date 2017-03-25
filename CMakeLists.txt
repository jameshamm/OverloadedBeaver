#
# This is a CMake makefile.  You can find the cmake utility and
# information about it at http://www.cmake.org
#
cmake_minimum_required(VERSION 2.8.4)

PROJECT(OverloadedBeaver)

# Since there are a lot of examples I'm going to use a macro to simply this
# CMakeLists.txt file.  However, usually you will create only one executable in
# your cmake projects and use the syntax shown above.
MACRO(add_exec name)
   ADD_EXECUTABLE(${name} ${name}.cpp)
ENDMACRO()

#here we apply our macros
add_exec(run)
add_exec(TM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -pthread")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -O2 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -DRELEASE")
