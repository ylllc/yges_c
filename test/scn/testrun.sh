#!/bin/bash

# The work directory always this place. 
cd $(dirname $0)

# Become 1 if failed.
EXITCODE=0

BASEDIR=$1
if [ -z $BASEDIR ]; then
	BASEDIR='.'
fi

# Test a scenario. 
test_one () {

	tmp=$1
	EXE=${tmp#$BASEDIR/}

	"$BASEDIR/$EXE"
	if [ $? -ne 0 ]; then
		EXITCODE=1

		# Bad end in a scenario.
		echo "* [FAILED] $EXE"
		echo "*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*"
	fi
}

# Find all scenaria in the base directory 
# And run them.
test_all () {

	while read exe
	do
		test_one "$exe"
	done <<< $(find "$BASEDIR" -name '*.exe')
}

# BASEDIR is required
if ! [ -d $BASEDIR ]; then
	echo "* $BASEDIR not found"
	EXITCODE=1
else
	test_all
fi

# Good end in all scenaria.
if [ $EXITCODE -eq 0 ]; then
	echo "* Test all OK in $BASEDIR"
fi

exit $EXITCODE
