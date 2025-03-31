/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:18:18 by belinore          #+#    #+#             */
/*   Updated: 2025/03/31 12:34:22 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

volatile sig_atomic_t	g_ack;

int	pid_validation_atoi(const char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (str[i] == ' ')
		i++;
	if (!(str[i] >= '0' && str[i] <= '9'))
	{
		ft_printf("\e[31mInvalid PID\n\e[0m");
		exit(1);
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num *= 10;
		num += str[i] - '0';
		i++;
	}
	if (kill(num, 0) < 0)
	{
		ft_printf("\e[31mInvalid PID\n\e[0m");
		exit(1);
	}
	return (num);
}

void	encode_and_send_character(unsigned char c, int pid)
{
	int	i;
	int	retry;

	i = 7;
	retry = 0;
	while (i >= 0)
	{
		g_ack = 0;
		if (((c >> i) & 1) + '0' == '1')
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i--;
		while (g_ack == 0 && retry < 10)
		{
			usleep(1000);
			retry++;
		}
		if (retry == 10)
		{
			ft_printf("\e[31mError: bit not acknoledged\n\e[0m");
			exit(1);
		}
	}
	i = 0;
}

void	conf_handler(int signal)
{
	if (signal == SIGUSR1)
	{
		g_ack = 1;
		ft_printf("\e[32m.\e[0m");
	}
	else if (signal == SIGUSR2)
	{
		g_ack = 1;
		ft_printf("\e[32mDelivered\n\e[0m");
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	int					pid_server;
	int					i;
	struct sigaction	sa;

	sa.sa_handler = &conf_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	if (argc != 3)
	{
		ft_printf("Need 3 args");
		exit(1);
	}
	pid_server = pid_validation_atoi(argv[1]);
	i = 0;
	while (argv[2][i] != '\0')
	{
		encode_and_send_character(argv[2][i], pid_server);
		i++;
	}
	encode_and_send_character('\0', pid_server);
}
