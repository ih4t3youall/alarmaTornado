int led = 13; //led Rojo de prueba de conexión

float voltageValue[4] = {0,0,0,0};
char inbyte = 0; //Char para leer el led
int jumper = 7;
 
void setup() {
  // initialise serial communications at 9600 bps:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(jumper,OUTPUT);
  digitalWrite(led, LOW);

}
 
void loop() {
  getVoltageValue();
  //when serial values have been received this will be true
  
  if (Serial.available() > 0)
  {
    inbyte = Serial.read();
    Serial.println(inbyte);
    if (inbyte == '2')
    {
      digitalWrite(led, LOW); //LED off
      digitalWrite(jumper,LOW);
      voltageValue[0] = 0;
    }
    if (inbyte == '1')
    {
      digitalWrite(led, HIGH); //LED on
      digitalWrite(jumper,HIGH);
      voltageValue[0] = 1;
    }
  }
  sendAndroidValues();
  delay(2000); 
}
 
void getVoltageValue()
{
  voltageValue[0] = 1; //led
  voltageValue[1] = 2;
  voltageValue[2] = 3;
  voltageValue[3] = 4;
  
}

//enviar los valores por el dipositivo android por el modulo Bluetooth
void sendAndroidValues()
 {
  Serial.print('#'); //hay que poner # para el comienzo de los datos, así Android sabe que empieza el String de datos
  for(int k=0; k<4; k++)
  {
    Serial.print(voltageValue[k]);
    Serial.print("martin");
    Serial.print('+'); //separamos los datos con el +, así no es más fácil debuggear la información que enviamos
  }
 Serial.print('~'); //con esto damos a conocer la finalización del String de datos
 Serial.println();
 delay(10);        //agregamos este delay para eliminar tramisiones faltantes
}
