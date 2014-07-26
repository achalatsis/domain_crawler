//
//  main.c
//  DomainCrawler
//
//  Created by Alexandros Chalatsis on 28/4/14.
//  Copyright (c) 2014 Alexandros Chalatsis. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <pthread.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>

#include "permutations.h"
#include "DebugLog.h"
#include "logging.h"
#include "config.h"
#include "DnsOperations.h"
#include "mbrossard_threadpool.h"

volatile int run=1;

//interrupt SIGINT signal to prevent killing worker threads.
//we just stop scheduling new lookups
void killHandler(int sig)
{
    DebugLog(DebugLogActions, "\n%s(%lld): stopping new lookups. Please wait for scheduled lookups\n", __PRETTY_FUNCTION__, getThreadID());
    
    if (sig == SIGINT)
        run = 0;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s [first_domain]\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    //initial setup
    signal(SIGINT, killHandler);
    clock_t begin=clock();
    
    char *digit, *str = (char*)malloc(sizeof(char)*MAX_DOMAIN_LABEL_LENGTH); //setup
    memset(str, 0, sizeof(char)*MAX_DOMAIN_LABEL_LENGTH);
    strcpy(str, argv[1]); //and use supplied domain
    char *param;
    
    int N=2; //how many domains to lookup

    threadpool_t *threadPool = threadpool_create(MAX_THREADS, 1, 0);

    while (run && N)
    {
        //make a new copy of domain name
        param = (char*)malloc((sizeof(char)*MAX_DOMAIN_LABEL_LENGTH));
        memset(param, 0, MAX_DOMAIN_LABEL_LENGTH);
		strncpy(param, str, strlen(str)*sizeof(char));
        strncpy(param+strlen(param), ".gr\0", sizeof(char)*4);
        
        //keep trying to add to work queue if it's full
        while (threadpool_add(threadPool, &resolveDomain, param, 0) == threadpool_queue_full)
            nanosleep((struct timespec[]){{0, 500000000}}, NULL); //sleep 0.5sec inbetween
        
        //iterate to next domain
        digit = &str[strlen(str)-1];
        str = incrementString(str, digit);
        DebugLog(DebugLogActions, "%s(%lld): next permutation: %s\n", __PRETTY_FUNCTION__, getThreadID(), str);
		        
        N--;
    }
    
    threadpool_destroy(threadPool, 0);
    loggingCleanup();
    
    DebugLog(DebugLogActions, "%s(%lld): worked for %.2fsec system time\n", __PRETTY_FUNCTION__, getThreadID(),  (double)((clock()-begin)*1000)/CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}
