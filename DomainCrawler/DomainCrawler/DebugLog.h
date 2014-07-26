//  DebugLog.h
//  DebugTools-C
//
//  Created by Αλέξανδρος Χαλάτσης on 27/10/11.
//  Copyright (c) 2011 ahalatsis. All rights reserved.
//

#define DebugLogData 3 //output sample data too
#define DebugLogActions 2 //output only actions (functions calls, etc)
#define DebugLogErrors 1 //output errors only
#define DebugLogNothing 0 //no output


//intermediate macro definition
//so nothing executed unless DEBUG=1
#ifdef DEBUG
#define DebugLog(args...) _DebugLog(args);
#else
#define DebugLog(x...) //no uneccessary overhead in release
#endif

void _DebugLog(short level, const char *format, ...);
