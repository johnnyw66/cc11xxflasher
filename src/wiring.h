#define OUTPUT (1)
#define INPUT (0)
#define LOW (0)
#define HIGH (1)

extern void pinMode(int, int) ;
extern int digitalRead(int) ;
extern int digitalWrite(int,int) ;

extern void delay(int) ;
extern void delayMicroseconds(int) ;
extern int millis() ;
