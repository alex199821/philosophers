#include <pthread.h>
#include <stdio.h>

void	*computation(void *add);

int	main(void)
{
	pthread_t	thread1;
	pthread_t	thread2;
	long		value1;
	long		value2;

    value1 = 1;
    value2 = 2;
	computation((void *)&value1);
	computation((void *)&value2);
	// pthread_create(&thread1, NULL, computation, (void *)&value1);
	// pthread_join(thread1, NULL);
	// pthread_create(&thread2, NULL, computation, (void *)&value2);
	// pthread_join(thread2, NULL);
	return (0);
}

void	*computation(void *add)
{
	long sum = 0;
	long *add_num = (long *)(add);
	while (sum < 10000000000)
	{
		sum += *add_num;
	}
	printf("Add: %ld\n", *add_num);
	return (NULL);
}