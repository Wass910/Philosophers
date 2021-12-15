#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

void    *routine3(void *arg)
{
    int i = (int ) arg;
    int a = 0;
    while (a < 5)
	{
        printf("salut je suis le thread numero %d\n", i);
        a++;
    }
    return NULL;
}


int main(int argc, char **argv)
{
    int i;
    pthread_t philo;
	
    i = 1;
    while (i < 6)
    {
        if (pthread_create(&philo, NULL, &routine3, i) != 0)
            exit(EXIT_FAILURE);
        i++;
    }
	return 0;
}
