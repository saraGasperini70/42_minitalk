# Bynary names
NAME = 
SERVER = server
CLIENT = client

# ft_printf
LIBFTPRINTF = ft_printf/libftprintf.a
LIBFTPRINTF_DIR = ft_printf

# Command Variables
CC = gcc
FLAGS = -Wextra -Wall -Werror
RM = rm -rf

# Minitalk Variables
CLI_C = client.c
SRV_C = server.c
CLI_O = client.o
SRV_O = server.o
INC = minitalk.h

#Commands
all: $(LIBFTPRINTF) $(CLIENT) $(SERVER)

CLIENT: $(CLI_C) $(INC)
	@ $(CC) $(FLAGS) $(LIBFTPRINTF) -o $@ $(CLI_C)

SERVER: $(SRV_C) $(INC)
	@ $(CC) $(FLAGS) $(LIBFTPRINTF) -o $@ $(SRV_C)

%.o: %.c
	@ $(CC) $(FLAGS) -c $< -o $@

$(LIBFTPRINTF):
	@ $(MAKE) -C $(LIBFTPRINTF_DIR)

clean:
	@ $(MAKE) clean -C $(LIBFTPRINTF_DIR)
	@ $(RM) $(CLI_O) $(SRV_O)

fclean: clean
	@ $(MAKE) fclean -C $(LIBFTPRINTF_DIR)
	@ $(RM) $(CLIENT) $(SERVER)

re: fclean all

PHONY: all clean fclean re
