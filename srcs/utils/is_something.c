
#include "../../minishell.h"

int	is_alnum(int c)
{
	while ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}
