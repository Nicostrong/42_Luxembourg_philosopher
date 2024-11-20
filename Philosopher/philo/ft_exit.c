/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:51:12 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/07/22 09:35:01 by nfordoxc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * <cat>print</cat>
 *
 * <summary>
 *	void	ft_putstr_fd(char *s, int fd)
 * </summary>
 *
 * <description>
 *	ft_putchar_fd write the string s on the output designed by fd.
 * </description>
 *
 * <param type="char *" name="s">string to print</param>
 * <param type="int" name="fd">number of the file descriptor</param>
 *
 * <return>
 *	void.
 * </return>
 *
 */

static void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		write(fd, s++, 1);
}

/*
 * <cat>print</cat>
 *
 * <summary>
 *	void	ft_putendl_fd(char *s, int fd)
 * </summary>
 *
 * <description>
 *	ft_putendl_fd write the string s on the output designed by fd with '\n'.
 * </description>
 *
 * <param type="char *" name="s">string to print</param>
 * <param type="int" name="fd">number of the file descriptor</param>
 *
 * <return>
 *	void
 * </return>
 *
 */

static void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

/*
 * <cat>philo</cat>
 *
 * <summary>
 * 	int	ft_perror_exit(char *str_error, t_info *info)
 * </summary>
 *
 * <description>
 * 	ft_perror_exit print an error message on stderror and free the structure.
 * </description>
 *
 * <param type="char *" name="str_error">string error to print</param>
 * <param type="t_info *" name="info">structure with all info</param>
 *
 * <return>
 * 	exit with code 1.
 * </return>
 *
 */

int	ft_perror_exit(char *str_error, t_data *data)
{
	ft_putendl_fd(str_error, 2);
	if (data)
		free(data);
	exit(EXIT_FAILURE);
}
