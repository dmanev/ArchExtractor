'''
Created on Nov 10, 2014

@author: mitko
'''

import os
import Tkinter
import tkFileDialog
from ArchExtractor import ArchExtractor


class ArchExtractorGui(Tkinter.Tk):
    def __init__(self, parent):
        Tkinter.Tk.__init__(self, parent)
        self.parent = parent
        self.title('ArchExtractor')
        self.grid()
        self.entry = Tkinter.Entry(self)
        self.entry.grid(column=0, row=0, sticky='EW', columnspan=2)
        self.entry.insert(0, os.getcwd())
        self.buttonGetDir = Tkinter.Button(self,
                                           text=u"Get Project Directory",
                                           command=self.askDirectory)
        self.buttonGetDir.grid(column=0, row=2)
        self.buttonAnalyze = Tkinter.Button(self,
                                            text=u"Analyze",
                                            command=self.analyzeProject)
        self.buttonAnalyze.grid(column=1, row=2)
        self.label = Tkinter.Label(self,
                                   text="Select Project directory",
                                   anchor="w",
                                   fg="white",
                                   bg="blue")
        self.label.grid(column=0, row=1, columnspan=2, sticky='EW')

    def askDirectory(self):
        dirPath = tkFileDialog.askdirectory(parent=self,
                                            title='Choose directory')
        self.entry.delete(0, Tkinter.END)
        self.entry.insert(0, dirPath)
        return dirPath

    def analyzeProject(self):
        dirPath = self.entry.get()
        self.label.config(text="Analyzing...", fg="black", bg="yellow")
        self.label.update_idletasks()
        if os.path.exists(dirPath):
            archExtractor = ArchExtractor()
            archExtractor.analyze(dirPath)
            self.label.config(text="Analysis Done.", fg="black", bg="green")
        else:
            self.label.config(text="The directory does not exists",
                              fg="black",
                              bg="red")


class ArchExtractorGuiException(Exception):
    def __init__(self, message):
        super(self).__init__(message)


if __name__ == '__main__':
    app = ArchExtractorGui(None)
    app.mainloop()
