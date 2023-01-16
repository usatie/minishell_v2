#!/bin/bash

assert() {
	echo "[$1]: "

	echo "$1" | bash >cmp 2>&-
	expected=$?
	echo "$1" | ./minishell >out 2>&-
	actual=$?

	diff cmp out && echo 'diff OK' || echo 'diff NG'

	if [ "$actual" = "$expected" ]; then
		echo 'status OK'
	else
		echo "status NG, expected $expected but got $actual"
	fi
}

assert ''
assert '/bin/ls'
assert '/bin/echo'

echo 'all OK'
