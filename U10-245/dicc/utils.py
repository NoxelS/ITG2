def strip_file(file_path):
    s = ""
    with open(file_path, 'r') as f:
        for line in f:
            s = s + line.strip()
    return "".join(s.split())