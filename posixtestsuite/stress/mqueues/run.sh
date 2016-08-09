#!/bin/sh
# Copyright (c) 2002, Intel Corporation. All rights reserved.
# Created by:  crystal.xiong REMOVE-THIS AT intel DOT com
# This file is licensed under the GPL license.  For the full content
# of this license, see the COPYING file at the top level of this
# source tree.
#
# Run all the tests in the message queues stress area.

# Helper functions
RunTest()
{
	echo "TEST: " $1 $2
	TOTAL=$((TOTAL+1))
	./$1 $2
	if [ $? = 0 ]; then
		PASS=$((PASS+1))
		echo "                  ***TEST PASSED***"
		echo
	else
		FAIL=$((FAIL+1))
		echo "                  ***TEST FAILED***"
		echo
	fi
}

# Main program

TOTAL=0
PASS=0
FAIL=0

# Add lists of tests to these variables for execution
TESTS="multi_send_rev_1.test multi_send_rev_2.test"

echo "Run the message queue stress tests"
echo "=========================================="

RunTest multi_send_rev_1.test 10
RunTest multi_send_rev_2.test 100
 

echo
echo "         ****************"
echo "         * TOTAL:  " $TOTAL
echo "         * PASSED: " $PASS
echo "         * FAILED: " $FAIL
echo "         ****************"

exit 0


