#include "minitalk.h"

void    signal_error(void)
{
    printf("Errore inaspettato client.\n");
    exit(EXIT_FAILURE);
}

int	ft_atoi(const char *str)
{
	int	c;
	int	neg;
	int	n;

	c = 0;
	neg = 1;
	n = 0;
	while ((str[c] >= 9 && str[c] <= 13) || str[c] == 32)
	{
		c++;
	}
	if (str[c] == '-' || str[c] == '+')
	{
		if (str[c] == '-')
			neg *= -1;
		c++;
	}
	while (str[c] >= 48 && str[c] <= 57)
	{
		n = n * 10 + str[c] - 48;
		c++;
	}
	return (n * neg);
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
/*
void    ft_chartobin(unsigned char str, int pid)
{
    int bit;

    bit = 0;
    while (bit < 8)
    {
        //printf("%c\n", str);
        if (str & 128)
        {
            if (kill(pid, SIGUSR2) == -1)
                signal_error();            
        }
        else
        {
            if (kill(pid, SIGUSR1) == -1)
                signal_error();
        }
        str <<= 1;
        bit++;        
        pause();
        usleep(100);
    }
}
*/


void    ft_sent(char *str, int pid)
{
	int	i;

	i = 0;
	while (str[i])
		ft_chartobin(str[i++], pid);
	ft_chartobin('\0', pid);
}

void ft_recieved(int sig)
{
	static int	sent;

	if (sig == SIGUSR1)
	{
		printf("%d Segnale inviato con successo.\n", ++sent);
		exit(EXIT_SUCCESS);
	}
	if (sig == SIGUSR2)
		++sent;
}
int main(int ac, char **av)
{
    int server_pid;
    int client_pid;

    client_pid = getpid();
    if (ac == 3)
    {
        printf("client pid: %d\n",client_pid);
        signal(SIGUSR1, ft_recieved);
        signal(SIGUSR2, ft_recieved);
        server_pid = ft_atoi(av[1]);
        printf("Invio in corso...\n");
        ft_sent(av[2], server_pid);
    }
    else
        printf("Errore: inserire PID e messaggio da inviare\n");
    return(EXIT_FAILURE);
}