#!/usr/bin/python3
import argparse
import subprocess
import os
import sys
from colorama import Fore, Style

DESCRIPTION = "Helper script to build and format code in a cpp repository"

SCRIPT_DIR = os.path.dirname(__file__)
BUILD_DIR = f'{SCRIPT_DIR}/../build'
SRC_DIR = f'{SCRIPT_DIR}/..'

def print_col(txt, col):
    print(f'{col}{txt}{Style.RESET_ALL}')

def run(cmd, dryrun, verbose):
    if(dryrun or verbose):
        print_col(cmd, Fore.YELLOW)

    if(dryrun):
        return

    ret = subprocess.run(cmd, shell=True)
    if(ret.returncode != 0):
        raise RuntimeError(f"Command: {cmd} returned with non-zero return code {ret.returncode}")

    
def format_repo(dryrun, verbose):
    '''
    Runs clag-format one all *.cpp and *.h files in ../
    '''
    cmd = f'find {SRC_DIR} -iname *.h -o -iname *.cpp | xargs clang-format -i --style=file'

    if verbose:
        cmd =+ ' --verbose'
        
    run(cmd, dryrun, verbose)
    

def cmake(dryrun, verbose):
    cmd = f'cmake -B {BUILD_DIR} -S {SRC_DIR} -D CMAKE_CXX_COMPILER=g++'
    if verbose:
        cmd = 'export VERBOSE=1 && ' + cmd
    run(cmd, dryrun, verbose)

def build_application(dryrun, verbose):
    # cmd1 is needed by clang-tidy.
    cmd1 = 'export CPLUS_INCLUDE_PATH=/usr/include/c++/11:/usr/include/x86_64-linux-gnu/c++/11'
    cmd2 = f'cmake --build {BUILD_DIR}'

    if verbose:
        cmd1 = 'export VERBOSE=1 && ' + cmd1

    run(f'{cmd1} && {cmd2}', dryrun, verbose)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=DESCRIPTION)
    parser.add_argument('-a', '--all', action='store_true', help='Apply all actions (build, cmake, format, ...)')
    parser.add_argument('-d', '--dryrun', action='store_true', help='Show commands, but don\'t run them')
    parser.add_argument('-v', '--verbose', action='store_true', help='Verbose output')
    parser.add_argument('-c', '--cmake', action='store_true', help='Run cmake')
    parser.add_argument('-b', '--build', action='store_true', help='Build the project')
    parser.add_argument('-f', '--format', action='store_true', help='Run clang-format on all *.cpp and *.h files in the repository')
    args = parser.parse_args()

    if(args.all):
        args.format = True
        args.cmake = True
        args.build = True

    try:
        if(args.format):
            format_repo(args.dryrun, args.verbose)
    
        if(args.cmake):
            cmake(args.dryrun, args.verbose)

        if(args.build):
            build_application(args.dryrun, args.verbose)

        sys.exit(0)
        
    except Exception as e:
        print_col(e, Fore.RED)
        sys.exit(1)
