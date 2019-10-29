#include <stdio.h>

main(int argc, char *argv[], char *envp[]) {
		int			i;
		char		**p;
		extern char	**environ;

		printf("List command-line arguments\n");
		for (i = 0 ; i < argc ; i++)  {
				printf("%s\n", argv[i]);
		}

		printf("\n");
		printf("List environment variables from environ variable\n");
#if 1
		for (i = 0 ; environ[i] != NULL ; i++)  {
				printf("%s\n", environ[i]);
		}
#else
		for (p = environ ; *p != NULL ; p++)  {
				printf("%s\n", *p);
		}
#endif

		printf("\n");
		printf("List environment variables from envp variable\n");
#if 1
		for (i = 0 ; envp[i] != NULL ; i++)  {
				printf("%s\n", envp[i]);
		}
#else
		for (p = envp ; *p != NULL ; p++)  {
				printf("%s\n", *p);
		}
#endif
}
