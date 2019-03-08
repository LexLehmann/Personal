from Fraction import Fraction

x = [Fraction(2,7), Fraction(1,8), Fraction(1,8), Fraction(1,8), Fraction(1,8)]
x_a = [Fraction(2,7), Fraction(1,8), Fraction(1,8), Fraction(1,8)]
x_b = [Fraction(2,7), Fraction(1,8), Fraction(1,8), Fraction(1,8)]
x_ab = [Fraction(2,7), Fraction(1,8), Fraction(1,8)]
x_ba = [Fraction(2,7), Fraction(1,8), Fraction(1,8)]

votes = [x, x_a, x_b, x_ab, x_ba]
for num in range(0, 3):

    tempVotes = []
    for list in votes:
        temp = []
        for fraction in list:
            temp.append(Fraction(fraction.numer, fraction.denom))
        tempVotes.append(temp)

    #mathy stuff here


    for list in votes:
        line = ""
        for fraction in list:
            line = line + " " + str(fraction)
        print(line)
    print()