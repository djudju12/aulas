
// leds 
int A_ZERO = 6;
int B_ZERO = 5;
int C_ZERO = 4;
int D_ZERO = 3;
int E_ZERO = 2;
int F_ZERO = 1;
int G_ZERO = 0;
int A_UM = 7;
int B_UM = 8;
int C_UM = 9;
int D_UM = 10;
int E_UM = 11;
int F_UM = 12;
int G_UM = 13;
int TMP = A0;

int LEDS[] = {A_ZERO, B_ZERO, C_ZERO, D_ZERO, E_ZERO, F_ZERO, G_ZERO, A_UM, B_UM, C_UM, D_UM, E_UM, F_UM, G_UM};

int CODIGOS[] = {
// 0          1          2          3          4
   0b1111110, 0b0110000, 0b1101101, 0b1111001, 0b0110011, 
// 5          6          7          8          9
   0b1011011, 0b1011111, 0b1110000, 0b1111111, 0b1111011
};
   

void display_num(int num_1, int num_0)
{
  	int k = 6;
	for (size_t i = 0; i < 7; i++)
    {
      digitalWrite(LEDS[i], (CODIGOS[num_0] >> k) & 1);
      k--;
    }
  
  	k = 6;
  	for (size_t j = 7; j < 14; j++)
    {
      digitalWrite(LEDS[j], (CODIGOS[num_1] >> k) & 1);
      k--;
    }
}

void setup() 
{
   for (size_t i = 0; i < 14; i++)
   {
      pinMode(LEDS[i], OUTPUT);
   }
}

void loop() 
{
   unsigned int temp = analogRead(TMP);
   temp -= 100;
   temp /= 2;
   int unidade = temp % 10;
   int dezena = temp / 10;  
   display_num(dezena, unidade);
   delay(250);
}

