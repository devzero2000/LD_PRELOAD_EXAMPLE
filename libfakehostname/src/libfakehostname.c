// gcc -fPIC -shared -Wl,-soname,libfakehostname.so.1 -ldl -o /usr/lib64/libfakehostname.so.1 fakehostname.c
// gcc -m32 -fPIC -shared -Wl,-soname,libfakehostname.so.1 -ldl -o /usr/lib/libfakehostname.so.1 fakehostname.c
// export LD_PRELOAD=libfakehostname.so.1
// export FAKEHOSTNAME=myfakehostname.domain.com

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <stdbool.h>

#ifndef RTLD_NEXT
  #define RTLD_NEXT      ((void *) -1l)
#endif

int ret;
bool error_is_printed = false;
typedef int (*uname_t) (struct utsname * buf);
typedef int (*gethostname_t)(char *name, size_t len);

static void *getLibFunc(const char *funcname)
{
    void *func;
    char *error = NULL;

    func = dlsym(RTLD_NEXT, funcname);

    if ( func == NULL ) {
        error = dlerror();
        fprintf(stderr, "I can't locate lib function `%s' error: %s", funcname, error);
        exit(EXIT_FAILURE);
    }
    return func;
}

static void chkfakehost()
{
if ( (long int)(!error_is_printed && getenv("FAKEHOSTNAME") && strlen(getenv("FAKEHOSTNAME"))) > sysconf(_SC_HOST_NAME_MAX)){
    fprintf(stderr,"WARNING! FAKEHOSTNAME variable exceeds %ld (HOST_NAME_MAX) characters.\n",sysconf(_SC_HOST_NAME_MAX));
    error_is_printed = true;
    exit(1);
    }
}

int gethostname(char *name, size_t len) {
        gethostname_t old_gethostname = (gethostname_t) getLibFunc("gethostname");
        chkfakehost();

        ret = old_gethostname(name, len);

        if (getenv("FAKEHOSTNAME"))
                strncpy(name, getenv("FAKEHOSTNAME"), len);

        return ret;
}

int uname(struct utsname *buf)
{
   uname_t real_uname = (uname_t) getLibFunc("uname");
   chkfakehost();

   ret = real_uname((struct utsname *) buf);

   if (getenv("FAKEHOSTNAME")) {
      memset(buf->nodename, 0, sizeof(buf->nodename));
      strncpy(buf->nodename, getenv("FAKEHOSTNAME"), sizeof(buf->nodename)-1) ;
   }

   return ret;
}
