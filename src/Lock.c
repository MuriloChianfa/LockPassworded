#include <Keypad.h>
#include <Wire.h>

const byte qtdLinhas = 4;
const byte qtdColunas = 4;

char matrizTeclas[qtdLinhas][qtdColunas] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

byte PinosQtdLinhas[qtdLinhas] = { 12, 11, 10, 9 };
byte PinosQtdColunas[qtdColunas] = { 8, 7, 6, 5 };

Keypad teclado = Keypad(
    makeKeymap(matrizTeclas),
    PinosQtdLinhas,
    PinosQtdColunas,
    qtdLinhas,
    qtdColunas
);

void setup()
{
    Serial.begin(9600);

    Wire.begin();
}

void loop()
{
    char tecla = teclado.getKey();
  
    if (tecla)
    {
        Wire.beginTransmission(9);
        Wire.write(tecla);
        Wire.endTransmission();
    }
  
    delay(200);
}

