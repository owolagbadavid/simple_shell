#include "main.h"

/**
 * cd_rel - handle .
 *
 * @data: shell data
 */
void cd_rel(shell_dt *data)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, data);
	dir = data->args[1];
	if (_strcmp(".", dir) == 0)
	{
		set_env("PWD", cp_pwd, data);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	rev_string(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			rev_string(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd, data);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", data);
	}
	data->stat = 0;
	free(cp_pwd);
}

/**
 * cd_to - cd to dir
 * @data: shell data
 */
void cd_to(shell_dt *data)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = data->args[1];
	if (chdir(dir) == -1)
	{
		print_error2(data, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, data);

	cp_dir = _strdup(dir);
	set_env("PWD", cp_dir, data);

	free(cp_pwd);
	free(cp_dir);

	data->stat = 0;

	chdir(dir);
}

/**
 * cd_prev - cd to prev
 * @data: shell data
 */
void cd_prev(shell_dt *data)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD", data->_env);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_env("OLDPWD", cp_pwd, data);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd, data);
	else
		set_env("PWD", cp_oldpwd, data);

	p_pwd = _getenv("PWD", data->_env);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	data->stat = 0;

	chdir(p_pwd);
}

/**
 * cd_home - cd home
 * @data: shell data
 */
void cd_home(shell_dt *data)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME", data->_env);

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, data);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		print_error2(data, 2);
		free(p_pwd);
		return;
	}

	set_env("OLDPWD", p_pwd, data);
	set_env("PWD", home, data);
	free(p_pwd);
	data->stat = 0;
}
