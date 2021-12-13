# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thi-phng <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/13 11:32:21 by thi-phng          #+#    #+#              #
#    Updated: 2021/12/13 11:33:33 by thi-phng         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -rf

CC			=	clang

SRCS		=	main.c \


OBJS		=	$(SRCS:.c=.o)


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
MAG =   $(shell tput setaf 5)
WHI =   $(shell tput setaf 7)
D 	=	$(shell tput sgr0)


all:			TITLE launch $(NAME)
				@printf "\n$(B)$(CCYAN)$(NAME) compiled$(D)\n\n"

TITLE:
	printf "${CRED}  _   ${CGRIS} _     ${CYELLOW}_  ${CGREEN}    ${CCYAN}       ${CBLUE} _     ${CPURPLE}     ${CRED}      \n"
	printf "${CRED} | |_ ${CGRIS}| |_  ${CYELLOW}(_)${CGREEN} ___ ${CCYAN} _ __  ${CBLUE}| |_   ${CPURPLE}_ _  ${CRED} __ _ \n"
	printf "${CRED} |  _|${CGRIS}| ' \\ ${CYELLOW}| |${CGREEN}|___|${CCYAN}| '_ \\ ${CBLUE}| ' \\ ${CPURPLE}| ' \\ ${CRED}/ _\` |\n"
	printf "${CRED}  \__|${CGRIS}|_||_|${CYELLOW}|_|${CGREEN}     ${CCYAN}| .__/ ${CBLUE}|_||_|${CPURPLE}|_||_|${CRED}\\__, |\n"
	printf "${CRED}      ${CGRIS}      ${CYELLOW}   ${CGREEN}     ${CCYAN}|_|     ${CBLUE}     ${CPURPLE}      ${CRED}|___/ \n"
	printf "${CYELLOW}"
	@echo Clumsy minshell is on the way!


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
 
%.o : %.c
				$(CC) -c $(CFLAGS) -o $@ $<
				printf "█"

$(NAME) :		$(OBJS)
						$(CC) $(CLAGS) $(OBJS) -o $(NAME)

launch:
				$(call progress_bar)

clean:
				$(RM) $(OBJS)
				@echo "$(B)Cleared$(D)"

fclean:			clean
						$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re launch
