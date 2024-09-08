gcc c_linear_probing.c -o c_linear_probing -O3
g++ cpp_unordered_map.cpp -o cpp_unordered_map -O3
g++ cpp_map.cpp -o cpp_map -O3

clang c_linear_probing.c -o c_linear_probing_clang -O3
clang++ cpp_unordered_map.cpp -o cpp_unordered_map_clang -O3
clang++ cpp_map.cpp -o cpp_map_clang -O3

rustc rust_hashmap.rs -o rust_hashmap -C opt-level=3
rustc rust_btreemap.rs -o rust_btreemap -C opt-level=3
cargo build --manifest-path=rust_fxhash/Cargo.toml --release
