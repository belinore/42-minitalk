/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:18:16 by belinore          #+#    #+#             */
/*   Updated: 2025/03/31 12:35:12 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int signal, siginfo_t *info, void *x)
{
	static unsigned char	bytes_buf[4];
	static int				i;
	static int				j;

	(void)x;
	if (signal == SIGUSR1)
		bytes_buf[j] |= 1 << (7 - i);
	else if (signal == SIGUSR2)
		bytes_buf[j] &= ~(1 << (7 - i));
	if (++i == 8)
	{
		i = 0;
		if (++j == 4 || bytes_buf[j - 1] == '\0')
			write(1, &bytes_buf[0], j);
		if (bytes_buf[j - 1] == '\0')
		{
			write(1, "\n", 1);
			j = 0;
			kill(info->si_pid, SIGUSR2);
			return ;
		}
		else if (j == 4)
			j = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	sa.sa_sigaction = &signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid = getpid();
	ft_printf("PID of server (listener): %i\n", pid);
	while (1)
	{
		pause();
	}
}
