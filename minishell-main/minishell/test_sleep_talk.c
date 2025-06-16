
#include <unistd.h>

int	main()
{
	sleep(3);
	write(1, "Bonjour les amis !\nCa va ?\n", 29);
}
