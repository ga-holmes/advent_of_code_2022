
# in python today because I felt like it
# run with 'python day7.py' (NOTE: python3)

total_size = 0

class Directory:
    name = ''
    size = 0
    added = False
    files = []
    dirs = []

    def __init__(self, name):
        self.name = name

    def is_added(self):
        return self.added

    def get_name(self):
        return self.name

    def get_size(self):
        return self.size

    def add_dir(self, dir):
        self.dirs.append(dir)
    
    def add_file(self, file):
        self.files.append(file)

    def get_dir(self, name):
        for d in self.dirs:
            if(d.get_name() == name):
                return d
        return None

    def add_size(self, size):
        self.size += size

    def __str__(self):
        return f"\'{self.name}\'"


root = Directory("/")
currDir = root

visited = []
visited.append(currDir)

all_dirs = []
all_dirs.append(currDir)

# modes: 1=add to current directory, 
mode = 0
prev_file = False

with open("day7in.txt") as f:
    for line in f.readlines():
        line = line.replace('\n', '')
        
        print(line)
        if('$' in line):

            # if('$ ls' in line):
            #     print("\tmode = 1")
            #     mode = 1
            # else:
            #     mode = 0
            #     if(prev_file):
            #         currDir.added = True
            
            if('$ cd' in line):
                if ('..' in line):
                    visited.pop()
                    currDir = visited[-1]
                    print(f"\tmoving back, CD={currDir.get_name()}")
                else:
                    new_dir = currDir.get_dir(line.split(' ')[-1])
                    if(not new_dir == None):
                        currDir = new_dir
                        visited.append(currDir)
                        print(f"\tmoving forward, CD={currDir.get_name()}")
                print("\t", *visited)


        else:
            # prev_file = True
            if('dir' in line):
                new = Directory(line.split(' ')[-1])
                all_dirs.append(new)
                currDir.add_dir(new)
                print(f"\tadded dir {new} to {currDir}")
            else:
                fsize = int(line.split(' ')[0])
                total_size += fsize
                currDir.add_file((fsize, line.split(' ')[-1]))
                print(f"\tadded file {line.split(' ')[-1]} to {currDir}")

                for d in visited:
                    d.add_size(fsize)

    f.close()

print(*all_dirs)
print(total_size, "bytes in system")

final_count = 0
for d in all_dirs:
    print(d, "size:", d.get_size())
    if d.get_size() <= 100000:
        final_count += d.get_size()

print("final:", final_count)