#!/usr/bin/env python3

import time

lines = []
freq = {}

with open("words.txt", "r") as f:
	for line in f:
		lines.append(line.strip())

start = time.process_time()

for line in lines:
	freq[line] = freq.get(line, 0) + 1

end = time.process_time()
cpu_time_used = end - start
print(cpu_time_used)

# for key, value in freq.items():
#     print(key, value)
