import markov

mc = markov.MarkovChain()

mc.insert(1.0, 2.0)
mc.insert(2.0, 3.0)

print(mc.len())
print(mc.probableNextAggressive(1.0))
print(mc.probableNextSafe(1.0))