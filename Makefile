SRCS=$(addprefix ./srcs/, \
		$(addsuffix .c, \
			1_main \
			2_init \
			3_threads \
			4_graille \
			5_forks \
			6_death \
			7_utils \
			99_testers \
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

fclean	: clean
		rm -rf $(NAME)

re		: fclean all