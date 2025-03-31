#include "../../include/minirt.h"

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
		res += res2;
	else
		res += -res2;
	return (res);
}

int main()
{
	char *str = "2.43";
	
	float res = ft_atof(str);
	printf("%f\n", res);
	return (0);
}

//int	check_rgb(char *str, t_scene *data)
//{
//	char **split;
//	int	num1;
//	int	num2;
//	int	num3;
//
//	split = ft_split(str, ',');
//	if (!split)
//		return (1);
//	num1 = ft_atoi(split[0]);
//	num2 = ft_atoi(split[1]);
//	num3 = ft_atoi(split[2]);
//	ft_free_array(split);
//	if ((num1 > 255 || num1 < 0) || (num2 > 255 || num2 < 0) ||
//	(num3 > 255 || num3 < 0))
//		return (1);
//	data->ambient->color.x = num1;
//	data->ambient->color.y = num2;
//	data->ambient->color.z = num3;
//	return (0);
//}
//
//int	check_ratio(char *str, t_scene *data)
//{
//	int num;
//
//	num = ft_atoi(str);
//	if ((num < 0.0f) || (num > 1.0f))
//		return (1);
//	data->ambient->ratio = num;
//	return (0);
//}
//
//void	create_ambient_light(t_scene *s, char **res)
//{
//	s->ambient = (t_ambient_light *)malloc(sizeof(t_ambient_light));
//	if (!s->ambient)
//		return ;
//	if (check_ratio(res[1], s) == 1)
//		return ;
//	if (check_rgb(res[2], s) == 1)
//		return ;
//	printf("%f\n", s->ambient->color.x);
//	printf("%f\n", s->ambient->ratio);
//}
//
