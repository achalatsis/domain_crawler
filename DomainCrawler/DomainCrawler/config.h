//
//  config.h
//  DomainCrawler
//
//  Created by Alexandros Chalatsis on 29/4/14.
//  Copyright (c) 2014 Alexandros Chalatsis. All rights reserved.
//

#ifndef DomainCrawler_config_h
#define DomainCrawler_config_h


#define DOMAIN_BATCH_SIZE 1000
#define LOGGING_FILE "crawlData.txt"
#define CONFIG_FILE "crawlConfig.txt"
#define RESOLVE_TIMEOUT 5
#define MAX_DOMAIN_LABEL_LENGTH 64 //63+1NULL
#define MAX_THREADS 10

#endif

unsigned long long getThreadID();