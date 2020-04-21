/**
 * Wisol.h - Library for interfaciong with Wisol WSSFM11R2D Module.
 * Created by lgarciaos, February 9, 2020.
*/

#ifndef Wisol_h
#define Wisol_h

#include "Arduino.h"

#define CMD_AT    "AT"
#define CMD_ID    "AT$I=10"
#define CMD_PAC   "AT$I=11"
#define CMD_CB    "AT$CB=-1,0"
#define CMD_TR3  "AT$TR=3"
#define CMD_GI    "AT$GI?"
#define CMD_TEMP  "AT$T?"
#define CMD_VOLT  "AT$V?"
#define CMD_RC    "AT$RC"
#define CMD_WRITE "AT$SF="
#define CMD_SLEEP "AT$P=1"
#define CMD_DEEP_SLEEP "AT$P=2"

class Wisol
{
  public:
    Wisol(HardwareSerial * serial, int sleep_pin);
    void begin();
    String get_id(void);
    String get_pac(void);
    String get_temp(void);
    void send(String msg);
    void sleep(void);
    void deep_sleep(void);
    void wakeup(void);
  private:
    String read();
    int _sleep_pin;
    String _id;
    String _pac;
    HardwareSerial * _serial;
};

#endif
