int clkPin = 7;   // Pin for 12 kHz clock signal (simulated)
int dPin = 8;     // Pin for D input (AND gate output)
int q1Pin = 9;    // Pin to read Q1 from 7474 IC
int q2Pin = 10;   // Pin to read Q2 from 7474 IC

int Q1 = 0;      // Variable to store Q1 state (read from IC)
int Q2 = 0;      // Variable to store Q2 state (read from IC)

unsigned long prevTime = 0;
int clkFreq = 12000;  // 12 kHz clock frequency
int clkState = 0;     // Current state of the clock

void setup() {
  pinMode(clkPin, OUTPUT);  // Clock signal
  pinMode(dPin, OUTPUT);    // D input to 7474 IC
  pinMode(q1Pin, INPUT);    // Q1 output from 7474 IC
  pinMode(q2Pin, INPUT);    // Q2 output from 7474 IC

  Serial.begin(9600);
}

void loop() {
  // Generate 12 kHz clock signal
  if (micros() - prevTime >= (1000000 / clkFreq) / 2) { // Toggle clock every half cycle
    clkState = !clkState;
    digitalWrite(clkPin, clkState);  // Write clock signal to clkPin
    prevTime = micros();
  }

  // Read Q1 and Q2 from the 7474 IC
  Q1 = digitalRead(q1Pin);  // Read Q1 state from pin 9
  Q2 = digitalRead(q2Pin);  // Read Q2 state from pin 10

  // AND gate logic: Q1 && !Q2 (simulated internally)
  int D1 = Q1 && !Q2;

  // Write the AND gate result to D1 input of the first flip-flop (D1 = Q1 && !Q2)
  digitalWrite(dPin, D1);

  // Print the states of Q1 and Q2 to monitor the frequency division
  Serial.print("Q1: ");
  Serial.print(Q1);
  Serial.print("\tQ2: ");
  Serial.println(Q2);

  // Small delay to slow down the serial monitor output for better visualization
  delay(10);
}
