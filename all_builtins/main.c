#include "parsing.h"

unsigned int	g_exit_status;

static void	ft_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env				*env;
	struct sigaction	action;
	int					ret;

	if (argc > 1 || argv[1] != NULL)
		return (0);
	g_exit_status = 0;
	env = ft_envp_to_tenv(envp);
	action.sa_handler = ft_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	ret = 0;
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &action, NULL);
	while (!ret)
		ret = ft_prompt(&env);
	write(1, "exit\n", 5);
	exit(g_exit_status);
	return (0);
}
