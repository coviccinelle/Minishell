NAME	=	minishell
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror #-g3 -fsanitize=address
RM		=	rm -rf
SRC		=	srcs/main.c \
			\
			srcs/signal/signal.c \
			\
			srcs/parsing/init.c \
			srcs/parsing/quotes.c \
			srcs/parsing/quote_dollar.c \
			srcs/parsing/parsing.c \
			srcs/parsing/ft_each_cmd.c \
			srcs/parsing/stock_cmd.c \
			srcs/parsing/dollar_sign.c \
			srcs/parsing/redirrection.c \
			srcs/parsing/file_in_out.c \
			\
			srcs/utils/is_something.c \
			srcs/utils/ft_itoa.c \
			srcs/utils/skip_char.c \
			srcs/utils/ft_free.c \
			srcs/utils/cpy_stuff.c \
			srcs/utils/len.c \
			srcs/utils/print_avs.c \
			srcs/utils/utils.c \
			srcs/utils/ft_avs.c \
			srcs/utils/utils_tab.c \
			srcs/utils/utils_env.c \
			srcs/utils/ft_split_3.c \
			srcs/utils/ft_copy_tab.c \
			srcs/utils/ft_redir_utils.c \
			srcs/utils/utils_libft_1.c \
			srcs/utils/utils_libft_2.c \
			srcs/utils/utils_libft_3.c \
			srcs/utils/ft_pars_piping.c \
			srcs/utils/find_me_vs_token_dir.c \
			\
			srcs/execution/builtins_and_bin_exec/command_search_and_execution.c \
			srcs/execution/builtins_and_bin_exec/exit.c \
			srcs/execution/builtins_and_bin_exec/echo.c \
			srcs/execution/builtins_and_bin_exec/export_unset.c \
			srcs/execution/builtins_and_bin_exec/export_unset_2.c \
			srcs/execution/builtins_and_bin_exec/pwd_cd.c \
			srcs/execution/pipes/pipes.c \
			srcs/execution/pipes/pipes_utils.c \
			
			#srcs/utils/ft_split_3.c 
				
OBJ = ${SRC:.c=.o}

.SILENT:
SHELL	:= bash
CRED 	= \033[0;31m
CGRIS	= \033[0;214m
CWHITE	= \033[0;37m
CYELLOW	= \033[1;33m
CGREEN 	= \033[0;32m
CCYAN 	= \033[1;36m
CBLUE 	= \033[0;34m
CPURPLE	= \033[0;35m
B 	=	$(shell tput bold)
D =		$(shell tput sgr0)


all: TITLE launch $(NAME)
	@printf "\n$(B)$(CCYAN)$(NAME) compiled$(D)\n\n"

TITLE:
	printf "${CRED}  _   ${CGRIS} _     ${CYELLOW}_  ${CGREEN}    ${CCYAN}       ${CBLUE} _     ${CPURPLE}     ${CRED}      \n"
	printf "${CRED} | |_ ${CGRIS}| |_  ${CYELLOW}(_)${CGREEN} ___ ${CCYAN} _ __  ${CBLUE}| |_   ${CPURPLE}_ _  ${CRED} __ _ \n"
	printf "${CRED} |  _|${CGRIS}| ' \\ ${CYELLOW}| |${CGREEN}|___|${CCYAN}| '_ \\ ${CBLUE}| ' \\ ${CPURPLE}| ' \\ ${CRED}/ _\` |\n"
	printf "${CRED}  \__|${CGRIS}|_||_|${CYELLOW}|_|${CGREEN}     ${CCYAN}| .__/ ${CBLUE}|_||_|${CPURPLE}|_||_|${CRED}\\__, |\n"
	printf "${CRED}      ${CGRIS}      ${CYELLOW}   ${CGREEN}     ${CCYAN}|_|     ${CBLUE}     ${CPURPLE}      ${CRED}|___/ \n"
	printf "${CYELLOW}"
	@echo Clumsy ${NAME} is on the way!


 # ******************************************************************************* #
define  progress_bar
        @i=0; \
        while [[ $$i -le $(words $(SRCS)) ]]; do \
                printf " "; \
                ((i = i + 1)); \
        done; \
		printf "$(B)$(CWHITE)]\r[$(CGREEN)";
endef
 # ******************************************************************************* #

.c.o:
	${CC} -c ${CFLAGS} -o $@ $<

#	@$(CC) $(CFLAGS) $(OBJ) -L .brew/opt/readline/lib -I .brew/opt/readline/include -o $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(NAME)
	@printf "${B}${CWHITE}]\n"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	printf "█"

launch:
	$(call progress_bar)

clean:
	$(RM) $(OBJ)
	@echo "$(B)Cleared$(D)"

fclean:			clean
	$(RM) $(NAME) ${RM} objects

re:				fclean all

.PHONY:			all clean fclean re launch
