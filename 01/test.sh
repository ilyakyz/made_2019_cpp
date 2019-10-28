assert_result() {
	result=`./calc "$1"`
	code="$?"
	if [ "$code" -ne 0 ]; then
	    echo "WRONG CODE: $code"
	    exit -1
	fi
	if [ "$result" = "$2" ]; then
	    echo "OK"
	else
	    echo "WRONG RESULT $1: $result"
	    exit -1
	fi
}

assert_fail() {
	result=`./calc "$1" 2>/dev/null`
	code="$?"
	if [ "$code" -eq 0 ]; then
	    echo "WRONG CODE: $code"
	    exit -1
	fi
	echo "OK"
}

assert_fail ""
assert_result "2" 2
assert_result "-2" -2
assert_fail "- 2"
assert_result "2 + 3" 5
assert_result "2 - 3" -1
assert_result "2+3" 5
assert_result "  2  + 3  " 5
assert_fail "2 - + 2"
assert_result "2 * 3" 6
assert_result "1 + 1 * 2 + 3" 6
assert_result "1 + 1 * 2 * 3" 7
assert_result "1 + 1 * -2" -1
assert_result "3 / 2" 1.5
assert_fail "1 / 0"