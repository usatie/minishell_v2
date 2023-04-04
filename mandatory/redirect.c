/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoshika <myoshika@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 20:41:33 by myoshika          #+#    #+#             */
/*   Updated: 2023/03/15 17:18:53 by myoshika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"

	// open_redir_file(); // 必要なfileをopenしたり、heredocの場合はpipeを作成したり
	// do_redirect();     // dupを用いて、fdのredirectを行う
	// exec_cmd();        // コマンドを実行する
	// reset_redirect();

	// int		infile;
	// int		outfile;
	// char		*filename;
	// int		file_fd;
	// int		stashed_fd;

void	set_up_redirect()
{
	open_redir_file();
	do_redirect();
}

void	open_redir_file(int target_fd, char *filename)
{
	int	file_fd;
	int	stashed_target_fd;

	file_fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	file_fd = stashfd(file_fd);

	stashed_target_fd = stashfd(target_fd);
	// if (file_fd )
}

int	stashfd(int fd)
{
	int	stashfd;

	stashfd = fcntl(fd, F_DUPFD, 10);
	if (stashfd < 0)
		print_error_and_exit("fcntl failure");
	if (close(fd) < 0)
		print_error_and_exit("close failure");
	return (stashfd);
}
//この関数の重要性がわからないのでそのまま考えずに書き写しました。
//今度説明いただきたいです。