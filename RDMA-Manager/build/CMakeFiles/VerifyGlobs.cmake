# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.24
cmake_policy(SET CMP0009 NEW)

# SRC_FILES at src/network/CMakeLists.txt:1 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/home/lwjeong/git/RDMA-Manager/RDMA-Manager/src/network/*.cpp")
set(OLD_GLOB
  "/home/lwjeong/git/RDMA-Manager/RDMA-Manager/src/network/RDMA.cpp"
  "/home/lwjeong/git/RDMA-Manager/RDMA-Manager/src/network/myRDMA.cpp"
  "/home/lwjeong/git/RDMA-Manager/RDMA-Manager/src/network/tcp.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/lwjeong/git/RDMA-Manager/RDMA-Manager/build/CMakeFiles/cmake.verify_globs")
endif()
