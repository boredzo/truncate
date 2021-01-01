#include <unistd.h>
#include <stdlib.h>
#include <checkint.h>
#include <sysexits.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char const *const *argv) {
	if (argc != 3) {
		char const *cmd = argv[0];
		if (cmd == NULL) cmd = "truncate";
		fprintf(stderr, "usage: %s size path\n", cmd);
		fprintf(stderr, "size must be a number, optionally followed by a suffix such as M or G. The suffix S means 512-byte sectors/blocks.\n");
		return EX_USAGE;
	}
	char *afterSize = NULL;
	unsigned long long int size = strtoll(argv[1], &afterSize, 0);
	unsigned long long int sizeMultiplier = 1ULL;
	switch (*afterSize) {
		case 'b': case 'B':
			sizeMultiplier = 1ULL;
			break;
		case 's': case 'S':
			sizeMultiplier = 512ULL;
			break;
		case 'k': case 'K':
			sizeMultiplier = 1024ULL;
			break;
		case 'm': case 'M':
			sizeMultiplier = 1024ULL * 1024ULL;
			break;
		case 'g': case 'G':
			sizeMultiplier = 1024ULL * 1024ULL * 1024ULL;
			break;
		case 't': case 'T':
			sizeMultiplier = 1024ULL * 1024ULL * 1024ULL * 1024ULL;
			break;
		case 'p': case 'P':
			sizeMultiplier = 1024ULL * 1024ULL * 1024ULL * 1024ULL * 1024ULL;
			break;
		case 'e': case 'E':
			sizeMultiplier = 1024ULL * 1024ULL * 1024ULL * 1024ULL * 1024ULL * 1024ULL;
			break;
		case 'z': case 'Z':
			sizeMultiplier = 1024ULL * 1024ULL * 1024ULL * 1024ULL * 1024ULL * 1024ULL * 1024ULL;
			break;
		case 'y': case 'Y':
			sizeMultiplier = 1024ULL * 1024ULL * 1024ULL * 1024ULL * 1024ULL * 1024ULL * 1024ULL * 1024ULL;
			break;
	}

	int mulErr = CHECKINT_NO_ERROR;
	uint64_t finalSize = check_uint64_mul(size, sizeMultiplier, &mulErr);
	if (mulErr != CHECKINT_NO_ERROR) {
		fprintf(stderr, "Size too big\n");
		return EX_DATAERR;
	}
	int fd = open(argv[2], O_CREAT | O_WRONLY, 0644);
	if (fd < 0) {
		perror("open/create failed");
		return EX_CANTCREAT;
	}
	int result = ftruncate(fd, finalSize);
	if (result != 0) {
		perror("truncate failed");
		return EX_OSERR;
	}
	
	return EXIT_SUCCESS;
}
