use std::fs::File;
use std::io::{BufRead, BufReader};
use rustc_hash::FxHashMap;
use std::time::Instant;

fn main() {
	let file = File::open("words.txt").expect("Failed to open file");
	let reader = BufReader::new(file);

	let mut lines = Vec::new();
	let mut freq = FxHashMap::default();

	for line in reader.lines() {
		if let Ok(line) = line {
			lines.push(line);
		}
	}

	let start = Instant::now();

	for line in lines {
		*freq.entry(line).or_insert(0) += 1;
	}

	let end = Instant::now();
	let cpu_time_used = end.duration_since(start).as_secs_f64();
	println!("{}", cpu_time_used);

	// for (key, value) in freq {
	//     println!("{} {}", key, value);
	// }
}