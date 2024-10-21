#!/bin/bash

# The work directory always this place. 
cd $(dirname $0)

# Build 
make
if [ $? -ne 0 ]; then
	exit $?
fi

echo "*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*"
echo "* Start TestRunner"
echo "*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*"

# Run the TestRunner 
test/scn/testrun.sh
exit $?
