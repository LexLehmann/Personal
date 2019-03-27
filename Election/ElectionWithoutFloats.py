from Fraction import Fraction

def removeLowest():
    minVotes = -1
    for person in canadites:
# Need other qualifiers for who to eliminate if the canadites are tied
        if (minVotes == -1 or person[1] < canadites[minVotes][1]) and person[2]:
            minVotes = canadites.index(person)
    canadites[minVotes][2] = False
    canadites[minVotes][1] = Fraction(0, 1)

    canaditeCount = 0
    for canadite in partyVoters:
        if canaditeCount != minVotes:
            for vote in partyVoters[canaditeCount]:
                emptyList = 0
                for rank in vote[0]:
                    pos = 0
                    for item in rank:
                        if item == minVotes:
                            rank.pop(pos)
                            if len(vote[0][emptyList]) == 0:
                                vote[0].pop(emptyList)
                        pos += 1
                    emptyList += 1
        canaditeCount += 1

    for vote in partyVoters[minVotes]:
        distributeNewVotes(vote[0], vote[1])

def distributeNewVotes(voter, amount):
    for vote in voter[0]:
        newVote = []
        for list in voter:
            nextList = []
            for item in list:
                nextList.append(item)
            newVote.append(nextList)
        divs = len(newVote[0])
        newVote[0].pop(newVote[0].index(vote))

        if len(newVote[0]) == 0:
            newVote.pop(0)

        found, place = findCopy(newVote, vote)

        #print(newVote, place, found, vote)
        split = amount/divs
        if found:
            partyVoters[vote][place][1] += split
            canadites[vote][1] += split
        else:
            all = [newVote, split]
            partyVoters[vote].insert(place, all)
            canadites[vote][1] += split

def findCopy(vote, canaditeList):
    count = 0
    notPassed = True
    equal = False
    if len(partyVoters[canaditeList]) > 0:
        while(notPassed):
            if count >= len(partyVoters[canaditeList]) or len(vote) == 0 or len(vote[0]) > len(partyVoters[canaditeList][count][0][0]):
                notPassed = False
                #print("test")
            elif(len(vote[0]) == len(partyVoters[canaditeList][count][0][0])):
                i = 0
                equal = True
                for rank in vote:
                    if(len(rank) == len(partyVoters[canaditeList][count][0][i])):
                        j = 0
                        for item in rank:
                            if (item != partyVoters[canaditeList][count][0][i][j]):
                                equal = False
                            j += 1
                    else:
                        equal = False
                    i += 1
                if equal:
                    notPassed = False
            count += 1
    else:
        equal = False
        count = 1

    return equal, count-1

def cutTop(threshold):
    maxVotes = 0
    for canadite in canadites:
        if canadite[1] > maxVotes:
            maxVotes = canadite[1]

    print(maxVotes)

    while maxVotes >= threshold + Fraction(1, 10000):
        print(canadites)
        print(partyVoters)
        toDistribute = []
        for canadite in canadites:
            if canadite[1] > threshold:
                amountStaying = threshold/canadite[1]
                print(amountStaying)
                for vote in partyVoters[canadite[0]]:
                    print(vote[1])
                    var = vote[1]*amountStaying
                    newVote = [vote[0], vote[1]-var]
                    vote[1] = var
                    print(vote[1])
                    canadite[1] -= newVote[1]
                    toDistribute.append(newVote)

        print(partyVoters)

        for item in toDistribute:
            print(item)
            distributeNewVotes(item[0], item[1])

        print(partyVoters)

        maxVotes = 0
        for canadite in canadites:
            if canadite[1] > maxVotes:
                maxVotes = canadite[1]

        print(maxVotes)




def elimination():
    Seats = 5
    electionDone = False
    threshold = Fraction(len(votes), Seats)
    canaditesLeft = len(canadites)

    while canaditesLeft > Seats:
        cutTop(threshold)

        removeLowest()
        canaditesLeft -= 1

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
    canadite = [i, Fraction(0,1), True]
    i += 1
    canadites.append(canadite)

ranks = []

for voter in votes:
    thisRank = []
    added = 0
    previous = 0
    while added < len(canadites):
        minChoice = 100000000
        for vote in voter:
            if int(vote) < minChoice and int(vote) > previous:
                minChoice = int(vote)
        tied = []
        i = 0
        for vote in voter:
            if int(vote) == minChoice:
                tied.append(i)
            i += 1
        thisRank.append(tied)
        previous = minChoice
        added += len(tied)
    ranks.append(thisRank)

print(ranks)

partyVoters = []
for i in range(len(canadites)):
    partyVoters.append([])

for voter in ranks:
    distributeNewVotes(voter, Fraction(1,1))


elimination()
