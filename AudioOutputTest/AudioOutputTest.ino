
int f=200;
int d=10; 
int dVel=1;
int fVel=-2;

void setup() {

}

void loop() {
  if(d<10) dVel = random(1,5);
  if(d>500) dVel = random(-5,-1);
  
  if(f<35) fVel = random(1,5);
  if(f>500) fVel = random(-5,-1);

  f+=fVel;
  d+=dVel;
   
  tone(11, f, d);

}
