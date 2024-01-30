cmake_minimum_required (VERSION 3.2)

project(TRY_EMPLACE C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(BENCHMARK_ENABLE_TESTING OFF)

find_package(Threads REQUIRED)
find_package(benchmark REQUIRED)

project(fast_try_emplace)
add_executable(fast_try_emplace try_emp_hint.cpp)
target_link_libraries(fast_try_emplace benchmark::benchmark)
target_compile_options(fast_try_emplace PUBLIC ${BENCHMARK_FLAGS})
