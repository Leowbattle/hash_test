#!/usr/bin/env python3

import matplotlib.pyplot as plt
import random
import sys
import subprocess

def genwords(samplesize, numwords):
	words = open("/usr/share/dict/words").readlines()
	words = random.sample(words, samplesize)

	out = open("words.txt", "w")

	for i in range(numwords):
		out.write(random.choice(words))

	out.close()

numruns = 10

def runprog(name):
	output = subprocess.check_output(["./" + name], universal_newlines=True)
	return float(output)

def testprog(program_name):
	total_time = 0

	for _ in range(numruns):
		total_time += runprog(program_name)

	average_time = total_time / numruns
	return average_time * 1000

times = {
	"c_linear_probing": [],
	"cpp_unordered_map": [],
	"cpp_map": [],
	"python.py": [],
	"rust_hashmap": [],
	"rust_btreemap": [],
	"rust_fxhash/target/release/rust_fxhash": [],
}

x = range(0, 11000, 1000)

for i in x:
	genwords(i // 10, i)

	for prog in times.keys():
		times[prog].append(testprog(prog))

for prog, times_list in times.items():
	plt.plot(x, times_list, label=prog)

plt.xlim(0, 10000)
plt.ylim(0, 1)

plt.grid(True)
plt.xlabel('Number of Words')
plt.ylabel('Average Time (ms)')
plt.title('Program Execution Time')
plt.legend()
plt.savefig("graph.png")