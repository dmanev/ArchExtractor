#!/bin/bash

export PYTHONPATH="../:\
../umlgen:\
../umlgen/Base:\
../umlgen/Specific/STK:\
../umlgen/Base/SwComponent:\
../../xmi"

#echo $PYTHONPATH

./ArchExtractorGui.py

#ipython
