#!/usr/bin/env python3

import random
import sys

def genwords(samplesize, numwords):
	words = open("/usr/share/dict/words").readlines()
	words = random.sample(words, samplesize)

	out = open("words.txt", "w")

	for i in range(numwords):
		out.write(random.choice(words))

	out.close()

genwords(int(sys.argv[1]), int(sys.argv[2]))
