
# in python today because I felt like it
# run with 'python day5.py' (NOTE: python3)

columns = 0

# given one line in the expected format, gets the correct column index for each actual item and returns a list of the columns - where each column is either empty or has one item
def extract_line(line):
    column_index = 0

    columns = ['-']

    spaces = 0
    for c in line.split(' '):
        if(c == ''):
            spaces += 1
        else:
            columns[column_index] = c
        if spaces % 4 == 0:
            column_index += 1
            columns.append('-')

    return columns

stacks = [[]]

top_of_stacks = ''

with open("day5in.txt") as f:
    for line in f.readlines():

        # create the list of stacks from the input
        if('[' in line):
            extracted = extract_line(line.replace('\n', ''))

            for i, e in enumerate(extracted):

                if (len(stacks) < len(extracted)-1):
                    stacks.append([])

                if (not e == '-'):
                    stacks[i].append(e)

        elif('move' in line):
            lines = line.replace('\n', '').split(' ')

            # get values from the directions 
            count = int(lines[1])
            src = int(lines[3]) - 1
            dest = int(lines[-1]) - 1

            # re-arrange the crates
            for i in range(0, count):
                crate = stacks[src].pop(0)
                # part 1
                # stacks[dest].insert(0, crate)

                # part 2
                stacks[dest].insert(i, crate)


for i, s in enumerate(stacks):
    print(f"{i+1}: {s}")

    top_of_stacks += s[0].replace('[', '').replace(']', '')

print(top_of_stacks)

