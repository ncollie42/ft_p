/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollie <ncollie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 20:50:29 by ncollie           #+#    #+#             */
/*   Updated: 2019/02/24 21:14:30 by ncollie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/common_header.h"

static void		copy_name(char *name, char *s_name)
{
	int	n;

	n = -1;
	while (name && name[++n] && n < 100)
		s_name[n] = name[n];
}

/*
**	loop if fails?
*/

void			send_header(int socket_fd, unsigned int command,
											unsigned int size, char *name)
{
	struct s_header	header;
	int				n;

	header = (struct s_header){ .command = command, .length = size};
	copy_name(name, header.name);
	if ((n = write(socket_fd, &header, sizeof(header)) != sizeof(header)))
		err_n_die("seding header\n");
}

void			send_message(int socket_fd, char *message, int size)
{
	int n;

	if ((n = write(socket_fd, message, size) != size))
		err_n_die("writing bad\n");
}

struct s_header	get_header(int socket_fd)
{
	struct s_header	header;
	int				n;

	n = read(socket_fd, &header, sizeof(header));
	if (n < 0)
		err_n_die("read error\n");
	return (header);
}

void			process_incoming(int header_fd, int download_fd)
{
	struct s_header header;

	header = get_header(header_fd);
	handle(header_fd, download_fd, header);
}
