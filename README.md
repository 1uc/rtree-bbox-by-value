# Reproducer: compute bounding box on the fly
To reproduce the issue install Boost 1.79.0 and
```
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -B build .
cmake --build build && ./build/rtree_repro
```

A trimmed version of the ASAN output can be found in `asan_report.txt`.
