include(CMakeFindDependencyMacro)
find_dependency(Threads REQUIRED)
find_dependency(LAPACK REQUIRED NAMES OpenBLAS lapack)
find_dependency(ZeroMQ REQUIRED)
find_dependency(cereal REQUIRED)
include("${CMAKE_CURRENT_LIST_DIR}/polo-targets.cmake")
