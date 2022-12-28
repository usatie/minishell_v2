#!/bin/bash

# EOF
echo | bash
echo | ./minishell
echo 'EOF OK'

# echo hello
echo 'echo hello' | bash >cmp
echo 'echo hello' | ./minishell >out
diff cmp out
echo 'echo hello OK'

# exit status
echo 'grep hoge .' | bash >cmp 2>&-
expected=$?
echo 'grep hoge .' | ./minishell >out 2>&-
actual=$?

diff cmp out
if [ "$actual" = "$expected" ]; then
	echo 'status OK'
else
	echo "status NG, expected $expected but got $actual"
fi

echo 'all OK'
