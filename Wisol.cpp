/**
 * Wisol.h - Library for interfaciong with Wisol WSSFM11R2D Module.
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
}

String Wisol::read(){
  char inData[25];
  char rx_buffer;
  byte index = 0;
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
    delay(50);
    read(); //should return 'OK'
    delay(25);
    _serial->println(CMD_ID);// Command to get ID
    delay(50);
    _id= read();
    delay(25);
  }
  return _id;
}

String Wisol::get_pac(){
  if(_pac.equals("")){
    read(); //clean buffer
    _serial->println(CMD_AT);
    delay(50);
    read(); //should return 'OK'
    delay(25);
    _serial->println(CMD_PAC);// Command to get ID
    delay(50);
    _pac= read();
    delay(25);
  }
  return _pac;
}

void Wisol::send(String msg){ // takes ~680ms BEWARE
  String wisolResponse = "";
  read(); //clean buffer
  _serial->println(CMD_AT);
  delay(50);
  wisolResponse = read();
  delay(35);
  _serial->println(CMD_CB);
  delay(50);
  wisolResponse = read();
  delay(35);
  _serial->println(CMD_GI);
  delay(50);
  wisolResponse = read();
  delay(50);
  if (int(wisolResponse[0]) == 48 || int(wisolResponse[2]) < 51) {
    _serial->println(CMD_RC);
    delay(50);
    read();
    delay(50);
  }
  _serial->print(CMD_WRITE);
  _serial->println(msg);
  delay(100);
  //serial.print(",1");  // uncomment if expecting downlink response
  read();
  delay(200);
  read();
}

void Wisol::sleep(){
  read(); //clean buffer
  _serial->println(CMD_AT);
  delay(50);
  read();
  delay(10);
  _serial->println(CMD_SLEEP); //deep sleep
}

void Wisol::wakeup(){
  digitalWrite(_sleep_pin,LOW);
  delay(150);
  digitalWrite(_sleep_pin,HIGH);
}
