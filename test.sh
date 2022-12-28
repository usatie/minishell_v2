#!/bin/bash

assert() {
	echo "[$1]: "
	# exit status
	echo "$1" | bash >cmp 2>&-
	expected=$?
	echo "$1" | ./minishell >out 2>&-
	actual=$?

	diff cmp out
	echo '  diff OK'

	if [ "$actual" = "$expected" ]; then
		echo '  status OK'
	else
		echo "  status NG, expected $expected but got $actual"
	fi
}

assert ''
assert 'echo hello'
assert 'grep hoge .'

echo 'all OK'
