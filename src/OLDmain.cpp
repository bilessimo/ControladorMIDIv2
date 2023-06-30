/*
#include <Arduino.h>
#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

bool DEBUG_ON = false;

const int N_POTS = 2;
const int POTS_PINOS[N_POTS] = {A0, A1};

int pots_estadoAtual[N_POTS] = {0};
int pots_estadoAnterior_Map[N_POTS] = {0};
int pots_estadoAtual_Map[N_POTS] = {0};
int pots_ControlChange[N_POTS] = {7, 7};

int pots_ajuste = 2;
unsigned long pots_ajuste_Tempo = 10;
unsigned long tempo_Anterior_POTS[N_POTS] = {0};
unsigned long tempo_Atual_POTS[N_POTS] = {0};
unsigned long tempo_Limite = 200;

void setup() {
  //Serial.begin(115200);

  MIDI.begin(MIDI_CHANNEL_OMNI);

  if (DEBUG_ON)
  {
    Serial.println("Ligou");
  }
    
}

void MandaControle(int canal, int controle, int valor) {
  if (DEBUG_ON)
  {
    Serial.begin(115200);
    Serial.print("Canal: ");
    Serial.print(canal);
    Serial.print(" Controle: ");
    Serial.print(controle);
    Serial.print(" Valor: ");
    Serial.print(valor);
    Serial.println();

  } else {
    byte controle_byte = lowByte(controle);
    byte valor_byte = lowByte(valor);
    byte canal_byte = lowByte(canal);
    MIDI.sendControlChange(controle_byte, valor_byte, canal_byte);
  }
  
}

void loop() {

  for (size_t i = 0; i < N_POTS; i++)
  {
    pots_estadoAtual[i] = analogRead(POTS_PINOS[i]);
    pots_estadoAnterior_Map[i] = pots_estadoAtual_Map[i];
    pots_estadoAtual_Map[i] = map(pots_estadoAtual[i], 0, 1023, 0, 127);

    int diferenca = abs(pots_estadoAnterior_Map[i] - pots_estadoAtual_Map[i]);
    
    if (diferenca > pots_ajuste)
    {
      tempo_Anterior_POTS[i] = millis();
    }
    tempo_Atual_POTS[i] = millis() - tempo_Anterior_POTS[i];
    if (tempo_Atual_POTS[i] < tempo_Limite)
    {
      MandaControle(0, pots_ControlChange[i], pots_estadoAtual_Map[i]);
    }    
  }
}*/


