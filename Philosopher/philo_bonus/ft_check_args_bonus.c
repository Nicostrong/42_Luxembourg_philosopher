/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:08:52 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/07/30 15:26:28 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
 * <cat>philosopher</cat>
 *
 * <summary>
 * 	int	ft_check_arg(char **array)
 * </summary>
 *
 * <description>
 * 	ft_check_arg check if all args are a digit and a lenght less of 11 char.
 * </description>
 *
 * <param type="char **" name="array">array of arguments</param>
 *
 * <return>
 * 	0 if error.
 * 	1 if no error.
 * </return>
 *
 */

int	ft_check_args(char **array)
{
	int	i;
	int	j;

	i = 0;
	while (array[++i])
	{
		j = -1;
		while (array[i][++j])
		{
			if (array[i][j] < '0' || array[i][j] > '9')
				return (ft_perror_exit(E_DIGIT, NULL));
		}
		if (j > 10)
			return (ft_perror_exit(E_INT, NULL));
	}
	return (0);
}

/*
 * <cat>philosopher</cat>
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
		ret = 10 * ret + (str[i] - '0');
	return (ret);
}

/*
 * <cat>philosopher</cat>
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
 * <cat>philosopher</cat>
 *
 * <summary>
 * 	int	ft_valid_arg(t_data *data)
 * </summary>
 *
 * <description>
 * 	ft_valid_arg check if the arguments are logicals and init somes variables.
 * </description>
 *
 * <param type="t_data *" name="data">data structure</param>
 *
 * <return>
 * 	1 if arg is valid.
 * </return>
 *
 */

static int	ft_valid_arg(t_data *data)
{
	if (data->ttdie <= data->tteat || data->ttdie <= data->ttsleep)
		return (ft_perror_exit(E_ARG, NULL));
	if (data->nb_philo == 0 || data->nb_philo > 200 || data->ttdie == 0)
		return (ft_perror_exit(E_PH_DIE, NULL));
	data->stop = 0;
	data->all_eating = 0;
	return (1);
}

/*
 * <cat>philosopher</cat>
 *
 * <summary>
 * 	int	ft_read_args(int ac, char **args, t_data *data)
 * </summary>
 *
 * <description>
 * 	ft_read_args transform each arg from char * to int and save the value on a 
 * 	struct.
 * </description>
 *
 * <param type="int" name="ac">number of arg</param>
 * <param type="char **" name="args">array of arguments</param>
 * <param type="t_data *" name="data">data structure</param>
 *
 * <return>
 * 	1 if all right or exit faillure.
 * </return>
 *
 */

int	ft_read_args(int ac, char **args, t_data *data)
{
	int	i;

	data->nb_philo = ft_get_arg(args[1]);
	data->ttdie = ft_get_arg(args[2]);
	data->tteat = ft_get_arg(args[3]);
	data->ttsleep = ft_get_arg(args[4]);
	if (ac == 6)
		data->opt_eat = ft_get_arg(args[5]);
	else
		data->opt_eat = -1;
	ft_valid_arg(data);
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		return (ft_perror_exit(E_ALLOC, NULL));
	i = -1;
	while (++i < data->nb_philo)
	{
		data->philo[i] = (t_philo){0};
		data->philo[i].data = data;
		data->philo[i].id = i;
	}
	return (1);
}
