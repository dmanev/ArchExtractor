#!/bin/bash
#
# Runs all python unittest files in the current
# folder. And generates coverage html report.

COVERDIR="./cover"
TMPFILE="report.tmp"
REPORTFILE="report.txt"

export PYTHONPATH="${PYTHONPATH}:../:../umlgen:../umlgen/Base:\
../umlgen/Base/SwComponent:../umlgen/Specific/STK:../../xmi"

if [ -d ${COVERDIR} ]; then  
    rm -r ${COVERDIR}
fi

nosetests -v --with-coverage --cover-erase --cover-html\
          --cover-package=umlgen 2> ${TMPFILE}

cat ${TMPFILE}

mv ${TMPFILE} ${REPORTFILE}
