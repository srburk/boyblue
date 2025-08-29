
// log.h

#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

#include <stdint.h>

#define LOG_ALL	(uint8_t)(0xFF)

typedef enum {
   	LOG_CPU = 		1 << 0,  // 0x01
    LOG_MMU = 		1 << 1,  // 0x02
    LOG_GPU = 		1 << 2,  // 0x04
    LOG_DECODER = 	1 << 3,  // 0x08
} LogSubsystem_t;

typedef enum { 
	LOG_TRACE = 1 << 0,  
	LOG_ERROR = 1 << 1,
	LOG_INFO  = 1 << 2,
} LogLevel_t;

// void set_logs(uint8_t log_mask);
void set_log_level(uint8_t log_mask);
void log_event(LogLevel_t level, LogSubsystem_t, const char *fmt, ...);

#endif