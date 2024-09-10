#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <fstream>
#include <vector>
#include <tsl/robin_map.h>

int main() {
	std::ifstream f("words.txt");
	std::string line;

	std::vector<std::string> lines;
	tsl::robin_map<std::string, int> freq;

	while (std::getline(f, line)) {
		lines.push_back(line);
	}

	clock_t start = clock();

	for (std::string& line : lines) {
		freq[line] += 1;
	}

	clock_t end = clock();
	double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("%f", cpu_time_used);

	// for (auto kv : freq) {
	// 	printf("%s %d\n", kv.first.c_str(), kv.second);
	// }

	return 0;
}
