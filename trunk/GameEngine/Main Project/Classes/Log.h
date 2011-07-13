//
//  Log.h
//  GameEngine
//
//  Created by NoEvilPeople on 7/13/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

// Assert functionality only in debug
#ifdef DEBUG
#define LOG(x,...)					Log(__FILE__,__FUNCTION__,__LINE__,false,x,##__VA_ARGS__)
#define LOG_WITH_METADATA(x,...)	Log(__FILE__,__FUNCTION__,__LINE__,true,x,##__VA_ARGS__)
#else
#define LOG(x,...)
#define LOG_WITH_METADATA(x,...)	Log(__FILE__,__FUNCTION__,__LINE__,true,x,##__VA_ARGS__)
#endif

void Log(const char* file, const char* function, const int line, bool printMetaInfo, const char* format, ...);