
'''
todo valve set readonly permissions on files
'''

import sys
import os
from pathlib import Path
from shutil import copyfile

dirpath = os.getcwd()
file_name = open(sys.argv[1], "r")

def FileExists(file):
    my_file = Path(file)
    return my_file.exists()

def CleanFileName(filename):
    return filename.replace("\n", "")

for file in file_name:
    
    if file.startswith('//') or file.startswith('\n'):
        continue
    
    src_file = CleanFileName(file)
    src_file = dirpath + "\\" + src_file
    
    dst_file = CleanFileName(file).replace("_tmp", "")
    dst_file = dirpath + "\\" + dst_file

    if FileExists(src_file):
        copyfile(src_file, dst_file)
    else:
        print(src_file + " does not exist")

file_name.close()