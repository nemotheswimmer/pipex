#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	**paths;

	if (is_valid_argc(argc, argv))
	{
		paths = get_paths(envp);
		execute_job(argc, argv, paths);
		free_paths(paths);
	}
	else
	{
		ft_putstr_fd("Error: bad arguments", 2);
		return (0);
	}
	system("leaks a.out");
}
