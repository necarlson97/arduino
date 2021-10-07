
int button1 = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  int d1 = analogRead(A2);
  int d2 = analogRead(A3);

  int x1 = analogRead(A0);
  int y1 = analogRead(A1);

  if(d1 > 40) button1 = 0;
  if(d1 == 0) button1 = 1;

  Serial.println(x1);
  Serial.println();
  Serial.println(y1);
  //Serial.println(d2);
  //Serial.println(d3);
  //Serial.println(d4);

//  Serial.println("###########################");
//
//  Serial.print("Button One: ");
//  Serial.println(d1);
//  Serial.print("Button Two: ");
//  Serial.println(d2);
//  Serial.print("Button Three: ");
//  Serial.println(d3);
//  Serial.print("Button Four: ");
//  Serial.println(d4);
//
//  Serial.print("Joy One X");
//  Serial.println(x1);
//  Serial.print("Joy One Y");
//  Serial.println(y1);
//
//  Serial.print("Joy Two X");
//  Serial.println(x2);
//  Serial.print("Joy Two Y");
//  Serial.println(y2);

  //delay(2000);
}
