#include <stdio.h>
#include "wiring.h"
#include <chrono>

uint32_t GetMillis() {
	using namespace std::chrono;
	return static_cast<uint32_t>(duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()).count());
}

void pinMode(int pin, int mode) {
  //printf("pinMode : %d %d\n",pin,mode) ;
}

int digitalRead(int pin) {
  //printf("digitalRead : %d\n",pin) ;
  return 0 ;
}

int digitalWrite(int pin, int value) {
  //printf("digitalWrite : %d %d\n",pin,value) ;
  return 0 ;
}

void delay(int d) {
  //printf("delay %d\n",d) ;
}

void delayMicroseconds(int d) {
  //printf("delayMicroseconds %d\n",d) ;

}

int millis() {
  //printf("millis\n") ;
  return GetMillis() ;
}
