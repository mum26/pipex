#include <stdio.h>
#include "libft/libft.h"

extern char	**environ;

char	*ft_getenv(char *name)
{
	char	**env;
	size_t	len;

	env = environ;
	if (!name)
		return (NULL);
	len = ft_strlen(name);
	while (env)
	{
		if (ft_strlen(*env) < len)
		{
			env++;
			continue;
		}
		if (!ft_strncmp(*env, name, len) && (*env)[len] == '=')
			return (*env + len + 1);
		env++;
	}
	return (NULL);
}

//int main(int argc, char *argv[])
//{
//	if (argc < 2)
//		return (0);
//	char **dir = ft_split(ft_getenv(argv[1]), ':');
//	while (*dir)
//	{
//		printf("%s\n", *dir++);
//	}
//}

