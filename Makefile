NAME	=	minishell
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g3 -fsanitize=address
RM		=	rm -rf
SRC		=	main.c \
			\
			signal/signal.c \
			\
			parsing/parsing_mini.c \
			parsing/init.c \
			parsing/quotes.c \
			parsing/quote_dollar.c \
			parsing/ft_add_line_after.c \
			parsing/ft_each_cmd.c \
			parsing/stock_cmd.c \
			parsing/dollar_sign.c \
			parsing/redirrection.c \
			parsing/file_in_out.c \
			\
			utils/is_something.c \
			utils/ft_itoa.c \
			utils/skip_char.c \
			utils/ft_free.c \
			utils/cpy_stuff.c \
			utils/len.c \
			utils/ft_free_file.c \
			utils/print_avs.c \
			utils/utils.c \
			utils/ft_avs.c \
			utils/utils_tab.c \
			utils/utils_env.c \
			utils/ft_split_3.c \
			utils/ft_copy_tab.c \
			utils/ft_redir_utils.c \
			utils/utils_libft_1.c \
			utils/utils_libft_2.c \
			utils/utils_libft_3.c \
			utils/ft_print_av.c \
			utils/find_me_vs_token_dir.c \
			\
			execution/builtins_and_bin_exec/command_search_and_execution.c \
			execution/builtins_and_bin_exec/exit.c \
			execution/builtins_and_bin_exec/echo.c \
			execution/builtins_and_bin_exec/export_unset.c \
			execution/builtins_and_bin_exec/export_unset_1.c \
			execution/builtins_and_bin_exec/export_unset_2.c \
			execution/builtins_and_bin_exec/export_unset_3.c \
			execution/builtins_and_bin_exec/pwd_cd.c \
			execution/pipes/pipes.c \
			execution/pipes/pipes_1.c \
			execution/pipes/pipes_2.c \
			execution/pipes/pipes_utils.c \
			
			#/utils/ft_split_3.c 

OBJDIR = objs
SRCDIR = srcs

OBJ = $(addprefix ${OBJDIR}/, ${SRC:.c=.o})

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

#	@$(CC) $(CFLAGS) $(OBJ) -L .brew/opt/readline/lib -I .brew/opt/readline/include -o $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(NAME)
	@printf "${B}${CWHITE}]\n"

${OBJDIR}/%.o:${SRCDIR}/%.c
	@mkdir -p ${@D}
	@$(CC) $(CFLAGS) -c $< -o $@
	printf "█"

launch:
	$(call progress_bar)

clean:
	$(RM) $(OBJDIR)
	@echo "$(B)Cleared$(D)"

fclean:			clean
	$(RM) $(NAME) ${RM} objects

re:				fclean all

.PHONY:			all clean fclean re launch
