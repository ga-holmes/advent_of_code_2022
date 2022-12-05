
# in python today because I felt like it
# run with 'python day4.py' (NOTE: python3)

fully_contained = 0

overlaps = 0

with open("day4in.txt") as f:
    for line in f.readlines():
        
        elves = line.split(',')

        e1 = elves[0].split('-')
        e2 = elves[1].split('-')

        for i, e in enumerate(e1):
            e1[i] = int(e1[i])
            e2[i] = int(e2[i])

        # part 1
        if((e1[0] >= e2[0] and e1[1] <= e2[1]) or (e2[0] >= e1[0] and e2[1] <= e1[1])):
            fully_contained += 1

        if(e1[1] >= e2[0] and e1[0] <= e2[1]):
            print(e1, '|', e2)
            overlaps += 1

    f.close()

print(fully_contained, "pairs fully overlap")
print(overlaps, "pairs overlap at all")