/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgasperi <sgasperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:20:03 by sgasperi          #+#    #+#             */
/*   Updated: 2023/11/07 13:04:54 by sgasperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_error(void)
{
	ft_printf("Errore inaspettato server.\n");
	exit(EXIT_FAILURE);
}

void	ft_extended_action(char *c, siginfo_t *info, int *bit)
{
	ft_printf("%c", *c);
	if (*c == '\0')
	{
		ft_printf("\nMessaggio ricevuto con successo: %d\n", info->si_pid);
		kill(info->si_pid, SIGUSR1);
		*c = 0;
		*bit = 0;
	}
	*bit = 0;
}

void	ft_action(int signal, siginfo_t *info, void *context)
{
	static int	bit;
	static char	c;

	(void)context;
	c |= (signal == SIGUSR2);
	bit++;
	if (bit == 8)
		ft_extended_action(&c, info, &bit);
	c <<= 1;
	usleep(1500);
	kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	int					server_pid;
	struct sigaction	act;

	server_pid = getpid();
	ft_printf("Server PID: %i\n", server_pid);
	act.sa_sigaction = &ft_action;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, 0);
	sigaction(SIGUSR2, &act, 0);
	sigemptyset(&act.sa_mask);
	while (1)
	{
		pause();
	}
	return (EXIT_FAILURE);
}
