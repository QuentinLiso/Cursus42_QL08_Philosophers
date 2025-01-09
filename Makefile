SRCS=$(addprefix ./srcs/, \
		$(addsuffix .c, \
			death \
			forks \
			init \
			main \
			testers \
			threads \
			utils \
		) \
	)
OBJ=$(SRCS:%.c=%.o)
HEADER=./includes/philo.h
IFLAGS=-I./includes
CCFLAGS=-Wall -Werror -Wextra -pthread
NAME=philo

all 	: $(LIB) $(NAME)

$(NAME)	: $(OBJ)
		$(CC) $(CCFLAGS) $(IFLAGS) $(OBJ) -o $(NAME)

%.o		: %.c $(HEADER)
		$(CC) $(CCFLAGS) $(IFLAGS) -c $< -o $@

clean	:
		rm -rf $(OBJ)
		make -C $(LIB_FOLD) clean

fclean	: clean
		rm -rf $(NAME)

re		: fclean all