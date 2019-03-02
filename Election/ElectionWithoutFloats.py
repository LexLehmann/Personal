def removeLowest():
    minVotes = -1
    for person in canadites:
# Need other qualifiers for who to eliminate if the canadites are tied
        if (minVotes == -1 or person[1] < canadites[minVotes][1]) and person[2]:
            minVotes = canadites.index(person)
    canadites[minVotes][2] = False
    canadites[minVotes][1] = 0

    for voter in partyVoters[minVotes]:
        countOfTies = 0
        i = 0
        for choice in voter:
            if choice == voter[minVotes] and canadites[i][2]:
                countOfTies += 1
            i += 1

        if countOfTies != 0:
            eachPiece = (numVotesPerPerson/(countOfTies + 1)) / countOfTies
            i = 0
            #print(eachPiece)
            for vote in voter:
                if vote == voter[minVotes] and canadites[i][2]:
                    canadites[i][1] += eachPiece
                i = i + 1

        else :
            distributeNewVotes(voter);

def distributeNewVotes(voter):
    minVal = -1
    count = 0
    i = 0
    for vote in voter:
        if canadites[i][2] and (minVal == -1 or minVal > vote):
            minVal = vote
            count = 1
        elif canadites[i][2] and minVal == vote:
            count += 1
        i += 1
    #print(numVotesPerPerson/count)
    for j in range(len(voter)):
        if voter[j] == minVal and canadites[j][2]:
            canadites[j][1] = canadites[j][1] + numVotesPerPerson / count
            partyVoters[j].append(voter)


def elimination():
    Seats = 1
    electionDone = False
    threshold = len(votes)*numVotesPerPerson / Seats

    for canadite in canadites:
        if canadite[1] >= threshold:
            electionDone = True

    while not electionDone:
        removeLowest()
        totalVotes = 0

        for canadite in canadites:
            totalVotes += canadite[1]
        print(totalVotes)

        for canadite in canadites:
            if canadite[1] >= threshold:
                electionDone = True
        print(canadites)


from sys import stdin

inputFile = open("votes.txt", "r")
votes = []
for line in inputFile:
    vote = line.strip('\n').split(" ")
    votes.append(vote)

i = 0
canadites = []
for vote in votes[0]:
    canadite = [i, 0, True]
    i += 1
    canadites.append(canadite)

numVotesPerPerson = 1
for i in range(len(votes[0])):
    if i > 0 and numVotesPerPerson % (i) != 0:
        increaseBy = i
        for j in range(i):
            if j > 0 and i % (j) == 0:
                increaseBy /= (j)
        while increaseBy % 2 == 0:
            increaseBy /= 2
        numVotesPerPerson *= increaseBy

print(numVotesPerPerson)

partyVoters = []
for i in range(len(canadites)):
    partyVoters.append([])

canadites[1][2] = False

for vote in votes:
    distributeNewVotes(vote)

print(canadites)
elimination()