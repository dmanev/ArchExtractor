#!/usr/bin/python
'''
Created on Nov 10, 2014

@author: mitko
'''

import os
import Tkinter as tk
import tkFont
import tkFileDialog
from ArchExtractor import ArchExtractor


class ArchExtractorGui(tk.Frame):
    def __init__(self, master=None):
        tk.Frame.__init__(self, master)
        self.master.title('ArchExtractor')
        self.pack(fill="both", expand=True)
        self.customFont = tkFont.Font(family="Verdana", size=14)
#         self.bind('<Up>', self.onFontBigger())
        self.createWidgets()

#     def onFontBigger(self):
#         size = self.customFont['size']
#         self.customFont.configure(size=size+2)

    def createWidgets(self):
        top_frame = tk.Frame(self)
        button_frame = tk.Frame(self)
        top_frame.pack(side="top", fill="x")
        button_frame.pack(side="bottom", fill="both", expand=True)

        self.entry = tk.Entry(top_frame, font=self.customFont)
        self.entry.pack(side="top", fill="x")
        self.entry.insert(0, os.getcwd())

        self.label = tk.Label(top_frame,
                              text="Select Project directory",
                              anchor="w",
                              fg="white",
                              bg="blue",
                              font=self.customFont)
        self.label.pack(side="top", fill="x")

        self.buttonGetDir = tk.Button(button_frame,
                                      text=u"Get Project Directory",
                                      command=self.askDirectory,
                                      font=self.customFont)
        self.buttonGetDir.pack(side="left", fill="both", expand=True)

        self.buttonAnalyze = tk.Button(button_frame,
                                       text=u"Analyze",
                                       command=self.analyzeProject,
                                       font=self.customFont)
        self.buttonAnalyze.pack(side="left", fill="both", expand=True)

    def askDirectory(self):
        dirPath = tkFileDialog.askdirectory(parent=self,
                                            title='Choose directory')
        self.entry.delete(0, tk.END)
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
    app = ArchExtractorGui(tk.Tk())
    app.mainloop()
