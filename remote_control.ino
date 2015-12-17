 #include <IRremote.h>

//LED Pins
int receiver = 11;
int green = 7;
int yellow = 5;
int red = 6;

//Current LED
int current = 7;

bool on;

IRrecv irrecv(receiver);

decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  Serial.println("## Starting IR listener ##");
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);

}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    if (results.value == 0xFF30CF) {
      //turn green on
      digitalWrite(current, LOW);
      current = green;
      digitalWrite(green, HIGH);
    }else if (results.value == 0xFF18E7) {
       //Trun yello on
       digitalWrite(current, LOW);
       digitalWrite(yellow, HIGH);
       current = yellow;
    }else if (results.value == 0xFF7A85) {
      // Trun red on
      digitalWrite(current, LOW);
      digitalWrite(red, HIGH);
      current = red;
    }else if (results.value == 0xFFA25D) {
      // User pressed on/off
      onoff();
    }
    
    delay(100);
    irrecv.resume();
  }

}


void onoff() {
  if (on) {
    digitalWrite(current, LOW);
    on = false;
  }else {
    digitalWrite(current, HIGH);
    on = true;
  }
}


