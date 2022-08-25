#include "main.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "utils.h"
#include "cc_interface.h"
#include <iostream>
#include <fstream>
#include "intelhexclass.h"

char *program_name;

// Usage for this program
void usage()
{
    cerr << "Usage is " << program_name <<
                 " [file]" << " [file]" << endl;
    exit (EXIT_FAILURE);
}
// https://github.com/codinghead/Intel-HEX-Class


uint8_t * build_memblock(string fname, int *sz) {

  std::ifstream intelHexInput;
  intelhex iHexHelper;
  uint8_t * memblock ;


  intelHexInput.open(fname, ifstream::in);
  if(!intelHexInput.good())
	{
    	std::cerr << "Error: couldn't open " << fname << std::endl;
      return nullptr ;
	}

  cout << "Running IntelHEX Reader" << endl;

  intelHexInput >> iHexHelper;

  //printf("Current Address %lu\n",iHexHelper.currentAddress());
  //printf("End Address %x\n",iHexHelper.end());
  iHexHelper.begin();
  unsigned long start_address = iHexHelper.currentAddress() ;
  printf("Start Address %lu\n",start_address);
  iHexHelper.end() ;
  unsigned long end_address = iHexHelper.currentAddress();
  printf("End Address %lu\n", end_address) ;
  int size =  end_address - start_address ;
  printf("Size %d\n",size) ;
  *sz = size ;

  memblock = new uint8_t [size];
  int wr = 0 ;

  for (unsigned long i = 0 ; i < size ; i++) {
    memblock[i] = 0 ;
    unsigned char data ;
    if (iHexHelper.getData(&data, i)) {
      memblock[i] = data ;
    }
    wr++ ;
  }
  printf("Written %d bytes\n", wr) ;
  return memblock ;
}

int testihex(const int argc,  char *argv[])
{

  std::ifstream intelHexInput;

  // Create an output stream
  std::ofstream intelHexOutput;

  // Create a string to store lines of Intel Hex info
  std::string intelHexLine;
// Create a variable of the class we are testing
  intelhex classTest;

// Make class verbose
  classTest.verboseOn();

// The program name is the first argument - save for later use
  program_name = argv[0];

  // Make sure there are only <command> and 2 x <file> arguments
	if(argc != 3) {
    	usage();
  }

  intelHexInput.open(argv[1], ifstream::in);

	if(!intelHexInput.good())
	{
    	std::cerr << "Error: couldn't open " << argv[1] << std::endl;
    	usage();
	}

	intelHexOutput.open(argv[2], ofstream::out);

	if(!intelHexOutput.good())
	{
    	std::cerr << "Error: couldn't open " << argv[2] << std::endl;
    	usage();
	}

  cout << "Running IntelHEX Class Test" << endl;

  intelHexInput >> classTest;

  //cout << "Final address is 0x" << setw(2) << setfill('0') << uppercase << hex << classTest.currentAddress() << endl;

  cout << "File contained " << classTest.getNoWarnings() << " warnings and "
       << classTest.getNoErrors() << " errors." << endl;

  while (classTest.getNoErrors() > 0)
  {
    string message;
    classTest.popNextError(message);
    cout << message << endl;
  }
  while (classTest.getNoWarnings() > 0)
  {
      string message;
      classTest.popNextWarning(message);
      cout << message << endl;
  }

  intelHexOutput << classTest;

  return(0);

}

void flash_firmware(const char * firmware_filename)
{
  uint8_t * memblock ;
  int flashing_size ;
  memblock = build_memblock(firmware_filename, &flashing_size) ;
  printf("flash_firmware: size = %d\n", flashing_size) ;

  uint16_t device_id = cc.begin(CCDEBUG_CLK, CCDEBUG_DATA, CCDEBUG_RESET);
  printf("Device id: %s\n",array_to_hex_string((uint8_t *)&device_id, 2, true).c_str());

  printf("Chip erasing\n");
  cc.erase_chip();
  printf("Chip erasing done\n");

  for (int retry = 3; retry > 0; retry--)
  {
    printf("Flashing start\n");
    cc.write_code_memory(0x0000, memblock, flashing_size);
    printf("Flashing done\n");
    printf("Verify start\n");
    if (cc.verify_code_memory(0x0000, memblock, flashing_size) == 0)
    {
      printf("Verify successful\n");
      break;
    }
    else
    {
      printf("Verify failed\n");
    }
  }
  delete [] memblock;
  cc.reset_cc();
  printf("CC reset\n");
}



/*
void dump_firmware(const char * firmware_dump_filename)
{
  int dumping_size = 0 ;

  if (SPIFFS.totalBytes() - SPIFFS.usedBytes() < dumping_size)
  {
    printf("not enough empty flash on esp32");
    return;
  }
  File file = SPIFFS.open(firmware_dump_filename, "w");
  if (file == 0)
  {
    printf("Could not create file");
    return;
  }
  uint8_t *ptr = (uint8_t *)malloc(dumping_size);
  if (ptr == nullptr)
  {
    printf("No memory to allocate the buffer needed");
    return;
  }

  uint16_t device_id = cc.begin(CCDEBUG_CLK, CCDEBUG_DATA, CCDEBUG_RESET);
  printf("Device id: %s", array_to_hex_string((uint8_t *)&device_id, 2, true).c_str());
  printf("Reading flash start");
  cc.read_code_memory(0x0000, dumping_size, ptr);
  file.write(ptr, dumping_size);
  file.close();
  free(ptr);
  cc.reset_cc();
  printf("CC reset");
  printf("Reading done, %s downloaded.", firmware_dump_filename) ;
}

*/
//int pc ;

void percent_callback(uint8_t percent)
{
  printf(".") ;
  //psymbol = [ "|","/","-","\","|"]
  //printf("%s\r\n", psymbol[pc++ % 3]);
}

int main(const int argc,  char *argv[])
{
  //delay(1000);
  printf("Welcome to CC Flasher. DC %d DD %d RST %d TIMEOUT %d ms WRITE TIMEOUT %d ms\n",CCDEBUG_CLK,CCDEBUG_DATA,CCDEBUG_RESET,TIMEOUT,WR_TIMEOUT) ;
  cc.set_callback(percent_callback);
  //dump_firmware("dump") ;
  //flash_firmware("flash.hex");
  //testihex(argc, argv) ;
  flash_firmware(argv[1]) ;

}
