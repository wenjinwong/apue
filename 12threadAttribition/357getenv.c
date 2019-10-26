#include<limits.h>
#include<string.h>


#define MAXSTRINSZ 4096
static char envbuf[MAXSTRINSZ];
extern char **environ;

char *
getenv(const char *name)
{
	int i, len;
	len = strlen(name);
	for(i = 0; environ[i] != NULL; ++i) {
		if ((strcmp(name, environ[i], len) == 0) && (environ[i][len] == '=')) {
			strcpy(envbuf, &environ[i][len + 1], MAXSTRINGSZ - 1);
			return(envbuf);
		}
	}
	return NULL;
}

int 
main(void)
{
	ptintf("%s\n", getenv("PATH"));
}

