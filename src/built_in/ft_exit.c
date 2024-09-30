/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputiev <aputiev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:28:35 by mschulme          #+#    #+#             */
/*   Updated: 2023/08/04 00:59:09 by aputiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_str_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+')
			return (0);
		i++;
	}
	return (1);
}

int	check_double_plus(char *str)
{
	int	i;
	int	counter_plus;
	int	counter_minus;

	i = 0;
	counter_plus = 0;
	counter_minus = 0;
	while (str[i] != '\0')
	{
		if ((str[i]) && str[i] == '+')
			counter_plus++;
		if ((str[i]) && str[i] == '-')
			counter_minus++;
		i++;
	}
	if (counter_plus > 1 || counter_minus > 1)
		return (1);
	return (0);
}

int	check_exit_code(char *str)
{
	long long	exit_code;

	if (!str)
		exit_code = 0;
	else if (!ft_strcmp(str, "-"))
		exit_code = 255;
	else if (is_str_digit(str) && !check_double_plus(str))
		exit_code = ft_atoi(str);
	else
		exit_code = 255;
	if (!ft_strcmp(str, "9223372036854775808"))
		exit_code = 255;
	else if (!is_str_digit(str))
		ft_printf(2, "exit: %s: numeric argument required\n", str);
	return (exit_code);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	if (free_unsorted_list(data) != 1)
		exit(EXIT_FAILURE);
	if (free_sorted_list(data) != 1)
		exit(EXIT_FAILURE);
	while (data->lexer_output[i] != NULL)
		free(data->lexer_output[i++]);
	free(data->lexer_output);
	i = 0;
	while (i < data->pipe_count + 1)
		free(data->cmd_arr[i++]);
	free(data->cmd_arr);
	i = 0;
	while (data->split[i] != NULL)
		free(data->split[i++]);
	free(data->split);
	i = 0;
	while (data->envp[i] != NULL)
		free(data->envp[i++]);
	free(data->envp);
}

int	ft_exit(t_data *data)
{
	int	i;

	i = 0;
	if (data->split[1] && data->split[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		data->exit_code = 1;
		return (EXIT_FAILURE);
	}
	if (data->split[1])
		data->exit_code = check_exit_code(data->split[1]);
	free_data(data);
	free(data->command_line);
	i = data->exit_code;
	free(data);
	exit (i);
}
