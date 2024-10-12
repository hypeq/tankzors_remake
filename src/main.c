#include "main.h"

int main(
#ifdef __WIN32
	[[maybe_unused]]int argc, [[maybe_unused]]char **argv
#endif	
	)
{
	initVideo();
	initAudio();
	showMenu();
	return 0;
}
