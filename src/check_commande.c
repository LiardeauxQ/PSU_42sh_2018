/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** check_commande.c
*/

#include "minishell.h"

static int manage_builtin_cmd(shell_t *shell, cmd_t *cmd, int size)
{
	if (shell->env == NULL || cmd->argv == NULL)
		return (-2);
	if (my_strcmp(cmd->argv[0], "env")) {
		display_env_var(shell->env);
		return (0);
	}
	if (my_strcmp(cmd->argv[0], "setenv"))
		return (set_environment_cmd(&shell->env, cmd->argv, size));
	if (my_strcmp(cmd->argv[0], "echo"))
		return (execute_echo_command(cmd));
	if (my_strcmp(cmd->argv[0], "unsetenv"))
		return (unset_env_commande(&shell->env, cmd->argv));
	if (my_strcmp(cmd->argv[0], "cd"))
		return (change_dir_cmd(&shell->env, cmd->argv));
	if (my_strcmp(cmd->argv[0], "history"))
		return (manage_history_command(&shell->env, cmd->argv));
	if (my_strcmp(cmd->argv[0], "alias"))
		return (my_alias(shell->alias, cmd->argv[1]));
	if (my_strcmp(cmd->argv[0], "unalias"))
		return (my_unalias(shell->alias, cmd->argv[1]));
	return (-1);
}

int check_exe_signal(int wstatus)
{
	if (WIFSIGNALED(wstatus)) {
		switch (WTERMSIG(wstatus)) {
		case 6:
			my_puterror("Aborted core dumped\n");
			return (134);
			break;
		case 8:
			my_puterror("Floating exception\n");
			return (136);
			break;
		case 9:
			my_puterror("Killed\n");
			return (137);
			break;
		case 11:
			my_puterror("Segmentation fault\n");
			return (139);
			break;
		}
	}
	return (0);
}

static int execute_command(char **argv, char ***env)
{
	int child_pid = 0;
	int wstatus = 0;
	int status = 0;

	if (argv == NULL || env == NULL)
		return (-1);
	if (my_strcmp(argv[0], "exit")) {
		my_putstr("exit\n");
		return (-1);
	}
	if (check_if_is_cmd(*env, argv[0]) == 1) {
		child_pid = manage_executable(*env, argv);
		waitpid(child_pid, &wstatus, WCONTINUED);
		status = check_exe_signal(wstatus);
	} else
		status = 1;
	return (status);
}

int check_one_command(cmd_t *cmd, shell_t *shell)
{
	int size = my_strlen(cmd->cmd);
	int status = 0;

	if (cmd->cmd == NULL || cmd->argv == NULL || shell->env == NULL)
		return (-1);
	if (size == 0)
		return (0);
	if ((status = manage_builtin_cmd(shell, cmd, size)) == -1)
		status = execute_command(cmd->argv, &shell->env);
	return (status);
}
