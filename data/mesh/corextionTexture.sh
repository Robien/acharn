#!/bin/bash
find . | grep "\.irr" | grep -v svn | xargs ./transformTex.sh 
