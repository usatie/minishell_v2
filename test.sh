#!/bin/bash

cat <<EOF | gcc -xc -o a.out -
#include <stdio.h>
int main() { printf("hello from a.out\n"); }
EOF

cleanup() {
	rm -f cmp out a.out
}

assert() {
	printf '%-30s:' "\"$1\""
	# exit status
	echo -n -e "$1" | bash >cmp 2>&-
	expected=$?
	echo -n -e "$1" | ./minishell >out 2>&-
	actual=$?

	diff cmp out >/dev/null && echo -n '  diff OK' || echo -n '  diff NG'

	if [ "$actual" = "$expected" ]; then
		echo -n '  status OK'
	else
		echo -n "  status NG, expected $expected but got $actual"
	fi
	echo
}

# Empty line (EOF)
assert ''

# Absolute path commands without args 
assert '/bin/pwd'
assert '/bin/echo'
assert '/bin/ls'

# Search command path without args
assert 'pwd'
assert 'echo'
assert 'ls'
assert './a.out'

## no such command
assert 'a.out'
assert 'nosuchfile'

# Tokenize
assert 'ls /'
assert 'echo hello    world     '
assert 'nosuchfile\n\n'

cleanup
echo 'all OK'
