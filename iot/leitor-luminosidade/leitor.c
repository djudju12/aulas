#define ROW_1     0x80
#define ROW_2     0xC0
#define CLEAR     0x01
#define CUR_OFF   0x0C
#define CUR_ON    0x0E
#define CUR_BLINK 0x0F

#define DB7 7
#define DB6 6
#define DB5 5
#define DB4 4
#define DB3 3
#define DB2 2
#define DB1 1
#define DB0 0

#define LUM_OUT 10
#define LUM_IN  A0
#define LUM_MAX 510
#define LUM_MIN 255

#define RS 8
#define EN 9

#define ZERO     0x30
#define NEGATIVE 0x2D


void load_cmd(byte b)
{
  digitalWrite(RS, LOW);
  digitalWrite(EN, HIGH);
  
  digitalWrite(DB0, b&1);
  digitalWrite(DB1, b&2);
  digitalWrite(DB2, b&4);
  digitalWrite(DB3, b&8);
  digitalWrite(DB4, b&16);
  digitalWrite(DB5, b&32);
  digitalWrite(DB6, b&64);
  digitalWrite(DB7, b&128);
  
  delay(2);
  digitalWrite(EN, LOW);
  delay(2);
}

void load_write(byte b)
{
  digitalWrite(RS, HIGH);
  digitalWrite(EN, HIGH);
  
  digitalWrite(DB0, b&1);
  digitalWrite(DB1, b&2);
  digitalWrite(DB2, b&4);
  digitalWrite(DB3, b&8);
  digitalWrite(DB4, b&16);
  digitalWrite(DB5, b&32);
  digitalWrite(DB6, b&64);
  digitalWrite(DB7, b&128);
  
  delay(2);
  digitalWrite(EN, LOW);
  delay(2);
}

void write_str(char* s)
{
  while(*s)
    load_write(*s++);
}

byte toByte(int n)
{
  return n+ZERO;
}

void write_num(int num)
{
  int first_number, second_number, third_number;
  if (num < 0) {
    load_write(NEGATIVE);
  }
  
  
  num = abs(num);
  if (num < 10) {
    load_write(ZERO);
    load_write(ZERO);
  	load_write(toByte(num));
  } else if (num < 100) {
    load_write(ZERO);
  	first_number = num / 10;
  	second_number = num % 10;
  	load_write(toByte(first_number));
  	load_write(toByte(second_number));
  } else if (num < 1000) {
    first_number = num / 100;
  	second_number = (num % 100) / 10;
    third_number = (num % 100) % 10;
  	load_write(toByte(first_number));
  	load_write(toByte(second_number));
    load_write(toByte(third_number));
  } 
}

void clear()
{
  load_cmd(CLEAR);
}

void lcd_init()
{
  load_cmd(0x38);
  delay(5);
  load_cmd(0x38);
  delay(1);
  load_cmd(0x38);
  load_cmd(0x06);
  load_cmd(0x0E);
  load_cmd(0x01);
  delay(5);
}

void setup()
{
  pinMode(DB7, OUTPUT);
  pinMode(DB6, OUTPUT);
  pinMode(DB5, OUTPUT);
  pinMode(DB4, OUTPUT);
  pinMode(DB3, OUTPUT);
  pinMode(DB2, OUTPUT);
  pinMode(DB1, OUTPUT);
  pinMode(DB0, OUTPUT);
  pinMode(RS, OUTPUT);
  pinMode(EN, OUTPUT);
  lcd_init();
  load_cmd(0x87);
  load_write(0x30);
  clear();
  write_str("Luminosidade: ");
}

int read_lum()
{
  return analogRead(LUM_IN) - LUM_MIN;
}

void loop()
{
  load_cmd(ROW_2);
  int lum = read_lum();
  write_num(lum);

  float lum_norm = (float) lum/LUM_MIN;
  if (lum_norm < 0.7) {
    digitalWrite(LUM_OUT, HIGH);
    write_str(" Lamp ON ");
  } else {
    digitalWrite(LUM_OUT, LOW);
    write_str(" Lamp OFF");
  }

  delay(1000);
}