use std::fs::File;
use std::io::{BufRead, BufReader};
use std::collections::HashMap;
use std::time::Instant;

fn main() {
	let file = File::open("words.txt").expect("Failed to open file");
	let reader = BufReader::new(file);

	let mut lines = Vec::new();
	let mut freq: HashMap<&str, i32> = HashMap::new();

	for line in reader.lines() {
		if let Ok(line) = line {
			lines.push(line);
		}
	}

	let start = Instant::now();

	for line in lines.iter() {
		*freq.entry(line.as_str()).or_insert(0) += 1;
	}

	let end = Instant::now();
	let cpu_time_used = end.duration_since(start).as_secs_f64();
	println!("{}", cpu_time_used);

	// for (key, value) in freq {
	//     println!("{} {}", key, value);
	// }
}