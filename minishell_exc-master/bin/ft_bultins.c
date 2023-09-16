/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bultins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:50:58 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/16 14:18:00 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_bultin(t_token *data, char **arg, t_env **env)
{
	int is_bult_in = 9;
	static int exit_s = 0;
	
	if (ft_strcmp(arg[0], "env") == 0)
	{
		// printf("AKAKA________-------????\n");
		exit_s = ft_env(1, *env);
	}
	else if (ft_strcmp(arg[0], "unset") == 0)
		ft_unset(arg, env);
	else if (ft_strcmp(arg[0], "cd") == 0)
	{
		me_cd(arg, env);
	}
	else if(ft_strcmp(arg[0], "echo") == 0)
	{
		// printf("AKAKA________-------????\n");
		my_echo(data, arg, env);
	}
	else if(ft_strcmp(arg[0], "pwd") == 0)
		me_pwd(1, arg,  env);
	else if(ft_strcmp(arg[0], "exit") == 0)
		mini_exit(arg, env, exit_s);
	else if (ft_strcmp(arg[0], "export") == 0)
		export_it(arg, env);
	else 
		return 0;
	return is_bult_in;
}

int is_bult_in(char *arg)
{
	if (ft_strcmp(arg, "env") == 0)
		return BULT_IN;
	else if (ft_strcmp(arg, "unset") == 0)
		return BULT_IN;
	else if (ft_strcmp(arg, "cd") == 0)
		return BULT_IN;
	else if (ft_strcmp(arg, "export") == 0)
		return BULT_IN;
	else if (ft_strcmp(arg, "exit") == 0)
		return BULT_IN;
	else if (ft_strcmp(arg, "pwd") == 0)
		return BULT_IN;
	else if(ft_strcmp(arg, "echo") == 0)
		return BULT_IN;
	else
		return 0;
}
