#include"apue.h"
#include<dirent.h>
#include<limits.h>

typedef int Myfunc(const char* , const struct stat* ,int );

static Myfunc myfunc;
static int muftw(char*, Myfunc*);
static int dopath(Myfunc*);
static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

#define output(type, id) printf(type" = %7ld, %5.2f, %%\n", id, id *  100.0 / ntot);

int main(int argc, char* argv[])
{
	int ret;
	if(argc != 2)
		err_quit("usage: ftw <starting-pathname>");
	ret = myftw(argv[1], myfunc);
	ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
	if(ntot = 0)
		ntot = 1; /*avoid divide by 0*/
	output("regular files", nreg);
	output("directories" , ndir);
	output("block special", nblk);
	output("char special", nchr);
	output("Fifos", nfifo);
	output("symbolic links", nslink);
	output("sockets", nsock);
	exit(ret);
}

/*
 *Desend through the hierachy, starting at "pathname".
 *The caller's func() is called for wvery file.
 */
#define FTW_F 1					/* file other than directory */
#define FTW_D 2					/* directory */
#define FTW_DNR 3				/* directory that can not be read */
#define FTW_NS 4				/* file that we can't stat */

static char *fullpath;			/* contains full pathname for every file */
static size_t pathlen; 

static int						/* we return whatever func() returns */
myftw(char *pathname, Myfunc *func)
{
	fullpath = path_alloc(&pathlen);/* malloc PATH_MAX + 1 bytes */
	
	if(pathlen <= strlen(pathname)) {
		pathlen = strlen(pathname) * 2;
		if((fullpath = realloc(fullpath, pathlen)) == NULL)
			err_sys("realloc failed");
	}

	strcpy(fullpath, pathname);
	return(dopath(func));

}


/* 
 * Descend through the hierarchy, starting at "fullpath".
 * If "fullpath" is anything other than a directory, we lstat() it,
 * call func(), and return. for a directory, we call ourself
 * recursively for each name in the directory.
 */

static int
dopath(Myfunc* func)
{
	struct stat		statbuf;
	struct dirent	*dirp;
	DIR				*dp;
	int				ret, n;
	if(lstat(fullpath, &statbuf) < 0) /* stat error */
		return (func(fullpath, &statbuf, FTW_NS));
	if(S_ISDIR(statbuf.st_mode) == 0) /* not a directory */
		return (func(fullpath, &statbuf, FTW_F));

	/*
	 * It's a directory. First call func() for the directory,
	 * then process each filename in the directory.
	 */
	if((ret = func(fullpath, &statbuf, FTW_D)) != 0)
		return(ret);
	n = strlen(fullpath);
	if(n + NAME_MAC + 2 > pathlen) { /* expand path buffer */
		pathlen *= 2;
		if((fullpath = realloc(fullpath, pathlen)) == NULL)
			err_sys("realloc failed");
	}

	fullpath[n++] = '/';
	fullpath[n] = 0;
	if((dp = opendir(fullpath)) == NULL) /* can not read directory */
		return(func(fullpath, &statbuf, FTW_DNR));
	while((dirp = readdir(dp)) != NULL) {
		if(strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
			continue;
		strcpy(&fullpath[n], dirp->d_name); /* append name after "." */
		if((ret = dopath(func)) != 0)
			break;
	}
	fullpath[n-1] = 0;
	if(closedir(dp) < 0)
		err_ret("can't close directory %s", fullpath);
	return(ret);
}

static int
myfunc(const char* pathname, const struct stat *statptr, int type)
{
	switch(type) {
		case FTW_F:
			switch(statptr->st_mode & S_IFMT) {
				case S_IFREG: nreg++; break;
				case S_IFBLK: blk++;  break;
				case S_IFCHR: nchr++; break;
				case S_IFIFO: nfifo++; break;
				case S_IFLNK: nslink++; break;
				case S_IFSOCK: nsock++; break;
				case S_IFDIR: err_dump("for S_IFDIR for %d", pathname);
			};
			break;
		case FTW_D:
			ndir++;
			break;
		case FTW_DNR:
			err_ret("can't read directory %s", pathname);
			break;
		case FTW_NS:
			err_ret("stat error for %s", pathname);
			break;
		default:
			err_dump("unkown type %d for pathname %s", type, pathname);
	}
	return (0);
}
