'''
Created on Sep 30, 2010

@author: amanevd
'''

import re

class CCode(object):
    '''
    classdocs
    '''

    def __init__(self):
        '''
        Constructor
        '''
        super(CCode)

    def commentRemove(self, inpContent):        
        i = 0
        withoutComment = ''
        self._Content = inpContent
        #join end-line backslash
        wc_lines = re.split(r'\\\n', self._Content)
        self._Content = ''.join(wc_lines)
        wc_lines = re.split('\n', self._Content)
        new_wc_lines = []
        for str in wc_lines:
            if str!='':
                line = re.sub(r'/\*.*\*/', '', str)
                line = re.sub(r'//.*$', '', line)
                if line != '':
                    new_wc_lines.append(line)
        self._Content = '\n'.join(new_wc_lines)        
        comment = False
        while i < len(self._Content):
            if comment:
                if self._Content[i] == '*' and self._Content[i+1] == '/':  
                    comment = False
                    i = i + 2
                else:
                    i = i + 1                    
            else:
                if self._Content[i] == '/' and self._Content[i+1] == '*':
                    comment = True
                    i = i + 2
                else:
                    withoutComment = withoutComment + self._Content[i]                    
                    i = i + 1
        self._Content = withoutComment

        return self._Content
