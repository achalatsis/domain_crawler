//
//  logging.h
//  DomainCrawler
//
//  Created by Alexandros Chalatsis on 29/4/14.
//  Copyright (c) 2014 Alexandros Chalatsis. All rights reserved.
//

#ifndef DomainCrawler_logging_h
#define DomainCrawler_logging_h

/**
 * Apped a discovered registered domain at the end of the file.
 */
void saveDiscoveredDomain(const char *domain);

/**
 * Logging clean-up. Close file, flush caches, destroy mutexes, etc
 */
void loggingCleanup();

#endif
