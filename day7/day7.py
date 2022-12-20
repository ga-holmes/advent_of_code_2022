
# in python today because I felt like it
# run with 'python day7.py' (NOTE: python3)

total_size = 0

class Directory:
    name = ''
    size = 0
    files = []
    dirs = []

    def __init__(self, name):
        self.name = name

    def get_name(self):
        return self.name

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

root = Directory("/")
currDir = root

# modes: 0=add to current directory, 
mode = 0

with open("day7in.txt") as f:
    for line in f.readlines():
        
        if('$ cd' in line and not '/' in line):
            new_dir = currDir.get_dir(line.split(' ')[-1])
            if(not new_dir == None):
                currDir = new_dir
        
        if(not '$' in line):

            if('dir' in line):
                currDir.add_dir(Directory(line.split(' ')[-1]))
            else:
                fsize = int(line.split(' ')[0])
                currDir.add_size(fsize)
                total_size += fsize
                currDir.add_file((fsize, line.split(' ')[-1]))

    f.close()

print(total_size, "bytes in system")