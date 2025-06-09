MAKEFLAGS       = --no-print-directory

NAME            = philo

SRC             = ./src

BUILD           = ./build

HEADER          = includes/philo.h

SRCS            = $(SRC)/actions.c \
				  $(SRC)/actions_utils.c \
                  $(SRC)/utils.c \
                  $(SRC)/free.c \
                  $(SRC)/initialization.c \
                  $(SRC)/validation.c \
                  $(SRC)/timing.c \
                  $(SRC)/philosophers.c \
                  $(SRC)/main.c \
                  $(SRC)/threads.c

OBJS            = $(patsubst $(SRC)/%.c,$(BUILD)/%.o,$(SRCS))

CC              = cc

CFLAGS = -Wall -Wextra -Werror -Iincludes -g


RESET           = \033[0m
PURPLE          = \033[0;35m
LIGHT_PURPLE    = \033[1;35m
CYAN            = \033[1;36m
RED             = \033[0;31m
BLUE            = \033[0;34m

all: $(BUILD) $(NAME)

$(BUILD):
	@mkdir -p $(BUILD)

$(BUILD)/%.o: $(SRC)/%.c $(HEADER) Makefile
	@$(CC) $(CFLAGS) -c $< -o $@
	@sleep 0.05;
	@printf "${PURPLE}✧ ${RESET}"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo
	@echo "${LIGHT_PURPLE}philo created${RESET}"
	@echo "$(PURPLE)------------------------------------------------------------------$(RESET)"
	@echo "$(PURPLE)| $(LIGHT_PURPLE)Usage$(LIGHT_PURPLE)         $(PURPLE)|$(PURPLE) $(PURPLE)./philo  $(PURPLE)$(PURPLE)              			 |$(PURPLE)$(RESET)"
	@echo "$(PURPLE)------------------------------------------------------------------$(RESET)"
	@echo "$(PURPLE)|         	$(PURPLE)|$(PURPLE) $(PURPLE)1. number_of_philosophers $(PURPLE)                     $(PURPLE)|$(PURPLE) $(RESET)"
	@echo "$(PURPLE)|         	$(PURPLE)|$(PURPLE) $(PURPLE)2. time_to_die $(PURPLE)                                $(PURPLE)|$(PURPLE) $(RESET)"
	@echo "$(PURPLE)| $(LIGHT_PURPLE)Arguments$(LIGHT_PURPLE)     $(PURPLE)|$(PURPLE) $(PURPLE)3. time_to_eat $(PURPLE)                                $(PURPLE)|$(PURPLE) $(RESET)"
	@echo "$(PURPLE)|         	$(PURPLE)|$(PURPLE) $(PURPLE)4. time_to_sleep $(PURPLE)                              $(PURPLE)|$(PURPLE) $(RESET)"
	@echo "$(PURPLE)|         	$(PURPLE)|$(PURPLE) $(PURPLE)5. *number_of_times_each_philosopher_must_eat $(PURPLE) $(PURPLE)|$(PURPLE) $(RESET)"
	@echo "$(PURPLE)------------------------------------------------------------------$(RESET)"
	@echo "$(PURPLE)| $(LIGHT_PURPLE)Example$(LIGHT_PURPLE)      	$(PURPLE)|$(PURPLE) $(PURPLE)./philo 5 800 200 200 $(PURPLE)                         $(PURPLE)|$(PURPLE) $(RESET)"
	@echo "$(PURPLE)------------------------------------------------------------------$(RESET)"
	@echo "$(PURPLE)| $(LIGHT_PURPLE)Help$(LIGHT_PURPLE)          $(PURPLE)|$(PURPLE) $(PURPLE)make help$(PURPLE)                                      $(PURPLE)|$(PURPLE) $(RESET)"
	@echo "$(PURPLE)------------------------------------------------------------------$(RESET)"


clean:
	@rm -rf $(BUILD)
	@echo "${RED}Build files cleaned.${RESET}"

fclean: clean
	@rm -f $(NAME)
	@echo "${RED}Executable removed.${RESET}"

re: fclean all

help :
	@echo
	@echo "${CYAN} make help ${RESET}"
	@echo "$(BLUE)------------------------------------------------------------------$(RESET)"
	@echo "$(BLUE)| $(CYAN)Cases$(CYAN)         $(BLUE)|$(BLUE) $(BLUE)./philo  $(BLUE)$(BLUE)                			 |$(BLUE)$(RESET)"
	@echo "$(BLUE)------------------------------------------------------------------$(RESET)"
	@echo "$(BLUE)|         	$(BLUE)|$(BLUE) $(BLUE)1. ./philo 2 800 200 200 $(BLUE)                      $(BLUE)|$(BLUE) $(RESET)"
	@echo "$(BLUE)|         	$(BLUE)|$(BLUE) $(BLUE)2. ./philo 4 410 200 200 $(BLUE)                      $(BLUE)|$(BLUE) $(RESET)"
	@echo "$(BLUE)| $(CYAN)Valid$(CYAN)         $(BLUE)|$(BLUE) $(BLUE)3. ./philo 5 800 200 200 $(BLUE)                      $(BLUE)|$(BLUE) $(RESET)"
	@echo "$(BLUE)| $(CYAN)Shouldn't die$(CYAN) $(BLUE)|$(BLUE) $(BLUE)4. ./philo 10 700 200 100 $(BLUE)                     $(BLUE)|$(BLUE) $(RESET)"
	@echo "$(BLUE)|         	$(BLUE)|$(BLUE) $(BLUE)5. ./philo 200 800 200 200 $(BLUE)                    $(BLUE)|$(BLUE) $(RESET)"
	@echo "$(BLUE)------------------------------------------------------------------$(RESET)"
	@echo "$(BLUE)|         	$(BLUE)|$(BLUE) $(BLUE)1. ./philo 1 800 200 200 $(BLUE)                      $(BLUE)|$(BLUE) $(RESET)"
	@echo "$(BLUE)|         	$(BLUE)|$(BLUE) $(BLUE)2. ./philo 4 400 200 200 $(BLUE)                      $(BLUE)|$(BLUE) $(RESET)"
	@echo "$(BLUE)| $(CYAN)Invalid$(CYAN)       $(BLUE)|$(BLUE) $(BLUE)3. ./philo 5 800 200 200 $(BLUE)                      $(BLUE)|$(BLUE) $(RESET)"
	@echo "$(BLUE)| $(CYAN)Should die$(CYAN)    $(BLUE)|$(BLUE) $(BLUE)4. ./philo 3 310 200 100 $(BLUE)                      $(BLUE)|$(BLUE) $(RESET)"
	@echo "$(BLUE)|         	$(BLUE)|$(BLUE) $(BLUE)5. ./philo 200 500 200 100 $(BLUE)                    $(BLUE)|$(BLUE) $(RESET)"
	@echo "$(BLUE)------------------------------------------------------------------$(RESET)"

.PHONY: all clean fclean help re
