/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgasperi <sgasperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:21:07 by sgasperi          #+#    #+#             */
/*   Updated: 2023/11/07 12:52:05 by sgasperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_error(void)
{
	ft_printf("Errore inaspettato client.\n");
	exit(EXIT_FAILURE);
}

void	ft_chartobin(unsigned char c, int pid)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if (c & 128)
		{
			if (kill(pid, SIGUSR2) == -1)
				signal_error();
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				signal_error();
		}
		c <<= 1;
		bit++;
		pause();
		usleep(100);
	}
}

void	ft_sent(char *str, int pid)
{
	int	i;

	i = 0;
	while (str[i])
		ft_chartobin(str[i++], pid);
	ft_chartobin('\0', pid);
}

void	ft_recieved(int sig)
{
	static int	sent;

	if (sig == SIGUSR1)
	{
		ft_printf("%d Segnale inviato con successo.\n", ++sent);
		exit(EXIT_SUCCESS);
	}
	if (sig == SIGUSR2)
		++sent;
}

int	main(int ac, char **av)
{
	int	server_pid;
	int	client_pid;

	client_pid = getpid();
	if (ac == 3)
	{
		ft_printf("client pid: %d\n", client_pid);
		signal(SIGUSR1, ft_recieved);
		signal(SIGUSR2, ft_recieved);
		server_pid = ft_atoi(av[1]);
		ft_printf("Invio in corso...\n");
		ft_sent(av[2], server_pid);
	}
	else
		ft_printf("Errore: inserire PID e messaggio da inviare\n");
	return (EXIT_FAILURE);
}
