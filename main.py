import markov
import random

mc = markov.MarkovChain()

for i in range(100000):
    mc.insert(1.0, round(random.random(), 1))

print(mc.len())
print(mc.probableNextAggressive(1.0))
print(mc.probableNextSafe(1.0))