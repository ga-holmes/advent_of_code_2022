
my_score = 0
your_score = 0

# conversion values
# (score, type you, type me, item that it beats)
conv = [
    (1, 'A', 'X', 3), # rock
    (2, 'B', 'Y', 1), # paper
    (3, 'C', 'Z', 2) # scissors
]

with open("day2in.txt") as f:
    for line in f.readlines():
        
        for c in conv: # associate the input with the rps conversion values
            if(line[0] == c[1]):
                you = c

            if(line[2] == c[2]):
                me = c

        if (you == me): # tie
            my_score += 3
            your_score += 3
        elif(you[0] == me[3]): # i won
            my_score += 6 + me[0]
        elif(me[0] == you[3]): # you won
            your_score += 6 + you[0]


    f.close()

print("you:", your_score)
print("me:", my_score)