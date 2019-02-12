import random

file = open("votes.txt", "w")
numVotes = 10000
numRanks = 10

for i in range(numVotes):
    vote = ""
    for j in range(numRanks):
        vote += str(random.randint(1, numRanks)) + " "
    file.write(vote + '\n')
