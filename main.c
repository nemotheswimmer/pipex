#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	if (is_valid_argc(argc, argv))
	{
		execute_job(argc, argv, envp);
	}
	else
	{
		ft_putstr_fd("Error: bad arguments", 2);
		return (0);
	}
	// system("leaks a.out");
	while (1);
}
