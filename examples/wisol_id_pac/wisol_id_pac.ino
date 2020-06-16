#include <Wisol.h>

Wisol my_wisol(2); //sleep pin
String vara, varb;
void setup(){

  my_wisol.begin(&Serial);
}
void loop(){
  vara= my_wisol.get_id();
  varb= my_wisol.get_pac();
  delay(3000);
}
