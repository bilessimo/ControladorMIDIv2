#include <Arduino.h>
#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

int pot_ValorAtual = 0;
int pot_ValorAnterior = 0;
int pot_LimiteValor = 1;

int PC_pot_ValorAtual = 60;

void setup() {

  MIDI.begin(MIDI_CHANNEL_OMNI);
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);   
}

void loop() {

  pot_ValorAtual = map(analogRead(A0), 0, 1023, 0, 127);
  int diferenca = abs(pot_ValorAtual - pot_ValorAnterior);

  if (diferenca > pot_LimiteValor)
  {
    MIDI.sendControlChange(11, pot_ValorAtual, 1);
    pot_ValorAnterior = pot_ValorAtual;
  }   
  
}