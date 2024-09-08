#!/usr/bin/env python3

import random
import sys

words = open("/usr/share/dict/words").readlines()
words = random.sample(words, 1000)

numwords = int(sys.argv[1]) if len(sys.argv) > 1 else 10000

out = open("words.txt", "w")

for i in range(numwords):
	out.write(random.choice(words))

out.close()
