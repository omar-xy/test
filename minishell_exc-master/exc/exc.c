/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:05:55 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/15 16:27:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*check_path(char **s_path, char *cmd)
{
	int		i;
	char	*j_cmd;
	char	*j_path;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	j_cmd = ft_strjoin("/", cmd);
	if (!j_cmd)
		return (NULL);
	while (s_path[i])
	{
		j_path = ft_strjoin(s_path[i], j_cmd);
		if (access(j_path, X_OK) == 0)
		{
			free(j_cmd);
			return (j_path);
		}
		free(j_path);
		i++;
	}
	free(j_cmd);
	return (NULL);
}

void	excute_one_cmd(t_token **args, char **contents, t_env **env)
{
	char	*path;
	char	*str;
	char	**splited_path;


	(void)args;
	if (!contents[0])
		return ;
	else
	{
		path = value_by_key(*env, "PATH");
		if (path == NULL)
			return ; // error handel : PATH NOT FOUND;(to add)
		splited_path = ft_split(path, ':');
		str = check_path(splited_path, contents[0]);
		if (!str)
			return ;// error handel
		execve(str, contents, get_normal_env(*env));// check case of failure
	}
}

void	one_cmd(t_token **cmds, char **args, t_env **env)
{	
	int save;

	save = dup(0);
	if (!args[0])
		return ;
	if (ft_bultin(*cmds, args, env) == BULT_IN)
	{
		printf("IS A FUCING BULTIN!!!\n");
		if((*cmds)->fdin != 0)
		{
			dup2((*cmds)->fdin, STDIN_FILENO);
			close((*cmds)->fdin);
		}
		if((*cmds)->fdout != 1)
		{
			printf("the in %d-- the out %d\n", (*cmds)->fdin, (*cmds)->fdout);
			dup2((*cmds)->fdout, STDOUT_FILENO);
			close((*cmds)->fdout);
			// close(STDOUT_FILENO);
		}
		dup2(STDIN_FILENO, save);
		close(save);
		return ;
	}
	else
		multi_cmd(cmds, env, 0);
}

void	exceute_it(t_token **data, t_env **env)
{
	t_token *iter;
	int		numb_pipes;

	iter = *data;
	numb_pipes = -1;
	while (iter)
	{
		open_red(&iter, iter->content, env);
		numb_pipes++;
		iter = iter->forward;// check if theres a | 
	}
	// printf("NUMBER OF PIPES ==> %d\n", numb_pipes);
	if (numb_pipes == 0)
		one_cmd(data, (*data)->content, env);
	else 
		multi_cmd(data, env, numb_pipes);
	// }
}