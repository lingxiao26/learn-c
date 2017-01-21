#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

#define PATH_LEN 256

int fetchdir(char *path, void (*isfile)(char *))
{
    char name[PATH_LEN];
    struct dirent *ds = NULL;
    DIR *dp = opendir(path);
    
    if ( dp == NULL ) {
        perror("opendir: ");
        exit(1);
    }
    while ( (ds=readdir(dp)) != NULL ) {
        if( strcmp(ds->d_name, ".") == 0 || strcmp(ds->d_name, "..") == 0 ) {
            continue;
        }
        sprintf(name, "%s/%s", path, ds->d_name);
        isfile(name);
    }
    if ( errno ) {
        perror("readdir error: ");
        exit(1);
    }
    closedir(dp);
    return 0;
}

void isfile(char *name)
{
    struct stat sb;
    int ret = stat(name, &sb);

    if ( ret == -1 ) {
        perror("stat error: ");
        exit(1);
    }
    if ( (sb.st_mode & S_IFMT) == S_IFDIR ) {
        fetchdir(name, isfile);
        //printf("%s is DIR\n", name);
    }
    printf("%8ld %s\n", sb.st_size, name);

}

int main(int argc, char *argv[])
{   
    if ( argc != 2 ) {
        fprintf(stderr, "Usage: %s {Filename or dir}\n", __FILE__);
        exit(1);
    }
    char *name = argv[1];
    isfile(name);

    return 0;
}
