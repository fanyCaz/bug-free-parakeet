#include <Servo.h>
#include <Keypad.h>

//Button
const int push_btn = 3;

//Servo
Servo bote;
const int pin_bote = 4;

//Keypad
const int ROW_NUM=4;
const int COLUMN_NUM=4;

char keys[ROW_NUM][COLUMN_NUM] = {
	{'1','2','3','A'},
	{'4','5','6','B'},
	{'7','8','9','C'},
	{'*','0','#','D'}
};

byte pin_rows[ROW_NUM] = {9,8,7,6};
byte pin_column[COLUMN_NUM] = {5,4,3,2};

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

void setup(){
	Serial.begin(9600);
	bote.attach(pin_bote);
	pinMode(push_btn, INPUT);
}

//Aqui se debe checar del 0 al 9 la cantidad de una pintura que se va a usar
void loop(){
	char key = keypad.getKey();
	int val = digitalRead(push_btn);
	if(val == HIGH){
		
		if(key){
			Serial.println(key);
			bote.write(90);
			delay(600);
		}
	}
  bote.write(0);
}
