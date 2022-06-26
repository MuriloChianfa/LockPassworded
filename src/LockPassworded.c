#include <LiquidCrystal.h>
#include <Servo.h>
#include <Wire.h>

#define TAMANHO_DA_SENHA 7

LiquidCrystal lcd(12, 10, 5, 4, 3, 2);

#define SERVO_MOTOR 6
Servo servoMotor;

char senha[TAMANHO_DA_SENHA] = {
    '1', '5', '7',
    '6', '9', '3', '\0'
};

char senhaDigitada[TAMANHO_DA_SENHA];

int estadoFechadura = 0;

void limparSenha()
{
    for (unsigned int i = 0; i < TAMANHO_DA_SENHA; i++)
    {
        if (i == (TAMANHO_DA_SENHA - 1))
        {
            break;
        }
      
        senhaDigitada[i] = NULL;
    }
}

void swapState(int *var)
{
    if (*var == 0)
    {
        *var = 1;
        return;
    }
    
    *var = 0;
}

void verificaSenha()
{
    for (unsigned int i = 0; i < TAMANHO_DA_SENHA; i++)
    {
        if (i == (TAMANHO_DA_SENHA - 1))
        {
            break;
        }
      
        if (NULL == senhaDigitada[i])
        {
            limparSenha();
            return;
        }
      
        if (senhaDigitada[i] != senha[i])
        {
            limparSenha();
            return;
        }
    }
  
    limparSenha();
    swapState(&estadoFechadura);
    return;
}

void adicionarTecla(char tecla)
{
    if (tecla == 'D')
    {
        limparSenha();
        return;
    }
  
    if (tecla == 'A')
    {
        verificaSenha();
        return;
    }
  
    for (unsigned int i = 0; i < TAMANHO_DA_SENHA; i++)
    {
        if (i == (TAMANHO_DA_SENHA - 1))
        {
            break;
        }
      
        if (NULL != senhaDigitada[i])
        {
            continue;
        }
      
        senhaDigitada[i] = tecla;
        return;
    }
}

void mostraFechadura()
{
    lcd.setCursor(0, 0);
    lcd.print("Senha: ");
    lcd.print(senhaDigitada);
  
    lcd.setCursor(0, 1);
    lcd.print("Porta: ");
  
    if (0 == estadoFechadura)
    {
        servoMotor.write(0);
        lcd.print("Fechada");
        return;
    }
  
    servoMotor.write(90);
    lcd.print("Aberta");
}

void receiveEvent(int bytes)
{
    adicionarTecla(Wire.read());
}

void setup()
{
    Serial.begin(9600);
  
    lcd.begin(16, 2);
  
    servoMotor.attach(SERVO_MOTOR, 500, 2500);
  
    Wire.begin(9);
  
    Serial.println("Pressione \"A\" para entrar com a senha");
    Serial.println("Pressione \"D\" para limpar a senha");
    Serial.println("Senha correta: 157693");
}

void loop()
{
    lcd.clear();
    Wire.onReceive(receiveEvent);
    mostraFechadura();
    
    delay(600);
}

