cmake_minimum_required(VERSION 3.5)
project(async)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# .cpp files
set(MY_PROGRAM_REQUIRED_FILES
    src/main.cpp
)

# executable
add_executable(my_node ${MY_PROGRAM_REQUIRED_FILES})
target_link_libraries(my_node pthread)
