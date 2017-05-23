//
//  main.cpp
//  L2UIUnpack
//

#include <exception>
#include <cstdio>
#include <memory>

#include <fcntl.h>
#include <unistd.h>

#include <libxml/encoding.h>
#include <libxml/tree.h>

#include "ct26.h"

int main(int argc, const char * argv[]) {
	if (argc < 2) {
		fprintf(stderr, "usage: %s xdat\n", argv[0]);
		return 1;
	}
	
	LIBXML_TEST_VERSION
	
	int fd = open(argv[1], O_RDONLY
#if defined(_WIN32)
				  | O_BINARY
#endif
);
	if (fd == -1) {
		perror("open:");
		return 1;
	}
	std::unique_ptr<CT26::Schema> ct26;
	
	try {
		ct26 = std::unique_ptr<CT26::Schema>(new CT26::Schema(fd, argv[1]));
	}
	catch (const std::exception& err) {
		fprintf(stderr, "error reading %s: %s (at 0x%llx)\n", argv[1], err.what(), static_cast<long long unsigned>(lseek(fd, 0, SEEK_CUR)));
		close(fd);
		return 1;
	}

	ct26->dump();
	
    return 0;
}
