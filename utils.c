#include "philo.h"

int		ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_strncmp(char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}

int	is_digit(char c)
{
	if (c < 48 || c > 57)
		return (0);
	else
		return (1);
}

int	is_number(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!is_digit(str[i]))
				return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10 + str[i] - 48);
		i++;
		if (result > 9223372036854775807 && sign == 1)
			return (-1);
		if (result > 9223372036854775807 && sign == -1)
			return (0);
	}
	return (result * sign);
}

unsigned long int	get_time_now(void)
{
	struct			timeval time;
	int				ret;

	ret = gettimeofday(&time, NULL);
	if (ret  == -1)
	{
		printf("gettimeday() failed\n");
		return (-1);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void    better_sleep(int total_ms)
{
	long begin = get_time_now();
		// printf(" %lu I am here\n", total_ms);
    // total_ms *= 100;
		// printf(" %lu I am here\n", total_ms);
	// printf("%d|%lu\n", total_ms, get_time_now() - begin);
    while ((get_time_now() - begin) < total_ms)
	{
		// printf("%lu|%lu\n", total_ms, get_time_now() - begin);
        usleep(100);
	}
	// usleep(total_ms * 1000);
}
