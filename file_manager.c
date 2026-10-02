#include <stdio.h>
#include <direct.h>
#include <errno.h>
#include "file_manager.h"

int prepareDataFolder(void)
{
    int result;

    result = _mkdir("data");

    if (result == 0)
        return 1;

    if (errno == EEXIST)
        return 1;

    return 0;
}