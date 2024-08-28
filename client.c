/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:45:52 by ccolin            #+#    #+#             */
/*   Updated: 2024/08/28 12:53:39 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_error(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 3)
	{
		ft_printf("Error\nUsage = ./client PID \"String to send\"\n");
		exit(1);
	}
	while (argv[1][i])
	{
		if (!ft_strchr("1234567890", argv[1][i]))
		{
			ft_printf("Error\nInvalid PID\n");
			exit(1);
		}
		i++;
	}
	if (kill(ft_atoi(argv[1]), 0) != 0)
	{
		ft_printf("Error\nThe provided PID does not belong to "
		"any running process\n");
		exit(1);
	}
}

static void	ft_send_signals(char *str, int	PID)
{
	int	i;
	int	j;

	i = 0;
	j = 8;
	while (1)
	{
		while (j--)
		{
			if (((str[i] >> j) & 1) == 0)
				kill(PID, SIG0);
			else
				kill(PID, SIG1);
			usleep(100);
		}
		j = 8;
		if (str[i] == '\0')
			break;
		i++;
	}
}

int	main(int argc, char **argv)
{
	ft_error(argc, argv);
	ft_send_signals(argv[2], ft_atoi(argv[1]));
	return (0);
}