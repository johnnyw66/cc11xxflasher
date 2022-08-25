#pragma once

// CC pins
#define CCDEBUG_CLK 27
#define CCDEBUG_DATA 28
#define CCDEBUG_RESET 24 

void set_firmware_file(char * firmware, int file_size);
void set_firmware_dump_file(char * firmware, int file_size);
