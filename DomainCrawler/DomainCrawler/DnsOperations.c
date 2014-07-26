//
//  DnsOperations.c
//  DomainCrawler
//
//  Created by Alexandros Chalatsis on 29/4/14.
//  Copyright (c) 2014 Alexandros Chalatsis. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/nameser.h>
#include <resolv.h>
#include <unistd.h>
#include <errno.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <netdb.h>

#include "DnsOperations.h"
#include "DebugLog.h"
#include "logging.h"
#include "config.h"


//predefined list of  nameservers to use
const char *nameservers[] = {"208.67.222.222", "208.67.220.220"}; //opendns servers

void resolveDomain(void *param)
{
    char *domain = (char*)param;
    DebugLog(DebugLogActions, "%s(%lld): will lookup %s\n", __PRETTY_FUNCTION__, getThreadID(), domain);
    
    int response;                                                   //count of records in reply
    u_char answer[4096];                                            //unformatted reply
    //FIXME: tyxaio 4096 buffer, kanei return to megethos pou thelei
    ns_msg msg;                                                     //reply converted for processing
    ns_rr rr;                                                       //record extracted from reply
    char *displayBuffer = (char*)malloc(sizeof(char)*4096);         //buffer for displaying in human readable form

    struct __res_state connectionOptions;               //create custom request
    res_ninit(&connectionOptions);                      //default settings
    connectionOptions.retrans = 1;                      //interval between retries
    connectionOptions.retry = 1;                        //retries per dns server
    connectionOptions.nscount = 2;                      //number of dns server
    for (int i=0; i<connectionOptions.nscount; i++)     //add our dns server
    {
        struct sockaddr_in ns;
        ns.sin_family = AF_INET;
        ns.sin_port = htons(NS_DEFAULTPORT);
        ns.sin_addr.s_addr = inet_addr(nameservers[i]);
        connectionOptions.nsaddr_list[i] = ns;
    }
    //TODO: optimize na mi ta ksanaftaixnei kathe fora
    
    response = res_nquery(&connectionOptions, domain, ns_c_in, ns_t_ns, answer, sizeof(answer));
    
    if (response > 0) //valid response
    {
        ns_initparse(answer, response, &msg); //prepare answer for parsing

        int responseCount = ns_msg_count(msg, ns_s_an); //count records
        DebugLog(DebugLogActions, "%s(%lld): have %i answers for %s\n", __PRETTY_FUNCTION__, getThreadID(), responseCount, domain);
        
        for (int i=0; i<responseCount; i++)
        {
            ns_parserr(&msg, ns_s_an, i, &rr); //parse for NS (ns_s_ns) records
            ns_sprintrr(&msg, &rr, NULL, NULL, displayBuffer, sizeof(char)*4096); //convert to readable form
            DebugLog(DebugLogData, "%s(%lld): data for %s: %s\n", __PRETTY_FUNCTION__, getThreadID(), domain,  displayBuffer);
        }
        saveDiscoveredDomain(domain);
    }
    else
    {
        DebugLog(DebugLogErrors, "%s(%lld): result getting data (%d) for %s: %s\n", __PRETTY_FUNCTION__, getThreadID(), response, domain, hstrerror(response));
    }
    
    free(displayBuffer);
#ifdef __APPLE__
    res_ndestroy(&connectionOptions);
#else
    res_nclose(&connectionOptions);
#endif
    free(domain);
}
