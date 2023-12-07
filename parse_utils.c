/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/15 13:11:20 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/03/02 10:50:12 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<limits.h>

static int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ');
}

int	atoi_overflow(char *str, double *num)
{
	unsigned int	res;

	res = 0;
	*num = 1;
	while (ft_isspace(*str))
		++str;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			*num = -1;
		++str;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		if ((*num == 1 && res > INT_MAX) || (*num == -1 && res - 1 > INT_MAX))
			return (0);
		++str;
	}
	*num *= res;
	return (1);
}
