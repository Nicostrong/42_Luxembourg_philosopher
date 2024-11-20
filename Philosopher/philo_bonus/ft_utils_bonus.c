/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 07:07:52 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/07/30 15:28:01 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
 * <cat>philosopher_bonus</cat>
 *
 * <summary>
 * 	char	ft_isdigit(int c)
 * </summary>
 *
 * <description>
 * 	ft_isdigit check if the char in argument is a digit or not.
 * </description>
 *
 * <param type="char" name="c">char to evaluate</param>
 *
 * <return>
 * 	1 if the char is a digit.
 * 	0 if the char isn't a digit.
 * </return>
 *
 */

char	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/*
 * <cat>philosopher_bonus</cat>
 *
 * <summary>
 * 	double	ft_min(double a, double b)
 * </summary>
 *
 * <description>
 * 	ft_min return the minimum value betwenn two values.
 * </description>
 *
 * <param type="double" name="a">value a</param>
 * <param type="double" name="b">value b</param>
 *
 * <return>
 * 	the value a if a < b
 * 	the value b if b < a
 * </return>
 *
 */

double	ft_min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

/*
 * <cat>philosopher_bonus</cat>
 *
 * <summary>
 * 	double	ft_max(double a, double b)
 * </summary>
 *
 * <description>
 * 	ft_max return the maximum value betwenn two values.
 * </description>
 *
 * <param type="double" name="a">value a</param>
 * <param type="double" name="b">value b</param>
 *
 * <return>
 * 	the value a if a > b
 * 	the value b if b > a
 * </return>
 *
 */

double	ft_max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}
