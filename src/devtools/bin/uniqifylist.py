import sys
files = set()

for line in sys.stdin:
    files.add(line)

files = sorted(files)

for f in files:
    print(f, end=' ')
