#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>          // printf() needs this, man 3 printf
#include <stdlib.h>         // exit() needs this, man 3 exit
#include <pwd.h>            // getpwuid()
#include <grp.h>            // getgrgid()
#include <time.h>           // ctime()
#include <string.h>         // strlen()


#define STRLEN1 128
#define STRLEN2 64


void printName(char *str_path);
void printPermissions(char *str_path);
void printType(char *str_path);
void printSize(char *str_path);


int main(int argc, char *argv[])
{
	
        DIR *p_dir;
        struct dirent *p_dirent;

        if (argc < 2) {
                printf("Usage: %s <directory name>\n", argv[0]);
                exit (1);
        }

        if ((p_dir = opendir(argv[1])) == NULL) {
                printf("opendir(%s) failed\n", argv[1]);
                exit(1);
	}

        while ((p_dirent = readdir(p_dir)) != NULL) {

                char *str_path = p_dirent->d_name;      // relative path name!
		printPermissions(str_path);
		printf("\t");
		printName(str_path);
		printf("\t");
		printType(str_path);
		printf("\t");
		printSize(str_path);
		printf("\n");
	}

	return 0;
}



void printName( char *str_path )
{
	if (str_path == NULL) {
	         printf("Null pointer found!");
	         exit(2);
	} else {
	         printf("%s", str_path);
	}
}
	
void printSize( char *str_path )
{
	struct stat buf;

        if (stat(str_path, &buf) < 0) {
        	perror("stat error");
                return;
        }

	printf( "%llu", (unsigned long long) buf.st_size );
}

void printPermissions( char *str_path )
{
	char str[] = "---";
	struct stat buf;

        if (lstat(str_path, &buf) < 0) {
        	perror("lstat error");
                return;
        }

        mode_t mode = buf.st_mode;

	// owner permission
        str[0] = (mode & S_IRUSR) ? 'r' : '-';
	str[1] = (mode & S_IWUSR) ? 'w' : '-';
        str[2] = (mode & S_IXUSR) ? 'x' : '-';
	printf("%s", str);

	// group permission
        str[0] = (mode & S_IRGRP) ? 'r' : '-';
	str[1] = (mode & S_IWGRP) ? 'w' : '-';
        str[2] = (mode & S_IXGRP) ? 'x' : '-';
	printf("%s", str);

	// other permission
        str[0] = (mode & S_IROTH) ? 'r' : '-';
	str[1] = (mode & S_IWOTH) ? 'w' : '-';
        str[2] = (mode & S_IXOTH) ? 'x' : '-';
	printf("%s", str);
}

void printType( char *str_path )
{
        struct stat buf;
        char *ptr;

	if (lstat(str_path, &buf) < 0) {
        	perror("lstat error");
		return;
        }

        if      (S_ISREG(buf.st_mode))  ptr = "regular";
        else if (S_ISDIR(buf.st_mode))  ptr = "directory";
        else if (S_ISCHR(buf.st_mode))  ptr = "character special";
        else if (S_ISBLK(buf.st_mode))  ptr = "block special";
        else if (S_ISFIFO(buf.st_mode)) ptr = "fifo";
#ifdef S_ISLNK
        else if (S_ISLNK(buf.st_mode))  ptr = "symbolic link";
#endif
#ifdef S_ISSOCK
        else if (S_ISSOCK(buf.st_mode)) ptr = "socket";
#endif
        else                            ptr = "**unknown mode**";
        printf("%s", ptr);

}
