#include "minitalk.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = (0);
		i++;
	}
}

void    ft_calloc_exit(int count, int size)
{
    int tot_size;
    void *ret_value;

    tot_size = count * size;
    ret_value = malloc(sizeof(tot_size));
    if (!ret_value)
        exit(EXIT_FAILURE);
    ft_bzero(ret_value, tot_size);
    return (ret_value);
}

int ft_recursive_power(int number, int power)
{
    if (power <= 0)
        return (1);
    else
        return (number * ft_recursive_power(number, power - 1));
}

void    ft_receive_strlen(int *curr_bit, char **str, int *received, int signal)
{
    static int str_len;

    if (signal == SIGUSR2)
        str_len = ft_recursive_power(1, *curr_bit);
    if (*curr_bit == 31)
    {
        *received = 1
        *str = ft_calloc_exit(str_len + 1, sizeof(char));
        *curr_bit = 0;
        str_len = 0;
        return ;
    }
    *curr_bit++;
}

int ft_pustr_fd(char *str, int fd)
{
    int i;

    i = 0;
    while (str[i])
        write(fd, str[i], 1);
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putstr_fd('\n', fd);
}

void    ft_restart_variables(int *len_received, char **str, int i)
{
    *len_received = 0;
    if (str)
    {
        ft_putendl_fd(*str, 1);
        free(*str);
        *str = 0;
    }
    *i = 0;
}
/*ft_calloc_exit*/
void    ft_recieve_info_from_client(int signal)
{
    int char_val = 0;
    int current_bit = 0;
    int received_length = 0;
    int i = 0;
    char *final_str;

    if (!received_length)
        ft_receive_strlen(&current_bit, &final_str, &received_length, signal);
    else
    {
        if (signal == SIGUSR2)
            char_val = ft_recursive_power(2, current_bit);
        if (current_bit == 7)
        {
            final_str[i++] = char_val;
            current_bit = 0;
            if (char_val == 0)
                return ft_restart_variables(received_length, final_str, i);
            char_val = 0;
            return ;
        }
        current_bit++;
    }
}

int main(void)
{
    int server_pid;

    server_pid = (int)getpid();
    ft_putnbr_fd(server_pid, 1);
    ft_putchar_fd('\n', 1);
    signal(SIGUSR1, ft_recieve_info_from_client);
    signal(SIGUSR2, ft_recieve_info_from_client);
    while (1)
        usleep(WAIT_TIME);
}