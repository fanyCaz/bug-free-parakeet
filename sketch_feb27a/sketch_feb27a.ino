#include <Servo.h>

Servo puerta;
int echo = 12;
int trigger = 13;
int tiempo;
int distancia;
int led = 2;
void setup()
{
  Serial.begin(9600);
  puerta.attach(4);
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(led,OUTPUT);
}

void loop()
{
  /*
   * PUERTA DE MINA
   * Cuando acercas tu mano al ultrasonico, la puerta se abre,
   * cuando la quitas se cierra.
   * Dentro del contenedor de la puerta, se tiene el alimento de la gata esa.
   */
  digitalWrite(trigger,HIGH);
  delay(1);
  digitalWrite(trigger,LOW);
  tiempo = pulseIn(echo,HIGH);
  distancia = tiempo/58.2;
  Serial.println("distancia");
  Serial.println(distancia);
  if(distancia < 15){
    Serial.println("distancia");
    puerta.write(90);
    digitalWrite(led,HIGH);
    delay(800);
  }else{
    digitalWrite(led,LOW);
    Serial.println("no");
    puerta.write(0);
  }
  delay(100);
}
