# ======================================================================================================================
# BSD 3-Clause License

# Copyright (c) 2024 Giri M. Kumar, Mattia Gramuglia, Andrea L'Afflitto. All rights reserved.

# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:

# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.

# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.

# 3. Neither the name of the copyright holder nor the names of its
#    contributors may be used to endorse or promote products derived from
#    this software without specific prior written permission.

# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# ======================================================================================================================

cmake_minimum_required(VERSION 3.8)
project(pole_placement)

# Set C and C++ standards
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

# Enable warnings for GCC or Clang
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find Boost and Python packages
find_package(Boost 1.86 REQUIRED COMPONENTS filesystem python numpy)
find_package(PythonLibs REQUIRED)

# Include directories
include_directories(${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/pole_placement/
  ${CMAKE_CURRENT_SOURCE_DIR}/include/eigen/
)

# Set source files for the example
set(EXAMPLE_SOURCE_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/examples/example.cpp
)

# Add the executable for the example
add_executable(pole_placement_example ${EXAMPLE_SOURCE_FILES})

# Link the example executable with Boost/Python libraries
target_link_libraries(pole_placement_example ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

# Install Python script
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/pole_placement/pole_placement.py DESTINATION ${CMAKE_CURRENT_BINARY_DIR})