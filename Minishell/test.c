#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	my_cd(char **args);
void	my_exit(char **args);
void	my_echo(char **args);
void	my_pwd(void);
void	my_export(char **args);
void	my_unset(char **args);
void	my_env(char **envp);

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	size_t	len;
	char	*token;
		char *args[100];
	int		i;

	// Main loop for the shell
	while (1)
	{
		printf("> ");
		input = NULL;
		len = 0;
		getline(&input, &len, stdin);
		// Parse input into command and arguments
		token = strtok(input, " \n");
		i = 0;
		while (token != NULL)
		{
			args[i++] = token;
			token = strtok(NULL, " \n");
		}
		args[i] = NULL;
		// Check for built-in commands
		if (args[0] == NULL)
		{
			// No command entered
			continue ;
		}
		else if (strcmp(args[0], "cd") == 0)
		{
			my_cd(args);
		}
		else if (strcmp(args[0], "exit") == 0)
		{
			my_exit(args);
		}
		else if (strcmp(args[0], "echo") == 0)
		{
			my_echo(args);
		}
		else if (strcmp(args[0], "pwd") == 0)
		{
			my_pwd();
		}
		else if (strcmp(args[0], "export") == 0)
		{
			my_export(args);
		}
		else if (strcmp(args[0], "unset") == 0)
		{
			my_unset(args);
		}
		else if (strcmp(args[0], "env") == 0)
		{
			my_env(envp);
		}
		else
		{
			// External command handling (not shown here)
			printf("Command not found: %s\n", args[0]);
		}
		free(input);
	}
	return (0);
}

void	my_cd(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "cd: expected argument\n");
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("cd");
		}
	}
}

void	my_exit(char **args)
{
	(void)args; // Suppress unused parameter warning
	exit(0);
}

void	my_echo(char **args)
{
	for (int i = 1; args[i] != NULL; i++)
	{
		printf("%s ", args[i]);
	}
	printf("\n");
}

void	my_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
	}
	else
	{
		perror("pwd");
	}
}

void	my_export(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "export: expected argument\n");
	}
	else
	{
		putenv(args[1]);
	}
}

void	my_unset(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "unset: expected argument\n");
	}
	else
	{
		unsetenv(args[1]);
	}
}

void	my_env(char **envp)
{
	for (char **env = envp; *env != 0; env++)
	{
		printf("%s\n", *env);
	}
}
