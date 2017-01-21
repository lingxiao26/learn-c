#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>


int main(int argc, char *argv[])
{
    if ( argc != 2 ) {
        fprintf(stderr, "Usage: %s DIR\n", __FILE__);
        exit(1);
    }
    char *mdzz = argv[1];
    struct dirent *ds = NULL;

    DIR *dp = opendir(mdzz);

    if ( dp == NULL ) {
        perror("opendir failed: ");
        exit(1);
    }
    while ( (ds = readdir(dp)) != NULL ) {
        printf("inode: %d\tfilename: %s\n", ds->d_ino, ds->d_name);
    }

    if ( errno ) {
        perror("Error: ");
    }

    return 0;
}
