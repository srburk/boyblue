
#include "log.h"

#include <stdio.h>
#include <stdarg.h>

static uint8_t log_enabled_mask = 0x00; // all off by default

static const char* get_subsystem_label(LogSubsystem_t subsystem) {
    switch (subsystem) {
        case LOG_CPU:   return "CPU";
        case LOG_MMU:   return "MMU";
        case LOG_GPU:   return "GPU";
        default:        return "DEFAULT";
    }
}
void set_logs(uint8_t log_mask) {
	log_enabled_mask = log_mask;
}

void log_event(LogLevel_t level, LogSubsystem_t subsystem, const char *fmt, ...) {

	// check if subsystem is enabled
	if (!(log_enabled_mask & subsystem)) return;

	FILE *fp = NULL;
		
	switch (level) {
		case LOG_TRACE:
			fp = fopen("trace.log", "a"); 
			break;
		case LOG_INFO:
			fp = fopen("info.log", "a");
			break;
		case LOG_ERROR:
			fp = stderr;
			break;	
	}
	
	va_list args;
	va_start(args, fmt);
	fprintf(fp, "[%s] ", get_subsystem_label(subsystem));
	vfprintf (fp, fmt, args);
	va_end (args);
	
	fprintf(fp, "\n");
	fclose(fp);
}