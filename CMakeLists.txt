cmake_minimum_required(VERSION 3.19)
project(RTreeBoundingBoxReproducer)

find_package(Boost REQUIRED)


add_executable(rtree_repro rtree_repro.cpp)
target_link_libraries(rtree_repro PUBLIC Boost::boost)
target_compile_options(rtree_repro PUBLIC -fsanitize=address)
target_link_options(rtree_repro PUBLIC -fsanitize=address)
