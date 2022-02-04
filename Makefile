# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/13 11:32:21 by thi-phng          #+#    #+#              #
#    Updated: 2022/02/04 15:05:49 by thi-phng         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CC		=	clang
CFLAGS	=	-Wall -Wextra -Werror #-g
RM		=	rm -rf
SRC		=	srcs/main.c \
			srcs/utils/pars_utils_01.c \
			srcs/parsing/parsing.c \
			srcs/signal/signal.c \
			srcs/utils/ft_strtrim.c \
			srcs/utils/utils_libft_1.c \
			srcs/utils/dont_mind_me_test.c \
			srcs/utils/ft_space_skip.c \
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