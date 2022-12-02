
# in python today because I felt like it
# run with 'python day2.py' (NOTE: python3)

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
        
        # part 1
        # for c in conv: # associate the input with the rps conversion values
        #     if(line[0] == c[1]):
        #         you = c

        #     if(line[2] == c[2]):
        #         me = c
        
        # part 2
        for c in conv: # associate the input with the correct win/lose/draw
            if(line[0] == c[1]):
                you = c

        # get the 'me' move type
        if(line[2] == 'Y'):
            me = you
        elif(line[2] == 'X'): # selects the play that loses against 'you'
            me = conv[you[3]-1]
        elif(line[2] == 'Z'): # the 'me' that beats 'you' will always be the next index in the conv list
            me = conv[you[0]%3]

        print(you, me)

        if (you == me): # tie
            my_score += 3 + me [0]
            your_score += 3 + you[0]
            print("tie")
        elif(you[0] == me[3]): # i won
            print("I won, score:", 6 + me[0])
            my_score += 6 + me[0]
            your_score += you[0]
        elif(me[0] == you[3]): # you won
            print("you won, score:", 6 + you[0])
            your_score += 6 + you[0]
            my_score += me[0]


    f.close()

print("you:", your_score)
print("me:", my_score)