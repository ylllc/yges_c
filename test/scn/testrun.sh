#!/bin/bash

# The work directory always this place. 
cd $(dirname $0)
ROOTDIR=$PWD

# Log directory.
LOGDIR=../log

# Become 1 if failed.
EXITCODE=0

BASEDIR=$1
if [ -z $BASEDIR ]; then
	BASEDIR='.'
fi

# Prepare log directory.
if ! [ -d "$LOGDIR" ]; then
	mkdir "$LOGDIR"
fi

# Test a scenario. 
test_one () {

	# EXE path.
	tmp=$1
	EXE=${tmp#$BASEDIR/}

	# Log path.
	DATE=`date +%Y%m%d-%H%M%S`
	PATH2=`echo $EXE | sed -e 's/\//~/g'`
	LOGFILE="${DATE}_${PATH2%.*}.log"
	LOGPATH="$ROOTDIR/$BASEDIR/${LOGDIR}/${LOGFILE}"

	# Test Settings 
	TEST_WILL_EXIT_WITH=0

	CFGFILE="${EXE%.*}.cfg"
	if [ -f $CFGFILE ]; then
		source $CFGFILE
	fi

	# Execute and result.
	WORKDIR="$BASEDIR/$(dirname $EXE)"
	EXENAME=$(basename $EXE)

	pushd "$WORKDIR" >/dev/null
	"./$EXENAME" > "$LOGPATH"
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
		echo "* [FAILED] $EXE exited as $RESULT ($LOGINFO)"
		echo "*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*"
	fi
}

# Find all scenaria in the base directory 
# And run them.
test_all () {

echo "test_all"

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
