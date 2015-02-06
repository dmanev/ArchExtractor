#!/bin/bash
#
# Runs all python unittest files in the current
# folder. And generates coverage html report.

COVERDIR="./cover"

export PYTHONPATH="${PYTHONPATH}:../:../umlgen:../umlgen/Base:\
../umlgen/Base/SwComponent:../umlgen/Specific/STK:../../xmi"

if [ -d ${COVERDIR} ]; then  
    rm -r ${COVERDIR}
fi

nosetests --with-coverage --cover-erase --cover-html\
          --cover-package=umlgen
