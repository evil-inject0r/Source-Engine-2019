
'''
todo valve set readonly permissions on files
'''

import sys
import os
from pathlib import Path
from shutil import copyfile

dirpath = os.getcwd()
file_name = open(sys.argv[1], "r")

def file_exists(file):
    my_file = Path(file)
    return my_file.exists()

for file in file_name:
    
    if file.startswith('//') or file.startswith('\n'):
        continue

    file = file.replace("\n", "")
    
    src_file = dirpath + "\\" + file
    dst_file = dirpath + "\\" + file.replace("_tmp", "")

    if file_exists(src_file):
        copyfile(src_file, dst_file)
    else:
        print(src_file + " does not exist")

file_name.close()