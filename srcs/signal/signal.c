/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:38:11 by thi-phng          #+#    #+#             */
/*   Updated: 2022/01/25 15:03:26 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    ft_sigint_ctr_c(int sig)
{
    (void)sig;
    printf("\n");
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

void    ft_sigquit_ctr_d(int sig)
{
    (void)sig;
}

// In case we fork / in another processus //
void    ft_ignore(int sig)
{
    if (sig == SIGINT)
    {
        printf("\n");
        g_n_exit = 130;
    }
    else if (sig = SIGQUIT)
    {
        printf("Quit (core dumped)\n");
        g_n_exit = 131;
    }
}

void    ft_disable_if_fork(int pid)
{
    if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
    }
    else
    {
        signal(SIGINT, ft_ignore);
        signal(SIGQUIT, ft_ignore);
    }
}

void    ft_start_signal(void)
{
    signal(SIGINT, ft_sigint_ctr_c);
    signal(SIGQUIT, ft_sigquit_ctr_d);
}
