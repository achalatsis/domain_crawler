//
//  config.c
//  DomainCrawler
//
//  Created by Alexandros Chalatsis on 30/4/14.
//  Copyright (c) 2014 Alexandros Chalatsis. All rights reserved.
//

#include <stdio.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <pthread.h>


#include "config.h"

unsigned long long getThreadID()
{
    unsigned long long tid;
    
#ifdef __APPLE__
    pthread_threadid_np(NULL, &tid);
#endif
    
#ifdef __linux__
    tid = syscall(SYS_gettid);
#endif
    
    return tid;
}
