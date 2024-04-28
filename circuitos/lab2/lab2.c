#define UNI 5
#define DEZ 6

#define A  7
#define B  8
#define C  9
#define D 10
#define E 11
#define F 12
#define G 13

#define APAGADO 10

//Decodificacao Display em Matriz
const byte tabelaSeteSeg[11][7] = {
    //A B C D E F G
    { 1,1,1,1,1,1,0 }, // 0
    { 0,1,1,0,0,0,0 }, // 1
    { 1,1,0,1,1,0,1 }, // 2
    { 1,1,1,1,0,0,1 }, // 3
    { 0,1,1,0,0,1,1 }, // 4
    { 1,0,1,1,0,1,1 }, // 5
    { 1,0,1,1,1,1,1 }, // 6
    { 1,1,1,0,0,0,0 }, // 7
    { 1,1,1,1,1,1,1 }, // 8
    { 1,1,1,1,0,1,1 }, // 9
    { 0,0,0,0,0,0,0 }  //Apagado
};

void decodifica(byte valor) {
    for(byte x = 0, pino = A; x < 7; x++, pino++) {
        digitalWrite(pino, tabelaSeteSeg[valor][x]);
    }
}

void setup() {
    pinMode(A, OUTPUT);
    pinMode(B, OUTPUT);
    pinMode(C, OUTPUT);
    pinMode(D, OUTPUT);
    pinMode(E, OUTPUT);
    pinMode(F, OUTPUT);
    pinMode(G, OUTPUT);
    pinMode(DEZ, OUTPUT);
    pinMode(UNI, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    int p = analogRead(A0);
    int valor = (p*100.0)/1024.0;
    int dezena = valor/10;
    int unidade = valor%10;

    Serial.print("Potenciometro: ");
    Serial.print(p);
    Serial.print('\n');
    Serial.print("Valor 0-99: ");
    Serial.print(valor);
    Serial.print('\n');
    Serial.print("---\n");

    digitalWrite(UNI, LOW);
    digitalWrite(DEZ, HIGH);
    decodifica(dezena);
    delay(50);

    digitalWrite(DEZ, LOW);
    digitalWrite(UNI, HIGH);
    decodifica(unidade);
    delay(50);
}

