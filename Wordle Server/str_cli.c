/******************************************************
*       client function for talk server program       *
******************************************************/


#include "jc_unp.h" //"unp.h"

void str_cli(FILE *fp, int sockfd)
{
	char sendline[MAXLINE], recvline[MAXLINE]; //strings for send & receive
	char word[5];
	char guess[5] = "*****";
	char right[5] = "*****";


	if (fgets(sendline, MAXLINE, fp) != NULL) 
	{
		write(sockfd, sendline, strlen(sendline));  //write to socket

		if (read(sockfd, recvline, MAXLINE) == 0)   //read from socket
		{
			printf("str_cli: server terminated prematurely");  //error mssg
			exit(1);
		}
		//fputs(word, recvline);  //print string from socket
		printf("\n%s\n", recvline); //recvline is right answer		
	}
	
	int j;
	for(j = 0; j < 5; j++)
	   word[j] = recvline[j];


	printf("%s\n", word);

	int temp = 1;
        int count = 6;
	guess[5] = '\0';
        do {
            do {
                printf("%s - %i tries left. Please enter a guess(must be 5 letters) : ", right, count);
                fgets(guess, MAXLINE, stdin);
            } while (strlen(guess) != 6);

            //if (guess == word)
            //    count = 0;
            
	    //else {
                int i;
		temp = 1;
                for (i = 0; i < 5; i++) {
                    if (guess[i] == word[i])
                        right[i] = guess[i];
		    else
			temp = 0;
		}
		if (temp == 1)
		    count = 0;
 		else
                    count -= 1;
        } while (count != 0);
        if (temp == 1)
            printf("\nYOU WIN!!!\n");
        else
            printf("\nSorry, you lose. Maybe next time!");
}
