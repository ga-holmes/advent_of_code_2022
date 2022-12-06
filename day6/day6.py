
# in python today because honestly its just the best language for this one
# run with 'python day5.py' (NOTE: python3)

# set to 14 for part 2, 4 for part 1
n = 14

first_sequence = 0

# checks whether all values inan array are unique
def not_inc(arr):
    # converting to a set will remove all duplicate items
    set_arr = set(arr)

    # compare the length - if the same, there were no duplicates
    if (len(set_arr) == len(arr)):
        return True
    
    return False
    

# array containing the last (n) elements
last_n = []

with open("day6in.txt") as f:
    line = f.readline()

    for i, c in enumerate(line):
        first_sequence += 1

        # for the first part - to fill up last_n array
        if i < n:
            last_n.append(c)
        else: # adding new elements and checking
            last_n.pop(0)
            last_n.append(c)
            
            if(not_inc(last_n)):
                break

    f.close()

print("first sequence at index", first_sequence)