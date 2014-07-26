//
//  DnsOperations.h
//  DomainCrawler
//
//  Created by Alexandros Chalatsis on 29/4/14.
//  Copyright (c) 2014 Alexandros Chalatsis. All rights reserved.
//

#ifndef DomainCrawler_DnsOperations_h
#define DomainCrawler_DnsOperations_h

/**
 * Supplied the domain name, it will look for its NS records,
 * and if any are found (= domain is registered), it will save
 * the domain name. The function is thread-safe, so the memory pointed by domain
 * should not be altered/changed/free()d.
 * @param domain The domain name to lookup. domain should be possible to get free()d.
 */
void resolveDomain(void *param);

#endif
