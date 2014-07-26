//
//  AHDebugLog.c
//  statistiks
//
//  Created by Αλέξανδρος Χαλάτσης on 27/10/11.
//  Copyright (c) 2011 ahalatsis. All rights reserved.
//

#include <stdio.h>
#include <stdarg.h>

#include "DebugLog.h"

#ifdef DEBUG
void _DebugLog(short level, const char *format, ...)
{
    //DEBUGLOGLEVEL: current debug level
    if (DEBUGLOGLEVEL >= level) //message is of minimum level of interest
    {
        va_list ap;
        va_start(ap, format);
        switch (level)
        {
            case DebugLogErrors: vfprintf(stderr, format, ap);
                break;
            default: vfprintf(stdout, format, ap);
                break;
        }
        va_end (ap);
    }
}
#endif