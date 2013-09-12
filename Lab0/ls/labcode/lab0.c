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
void printPermissions(struct stat buf);
void printType(struct stat buf);
void printSize(struct stat buf);
void printUserOwnership(struct stat buf);
void printGroupOwnership(struct stat buf);
void printDates(struct stat buf);

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
		
		struct stat buf;

		if (stat(str_path, &buf) < 0) {
			perror("stat error");
			continue;
		}
		
		printPermissions(buf);
		printf("\t");
		printName(str_path);
		printf("\nSize: ");
		printSize(buf);
		printf("\nType: ");
		printType(buf);
		printf("\nUser: ");
		printUserOwnership(buf);
		printf("\tGroup: ");
		printGroupOwnership(buf);
		printf("\n");
		printDates(buf); 
		printf("\n");
		
	}

	return 0;
}

void printDates( struct stat buf )
{
	printf( "Access: %s", ctime( &buf.st_atime ) );
	printf( "Modify: %s", ctime( &buf.st_mtime ) );
	printf( "Change: %s", ctime( &buf.st_ctime ) );
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

void printSize( struct stat buf )
{
	printf( "%llu", (unsigned long long) buf.st_size );
}


void printUserOwnership( struct stat buf )
{
	struct passwd *userInfo = getpwuid( buf.st_uid );
	if( userInfo != NULL ) {
		printf( "%s", userInfo->pw_name );
	} else {
		printf( "invalid uid" );
	}
}

void printGroupOwnership( struct stat buf )
{
	struct group *groupInfo = getgrgid( buf.st_gid );
	if( groupInfo != NULL ) {
        	printf( "%s", groupInfo->gr_name );
	} else {
		printf( "invalid gid" );
	}
}

void printPermissions( struct stat buf )
{
	char str[] = "---";

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

void printType( struct stat buf )
{
        char *ptr;

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
