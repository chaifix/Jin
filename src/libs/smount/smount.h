/**
* Copyright (c) 2017 chai(neonum) 
*/
#ifndef SMOUNT_H
#define SMOUNT_H

// path type 
enum
{
    PATH_DIR = 1, // directory  
    PATH_REG = 2   // regular file
};

// sm status
enum
{
    SM_SUCCESS = 0,
    SM_INVALIDMOUNT = 1, // invalid mount directory.
    SM_NOSUCHDIR = 2,    // directory or file doesn't exsist. 
    SM_UNABLEOPEN = 3,   // 
    SM_CANTWRITE = 4,
};

typedef struct sm_Path
{
    int type;
    char* path;
    struct sm_Path* next;
}sm_Path;

/**
* A shared context structrue.
*/
typedef struct sm_Shared
{
    // the root directory
    sm_Path* mount;

}sm_Shared;

sm_Shared* sm_newshared();

void sm_closeshared(sm_Shared* S);

/**
* Get error string with given error code.
*/
const char *sm_errstr(int err);

/**
* Mount a sub file system.
*/
int sm_mount(sm_Shared* S, const char *path);

/**
* Free mount
*/
void sm_unmount(sm_Shared* S);

int sm_exists(sm_Shared* S, const char *path);

/**
* Get size of a file.
*/
int sm_size(sm_Shared* S, const char *path);

/**
* Can only read files under root directory.
*/
void *sm_read(sm_Shared* S, const char *path, unsigned int *size);

int sm_isdir(sm_Shared* S, const char *path);

int sm_isreg(sm_Shared* S, const char *path);

/**
* List all folders and files inside current mount directory.
*/
sm_Path *sm_list(sm_Shared*S, const char *path);

void sm_freelist(sm_Path* S);

int sm_write(sm_Shared* S, const char *path, const void *data, int size);

void sm_delete(sm_Shared* S, const char *path);

int sm_mkdir(sm_Shared* S, const char *path);

char* sm_fullpath(sm_Shared* S, const char* path);

#endif