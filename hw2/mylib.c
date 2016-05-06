#include <stdarg.h>
#include <string.h>
#include <dlfcn.h>
#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <errno.h>
#include <getopt.h>
#include <langinfo.h>
#include <libintl.h>
#include <limits.h>
#include <locale.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

void foo(int count, ...){
    int i;
    va_list vl;

    va_start(vl, count);
    for (i=0; i< count; i++){
        char *str = va_arg(vl, char*);
        int is_ptr = va_arg(vl, int);
        int is_str = va_arg(vl, int);
        void *raw_arg_value = va_arg(vl, void*);
        if (is_ptr)
            printf("%s = \"%p\"\n", str,        raw_arg_value);
        else if (is_str)
            printf("%s = \"%s\"\n", str, (char*)raw_arg_value);
        else
            printf("%s = %d\n"      , str,   (int)raw_arg_value);
        fflush(stdout);
    }
    va_end(vl);
}
char *getenv(const char *name){
    static char *(*__getenv)(const char *name);
    puts("----getenv called----");
    fflush(stdout);
    if(__getenv == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __getenv = dlsym(handle, "getenv");
    }
    foo(1, "name", 0, 1, name);

    if(__getenv != NULL)
        return __getenv(name);
}
char *nl_langinfo(nl_item item){
    static char *(*__nl_langinfo)(nl_item item);
    puts("----nl_langinfo called----");
    fflush(stdout);
    if(__nl_langinfo == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __nl_langinfo = dlsym(handle, "nl_langinfo");
    }
    foo(1, "item", 0, 0, item);

    if(__nl_langinfo != NULL)
        return __nl_langinfo(item);
}
char *setlocale(int category, const char *locale){
    static char *(*__setlocale)(int category, const char *locale);
    puts("----setlocale called----");
    fflush(stdout);
    if(__setlocale == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __setlocale = dlsym(handle, "setlocale");
    }
    foo(2, "category", 0, 0, category, "locale", 0, 1, locale);

    if(__setlocale != NULL)
        return __setlocale(category, locale);
}
char *strcasestr(const char *haystack, const char *needle){
    static char *(*__strcasestr)(const char *haystack, const char *needle);
    puts("----strcasestr called----");
    fflush(stdout);
    if(__strcasestr == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __strcasestr = dlsym(handle, "strcasestr");
    }
    foo(2, "haystack", 0, 1, haystack, "needle", 0, 1, needle);

    if(__strcasestr != NULL)
        return __strcasestr(haystack, needle);
}
char *strchr(const char *s, int c){
    static char *(*__strchr)(const char *s, int c);
    puts("----strchr called----");
    fflush(stdout);
    if(__strchr == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __strchr = dlsym(handle, "strchr");
    }
    foo(2, "s", 0, 1, s, "c", 0, 0, c);

    if(__strchr != NULL)
        return __strchr(s, c);
}
char *strcpy(char *dest, const char *src){
    static char *(*__strcpy)(char *dest, const char *src);
    puts("----strcpy called----");
    fflush(stdout);
    if(__strcpy == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __strcpy = dlsym(handle, "strcpy");
    }
    foo(2, "dest", 0, 1, dest, "src", 0, 1, src);

    if(__strcpy != NULL)
        return __strcpy(dest, src);
}
char *strpbrk(const char *s, const char *accept){
    static char *(*__strpbrk)(const char *s, const char *accept);
    puts("----strpbrk called----");
    fflush(stdout);
    if(__strpbrk == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __strpbrk = dlsym(handle, "strpbrk");
    }
    foo(2, "s", 0, 1, s, "accept", 0, 1, accept);

    if(__strpbrk != NULL)
        return __strpbrk(s, accept);
}
char *strptime(const char *s, const char *format, struct tm *tm){
    static char *(*__strptime)(const char *s, const char *format, struct tm *tm);
    puts("----strptime called----");
    fflush(stdout);
    if(__strptime == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __strptime = dlsym(handle, "strptime");
    }
    foo(3, "s", 0, 1, s, "format", 0, 1, format, "tm", 1, 0, tm);

    if(__strptime != NULL)
        return __strptime(s, format, tm);
}
char *strrchr(const char *s, int c){
    static char *(*__strrchr)(const char *s, int c);
    puts("----strrchr called----");
    fflush(stdout);
    if(__strrchr == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __strrchr = dlsym(handle, "strrchr");
    }
    foo(2, "s", 0, 1, s, "c", 0, 0, c);

    if(__strrchr != NULL)
        return __strrchr(s, c);
}
FILE *fopen(const char *path, const char *mode){
    static FILE *(*__fopen)(const char *path, const char *mode);
    puts("----fopen called----");
    fflush(stdout);
    if(__fopen == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __fopen = dlsym(handle, "fopen");
    }
    foo(2, "path", 0, 1, path, "mode", 0, 1, mode);

    if(__fopen != NULL)
        return __fopen(path, mode);
}
int clock_getres(clockid_t clk_id, struct timespec *res){
    static int (*__clock_getres)(clockid_t clk_id, struct timespec *res);
    puts("----clock_getres called----");
    fflush(stdout);
    if(__clock_getres == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __clock_getres = dlsym(handle, "clock_getres");
    }
    foo(2, "clk_id", 0, 0, clk_id, "res", 1, 0, res);

    if(__clock_getres != NULL)
        return __clock_getres(clk_id, res);
}
int clock_gettime(clockid_t clk_id, struct timespec *tp){
    static int (*__clock_gettime)(clockid_t clk_id, struct timespec *tp);
    puts("----clock_gettime called----");
    fflush(stdout);
    if(__clock_gettime == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __clock_gettime = dlsym(handle, "clock_gettime");
    }
    foo(2, "clk_id", 0, 0, clk_id, "tp", 1, 0, tp);

    if(__clock_gettime != NULL)
        return __clock_gettime(clk_id, tp);
}
int close(int fd){
    static int (*__close)(int fd);
    puts("----close called----");
    fflush(stdout);
    if(__close == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __close = dlsym(handle, "close");
    }
    foo(1, "fd", 0, 0, fd);

    if(__close != NULL)
        return __close(fd);
}
int fclose(FILE *fp){
    static int (*__fclose)(FILE *fp);
    puts("----fclose called----");
    fflush(stdout);
    if(__fclose == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __fclose = dlsym(handle, "fclose");
    }
    foo(1, "fp", 1, 0, fp);

    if(__fclose != NULL)
        return __fclose(fp);
}
int ferror(FILE *stream){
    static int (*__ferror)(FILE *stream);
    puts("----ferror called----");
    fflush(stdout);
    if(__ferror == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __ferror = dlsym(handle, "ferror");
    }
    foo(1, "stream", 1, 0, stream);

    if(__ferror != NULL)
        return __ferror(stream);
}
int fileno(FILE *stream){
    static int (*__fileno)(FILE *stream);
    puts("----fileno called----");
    fflush(stdout);
    if(__fileno == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __fileno = dlsym(handle, "fileno");
    }
    foo(1, "stream", 1, 0, stream);

    if(__fileno != NULL)
        return __fileno(stream);
}
int getpeername(int sockfd, struct sockaddr *addr, socklen_t *addrlen){
    static int (*__getpeername)(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    puts("----getpeername called----");
    fflush(stdout);
    if(__getpeername == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __getpeername = dlsym(handle, "getpeername");
    }
    foo(3, "sockfd", 0, 0, sockfd, "addr", 1, 0, addr, "addrlen", 1, 0, addrlen);

    if(__getpeername != NULL)
        return __getpeername(sockfd, addr, addrlen);
}
int isatty(int fd){
    static int (*__isatty)(int fd);
    puts("----isatty called----");
    fflush(stdout);
    if(__isatty == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __isatty = dlsym(handle, "isatty");
    }
    foo(1, "fd", 0, 0, fd);

    if(__isatty != NULL)
        return __isatty(fd);
}
int memcmp(const void *s1, const void *s2, size_t n){
    static int (*__memcmp)(const void *s1, const void *s2, size_t n);
    puts("----memcmp called----");
    fflush(stdout);
    if(__memcmp == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __memcmp = dlsym(handle, "memcmp");
    }
    foo(3, "s1", 1, 0, s1, "s2", 1, 0, s2, "n", 0, 0, n);

    if(__memcmp != NULL)
        return __memcmp(s1, s2, n);
}
int socket(int domain, int type, int protocol){
    static int (*__socket)(int domain, int type, int protocol);
    puts("----socket called----");
    fflush(stdout);
    if(__socket == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __socket = dlsym(handle, "socket");
    }
    foo(3, "domain", 0, 0, domain, "type", 0, 0, type, "protocol", 0, 0, protocol);

    if(__socket != NULL)
        return __socket(domain, type, protocol);
}
int strcasecmp(const char *s1, const char *s2){
    static int (*__strcasecmp)(const char *s1, const char *s2);
    puts("----strcasecmp called----");
    fflush(stdout);
    if(__strcasecmp == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __strcasecmp = dlsym(handle, "strcasecmp");
    }
    foo(2, "s1", 0, 1, s1, "s2", 0, 1, s2);

    if(__strcasecmp != NULL)
        return __strcasecmp(s1, s2);
}
int strcmp(const char *s1, const char *s2){
    static int (*__strcmp)(const char *s1, const char *s2);
    puts("----strcmp called----");
    fflush(stdout);
    if(__strcmp == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __strcmp = dlsym(handle, "strcmp");
    }
    foo(2, "s1", 0, 1, s1, "s2", 0, 1, s2);

    if(__strcmp != NULL)
        return __strcmp(s1, s2);
}
int strncasecmp(const char *s1, const char *s2, size_t n){
    static int (*__strncasecmp)(const char *s1, const char *s2, size_t n);
    puts("----strncasecmp called----");
    fflush(stdout);
    if(__strncasecmp == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __strncasecmp = dlsym(handle, "strncasecmp");
    }
    foo(3, "s1", 0, 1, s1, "s2", 0, 1, s2, "n", 0, 0, n);

    if(__strncasecmp != NULL)
        return __strncasecmp(s1, s2, n);
}
int strncmp(const char *s1, const char *s2, size_t n){
    static int (*__strncmp)(const char *s1, const char *s2, size_t n);
    puts("----strncmp called----");
    fflush(stdout);
    if(__strncmp == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __strncmp = dlsym(handle, "strncmp");
    }
    foo(3, "s1", 0, 1, s1, "s2", 0, 1, s2, "n", 0, 0, n);

    if(__strncmp != NULL)
        return __strncmp(s1, s2, n);
}
long sysconf(int name){
    static long (*__sysconf)(int name);
    puts("----sysconf called----");
    fflush(stdout);
    if(__sysconf == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __sysconf = dlsym(handle, "sysconf");
    }
    foo(1, "name", 0, 0, name);

    if(__sysconf != NULL)
        return __sysconf(name);
}
size_t strlen(const char *s){
    static size_t (*__strlen)(const char *s);
    puts("----strlen called----");
    fflush(stdout);
    if(__strlen == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __strlen = dlsym(handle, "strlen");
    }
    foo(1, "s", 0, 1, s);

    if(__strlen != NULL)
        return __strlen(s);
}
ssize_t read(int fd, void *buf, size_t count){
    static ssize_t (*__read)(int fd, void *buf, size_t count);
    puts("----read called----");
    fflush(stdout);
    if(__read == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __read = dlsym(handle, "read");
    }
    foo(3, "fd", 0, 0, fd, "buf", 1, 0, buf, "count", 0, 0, count);

    if(__read != NULL)
        return __read(fd, buf, count);
}
ssize_t recv(int sockfd, void *buf, size_t len, int flags){
    static ssize_t (*__recv)(int sockfd, void *buf, size_t len, int flags);
    puts("----recv called----");
    fflush(stdout);
    if(__recv == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __recv = dlsym(handle, "recv");
    }
    foo(4, "sockfd", 0, 0, sockfd, "buf", 1, 0, buf, "len", 0, 0, len, "flags", 0, 0, flags);

    if(__recv != NULL)
        return __recv(sockfd, buf, len, flags);
}
time_t timegm(struct tm *tm){
    static time_t (*__timegm)(struct tm *tm);
    puts("----timegm called----");
    fflush(stdout);
    if(__timegm == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __timegm = dlsym(handle, "timegm");
    }
    foo(1, "tm", 1, 0, tm);

    if(__timegm != NULL)
        return __timegm(tm);
}
void exit(int status){
    static void (*__exit)(int status);
    puts("----exit called----");
    fflush(stdout);
    if(__exit == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __exit = dlsym(handle, "exit");
    }
    foo(1, "status", 0, 0, status);

    if(__exit != NULL)
        return __exit(status);
}
void freeaddrinfo(struct addrinfo *res){
    static void (*__freeaddrinfo)(struct addrinfo *res);
    puts("----freeaddrinfo called----");
    fflush(stdout);
    if(__freeaddrinfo == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __freeaddrinfo = dlsym(handle, "freeaddrinfo");
    }
    foo(1, "res", 1, 0, res);

    if(__freeaddrinfo != NULL)
        return __freeaddrinfo(res);
}
void *memchr(const void *s, int c, size_t n){
    static void *(*__memchr)(const void *s, int c, size_t n);
    puts("----memchr called----");
    fflush(stdout);
    if(__memchr == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __memchr = dlsym(handle, "memchr");
    }
    foo(3, "s", 1, 0, s, "c", 0, 0, c, "n", 0, 0, n);

    if(__memchr != NULL)
        return __memchr(s, c, n);
}
void *memcpy(void *dest, const void *src, size_t n){
    static void *(*__memcpy)(void *dest, const void *src, size_t n);
    puts("----memcpy called----");
    fflush(stdout);
    if(__memcpy == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __memcpy = dlsym(handle, "memcpy");
    }
    foo(3, "dest", 1, 0, dest, "src", 1, 0, src, "n", 0, 0, n);

    if(__memcpy != NULL)
        return __memcpy(dest, src, n);
}
void *memrchr(const void *s, int c, size_t n){
    static void *(*__memrchr)(const void *s, int c, size_t n);
    puts("----memrchr called----");
    fflush(stdout);
    if(__memrchr == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __memrchr = dlsym(handle, "memrchr");
    }
    foo(3, "s", 1, 0, s, "c", 0, 0, c, "n", 0, 0, n);

    if(__memrchr != NULL)
        return __memrchr(s, c, n);
}
void *memset(void *s, int c, size_t n){
    static void *(*__memset)(void *s, int c, size_t n);
    puts("----memset called----");
    fflush(stdout);
    if(__memset == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __memset = dlsym(handle, "memset");
    }
    foo(3, "s", 1, 0, s, "c", 0, 0, c, "n", 0, 0, n);

    if(__memset != NULL)
        return __memset(s, c, n);
}
void *realloc(void *ptr, size_t size){
    static void *(*__realloc)(void *ptr, size_t size);
    puts("----realloc called----");
    fflush(stdout);
    if(__realloc == NULL) {
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL)
            __realloc = dlsym(handle, "realloc");
    }
    foo(2, "ptr", 1, 0, ptr, "size", 0, 0, size);

    if(__realloc != NULL)
        return __realloc(ptr, size);
}

