String input;
byte current_Sensing_PIN = 5;
byte command_PIN_1 = 7;
byte command_PIN_2 = 8;

byte UP[2] = {LOW, HIGH};
byte DOWN[2] = {HIGH, LOW};
byte STOP[2] = {HIGH, HIGH};


void move_up() {
  digitalWrite(command_PIN_1, UP[0]);
  digitalWrite(command_PIN_2, UP[1]);  
}

void move_down() {
  digitalWrite(command_PIN_1, DOWN[0]);
  digitalWrite(command_PIN_2, DOWN[1]);  
}

void stop() {
  digitalWrite(command_PIN_1, STOP[0]);
  digitalWrite(command_PIN_2, STOP[1]);  
}

void setup() {
  Serial.begin(9600);
  pinMode(current_Sensing_PIN, INPUT);
  pinMode(command_PIN_1, OUTPUT);
  pinMode(command_PIN_2, OUTPUT);
  stop();
}


void loop() {
  if (Serial.available() > 0) {
    input = Serial.readStringUntil('\n');
    if (input == "H") {
      move_up();
    }
    else if (input == "B") {
      move_down();
    }
    else {
      // Raise error
      Serial.println("[ACTUATOR -> ERROR] Unknown command.");
      return;
    }

    Serial.println("[ACTUATOR -> INFO] Command received. Moving...");
    delay(500);
    while ( digitalRead(current_Sensing_PIN) == HIGH ) {
      delay(100);
    }
    delay(100);
    stop();
    Serial.println("[ACTUATOR -> SUCCESS] Command executed: actuator in position=" + input);
  }
}
