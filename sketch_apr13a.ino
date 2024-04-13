#include <Servo.h>

#define BLYNK_PRINT Serial


#define BLYNK_TEMPLATE_ID "TMPL6fxnskw1g"
#define BLYNK_TEMPLATE_NAME "Esp8266"
#define BLYNK_AUTH_TOKEN "DgolYcs8BLgpBQoxlUXiiTtMWhhh"

#define FORWARD_PIN  D7  
#define REVERSE_PIN  D8


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266_SSL.h>

char auth[] = "DgolYcs8BLgpBQoxlUXiiTtMWPofBwhh";
char ssid[] = "Redmi";
char pass[] = "";

int dir = 0;
int M1PWM = D6; 
Servo servo1;
Servo servo2;

BLYNK_WRITE(V1)
{
  int pinValue1 = param.asInt(); // assigning incoming value from pin V1 to a variable
  analogWrite(M1PWM,pinValue1);
  Blynk.virtualWrite(V1, pinValue1);
  Serial.print("V1 Slider value is: ");
  Serial.println(pinValue1);
}

BLYNK_WRITE(V4){
  dir = param.asInt();
}

BLYNK_WRITE(V2){
  if (dir == 1){
   servo1.write(param.asInt());
    digitalWrite(FORWARD_PIN, HIGH);
    digitalWrite(REVERSE_PIN, LOW);
  }else if (dir == 0){
    servo1.write(param.asInt());
    digitalWrite(FORWARD_PIN, LOW);
    digitalWrite(REVERSE_PIN, HIGH);
  }
}

BLYNK_WRITE(V3){

  servo2.write(param.asInt());

}
void setup(){
  Serial.begin(9600);

  pinMode(FORWARD_PIN, OUTPUT);
  pinMode(REVERSE_PIN, OUTPUT);

  // Initialize both relays to OFF state
  digitalWrite(FORWARD_PIN, LOW);
  digitalWrite(REVERSE_PIN, LOW);

  servo1.attach(D3);
  servo2.attach(D4);
  pinMode (M1PWM,OUTPUT);
  servo1.write(180);
  delay(3000);
  servo1.write(90);
  Blynk.begin(auth, ssid, pass);

}

void loop()

{

  Blynk.run();

}