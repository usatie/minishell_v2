#!/bin/bash
RED="\033[31m"
GREEN="\033[32m"
RESET="\033[0m"
OK=$GREEN"OK"$RESET
NG=$RED"NG"$RESET

cat <<EOF | gcc -xc -o a.out -
#include <stdio.h>
int main() { printf("hello from a.out\n"); }
EOF

cat <<EOF | gcc -xc -o print_args -
#include <stdio.h>
int main(int argc, char *argv[]) {
	for (int i = 0; argv[i]; i++)
		printf("argv[%d] = %s\n", i, argv[i]);
}
EOF

cleanup() {
	rm -f cmp out a.out print_args
}

assert() {
	COMMAND="$1"
	shift
	printf '%-50s:' "[$COMMAND]"
	# exit status
	echo -n -e "$COMMAND" | bash >cmp 2>&-
	expected=$?
	for arg in "$@"
	do
		mv "$arg" "$arg"".cmp"
	done
	echo -n -e "$COMMAND" | ./minishell >out 2>&-
	actual=$?
	for arg in "$@"
	do
		mv "$arg" "$arg"".out"
	done

	diff cmp out >/dev/null && echo -e -n "  diff $OK" || echo -e -n "  diff $NG"

	if [ "$actual" = "$expected" ]; then
		echo -e -n "  status $OK"
	else
		echo -e -n "  status $NG, expected $expected but got $actual"
	fi
	for arg in "$@"
	do
		echo -n "  [$arg] "
		diff "$arg"".cmp" "$arg"".out" >/dev/null && echo -e -n "$OK" || echo -e -n "$NG"
		rm -f "$arg"".cmp" "$arg"".out"
	done
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
## unquoted word
assert 'ls /'
assert 'echo hello    world     '
assert 'nosuchfile\n\n'

## single quote
assert "./print_args 'hello   world' '42Tokyo'"
assert "echo 'hello   world' '42Tokyo'"
assert "echo '\"hello   world\"' '42Tokyo'"

## double quote
assert './print_args "hello   world" "42Tokyo"'
assert 'echo "hello   world" "42Tokyo"'
assert "echo \"'hello   world'\" \"42Tokyo\""

## combination
assert "echo hello'      world'"
assert "echo hello'  world  '\"  42Tokyo  \""

# Redirect
## Redirecting output
assert 'echo hello >hello.txt' 'hello.txt'
assert 'echo hello >f1>f2>f3' 'f1' 'f2' 'f3'

## Redirecting input
assert 'cat <Makefile'
echo hello >f1
echo world >f2
echo 42Tokyo >f3
assert 'cat <f1<f2<f3'
rm -f f1 f2 f3
assert 'cat <hoge'

## Appending Redirected output
assert 'pwd >>pwd.txt' 'pwd.txt'
assert 'pwd >>pwd.txt \n pwd >>pwd.txt' 'pwd.txt'

## Here Document
assert 'cat <<EOF\nhello\nworld\nEOF\nNOPRINT'
assert 'cat <<EOF<<eof\nhello\nworld\nEOF\neof\nNOPRINT'
assert 'cat <<EOF\nhello\nworld'
assert 'cat <<E"O"F\nhello\nworld\nEOF\nNOPRINT'

cleanup
