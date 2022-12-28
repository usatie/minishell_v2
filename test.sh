#!/bin/bash -e

# EOF
echo | bash
echo | ./minishell
echo 'EOF OK'

# echo hello
echo 'echo hello' | bash >cmp
echo 'echo hello' | ./minishell >out
diff cmp out
echo 'echo hello OK'

echo 'all OK'
