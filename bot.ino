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

void bot_setup()
{
  left();
  delay(300);
  stp();
  delay(100);
  right();
  delay(600);
  stp();
  delay(100);
  left();
  delay(300);
  stp();
}

void setup() {
  motor_init();
  bot_setup();
  
}

void loop() {
  delay(1000);
  delay(1000);
  fwd();
  delay(1000);
  stp();
  delay(100000);
}
