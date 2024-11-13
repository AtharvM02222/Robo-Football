#define in1 3 // L298N Motor Driver pins
#define in2 5
#define in3 11
#define in4 6

int command = 'S'; // Default command is Stop
int Speed = 100; // Initial speed (range: 0-255)
unsigned long lastCommandTime = 0; // Time of the last command
const unsigned long timeout = 100; // Timeout period in milliseconds

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600); // Set the baud rate for Bluetooth communication
}

void loop() {
  bool newCommand = false;

  // Check if a command is available
  if (Serial.available() > 0) {
    command = Serial.read();
    lastCommandTime = millis(); // Update the time of the last command
    newCommand = true; // A new command is received
  }

  // Execute the command only if it's new
  if (newCommand) {
    handleCommand(command);
  }

  // Stop the car if the timeout has passed since the last command
  if (millis() - lastCommandTime > timeout) {
    Stop();
  }

  // Reset command after each loop to prevent it from sticking
  command = 'S';
}

void handleCommand(char cmd) {
  switch (cmd) {
    case 'F':
      forward();
      break;
    case 'B':
      back();
      break;
    case 'L':
      left();
      break;
    case 'R':
      right();
      break;
    case 'G':
      forwardleft();
      break;
    case 'I':
      forwardright();
      break;
    case 'H':
      backleft();
      break;
    case 'J':
      backright();
      break;
    case 'S': // Stop the robot
    case 'D': // Stop all movements
      Stop();
      break;
    case '0':
      Speed = 0;
      break;
    case '1':
      Speed = 10;
      break;
    case '2':
      Speed = 20;
      break;
    case '3':
      Speed = 30;
      break;
    case '4':
      Speed = 40;
      break;
    case '5':
      Speed = 50;
      break;
    case '6':
      Speed = 60;
      break;
    case '7':
      Speed = 70;
      break;
    case '8':
      Speed = 80;
      break;
    case '9':
      Speed = 90;
      break;
    case 'q':
      Speed = 100;
      break;
  }
}

void forward() {
  analogWrite(in1, Speed);
  analogWrite(in3, Speed);
  analogWrite(in2, 0);
  analogWrite(in4, 0);
}

void back() {
  analogWrite(in2, Speed);
  analogWrite(in4, Speed);
  analogWrite(in1, 0);
  analogWrite(in3, 0);
}

void left() {
  analogWrite(in3, Speed);
  analogWrite(in2, Speed);
  analogWrite(in1, 0);
  analogWrite(in4, 0);
}

void right() {
  analogWrite(in4, Speed);
  analogWrite(in1, Speed);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
}

void forwardleft() {
  analogWrite(in1, Speed * 0.7);
  analogWrite(in3, Speed);
  analogWrite(in2, 0);
  analogWrite(in4, 0);
}

void forwardright() {
  analogWrite(in1, Speed);
  analogWrite(in3, Speed * 0.7);
  analogWrite(in2, 0);
  analogWrite(in4, 0);
}

void backleft() {
  analogWrite(in2, Speed * 0.7);
  analogWrite(in4, Speed);
  analogWrite(in1, 0);
  analogWrite(in3, 0);
}

void backright() {
  analogWrite(in2, Speed);
  analogWrite(in4, Speed * 0.7);
  analogWrite(in1, 0);
  analogWrite(in3, 0);
}

void Stop() {
  analogWrite(in1, 0);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
  analogWrite(in4, 0);
}
