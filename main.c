#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	if (is_valid_argc(argc, argv))
		execute_job(argc, argv, envp);
	else
		write(2, "Error: bad arguments\n", 22);
	return (0);
}
