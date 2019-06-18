#ifndef TMP_H
# define TMP_H

# include <sys/mman.h>
/*
** void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
** int munmap(void *addr, size_t length);
*/

# include <unistd.h>

/*
** int getpagesize(void);
** ssize_t write(int fd, const void *buf, size_t count);
*/

# include <sys/time.h>
# include <sys/resource.h>
/*
** int getrlimit(int resource, struct rlimit *rlim);
*/

# include <pthread.h>

# define TINY
# define SMALL
# define LARGE

#endif