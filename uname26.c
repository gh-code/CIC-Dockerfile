#include <sys/personality.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define UNAME26 0x0020000

int main(int ac, char **av)
{
    if (!av[1]) { 
        fprintf(stderr, "Usage: uname26 program ...\n"
                "Run program with the uname 2.6 personality\n");
        exit(1);
    }
    if (personality(PER_LINUX | UNAME26) < 0)
        perror("personality"), exit(1);

    execvp(av[1], av + 1);
    fprintf(stderr, "Cannot execute %s: %s\n", av[1], strerror(errno));
    exit(1);
}
