#include "philo.h"

int mail = 0;   
pthread_mutex_t mutex;

void    *routine()
{
    int i = 0;
    while (i < 100000)
    {   
        i++;
        pthread_mutex_lock(&mutex); 
        mail++;
        pthread_mutex_unlock(&mutex); 
    }
    return NULL;
}

int init_philo(int nb_philo)
{   
    pthread_t   philo[nb_philo];
    int         i;

    i = 0;
    while (nb_philo > 0)
    {
        if (pthread_create(&philo[i], NULL, &routine, NULL) != 0)
            exit(EXIT_FAILURE);
        printf("Creation of philo number : %d\n", i);
        nb_philo--;
        i++;
    }
    while (nb_philo < i)
    {
        if (pthread_join(philo[nb_philo], NULL) != 0)
            exit(EXIT_FAILURE);
        printf("End of philo number : %d\n", nb_philo);
        nb_philo++;
    }
    return 1;
}

int main(int argc, char **argv)
{
    int nb_philo;
    
    nb_philo = ft_atoi(argv[1]);
    pthread_mutex_init(&mutex, NULL);
    init_philo(nb_philo);
    pthread_mutex_destroy(&mutex);
    printf("mail = %d\n", mail);
    return 0;
}
