line = input().strip('/r').split(" ")

breaks = input().strip('/r').split(" ")

currentTotal = 0
maxTotal = 0

for num in breaks:
    currentTotal = currentTotal + int(num) - int(line[1])
    if currentTotal > maxTotal:
        maxTotal = currentTotal
    elif currentTotal < 0:
        currentTotal = 0

print(maxTotal)
