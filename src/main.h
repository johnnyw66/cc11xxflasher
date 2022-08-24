#pragma once

// CC pins
#define CCDEBUG_CLK 19
#define CCDEBUG_DATA 23
#define CCDEBUG_RESET 33

void set_firmware_file(char * firmware, int file_size);
void set_firmware_dump_file(char * firmware, int file_size);
