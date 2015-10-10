#define left_speed 9
#define right_speed 10
#define le 0 //leftend
#define lm 1 //leftmiddle
#define m 2 //middle
#define rm 3  //rightmiddle
#define re 4  //rightend
#define lmf 8   //left motor forward
#define lmb 7   //left motor back
#define rmf 6   //right motor forward
#define rmb 5   //left motor back

int i;
int high[6]; //config high diff readings
int low[6];  //config low diff readings
int on[6];  //present on readings
int off[6];  //present off readings
int diff[6]; //present diff

int lcount = 0;
int rcount = 0;
void left ( int turn_speed = 255)
{
  analogWrite(left_speed , turn_speed);
  analogWrite(right_speed , turn_speed);
  digitalWrite(lmf, LOW);
  digitalWrite(lmb, HIGH);
  digitalWrite(rmf, HIGH);
  digitalWrite(rmb, LOW);
}

void right ( int turn_speed = 255)
{
  analogWrite(left_speed , turn_speed);
  analogWrite(right_speed , turn_speed);
  digitalWrite(lmf, HIGH);
  digitalWrite(lmb, LOW);
  digitalWrite(rmf, LOW);
  digitalWrite(rmb, HIGH);
}

void fwd ( int turn_speed = 255)
{
  analogWrite(left_speed , turn_speed);
  analogWrite(right_speed , turn_speed);
  digitalWrite(lmf, HIGH);
  digitalWrite(lmb, LOW);
  digitalWrite(rmf, HIGH);
  digitalWrite(rmb, LOW);
}

void rev ( int turn_speed = 255)
{
  analogWrite(left_speed , turn_speed);
  analogWrite(right_speed , turn_speed);
  digitalWrite(lmf, LOW);
  digitalWrite(lmb, HIGH);
  digitalWrite(rmf, LOW);
  digitalWrite(rmb, HIGH);
}

void stp ()
{
  digitalWrite(lmf, LOW);
  digitalWrite(lmb, LOW);
  digitalWrite(rmf, LOW);
  digitalWrite(rmb, LOW);
}

void motor_init()
{
  for (i = 5; i<=10; i++)
    pinMode(i , OUTPUT);
  analogWrite( left_speed, 255);
  analogWrite( right_speed, 255);
}

void test()
{
left();
delay(1000);
right();
delay(1000);
fwd();
delay(1000);
rev();
delay(1000);
stp();
delay(1000000);
}

void find_diff()
{
  digitalWrite(13, LOW);
  Serial.print("off  ");
  delay(50);
  for( int i =0; i<5; i++)
  {
    off[i] = analogRead(i);
     Serial.print(off[i] );
      Serial.print("\t");
  }
  Serial.print("\n");
  delay(50);
  
  digitalWrite(13,HIGH);
  Serial.print("on  ");
  delay(50);
  for( int i =0; i<5; i++)
  {
    on[i] = analogRead(i);
     Serial.print( on[i]);
      Serial.print("\t");
  }
  Serial.print("\n");
  delay(50);
  
  Serial.print("Diff  ");
  for( int i =0; i<5; i++)
  {
    diff[i] = on[i] - off[i];;
     Serial.print( diff[i]);
      Serial.print("\t");
  }
  Serial.print("\n");  
}

void bot_setup()
{
  find_diff();
  high[0] = analogRead(diff[0]);
  high[1] = analogRead(diff[1]);
  high[3] = analogRead(diff[3]);
  high[4] = analogRead(diff[4]);
  high[2] = (high[0] + high[1] + high[3] + high[4])/4;
  low[2] = diff[2];
  /*left();
  delay(300);
  stp();
  delay(100);
  right();
  delay(600);
  stp();
  delay(100);
  left();
  delay(300);
  stp();*/
}

void setup() {
  motor_init();
  bot_setup();
  
}

void loop() {
  find_diff();
  if(diff[1]<(high[1]+low[2])/2)
   while(!(diff[1]<(high[1]+low[2])/2))
   {
     left();
     find_diff();
   }
  else if(diff[3]<(high[3]+low[2])/2)
   while(!(diff[3]<(high[3]+low[2])/2))
   {
     right();
     find_diff();
   }
  else
   fwd();
}
