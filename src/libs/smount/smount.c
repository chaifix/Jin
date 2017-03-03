#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <vadefs.h>
#include "smount.h"
#include "dirent.h"

#define isseparator(c) (c == '/' || c == '\\')

static sm_Path* sm_newpath(int type, const  char* path, sm_Path* next)
{
    sm_Path* temp = (sm_Path*)malloc(sizeof(sm_Path));
    int len = strlen(path);
    temp->path = (char*)malloc(len + 1);
    memcpy(temp->path, path, len);
    temp->path[len] = '\0';
    // trim trailing separator 
    while (isseparator(temp->path[--len]))
        temp->path[len] = '\0';
    temp->next = next;
    temp->type = type;
    return temp;
}

static const char* mkstr(const char* str)
{
    int len = strlen(str);
    char* temp = (char*)malloc(strlen(str));
    memcpy(temp, str, len);
    return temp;
}

/**
* Create a new shared contex.
*/
sm_Shared* sm_newshared()
{
    sm_Shared* shared = (sm_Shared*)malloc(sizeof(sm_Shared));
    shared->mount = 0;
    return shared;
}

/**
* Concatenate strings together.
*/
char *concat(const char *str, ...) {
    va_list args;
    const char *s;
    // Get len
    int len = strlen(str);
    va_start(args, str);
    while ((s = va_arg(args, char*))) {
        len += strlen(s);
    }
    va_end(args);
    // Build string 
    char *res = (char*)malloc(len + 1);
    if (!res) return NULL;
    strcpy(res, str);
    va_start(args, str);
    while ((s = va_arg(args, char*))) {
        strcat(res, s);
    }
    va_end(args);
    return res;
}

static int isdir(const char *path) {
    struct stat s;
    int res = stat(path, &s);
    return S_ISDIR(s.st_mode);
}

int sm_mount(sm_Shared* S, const char *path)
{
    if (!isdir(path))
    {
        return SM_INVALIDMOUNT;
    }

    S->mount = sm_newpath(PATH_DIR, path, 0);

    return SM_SUCCESS;
}

void sm_unmount(sm_Shared* S)
{
    sm_Path* mount = S->mount;
    while (mount)
    {
        free(mount->path);
        mount = mount->next;
    }
}

int sm_exists(sm_Shared* S, const char *path)
{
    char* r = concat(S->mount->path, "/", path, 0);
    if (!r) return SM_NOSUCHDIR;
    struct stat s;
    int res = stat(r, &s);
    free(r);
    if (res == 0)
        return SM_SUCCESS;
    return SM_NOSUCHDIR;
}

static struct stat sm_getstat(sm_Shared* S, const char*path)
{
    char* r = concat(S->mount->path, "/", path, 0);
    struct stat s = {};
    if (!r) return s;
    int res = stat(r, &s);
    free(r);
    return s;
}

int sm_isdir(sm_Shared* S, const char *path)
{
    struct stat s = sm_getstat(S, path);
    return S_ISDIR(s.st_mode);
}

int sm_isreg(sm_Shared* S, const char *path)
{
    struct stat s = sm_getstat(S, path);
    return S_ISREG(s.st_mode);
}

const char* sm_errstr(int e)
{
    switch (e)
    {
    case SM_INVALIDMOUNT: return "invalid mount directory";
    default: return "unknown error";
    }
}

void *sm_read(sm_Shared* S, const char *path, unsigned int *size)
{
    if (!sm_isreg(S, path)) return 0;
    int fr = 0;
    if (size == 0)
    {
        fr = 1;
        size = (unsigned int*)malloc(sizeof(unsigned int));
    }
    char *r = concat(S->mount->path, "/", path, NULL);
    if (!r) return NULL;
    FILE *fp = fopen(r, "rb");
    free(r);
    if (!fp) return 0;
    /* Get file size */
    fseek(fp, 0, SEEK_END);
    *size = ftell(fp);
    /* Load file */
    fseek(fp, 0, SEEK_SET);
    char *res = (char*)malloc(*size + 1);
    if (!res) return NULL;
    res[*size] = '\0';
    if (fread(res, 1, *size, fp) != *size) {
        free(res);
        fclose(fp);
        return NULL;
    }
    fclose(fp);
    if (fr) free(size);
    return res;
}

char* sm_fullpath(sm_Shared* S, const char* path)
{
    return concat(S->mount->path, "/", path, 0);
}

int sm_size(sm_Shared* S, const char *path)
{
    struct stat s = sm_getstat(S, path);
    return s.st_size;
}

void sm_delete(sm_Shared* S, const char *path)
{
    char* name = sm_fullpath(S, path);
    remove(name);
    free(name);
}

int sm_write(sm_Shared* S, const char *path, const void *data, int size)
{
    char* name = sm_fullpath(S, path);
    if (!name) return SM_NOSUCHDIR;
    FILE *fp = fopen(name, "wb");
    free(name);
    if (!fp) return SM_UNABLEOPEN;
    int res = fwrite(data, size, 1, fp);
    fclose(fp);
    return (res == 1) ? SM_SUCCESS : SM_CANTWRITE;
}