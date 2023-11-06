#include "minitalk.h"
void    signal_error(void)
{
    printf("Errore inaspettato server.\n");
    exit(EXIT_FAILURE);
}

void    ft_extended_action(char *c, int *received, int *client_pid, int *bit)
{
    printf("%c", *c);
    if (*c == '\0')
    {
        printf("\n%d: Messaggio ricevuto con successo: %d\n", *received, *client_pid);
        *received = 0;
        *c = 0;
        if (kill(*client_pid, SIGUSR1) == -1)
            signal_error();
        return ;
    }
    *bit = 0;
}

void    ft_action(int signal, siginfo_t *info, void *context)
{
    static int  client_pid;
    static int  bit;
    static char c;
    static int  current_pid;
    static int  received;

    (void)context;
    if (!client_pid)
        client_pid = info->si_pid;
    current_pid = info->si_pid;
    if (client_pid != current_pid)
    {
        client_pid = current_pid;
        bit = 0;
        c = 0;
        received = 0;
    }
    c |= (signal == SIGUSR2);
    received++;
    bit++;
    if (bit == 8)
        ft_extended_action(&c, &received, &client_pid, &bit);
    c <<= 1;
    usleep(100);
    kill(client_pid, SIGUSR2);
}

int main(void)
{
    int                 server_pid;
    struct sigaction	act;  

    server_pid = getpid();
    printf("Server PID: %i\n", server_pid);
    act.sa_sigaction = ft_action;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    while (1)
    {
        sigaction(SIGUSR1, &act, 0);
        sigaction(SIGUSR2, &act, 0);
        pause();
    }
    return (EXIT_FAILURE);
}