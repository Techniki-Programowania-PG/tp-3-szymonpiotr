cmake_minimum_required(VERSION 3.14)
project(SignalProcessing)

set(CMAKE_CXX_STANDARD 17)


include(FetchContent)
FetchContent_Declare(
  matplotplusplus
  GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus.git
  GIT_TAG master
)
FetchContent_MakeAvailable(matplotplusplus)


add_executable(SignalProcessing main.cpp SignalProcessing.hpp)


target_link_libraries(SignalProcessing PRIVATE matplot)