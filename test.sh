#!/bin/bash

# The work directory always this place. 
cd $(dirname $0)

# TestRunner base directory 
BASEDIR=$1

# Build 
make
if [ $? -ne 0 ]; then
	exit $?
fi

echo "*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*"
echo "* Start TestRunner"
echo "*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*"

# Run the TestRunner 
test/scn/testrun.sh "$BASEDIR"
exit $?
