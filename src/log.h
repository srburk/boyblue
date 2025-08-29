
// log.h

#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

#include <stdint.h>

#define LOG_ALL	(uint8_t)(0xFF)

typedef enum {
   	LOG_CPU = 1 << 0,  // 0x01
    LOG_MMU = 1 << 1,  // 0x02
    LOG_GPU = 1 << 2,  // 0x04
} LogSubsystem_t;

typedef enum { LOG_TRACE, LOG_ERROR, LOG_INFO } LogLevel_t;

void set_logs(uint8_t log_mask);
void log_event(LogLevel_t level, LogSubsystem_t, const char *fmt, ...);

#endif