gcc c_linear_probing.c -o c_linear_probing -O3
gcc c_chaining.c -o c_chaining -O3
g++ cpp_unordered_map.cpp -o cpp_unordered_map -O3
g++ cpp_map.cpp -o cpp_map -O3
g++ cpp_robin_map.cpp -o cpp_robin_map -O3 -Irobin-map/include

clang c_linear_probing.c -o c_linear_probing_clang -O3
clang++ cpp_unordered_map.cpp -o cpp_unordered_map_clang -O3
clang++ cpp_map.cpp -o cpp_map_clang -O3

rustc rust_hashmap.rs -o rust_hashmap -C opt-level=3
rustc rust_btreemap.rs -o rust_btreemap -C opt-level=3
cargo build --manifest-path=rust_fxhash/Cargo.toml --release
