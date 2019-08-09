/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollie <ncollie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 20:54:33 by ncollie           #+#    #+#             */
/*   Updated: 2019/02/24 21:28:05 by ncollie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/common_header.h"

/*
** ERR_N_DIE should close CONNECTION TOO!!! with client(just in case) ???
*/

void	err_n_die(const char *fmt, ...)
{
	va_list		args;
	int			errno_save;

	errno_save = errno;
	va_start(args, fmt);
	printf("%s--------------------------------------%s\n", RED, RESET);
	printf("%s*%s", RED, RESET);
	vprintf(fmt, args);
	if (errno_save != 0)
		perror("Error");
	va_end(args);
	printf("%s--------------------------------------%s\n", RED, RESET);
	exit(1);
}

void	simple_print(int socket_fd, unsigned int length)
{
	char	incoming[MAXLINE];
	int		n;

	memset(incoming, 0, MAXLINE);
	if (length == 0)
		return ;
	while ((n = read(socket_fd, incoming, MAXLINE - 1)) > 0)
	{
		printf("%s\n", incoming);
		if (n < (int)length)
			length -= (int)n;
		else
			break ;
		memset(incoming, 0, MAXLINE);
	}
	if (n < 0)
		err_n_die("read error\n");
}

void	read_n_put_in_file(int file, int data_fd, int length)
{
	int		n;
	char	incoming[MAXLINE];

	memset(incoming, 0, MAXLINE);
	while ((n = read(data_fd, incoming, MAXLINE - 1)) > 0)
	{
		write(file, incoming, n);
		if (n < length)
			length -= n;
		else
			break ;
		memset(incoming, 0, MAXLINE);
	}
	if (n < 0)
		err_n_die("read error\n");
}

void	debug(const char *fmt, ...)
{
	va_list		args;

	printf("%s", RED);
	vprintf(fmt, args);
	printf("%s", RESET);
	fflush(stdout);
}
