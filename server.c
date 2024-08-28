/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:45:29 by ccolin            #+#    #+#             */
/*   Updated: 2024/08/28 12:29:25 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_receive_signals(int	sig)
{
	static int	i;
	static char	c;

	if (sig == SIG1)
		c |= (1 << (7 - i));
	i++;
	if (i == 8)
	{
		if (c != '\0')
			ft_printf("%c", c);
		else
			ft_printf("\n\nWaiting for next message...\n\n");
		i = 0;
		c = 0;
	}
}

int	main(void)
{
	ft_printf("Server PID = [%d]\nWaiting for messages...\n\n", getpid());
	signal(SIG0, ft_receive_signals);
	signal(SIG1, ft_receive_signals);
	while (1)
		pause();
}