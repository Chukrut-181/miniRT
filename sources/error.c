#include "../include/minirt.h"

int	ft_error_exit(char *err_msg, int err_code)
{
	ft_printf("%s\n", err_msg);
	exit (err_code);
}

