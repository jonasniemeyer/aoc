class Directory:
    def __init__(self, name, parent=None):
        self.name = name
        self.parent = parent
        self.children = {}
        self.files = {}
    
    def add_file(self, name, size):
        self.files[name] = size
    
    def add_children(self, name, dir):
        if dir not in self.children:
            self.children[name] = dir

def build_directory_tree(input_str: str) -> Directory:    
    root_dir = Directory(name="/", parent=None)
    dir = root_dir
    for row in input_str.splitlines()[1:]:
        if row.startswith("$ cd"):
            old_dir = dir
            dir_name = row.split("$ cd")[1].strip()
            if dir_name == "..":
                dir = old_dir.parent
            elif dir_name in old_dir.children:
                dir = old_dir.children[dir_name]
            else:
                dir = Directory(name=dir_name, parent=old_dir)
                old_dir.add_children(dir.name, dir)
        
        elif not row.startswith("$ ls"):
            if row.startswith("dir"):
                dir_name = row.split(" ")[1]
                dir.add_children(dir_name, Directory(dir_name, dir))
            else:
                size, file_name = row.split(" ")
                size = int(size)
                dir.add_file(file_name, size)
        
    return root_dir

def compute_dir_size(dir: Directory) -> int:
    size = sum(dir.files.values())
    for child in dir.children.values():
        size += compute_dir_size(child)
    return size

def compute_total_size(dir: Directory, threshold: int) -> None:
    global total_dir_size
    size = compute_dir_size(dir)
    if size <= threshold:
        total_dir_size += size
    
    for child in dir.children.values():
        compute_total_size(child, threshold)

    return None

if __name__ == "__main__":
    with open("input7.txt", "r") as file:
        puzzle_input = file.read()
    
    root_dir = build_directory_tree(puzzle_input)
    total_dir_size = 0
    compute_total_size(root_dir, threshold=100000)
    
    print(total_dir_size)