
line = input()

numOnes = 0
versions = 1
count = 0

for char in line:
    if(char == '1'):
        numOnes += versions
        numOnes = numOnes%1000000007
    elif(char == '0'):
        count += numOnes
        count = count%1000000007
    else:
        count = count * 2 + numOnes
        numOnes = numOnes * 2 + versions
        versions = versions * 2
        numOnes = numOnes%1000000007
        count = count%1000000007
        versions = versions%1000000007

print(count)