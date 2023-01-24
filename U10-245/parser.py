import sys
import os
import argparse
from dicc import utils

# Instantiate the parser
parser = argparse.ArgumentParser(description='CoCC Compiler')

# Required positional argument
parser.add_argument('file', type=str,
                    help='DICC file to compile')
                    

args = parser.parse_args()

# Read file
if not os.path.exists(args.file):
    raise Exception(f"Specified file \"{args.file}\" not found!")

filestring = utils.strip_file(args.file)


print(filestring)
