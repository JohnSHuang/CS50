from sys import argv
import csv

def is_match(maxcounters, peoples):
    for row in peoples[1:]:
        for count in range(len(row) - 1):
            row[count + 1] = int(row[count + 1])

    for row in peoples:
        if row[1:] == maxcounters:
            print(row[0])
            exit(1)

    print("No match")

while(True):
    if len(argv) != 3:
        print("Invalid number of command-line arguments")
        exit(1)
    else:
        break

with open(argv[1], "r") as namefile:
    reader = csv.reader(namefile)
    peoples = list(reader)
    dnastrands = peoples[0][1:]

with open(argv[2], "r") as dnafile:
    dnadata = dnafile.read()

    maxcounters = []
    for strands in dnastrands:
        maxcounter = 0
        counter = 0
        start = 0
        found = 0
        l = len(strands)

        while(found != -1):
            found = dnadata.find(strands, start)
            if start != found:
                start = found + l
                counter = 0
                counter += 1
            else:
                counter += 1
                start = found + l
            if counter > maxcounter:
                maxcounter = counter
        maxcounters.append(maxcounter)
    is_match(maxcounters, peoples)
