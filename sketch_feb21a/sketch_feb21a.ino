int time = 500;
void setup()
{
  pinMode(13, OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(3, OUTPUT);
}

void encender(int pri, int seg, int ter, int tiempo){
  while(seg != 5){
    digitalWrite(pri, HIGH);
    digitalWrite(seg, HIGH);
    digitalWrite(ter, HIGH);
    delay(tiempo);
    digitalWrite(pri, LOW);
    pri = pri - 1;
    seg = seg -1;
    ter = ter -1;
  }
  digitalWrite(pri, HIGH);
  digitalWrite(seg, HIGH);
  delay(tiempo);
  digitalWrite(pri, LOW);
  delay(tiempo);
  digitalWrite(seg, LOW);
}

void loop()
{
  int primer = 13;
  int segundo = 12;
  int tercero = 11;
  if(time > 0){
    encender(primer,segundo,tercero,time);
    time = time - 200;
    digitalWrite(3,HIGH);
    delay(500);
    digitalWrite(3,LOW);
  }else{
    time = 1000;
  }
  
}
