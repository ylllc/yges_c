#!/bin/bash

# The work directory always this place. 
cd $(dirname $0)
ROOTDIR=$PWD

# Log directory.
LOGDIR=../log

# Become 1 if failed.
EXITCODE=0

# running target directory 
BASEDIR=$1
if [ -z "$BASEDIR" ]; then
	BASEDIR='.'
fi

# Reject illegal basedir 
if [[ ${BASEDIR:0:1} = '/' ]]; then
	echo "* Illegal BASEDIR"
	exit 1
fi
if [[ $BASEDIR =~ \.\. ]]; then
	echo "* Illegal BASEDIR"
	exit 1
fi

# Prepare log directory.
if ! [ -d "$LOGDIR" ]; then
	mkdir "$LOGDIR"
fi

# Test a scenario. 
test_one () {

	# EXE local path.
	EXENAME=$1
	if [ ${EXENAME:0:2} = './' ]; then
		EXENAME=${EXENAME:2}
	fi

	# Log path.
	DATE=`date +%Y%m%d-%H%M%S`
	PATH2=`echo $EXENAME | sed -e 's/\//~/g'`
	LOGFILE="${DATE}_${PATH2%.*}.log"
	LOGPATH="$ROOTDIR/$LOGDIR/$LOGFILE"

	# Test settings.
	TEST_WILL_EXIT_WITH=0

	# Work directory and binary path.
	WORKDIR="$ROOTDIR/$(dirname $EXENAME)"
	EXEFILE=$(basename $EXENAME)

	pushd "$WORKDIR" >/dev/null

	# Config file 
	CFGFILE="${EXEFILE%.*}.cfg"
	if [ -f $CFGFILE ]; then
		source $CFGFILE
	fi

	# Execute and result.
	"./$EXEFILE" > "$LOGPATH"
	RESULT=$?
	popd >/dev/null

	# Remove empty log file.
	LOGSIZE=`wc -c "$LOGPATH" | cut -d' ' -f1`
	if [ $LOGSIZE = 0 ]; then
		rm "$LOGPATH"
	fi

	if [ "$RESULT" != "$TEST_WILL_EXIT_WITH" ]; then
		EXITCODE=1

		if [ -f "$LOGPATH" ]; then
			LOGINFO="see $LOGFILE"
		else
			LOGINFO="no logfile"
		fi

		# Bad end in a scenario.
		echo "* [FAILED] $EXENAME exited as $RESULT ($LOGINFO)"
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
