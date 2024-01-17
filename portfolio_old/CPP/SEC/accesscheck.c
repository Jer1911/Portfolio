/*******************************************************************************
* accesscheck.c                                                                *
* author: Jeremy Ecker                                                         *
* purpose: enforce access control in Linux                                     *
*                                                                              *
* example usage:                                                               *
*  run          path, operation, user id, group id                             *
* ./accesscheck /my/filename 2 999 999                                         *
*******************************************************************************/

#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

/* Permission Struct: *********************************************************/
typedef struct
{
        unsigned int uid; // owner id
        unsigned int gid; // group id
        unsigned char u; // owner's permission
        unsigned char g; // group's permission
        unsigned char o; // other's permission
} Permission;

/* getPermission: *************************************************************
*  Creates a Permission struct from information taken from stat()             *
*  Takes as argument the filename                                             *
******************************************************************************/
Permission getPermission(char path[])
{
        struct stat st;
        int res;
        res = stat(path, &st);
        Permission perm;
        perm.uid = st.st_uid;
        perm.gid = st.st_gid;
        perm.u = (st.st_mode & S_IRWXU) >> 6;
        perm.g = (st.st_mode & S_IRWXG) >> 3;
        perm.o = st.st_mode & S_IRWXO;
        printf("\nFile combined permissions %o\n",
                        st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
        return perm;
}

/* Access Check: **************************************************************
*  Takes 4 arguments as follows:                                              *
*  user id, group id, operation to test, filename                             *
******************************************************************************/
int accesscheck(unsigned int uid, unsigned int gid, unsigned int p,
                                char path[])
{
        // create a Permission struct:
        Permission perm = getPermission(path);
        // check if user is owner:
        if(uid == perm.uid)
        {
                // check if requested operation is permitted:
                if((p & perm.u) == p)
                {
                        return 1; // if true, allow operation.
                }
                else return 0; // if false, disallow.
        }
        // check if user is in group:
        else if(gid == perm.gid)
        {
                // check if requested operation is permitted:
                if((p & perm.g) == p)
                {
                        return 1; // if true, allow operation.
                }
                else return 0; // if false, disallow.
        }
        else // the user is other:
        {
                // check if requested operation is permitted:
                if((p & perm.o) == p)
                {
                        return 1; // if true, allow operation.
                }
        }
        return 0; // no checks passed, so operation is not allowed.
}

/* Main: **********************************************************************
*  Takes 4 command line arguments as follows:                                 *
*  filename, operation to test, user id, group id                             *
******************************************************************************/
int main(int argc, char *argv[])
{
        char path[64];
        strcpy(path, argv[1]);

        char *c = argv[2];
        unsigned int p = atoi(c);

        char *d = argv[3];
        unsigned int uid = atoi(d);

        char *e = argv[4];
        unsigned int gid = atoi(e);

        int perm = accesscheck(uid, gid, p, path);
        printf("Return value = %d\n\n",perm);

        return 0;
}


