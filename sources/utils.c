#include "../include/minirt.h"

float	ft_atof(char *str)
{
	float	res;
	float	res2;
	int	i;
	int	len;

	i = 0;
	res = (float)ft_atoi(str);
	while (str[i] && str[i] != '.')
		i++;
	if (str[i] == '.')
		i++;
	res2 = (float)ft_atoi(str + i);
	len = ft_strlen(str + i);
	while (len--)
		res2 /= 10;
	if (res2 > 0)
	{
		if (res < 0)
			res -= res2;
		else
			res += res2;
	}
	else
		res += -res2;
	return (res);
}

