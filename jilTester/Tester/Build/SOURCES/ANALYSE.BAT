echo off
if exist SCC2\SCC2.EXE goto SCC2

:JIL
echo JIL Analysis...
JIL.EXE %* -OUT:..\EXE\GEN -TOS
goto End

:SCC2
echo SCC2 Analysis...
SCC2\SCC2.EXE %* -OUT:..\EXE\GEN -G:SCC2 -Int -DUMP:..\EXE\DB.JIL
SCC2\SCC2.EXE %* -OUT:..\EXE\GENSIMU -G:SCC2 -Simu

:End