NAME = minitalk
NAME_CLIENT = client
NAME_SERVER = server
NAME_C_BONUS = client_bonus
NAME_S_BONUS = server_bonus

LIBFTPRINTF	= $(LIBFTPRINTF_DIR)/libftprintf.a
LIBFTPRINTF_DIR	= ft_printf

HDR = minitalk.h

SRC_CLIENT = client.c
SRC_SERVER = server.c
SRC_C_BONUS = client_bonus.c
SRC_S_BONUS = server_bonus.c

OBJS_CLIENT := $(SRC_CLIENT:%.c=%.o)
OBJS_SERVER := $(SRC_SERVER:%.c=%.o)
OBJS_C_BONUS := $(SRC_C_BONUS:%.c=%.o)
OBJS_S_BONUS := $(SRC_S_BONUS:%.c=%.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

LFLAGS = -L$(LIBFTPRINTF_DIR) -lftprintf

all: $(NAME)

$(NAME): $(LIBFTPRINTF) $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS_CLIENT) -o $(NAME_CLIENT) $(LFLAGS)

$(NAME_SERVER): $(OBJS_SERVER) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS_SERVER) -o $(NAME_SERVER) $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFTPRINTF):
	@ $(MAKE) -C $(LIBFTPRINTF_DIR)

bonus: $(LIBFTPRINTF) $(NAME_C_BONUS) $(NAME_S_BONUS)

$(NAME_C_BONUS): $(OBJS_C_BONUS) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS_C_BONUS) -o $(NAME_C_BONUS) $(LFLAGS)

$(NAME_S_BONUS): $(OBJS_S_BONUS) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS_S_BONUS) -o $(NAME_S_BONUS) $(LFLAGS)

clean:
	rm -f $(OBJS_CLIENT) $(OBJS_SERVER) $(OBJS_C_BONUS) $(OBJS_S_BONUS)

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER) $(NAME_C_BONUS) $(NAME_S_BONUS)
	@$(MAKE) -C $(LIBFTPRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re