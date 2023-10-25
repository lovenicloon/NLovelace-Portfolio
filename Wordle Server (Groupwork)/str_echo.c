#include	"jc_unp.h" //"unp.h"

void
str_echo(int sockfd)
{
	ssize_t		n;
	char		buf[MAXLINE];
	char word[5] = "night";

again:
	while ((n = read(sockfd, buf, MAXLINE)) > 0) {
		write(sockfd, word, MAXLINE);
	}

	if (n < 0 && errno == EINTR)
		goto again;
	else if (n < 0)
	{
		printf("str_echo: read error");
		exit(1);
	}
}
