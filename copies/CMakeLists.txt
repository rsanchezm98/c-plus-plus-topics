cmake_minimum_required(VERSION 3.5)
project(copies)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# .cpp files
set(MY_PROGRAM_REQUIRED_FILES
    src/main.cpp
)

include_directories(include)

# executable
add_executable(my_node ${MY_PROGRAM_REQUIRED_FILES})

install(DIRECTORY include/
  DESTINATION include/
)