'''
Created on Oct 1, 2010

@author: mitko
'''

import os

def pathDelimiter():
    Result = ''
    if 'posix'==os.name:
        Result='/'
    elif 'nt'==os.name:
        Result='\\'
    return Result
