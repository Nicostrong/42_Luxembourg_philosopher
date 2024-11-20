/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 07:06:24 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/10/30 09:01:46 by nfordoxc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
 * <cat>philosopher_bonus</cat>
 *
 * <summary>
 * 	long long	ft_atoll(char *str)
 * </summary>
 *
 * <description>global
 * 	ft_atoll transform the string to long long.
 * </description>
 *
 * <param type="char *" name="str">string to transform</param>
 *
 * <return>
 * 	long long value of str.
 * </return>
 *
 */

static long long	ft_atoll(char *str)
{
	long long	ret;
	int			i;

	ret = 0;
	i = -1;
	while (str[++i])
	{
		ret = 10 * ret + (str[i] - '0');
		if (ret > 2147483647)
			ft_perror_exit(E_INT);
	}
	return (ret);
}

/*
 * <cat>philosopher_bonus</cat>
 *
 * <summary>
 * 	int	ft_get_arg(char *arg)
 * </summary>
 *
 * <description>
 * 	ft_get_arg transform the parameter in integer and check if no override.
 * </description>
 *
 * <param type="char *" name="arg">arg to transform in int</param>
 *
 * <return>
 * 	the string arg in int value.
 * </return>
 *
 */

static int	ft_get_arg(char *arg)
{
	long long	arg_long;

	arg_long = ft_atoll(arg);
	if (arg_long > 2147483647)
		ft_perror_exit(E_INT);
	return ((int)arg_long);
}

/*
 * <cat>philosopher_bonus</cat>
 *
 * <summary>
 * 	void	ft_only_digit(int argc, char **argv)
 * </summary>
 *
 * <description>
 * 	ft_only_digit check if all char of all args are a digit.
 * </description>
 *
 * <param type="int" name="argc">number of arguments</param>
 * <param type="char **" name="argv">array of arguments</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */

static void	ft_only_digit(int argc, char **argv)
{
	int	idx;

	while (argc-- > 1)
	{
		idx = -1;
		while (argv[argc][++idx])
			if (!ft_isdigit(argv[argc][idx]))
				ft_perror_exit(E_DIGIT);
	}
}

/*
 * <cat>philosopher_bonus</cat>
 *
 * <summary>
 * 	void	ft_check(t_philo *philo)
 * </summary>
 *
 * <description>
 * 	ft_check check if all value in the data struct are correct.
 * </description>
 *
 * <param type="t_philo *" name="philo">philo struct</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */

static void	ft_check(t_philo *philo)
{
	t_data	*data;

	data = &philo->data;
	if (data->nb_philo == 0 || data->nb_philo > 200)
		ft_perror_exit(E_PHILO);
	if (data->ttdie < data->tteat || data->ttdie < data->ttsleep)
		ft_perror_exit(E_DIE);
	if (data->tteat < ft_militomicro(50))
		ft_perror_exit(E_EAT);
	if (data->ttsleep < ft_militomicro(50))
		ft_perror_exit(E_SLEEP);
}

/*
 * <cat>philosopher_bonus</cat>
 *
 * <summary>
 * 	void	ft_init(t_philo *philo, int argc, char **argv)
 * </summary>
 *
 * <description>
 * 	ft_init initialise the data stucture and philo structure.
 * </description>
 *
 * <param type="t_philo *" name="philo">philo struct</param>
 * <param type="int" name="argc">number of arguments</param>
 * <param type="char **" name="argv">array of arguments</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */

void	ft_init(t_philo *philo, int argc, char **argv)
{
	ft_only_digit(argc, argv);
	philo->data.start = ft_microtime() + 1000000;
	philo->data.nb_philo = ft_get_arg(argv[1]);
	philo->data.ttdie = ft_militomicro(ft_get_arg(argv[2]));
	philo->data.tteat = ft_militomicro(ft_get_arg(argv[3]));
	philo->data.ttsleep = ft_militomicro(ft_get_arg(argv[4]));
	philo->data.opt_eat = -1;
	if (argc == 6)
		philo->data.opt_eat = ft_get_arg(argv[5]);
	ft_check(philo);
	philo->last_change = philo->data.start;
	philo->last_eat = philo->data.start;
}
