from Fraction import Fraction

x = [Fraction(50,1), Fraction(36,1), Fraction(7,1), Fraction(5,1), Fraction(2,1)]
x_a = [Fraction(20,1), Fraction(10,1), Fraction(15,1), Fraction(5,1)]
x_b = [Fraction(15,1), Fraction(5,1), Fraction(6,1), Fraction(10,1)]
x_ab = [Fraction(13,1), Fraction(10,1), Fraction(7,1)]
x_ba = [Fraction(7,1), Fraction(5,1), Fraction(3,1)]

votes = [x, x_a, x_b, x_ab, x_ba]
T = 25

for num in range(0, 3):

    tempVotes = []
    for list in votes:
        temp = []
        for fraction in list:
            temp.append(Fraction(fraction.numer, fraction.denom))
        tempVotes.append(temp)

    first = T/tempVotes[0][0]
    second = (tempVotes[0][1]+(first*tempVotes[1][0]-T))/(tempVotes[0][1]+first*tempVotes[1][0])
    third = T/(tempVotes[0][1]+ first*tempVotes[1][0])

    count = 0
    for i in votes[0]:
        if count == 0:
            i = T + second*tempVotes[2][0]
        if count == 1:
            i = T
        else:
            i = first*tempVotes[1][count-1] + second * (tempVotes[2][count-1]+ first * tempVotes[3][count-2])
        count += 1

    count = 0
    for i in votes[1]:
        if count == 0:
            i = tempVotes[1][0]*first
        else:
            i = tempVotes[1][count]*first + second * tempVotes[4][count-1]
        count += 1

    count = 0
    for i in votes[2]:
        if count == 0:
            i = tempVotes[1][0]*third
        else:
            i = (tempVotes[2][count] + first*tempVotes[3][count-1]) * third
        count += 1

    count = 0
    for i in votes[3]:
        i = tempVotes[3][count]*first
        count += 1

    count = 0
    for i in votes[4]:
        i = tempVotes[4][count]*third
        count += 1

    for list in votes:
        line = ""
        for fraction in list:
            line = line + " " + str(fraction)
        print(line)
    print()
