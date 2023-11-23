// C++ code
//
#define LED_1   10
#define RES_1    6
#define RES_2    7
#define BUTTON   9

#define LUM_IN  A0
#define LUM_MIN 255
#define SECOND  100

#define TRUE  7
#define FALSE 0

float read_normal_lum()
{
  int lum = analogRead(LUM_IN) - LUM_MIN;
  return (float) lum/LUM_MIN;
}

int timer_ms = 0;
void set_timer()
{
  int res_1 = digitalRead(RES_1);
  int res_2 = digitalRead(RES_2);
  
  if ((res_1 == HIGH) && (res_2 == HIGH)) {
    timer_ms = 30 * SECOND;
  } else if (res_2 == HIGH) {
    timer_ms = 20 * SECOND;
  } else if (res_1 == HIGH) {
    timer_ms = 10 * SECOND;
  } else {
    timer_ms = 10 * SECOND;
  }
}

void setup()
{
  set_timer();
  pinMode(LED_1, OUTPUT);
  pinMode(BUTTON, INPUT);
}

int runned = FALSE;
void loop()
{
  float lum = read_normal_lum();
  
  if ((lum > 0.8) && !runned) {
    digitalWrite(LED_1, HIGH);
    delay(timer_ms);
    digitalWrite(LED_1, LOW);
    runned = TRUE;
  } else if (lum <= 0.8) {
    runned = FALSE;
    digitalWrite(LED_1, LOW);
  }
}
