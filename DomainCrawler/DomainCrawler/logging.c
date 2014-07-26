//
//  logging.c
//  DomainCrawler
//
//  Created by Alexandros Chalatsis on 29/4/14.
//  Copyright (c) 2014 Alexandros Chalatsis. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

#include "logging.h"
#include "config.h"
#include "DebugLog.h"

static pthread_mutex_t fileLock;

//pseudo-skeleton (better that global var) to keep our file open
FILE* getLoggingFile()
{
    DebugLog(DebugLogActions, "%s(%lld): opening %s\n", __PRETTY_FUNCTION__, getThreadID(), LOGGING_FILE);
    static FILE *loggingFile;
    if (loggingFile == NULL) loggingFile = fopen(LOGGING_FILE, "a+");//"singleton" not yet initialized
    
    if (loggingFile == NULL && errno == 2) //doesn't exist
        loggingFile = fopen(LOGGING_FILE, "w");
    else if (loggingFile == NULL) //still NULL so error
    {
        DebugLog(DebugLogErrors, "%s(%lld): Error (%d) opening config file\n", __PRETTY_FUNCTION__, getThreadID(), errno);
        return NULL;
    }

    return loggingFile;
}

void saveDiscoveredDomain(const char *domain)
{
	FILE *loggingFile;
    
	pthread_mutex_lock(&fileLock); //lock 
	loggingFile = getLoggingFile();
    if (loggingFile != NULL)
    {
        fseek(loggingFile, SEEK_END, 0);
        fprintf(loggingFile, "%s\n", domain);
        fflush(loggingFile);
    }
	pthread_mutex_unlock(&fileLock); //unlock
    
    DebugLog(DebugLogActions, "%s(%lld): saved %s as discovered\n", __PRETTY_FUNCTION__,getThreadID(), domain);
}

void loggingCleanup()
{
    fclose(getLoggingFile());
}