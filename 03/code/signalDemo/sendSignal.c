#include "common.h"

int main(int argc, char **argv) // "./sendSignals" "20673" "2"
{
	kill(atoi(argv[1]), atoi(argv[2]));
}
