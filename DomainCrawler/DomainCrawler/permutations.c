//
//  permutations.c
//  DomainCrawler
//
//  Created by Alexandros Chalatsis on 28/4/14.
//  Copyright (c) 2014 Alexandros Chalatsis. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "permutations.h"
#include "config.h"
#include "DebugLog.h"


static const char base37[37] = "0123456789abcdefghijklmnopqrstuvwxyz-";

char* incrementString(char *string, char *digit)
{
    //looped alphabet?
    if (strncmp(&base37[36], digit, sizeof(char)) == 0) //end of alphabet
    {
        //if we have previous digits to increment
        if (string != digit)
        {
            *digit = base37[0];
            string = incrementString(string, --digit);
        }
        else if (string == digit && strlen(string) < 63) //less than 63 chars alreday: prepend new digit and rewind last digit
        {
            *digit = base37[0];
            
            strncpy(string+1, string, sizeof(char)*strlen(string));
            strncpy(string, base37, sizeof(char));
        }
    }
    //find position of digit in alphabet and advance it once
    //unless it's the end of the alphabet; then rewind
    else
    {
        static char needle;
        strncpy(&needle, digit, sizeof(char));
        char *pos = strstr(base37, &needle);
        digit[0] = (++pos)[0];
    }
    return string;
}

