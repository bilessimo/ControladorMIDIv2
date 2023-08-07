/*
CONTROLADOR MIDI
Cadeia: Arduino Nano -> Hairless -> loopMidi -> Ableton
Potenciômetros: 1
Botões: 1 (Push Button)
LEDs: 2
*/

#include <Arduino.h>
#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

int pot_valor_atual = 0;      // Valor do potenciômetro no frame atual.
int pot_valor_anterior = 0;   // Último valor do potenciômetro que foi aceito.
int pot_valor_limite = 1;     // Valor que o potenciômetro precisa mudar para que o valor seja aceito.
long pot_tempo = 0;           
long pot_tempo_limite = 10;   // Valor mínimo (em milisegundos) para o debouncing do potenciômetro.

bool bot_estado = false;
bool led_estado = false;

// Resolve as mensagens que são recebidas.
// Por enquanto é um placeholder que só acende o led interno do Arduíno quando o valor recebido é maior do que um limite;
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

// Lê um botão físico ligado ao Arduino.
// Por enquanto é um placeholder que só acende um led quando o botão é apertado, para fins de debug.
void BOT1() {
  if (digitalRead(4) != bot_estado)
  {
    led_estado = !led_estado;
  }
  
  if (led_estado)
  {
    digitalWrite(9, HIGH);
  } else {
    digitalWrite(9, LOW);
  }
  
  // TODO: Enviar a mensagem de que o botão foi apertado.
}

// Resolve a leitura do potenciômetro e envia a mensagem de CC.
// TODO: Fazer resolver um array de potenciômetros.
void POT1() {
  pot_valor_atual = map(analogRead(A0), 0, 1023, 0, 127);     // Lê o potenciômetro e mapeia o valor em 7 bits.
  int diferenca = abs(pot_valor_atual - pot_valor_anterior);  // Determina a diferença entre o valor atual e a última leitura válida.

  if (millis() - pot_tempo > pot_tempo_limite)                // Debouncing
  {
    if (diferenca > pot_valor_limite)
    {
      MIDI.sendControlChange(11, pot_valor_atual, 1);         // TODO: Tirar os valores absolutos.
      pot_valor_anterior = pot_valor_atual;
      pot_tempo = millis();
    }
  }
}

void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT);     // Led interno.
  pinMode(9, OUTPUT);               // Led externo.
  pinMode(4, INPUT);                // Potenciômetro.

  MIDI.setHandleControlChange(HandleIncomeCC);  // Define a função que será chamada quando receber uma mensagem CC.
  MIDI.begin(1);                                // ??? Não tenho certeza, mas acho que a ordem em que a comunicação MIDI e a Serial são iniciadas tem influência.
  Serial.begin(115200);
}

void loop() {
  MIDI.read(1);
  POT1();  
  BOT1();
}