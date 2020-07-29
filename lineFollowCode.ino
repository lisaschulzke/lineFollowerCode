const int irSensor1 = A0; //LINKS
const int irSensor2 = A1; //Mitte_Links
const int irSensor3 = A2; //Mitte
const int irSensor4 = A3; //Mitte_Rechts
const int irSensor5 = A4; //RECHTS

int irSensor[] = {A0, A1, A2, A3, A4};
int pin[] = {0, 0, 0, 0, 0};


//Gleichstrommotor 1
int GSM1 = 10; //speed links
int in1 = 9; //vorwärts links
int in2 = 8; //rückwärts links


// Gleichstrommotor 2
int GSM2 = 5; //speed rechts
int in3 = 7; //vorwärts rechts
int in4 = 6; //rückwärts rechts

int speedValue = 120;


//int intensity = 90;

int geschwL = 80;
int geschwR = 80;

// needed to check if robot is in stop state
bool stopped = true;

bool sensorStop = 1;
bool motorStop = true;


//const int delay_time = 1000;


void setup() {
  pinMode(irSensor1, INPUT);
  pinMode(irSensor2, INPUT);
  pinMode(irSensor3, INPUT);
  pinMode(irSensor4, INPUT);
  pinMode(irSensor5, INPUT);
  pinMode(GSM1, OUTPUT);
  pinMode(GSM2, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  // LED soll blinken, wenn 'mforward' empfangen wurde.
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Serial.begin(9600);
}
String serialInput = "";
void loop() {
  while (Serial.available() > 0) {
    char serialChar = Serial.read();
    serialInput += serialChar;
    if (serialChar == '\n') {
      //hier logik mit if abfrage ob true ist und wenn ja sensorstop auf true oder false
      if (serialInput.charAt(0) == 'm') {
        serialInput.remove(0, 1);

        if (serialInput.equals("forward\n")) {
          motorStop = false;
          digitalWrite(13, HIGH);

        } else if (serialInput == "stop\n") {
          motorStop = true;
          digitalWrite(13, LOW);
        }
        Serial.println("DONE > " + serialInput);
        serialInput = "";
      }
    }
  }
  for (int x = 0; x <  5; x++) {
    pin[x] = analogRead(irSensor[x]);
    if (pin[x] < 800) {
      pin[x] = 1;
    } else {
      pin[x] = 0;
    }
  }

  // ## Motor speed control
  sensorStop = true;

  //mforward case
  if (sensorStop && !motorStop) {

    // Drive Left
    if ((pin[0] == 1) && (pin[1] == 0) && (pin[2] == 0) && (pin[3] == 0) && (pin[4] == 0))
    {
      geschwR = 200;
      geschwL = 0;
      sensorStop = true;
    }
    //Drive SuperLeft Left
    else if ((pin[0] == 1) && (pin[1] == 1) && (pin[2] == 0) && (pin[3] == 0) && (pin[4] == 0))
    {
      geschwR = 175;
      geschwL = 0;
      sensorStop = true;
    }
    //Drive SuperLeft
    else if ((pin[0] == 0) && (pin[1] == 1) && (pin[2] == 0) && (pin[3] == 0) && (pin[4] == 0))
    {
      geschwR = 125;
      geschwL = 0;
      sensorStop = true;
    }
    //Drive left center
    else if ((pin[0] == 0) && (pin[1] == 1) && (pin[2] == 1) && (pin[3] == 0) && (pin[4] == 0))
    {
      geschwR = 100;
      geschwL = 0;
      sensorStop = true;
    }
    // Drive center
    else if ((pin[0] == 0) && (pin[1] == 0) && (pin[2] == 1) && (pin[3] == 0) && (pin[4] == 0))
    {
      geschwR = 80;
      geschwL = 80;
      sensorStop = true;
    }
    // Drive right center
    else if ((pin[0] == 0) && (pin[1] == 0) && (pin[2] == 1) && (pin[3] == 1) && (pin[4] == 0))
    {
      geschwL = 100;
      geschwR = 0;
      sensorStop = true;
    }
    // Drive right 
    else if ((pin[0] == 0) && (pin[1] == 0) && (pin[2] == 0) && (pin[3] == 1) && (pin[4] == 0))
    {
      geschwL = 125;
      geschwR = 0;
      sensorStop = true;
    }
    // Drive right superRight
    else if ((pin[0] == 0) && (pin[1] == 0) && (pin[2] == 0) && (pin[3] == 1) && (pin[4] == 1))
    {
      geschwL = 175;
      geschwR = 0;
      sensorStop = true;
    }
    // Drive superRight
    else if ((pin[0] == 0) && (pin[1] == 0) && (pin[2] == 0) && (pin[3] == 0) && (pin[4] == 1))
    {
      geschwL = 200;
      geschwR = 0;
      sensorStop = true;
    }
    //stop when sensor detects only black
    else if ((pin[0] == 1) && (pin[1] == 1) && (pin[2] == 1) && (pin[3] == 1) && (pin[4] == 1))
    {
      stopped = false;
      geschwR = 0;
      geschwL = 0;
      sensorStop = false;
    }

    //stop when sensor detects only white
    else if ((pin[0] == 0) && (pin[1] == 0) && (pin[2] == 0) && (pin[3] == 0) && (pin[4] == 0))
    {
      stopped = false;
      geschwR = 0;
      geschwL = 0;
      sensorStop = false;
    }

    Serial.print("Speed Left Wheel: ");
    Serial.print(geschwL);
    Serial.print("\n");

    Serial.print("Speed Right Wheel: ");
    Serial.print(geschwR);
    Serial.print("\n");
    Serial.println("");
    Serial.println("");


    analogWrite(GSM1, geschwL);
    analogWrite(GSM2, geschwR);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    if (true) {
      Serial.print("SuperLeft: ");
      Serial.print(pin[1]);
      Serial.print("\t");
      Serial.print(" - Left: ");
      Serial.print(pin[0]);
      Serial.print("\t");
      Serial.print(" - Center: ");
      Serial.print(pin[2]);
      Serial.print("\t");
      Serial.print(" - Right: ");
      Serial.print(pin[3]);
      Serial.print("\t");
      Serial.print(" - SuperRight: ");
      Serial.print(pin[4]);

      Serial.println("");
    }

    // mstop case
  } else if (!sensorStop || motorStop) {
    analogWrite(GSM1, geschwL);
    analogWrite(GSM2, geschwR);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  };
}
