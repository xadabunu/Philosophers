/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:36:19 by xadabunu          #+#    #+#             */
/*   Updated: 2023/07/28 11:36:19 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(const char c)
{
	return (c == '\n' || c == '\t' || c == '\v' || c == ' ' || c == '\r' \
	|| c == '\f');
}

int	ft_atoi(const char *str)
{
	unsigned int	i;
	long			res;
	int				sign;
	long			tmp;

	if (!str)
		return (0);
	i = 0;
	while (ft_isspace(str[i]))
		++i;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	res = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		tmp = res;
		res = res * 10 + str[i] - '0';
		if (tmp > res)
			return (-1 * (sign == 1));
		++i;
	}
	return (sign * res);
}