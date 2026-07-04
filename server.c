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

static void	ft_receive_signals(int sig, siginfo_t *info, void *context)
{
	static int	i;
	static char	c;

	(void)context;
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
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server PID = [%d]\nWaiting for messages...\n\n", getpid());
	sa.sa_sigaction = ft_receive_signals;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIG0, &sa, NULL);
	sigaction(SIG1, &sa, NULL);
	while (1)
		pause();
}
