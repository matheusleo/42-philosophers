# Mandatory part
NAME				:= philo
INCLUDES		:= -I includes
SOURCE			:= ./source/main.c ./source/utils.c ./source/args.c \
							./source/forks.c ./source/philos.c ./source/time.c \
							./source/monitor.c ./source/logs.c ./source/routines.c
OBJS_PATH		:= objects
OBJS				:= $(SOURCE:./source/%.c=./$(OBJS_PATH)/%.o)
HEADERS			:= ./includes/philosophers.h

# General purpose
CC				:= cc
# C_FLAGS		:= -Wall -Werror -Wextra
RM				:= rm -rf

# Colors
OFF				:= \033[0m
RED				:= \033[0;31m
GREEN			:= \033[0;32m
BLUE			:= \033[0;34m

# Rules
all:			$(NAME)

$(NAME):		$(OBJS) $(HEADERS)
				@echo "$(GREEN)All object files from $(NAME) were created!$(OFF)"
				@$(CC) $(C_FLAGS) $(INCLUDES) -o $(NAME) $(OBJS)
				@echo "$(GREEN)$(NAME) files were sucessfully linked!$(OFF)"

./$(OBJS_PATH)/%.o:	./source/%.c
				@mkdir -p $(OBJS_PATH)
				@$(CC) $(C_FLAGS) -c $(INCLUDES) -o $@ $<

clean:
				@$(RM) $(OBJS)
				@$(RM) $(OBJS_PATH)
				@echo "$(RED)The object files from $(NAME) were sucessfully removed!$(OFF)"

fclean:			clean
				@echo "$(RED)The $(NAME) was removed!$(OFF)"

re:				fclean all

norm:
				@norminette ./source ./includes

.PHONY:			all clean fclean re
