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

int	main(void)
{
	struct sigaction	action;
	int					ret;

	g_exit_status = 0;
	action.sa_handler = ft_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	ret = 0;
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &action, NULL);
	while (!ret)
		ret = ft_prompt();
	printf("exit\n");
	printf("g_exxit_status = %u\n", g_exit_status);
	return (0);
}
