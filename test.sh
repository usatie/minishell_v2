#!/bin/bash

cleanup() {
	rm -f cmp out
}

assert() {
	printf '%-30s:' "\"$1\""
	# exit status
	echo "$1" | bash >cmp 2>&-
	expected=$?
	echo "$1" | ./minishell >out 2>&-
	actual=$?

	diff cmp out && echo -n '  diff OK' || echo -n '  diff NG'

	if [ "$actual" = "$expected" ]; then
		echo -n '  status OK'
	else
		echo -n "  status NG, expected $expected but got $actual"
	fi
	echo
}

assert ''
assert 'echo hello'
assert 'grep hoge .'

cleanup
echo 'all OK'
