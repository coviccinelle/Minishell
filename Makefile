# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/13 11:32:21 by thi-phng          #+#    #+#              #
#    Updated: 2022/02/09 16:22:20 by thi-phng         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CC		=	clang
CFLAGS	=	-Wall -Wextra -Werror -g3
RM		=	rm -rf
SRC		=	srcs/main.c \
			\
			srcs/signal/signal.c \
			\
			srcs/parsing/parsing.c \
			\
			srcs/utils/utils.c \
			srcs/utils/ft_avs.c \
			srcs/utils/utils_tab.c \
			srcs/utils/utils_env.c \
			srcs/utils/ft_split_3.c \
			srcs/utils/ft_copy_tab.c \
			srcs/utils/ft_space_skip.c \
			srcs/utils/utils_libft_1.c \
			srcs/utils/utils_libft_2.c \
			srcs/utils/utils_libft_3.c \
			srcs/utils/ft_pars_piping.c \
			srcs/utils/find_me_vs_token_dir.c \
			\
			srcs/execution/env.c \
			srcs/execution/builtins/exit.c \
			srcs/execution/builtins/echo.c \
			srcs/execution/builtins/pwd_cd.c \
			srcs/execution/command_expansion.c \
			srcs/execution/redirections/redir.c \
			srcs/execution/builtins/export_unset.c \
			srcs/execution/command_search_and_execution.c \
			
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