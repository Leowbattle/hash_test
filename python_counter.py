#!/usr/bin/env python3

from collections import Counter
import time

lines = []

with open("words.txt", "r") as f:
    for line in f:
        lines.append(line.strip())

start = time.process_time()

Counter(lines)
end = time.process_time()
cpu_time_used = end - start
print(cpu_time_used)