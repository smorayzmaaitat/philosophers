NAME = phillo
BONUS = phillo_bonus

OBJS =  philo/utils.o philo/phillo.o philo/utils2.o
OBJSS =  philo_bonus/utils.o philo_bonus/phillo.o philo_bonus/utils2.o 

CC = cc
CFLAGS = -Wall -Wextra -Werror 

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS)  -o $(NAME)
	
bonus:$(BONUS)

$(BONUS): $(OBJSS)
	@$(CC) $(CFLAGS) $(OBJSS)  -o $(BONUS)
	
$(OBJS): philo/phillo.h
$(OBJSS): philo_bonus/phillo.h
clean:
	@$(RM) $(OBJS)
	@$(RM) $(OBJSS)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(BONUS)

re: fclean all
