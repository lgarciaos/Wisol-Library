/**
 * Wisol.h - Library for interfaciong with Wisol WSSFM1xR2D Module.
 * Created by lgarciaos, February 9, 2020.
*/

#include "Arduino.h"
#include "Wisol.h"

Wisol::Wisol(HardwareSerial * serial,int sleep_pin){
  _serial= serial;
  _sleep_pin= sleep_pin;
  _id="";
  _pac="";
}

void Wisol::begin(){
  _serial->begin(9600); //9600 is a fixed baudrate for wisol modules
  _delay_ms(200);
  _serial->println(CMD_CB);
  _delay_ms(200);
  read();
  _serial->println(CMD_TR3); //setting repetition to 3
  _delay_ms(200);
  read();
}

String Wisol::read(){
  char inData[25];
  char rx_buffer;
  byte index = 0;
  _delay_ms(200);
  if (_serial->available() > 0) {
    while (_serial->available() > 0) {
      rx_buffer = _serial->read();
      inData[index] = rx_buffer;
      index++;
    }
    inData[index] = '\0';
  }
  return inData;
}

String Wisol::get_id(){
  if(_id.equals("")){
    read(); //clean buffer
    _serial->println(CMD_AT);
    _delay_ms(100);
    read(); //should return 'OK'
    _serial->println(CMD_ID);
    _delay_ms(100);
    _id= read();
  }
  return _id;
}

String Wisol::get_pac(){
  if(_pac.equals("")){
    read(); //clean buffer
    _serial->println(CMD_AT);
    _delay_ms(100);
    read(); //should return 'OK'
    _serial->println(CMD_PAC);
    _delay_ms(100);
    _pac= read();
  }
  return _pac;
}

String Wisol::get_temp(){
  read(); //clean buffer
  _serial->println(CMD_AT);
  _delay_ms(100);
  read(); //should return 'OK'
  _serial->println(CMD_TEMP);
  _delay_ms(100);
  return read();
}

void Wisol::send(String msg){ // takes ~4800ms BEWARE
  String wisolResponse = "";
  read(); //clean buffer
  _serial->printf(CMD_AT);
  _delay_ms(200);
  wisolResponse = read();

  _serial->println(CMD_GI);
  _delay_ms(200);
  wisolResponse = read();

  if (int(wisolResponse[0]) == 48 || int(wisolResponse[2]) < 51) {
    _serial->println(CMD_RC);
    _delay_ms(200);
    wisolResponse = read();
  }

  _serial->println(CMD_WRITE+msg);
  //_serial.println(",1");  // uncomment if expecting downlink response
  _delay_ms(4000);
  wisolResponse = read();
  Serial.println(wisolResponse);

  _serial->println(CMD_AT);
  _delay_ms(100);
  wisolResponse = read();
}

void Wisol::sleep(){
  read(); //clean buffer
  _serial->println(CMD_AT);
  _delay_ms(100);
  read();
  _serial->println(CMD_SLEEP);
  read();
}

void Wisol::deep_sleep(){
  read(); //clean buffer
  _serial->println(CMD_AT);
  _delay_ms(100);
  read();
  _serial->println(CMD_DEEP_SLEEP);
}

void Wisol::wakeup_sleep(){
  digitalWrite(_sleep_pin,LOW);
  _delay_ms(250);
  digitalWrite(_sleep_pin,HIGH);
  _serial->println(CMD_AT);
  _delay_ms(100);
  read();
}
void Wisol::wakeup_deep_sleep(){
  _serial->println(CMD_AT);
  _delay_ms(100);
  _serial->println(CMD_AT);
  _delay_ms(100);
  read();
}

void Wisol::close(){
  _serial->end();
}
