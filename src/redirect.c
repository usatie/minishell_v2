#include <fcntl.h>
#include <unistd.h>
#include "minishell.h"

int	stashfd(int fd)
{
	int	stashfd;

	stashfd = fcntl(fd, F_DUPFD, 10);
	if (stashfd < 0)
		fatal_error("fcntl");
	if (close(fd) < 0)
		fatal_error("close");
	return (stashfd);
}

int	open_redir_file(t_node *redir)
{
	if (redir == NULL)
		return (0);
	if (redir->kind == ND_REDIR_OUT)
		redir->filefd = open(redir->filename->word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir->kind == ND_REDIR_IN)
		redir->filefd = open(redir->filename->word, O_RDONLY);
	else
		todo("open_redir_file");
	if (redir->filefd < 0)
	{
		xperror(redir->filename->word);
		return (-1);
	}
	redir->filefd = stashfd(redir->filefd);
	return (open_redir_file(redir->next));
}

void	do_redirect(t_node *redir)
{
	if (redir == NULL)
		return ;
	if (redir->kind == ND_REDIR_OUT || redir->kind == ND_REDIR_IN)
	{
		redir->stashed_targetfd = stashfd(redir->targetfd);
		dup2(redir->filefd, redir->targetfd);
	}
	else
		todo("do_redirect");
	do_redirect(redir->next);
}

// Reset must be done from tail to head
void	reset_redirect(t_node *redir)
{
	if (redir == NULL)
		return ;
	reset_redirect(redir->next);
	if (redir->kind == ND_REDIR_OUT || redir->kind == ND_REDIR_IN)
	{
		close(redir->filefd);
		close(redir->targetfd);
		dup2(redir->stashed_targetfd, redir->targetfd);
	}
	else
		todo("reset_redirect");
}
