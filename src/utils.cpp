//#include <stdio.h>
//#include <stdint.h>
#include "utils.h"


unsigned char nibble(char c)
{
  if (c >= '0' && c <= '9')
    return c - '0';

  if (c >= 'a' && c <= 'f')
    return c - 'a' + 10;

  if (c >= 'A' && c <= 'F')
    return c - 'A' + 10;

  return 0;
}

void hexCharacterStringToBytes(unsigned char *byteArray, string hexString)
{
  bool oddLength = hexString.length() & 1;

  unsigned char currentByte = 0;
  int byteIndex = 0;

  for (int charIndex = 0; charIndex < hexString.length(); charIndex++)
  {
    bool oddCharIndex = charIndex & 1;
    if (oddLength)
    {
      if (oddCharIndex)
      {
        currentByte = nibble(hexString[charIndex]) << 4;
      }
      else
      {
        currentByte |= nibble(hexString[charIndex]);
        byteArray[byteIndex++] = currentByte;
        currentByte = 0;
      }
    }
    else
    {
      if (!oddCharIndex)
      {
        currentByte = nibble(hexString[charIndex]) << 4;
      }
      else
      {
        currentByte |= nibble(hexString[charIndex]);
        byteArray[byteIndex++] = currentByte;
        currentByte = 0;
      }
    }
  }
}

void tohex(unsigned char * in, size_t insz, char *out, size_t outsz)
{
  unsigned char *pin = in;
  const char *hex = "0123456789ABCDEF";
  char *pout = out;
  for (; pin < in + insz; pout += 3, pin++)
  {
    pout[0] = hex[(*pin >> 4) & 0xF];
    pout[1] = hex[*pin & 0xF];
    pout[2] = ':';
    if (pout + 3 - out > outsz)
    {
      break;
    }
  }
  pout[-1] = 0;
}

string split(string s, char parser, int index)
{
    string rs = "";
    int parserCnt = 0;
    int rFromIndex = 0, rToIndex = -1;
    while (index >= parserCnt)
    {
        rFromIndex = rToIndex + 1;
        rToIndex = s.find_first_of(parser, rFromIndex);
        if (index == parserCnt)
        {
            if (rToIndex == 0 || rToIndex == -1)
                return "";
            return s.substr(rFromIndex, rToIndex);
        }
        else
            parserCnt++;
    }
    return rs;
}


string array_to_hex_string(uint8_t *in_arr, size_t len, bool endian)
{
  string out_string = "";
  string hex = "0123456789ABCDEF";
  if(endian)
  {
    for(int i = len-1;i>=0;i--)
    {
      out_string += string(1,hex[(in_arr[i] >> 4) & 0xF]) + string(1,hex[in_arr[i] & 0xF]);
    }
  }
  else
  {
    for(int i = 0;i<len;i++)
    {
      out_string += string(1,hex[(in_arr[i] >> 4) & 0xF]) + string(1,hex[in_arr[i] & 0xF]);
    }
  }
  return out_string;
}


void unit_test_utils() {
  uint8_t test[5] = {'H','e','l','l','o'} ;
  string hs = array_to_hex_string(test,5,false) ;
  printf("unit_test_utils: array_to_hex_string: %s\n",hs.c_str());
}

//int main(const int argc, const char **argv) {
//  unit_test_utils() ;
//  return 0 ;
//}
