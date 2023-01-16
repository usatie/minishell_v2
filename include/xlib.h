/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xlib.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 18:46:00 by susami            #+#    #+#             */
/*   Updated: 2023/01/13 06:15:11 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XLIB_H
# define XLIB_H

# include <signal.h>
# include <sys/stat.h>

// src/lib/
void	*xmalloc(size_t size);
void	*xcalloc(size_t count, size_t size);
char	*xstrdup(const char *s1);
char	*xstrndup(const char *s1, size_t size);
int		xclose(int fd);
int		xdup2(int fildes, int fildes2);
int		xpipe(int fildes[2]);

#endif
