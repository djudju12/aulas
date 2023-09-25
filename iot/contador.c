
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

int LEDS[] = {A_ZERO, B_ZERO, C_ZERO, D_ZERO, E_ZERO, F_ZERO, G_ZERO, A_UM, B_UM, C_UM, D_UM, E_UM, F_UM, G_UM};

void setup() 
{
   for (size_t i = 0; i < 14; i++)
   {
      pinMode(LEDS[i], OUTPUT);
   }
}

void loop() 
{
   int CODIGOS[] = {
// 0          1          2          3          4
   0b1111110, 0b0110000, 0b1101101, 0b1111001, 0b0110011, 
// 5          6          7          8          9
   0b1011011, 0b1011111, 0b1110000, 0b1111111, 0b1111011};
   
   
   for (size_t i = 0; i < 10; i++)
   {
      digitalWrite(A_UM, (CODIGOS[i] >> 6) & 1); 
      digitalWrite(B_UM, (CODIGOS[i] >> 5) & 1); 
      digitalWrite(C_UM, (CODIGOS[i] >> 4) & 1); 
      digitalWrite(D_UM, (CODIGOS[i] >> 3) & 1); 
      digitalWrite(E_UM, (CODIGOS[i] >> 2) & 1); 
      digitalWrite(F_UM, (CODIGOS[i] >> 1) & 1); 
      digitalWrite(G_UM, (CODIGOS[i] >> 0) & 1); 
      
      for (size_t j = 0; j < 10; j++)
      {
         digitalWrite(A_ZERO, (CODIGOS[j] >> 6) & 1); 
         digitalWrite(B_ZERO, (CODIGOS[j] >> 5) & 1); 
         digitalWrite(C_ZERO, (CODIGOS[j] >> 4) & 1); 
         digitalWrite(D_ZERO, (CODIGOS[j] >> 3) & 1); 
         digitalWrite(E_ZERO, (CODIGOS[j] >> 2) & 1); 
         digitalWrite(F_ZERO, (CODIGOS[j] >> 1) & 1); 
         digitalWrite(G_ZERO, (CODIGOS[j] >> 0) & 1); 
	     delay(1000);
      }
   }
}

