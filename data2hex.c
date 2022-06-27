/* 0cc, V. Boiko, Jun 2022 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static char *d2hex = "0123456789abcdef";

int main(void) {
	ssize_t r;
	unsigned char c;
	char buf[] = {'\\', 'x', ' ', ' '};
	while ((r = read(0, &c, 1)) == 1) {
		ssize_t sz = 0;
		buf[2] = d2hex[c / 16];
		buf[3] = d2hex[c % 16];
		while (sz < sizeof buf) {
			ssize_t n = write(1, &buf[sz], sizeof buf - sz);
			if (n < 0){
				perror("write");
				return -1;
			}
			sz += n;
		}
	}

	if (r < 0) {
		perror("read");
		return -1;
	}

	return 0;
}
