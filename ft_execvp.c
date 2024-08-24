extern char	**environ;

int	ft_execvp(char *cmd, char *argv[])
{
	char	**dir;
	char	*path;

	dir = ft_split(ft_getenv("PATH"), ':');
	if (!dir)
		return (-1);
	while (*dir)
	{
		path = ft_strjoin(*dir, cmd);
		if (access(path, X_OK))
		{
			// path が free() できないけどいいんだろうか？
			if (execve(path, argv, environ) < 0)
				peer_exit("execve");
		}
		free (path);
		dir++;
	}
	return (-1);
}
