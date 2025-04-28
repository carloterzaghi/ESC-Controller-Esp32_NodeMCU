/**
 * Código para ESC Sensorizado adaptado para ESP32
 * Autor: Carlo (adaptado do código original)
 * Data: 01/04/2025
 * 
 * Descrição:
 * - Controla um motor BLDC usando sensores de efeito Hall.
 * - Utiliza MOSFETs para chaveamento.
 * - Utiliza timers do ESP32 para controle de tempo.
 */

 #include <Arduino.h>

 // Definição dos pinos dos sensores Hall
 #define HALL1 32
 #define HALL2 33
 #define HALL3 25
 
 // Definição dos pinos de saída para os MOSFETs
 #define MOSFET1 26
 #define MOSFET2 27
 #define MOSFET3 14
 #define MOSFET4 12
 #define MOSFET5 13
 #define MOSFET6 15
 
 volatile int stepState = 0; // Estado do motor
 volatile bool hall1State, hall2State, hall3State;
 
 hw_timer_t *timer = NULL; // Timer de hardware para controle do motor
 
 // Leitura dos sensores Hall e atualização do estado
 void IRAM_ATTR hallInterrupt() {
     hall1State = digitalRead(HALL1);
     hall2State = digitalRead(HALL2);
     hall3State = digitalRead(HALL3);
     nextStep();
 }
 
 // Configuração do timer para controle do motor
 void IRAM_ATTR onTimer() {
     switch (stepState) {
         case 1:
             digitalWrite(MOSFET1, HIGH);
             digitalWrite(MOSFET2, LOW);
             break;
         case 2:
             digitalWrite(MOSFET2, HIGH);
             digitalWrite(MOSFET3, LOW);
             break;
         case 3:
             digitalWrite(MOSFET3, HIGH);
             digitalWrite(MOSFET4, LOW);
             break;
         case 4:
             digitalWrite(MOSFET4, HIGH);
             digitalWrite(MOSFET5, LOW);
             break;
         case 5:
             digitalWrite(MOSFET5, HIGH);
             digitalWrite(MOSFET6, LOW);
             break;
         case 6:
             digitalWrite(MOSFET6, HIGH);
             digitalWrite(MOSFET1, LOW);
             break;
     }
 }
 
 // Define o próximo passo com base nos sensores Hall
 void nextStep() {
     if (hall1State && !hall2State && hall3State) stepState = 1;
     else if (!hall1State && !hall2State && hall3State) stepState = 2;
     else if (!hall1State && hall2State && hall3State) stepState = 3;
     else if (!hall1State && hall2State && !hall3State) stepState = 4;
     else if (hall1State && hall2State && !hall3State) stepState = 5;
     else if (hall1State && !hall2State && !hall3State) stepState = 6;
 }
 
 void setup() {
     Serial.begin(115200);
 
     // Configuração dos pinos dos sensores Hall
     pinMode(HALL1, INPUT_PULLUP);
     pinMode(HALL2, INPUT_PULLUP);
     pinMode(HALL3, INPUT_PULLUP);
     
     // Configuração dos pinos dos MOSFETs
     pinMode(MOSFET1, OUTPUT);
     pinMode(MOSFET2, OUTPUT);
     pinMode(MOSFET3, OUTPUT);
     pinMode(MOSFET4, OUTPUT);
     pinMode(MOSFET5, OUTPUT);
     pinMode(MOSFET6, OUTPUT);
 
     // Configuração das interrupções para os sensores Hall
     attachInterrupt(digitalPinToInterrupt(HALL1), hallInterrupt, CHANGE);
     attachInterrupt(digitalPinToInterrupt(HALL2), hallInterrupt, CHANGE);
     attachInterrupt(digitalPinToInterrupt(HALL3), hallInterrupt, CHANGE);
 
     // Configuração do timer de hardware do ESP32
     timer = timerBegin(0, 80, true);  // Timer 0, Prescaler 80 (1us por tick)
     timerAttachInterrupt(timer, &onTimer, true);
     timerAlarmWrite(timer, 10000, true);  // Interrupção a cada 10ms
     timerAlarmEnable(timer);
 }
 
 void loop() {
     // O loop principal fica vazio, pois tudo é controlado por interrupções e timers
 }
 