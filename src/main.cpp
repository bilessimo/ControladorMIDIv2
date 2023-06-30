#include <Arduino.h>
#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

int pot_ValorAtual = 0;
int pot_ValorAnterior = 0;
int pot_LimiteValor = 1;

int PC_pot_ValorAtual = 0;

void HandleIncomeCC(byte channel, byte number, byte value) {
  if (number == 11)
  {
    if (value > 60)
    {
      digitalWrite(LED_BUILTIN, true);
    } 
    else if (value < 60)
    {
      digitalWrite(LED_BUILTIN, false);
    } 
  }
  
}

void POT1() {
  pot_ValorAtual = map(analogRead(A0), 0, 1023, 0, 126);
  int diferenca = abs(pot_ValorAtual - pot_ValorAnterior);

  if (diferenca > pot_LimiteValor)
  {
    MIDI.sendControlChange(11, pot_ValorAtual, 1);
    pot_ValorAnterior = pot_ValorAtual;
  }  
}

void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT);   

  MIDI.setHandleControlChange(HandleIncomeCC);  
  MIDI.begin(1);
  Serial.begin(115200);
}

void loop() {
  MIDI.read(1);
  POT1();  
}