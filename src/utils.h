#pragma once

#include <stdint.h>
#include <string>
using namespace std;

unsigned char nibble(char c);
void hexCharacterStringToBytes(unsigned char *byteArray, string hexString);
void tohex(string in, size_t insz, char * out, size_t outsz);
string split(string s, char parser, int index);
string array_to_hex_string(uint8_t *in_arr, size_t len, bool endian = false);
