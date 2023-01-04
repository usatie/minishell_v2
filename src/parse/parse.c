#include <stdlib.h>
#include "minishell.h"

// <pipeline> = <simple_command> ('|' <pipeline>)
// <simple_command> = <command_element>+
// <command_element> = <word> | <redirection>
// <redirection> = '>' <word>
//               | '<' <word>
//               | '>>' <word>
//               | '<<' <word>
t_node	*parse(t_token *tok)
{
	return (pipeline(&tok, tok));
}
