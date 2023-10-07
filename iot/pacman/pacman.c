#define ROW_1     0x80
#define ROW_2     0xC0
#define CLEAR     0x01
#define CUR_OFF   0x0C
#define CUR_ON    0x0E
#define CUR_BLINK 0x0F

#define D7 7
#define D6 6
#define D5 5
#define D4 4
#define D3 3
#define D2 2
#define D1 1
#define D0 0

#define RS 8
#define EN 9

#define CMD LOW
#define WRITE HIGH

byte pacman_open[][8] = {
    {0x00, 0x03, 0x04, 0x08, 0x08, 0x10, 0x10, 0x10},
    {0x1F, 0x00, 0x06, 0x06, 0x00, 0x00, 0x03, 0x1C},
    {0x00, 0x18, 0x04, 0x02, 0x02, 0x0C, 0x10, 0x00},
    {0x10, 0x10, 0x08, 0x08, 0x04, 0x03, 0x00, 0x00},
    {0x1C, 0x03, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00},
    {0x10, 0x0C, 0x02, 0x02, 0x04, 0x18, 0x00, 0x00}
};

byte pacman_close[][8] = {
    {0x00, 0x03, 0x04, 0x08, 0x08, 0x10, 0x10, 0x10}, // 0 0
    {0x1F, 0x00, 0x06, 0x06, 0x00, 0x00, 0x00, 0x1F}, // 1 0
    {0x00, 0x18, 0x04, 0x02, 0x02, 0x01, 0x01, 0x1F}, // 2 0
    {0x10, 0x10, 0x08, 0x08, 0x04, 0x03, 0x00, 0x00}, // 0 1
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00}, // 1 1
    {0x01, 0x01, 0x02, 0x02, 0x04, 0x18, 0x00, 0x00}  // 1 2
};

byte point[][8]= {
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0E},
  {0x0E, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
};

void load(int type, byte b)
{
  if (type != CMD && type != WRITE)
    return;

  digitalWrite(RS, type);
  digitalWrite(EN, HIGH);

  digitalWrite(D0, b & 1);
  digitalWrite(D1, b & 2);
  digitalWrite(D2, b & 4);
  digitalWrite(D3, b & 8);
  digitalWrite(D4, b & 16);
  digitalWrite(D5, b & 32);
  digitalWrite(D6, b & 64);
  digitalWrite(D7, b & 128);

  delay(2);
  digitalWrite(EN, LOW);
  delay(2);
}

void write_custom(int col)
{ 
  byte adds[] = {0x40, 0x48, 0x50, 0x58, 0x60, 0x68, 0x70, 0x78};
  int k = 6;
  
  for (int i = 0; i < 2; i++)
  {
    load(CMD, adds[k+i]);
  	for (int j = 0; j < 8; j++)
      load(WRITE, point[i][j]);
  }
  
  for (int i = 0; i < k; i++)
  {
    load(CMD, adds[i]);
    for (int j = 0; j < 8; j++)
      load(WRITE, pacman_open[i][j]);
  }

  clear();
  load(CMD, ROW_1+col);
  load(WRITE, 0);
  load(WRITE, 1);
  load(WRITE, 2);

  load(WRITE, 6);

  load(CMD, ROW_2+col);
  load(WRITE, 3);
  load(WRITE, 4);
  load(WRITE, 5);
  
  load(WRITE, 7);


  delay(150);
  
  for (int i = 0; i < k; i++)
  {
    load(CMD, adds[i]);
    for (int j = 0; j < 8; j++)
    {
      load(WRITE, pacman_close[i][j]);
    }
  }
  
  clear();
  load(CMD, ROW_1+col);
  load(WRITE, 0);
  load(WRITE, 1);
  load(WRITE, 2);

  load(CMD, ROW_2+col);
  load(WRITE, 3);
  load(WRITE, 4);
  load(WRITE, 5);

  load(CMD, ROW_1+col); 
  
  delay(100);
}

void clear()
{
  load(CMD, CLEAR);
}


void lcd_init()
{
  load(CMD, 0x38);
  delay(5);
  load(CMD, 0x38);
  delay(1);
  load(CMD, 0x38);
  load(CMD, 0x06);
  load(CMD, 0x0C);
  load(CMD, 0x01);
  delay(5);
}

void setup()
{
  pinMode(D7, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D0, OUTPUT);
  pinMode(RS, OUTPUT);
  pinMode(EN, OUTPUT);

  lcd_init();
  clear();
}

void loop()
{
  for (int i = 0; i < 16; i++)
  	write_custom(i);
}