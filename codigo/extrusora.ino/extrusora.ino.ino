//Programa : Medidor de energia elétrica com Arduino e SCT-013
//https://www.filipeflop.com/blog/medidor-de-energia-eletrica-com-arduino/
 
//Carrega as bibliotecas
#include <EmonLib.h> 
#include <ModbusRtu.h> // biblioteca ModbusRtu para comunicação Modbus

//---------configuração modbus-----------//
#define ID   3 // identificador do escravo Modbus
Modbus slave(ID, Serial, 12); // objeto Modbus escravo
int8_t state = 0; // variável para armazenar o estado da comunicação Modbus
unsigned long tempus; // variável para temporização
uint16_t au16data[9]; // vetor para armazenar os dados Modbus

//----------parte do sensor de correte SCT-013/20A-----//
EnergyMonitor emon1; 
//Tensao da rede eletrica
int rede = 220.0;
//Pino do sensor SCT
int pino_sct = 1;
int current = 0;

 
void setup() 
{
  //---------parte do modbusRTU----------//
configuracionIO(); // configura as entradas e saídas do Arduino 
 slave.begin(9600); // inicia a comunicação Modbus
  tempus = millis() + 100; // configura o tempo para atualização do LED do Arduino
  digitalWrite(13, HIGH ); // acende o LED do Arduino
  pinMode(12, OUTPUT); // define o pino 2 como saída para controlar o driver RS485 pino RE/DE
  digitalWrite(12, LOW); // coloca o pino 2 em nível baixo (modo recepção)
  Serial.begin(9600); // inicia a comunicação serial
   //-------parte do sensor de corrente------// 
  //Pino, calibracao - Cur Const= Ratio/BurdenR. 1800/62 = 29. 
  emon1.current(pino_sct, 29);
} 
  
void loop() 
{
  
  //---------------parte do modbusRTU-----------//
  state = slave.poll( au16data, 9 ); // lê os dados Modbus e armazena no vetor au16data

  if (state > 4) { 
    tempus = millis() + 50; // configura o tempo para atualização do LED do Arduino
    digitalWrite(13, HIGH); // acende o LED do Arduino
  }
  if (millis() > tempus) digitalWrite(13, LOW ); // apaga o LED do Arduino
    
  MapeoIOmodbus(); // atualiza as entradas e saídas do Arduino de acordo com os dados Modbus
 // Corrente(); // lê a corrente medida pelo sensor SCT-013 e atualiza o valor no vetor au16data
}
void configuracionIO() {
 /* pinMode(3, OUTPUT); // define o pino 3 como saída
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, INPUT); // define o pino 6 como entrada
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);

  digitalWrite(3, LOW ); // coloca os pinos 3 a 5 em nível baixo
  digitalWrite(4, LOW );
  digitalWrite(5, LOW );
  
  analogWrite(10, 0 ); // configura o valor PWM do pino 10 em 0%
  analogWrite(11, 0 ); // configura o valor PWM do pino 11 em 0% 
  */
}
/*void Corrente(){

  //------------------parte do sensor de corrente------------//
   //Calcula a corrente  
  double Irms = emon1.calcIrms(1480);
  //int valor_inteiro = (int)Irms;
  int Irms_int = (int) round(Irms);
  //Mostra o valor da corrente
  Serial.print("Corrente : ");
  //Serial.print(Irms) ; // Irms 
  //Serial.print(valor_inteiro) ; // Irms
  Serial.print(Irms_int) ; // Irms
  Serial.print("\n");
  
//atualiza o valor da corrente no vetor au16data
  //au16data[0] = (uint16_t)Irms; // converte o valor da corrente para inteiro sem sinal e atualiza no vetor au16data
 

}*/
void MapeoIOmodbus() {

/*
  // saídas digitais -> au16data[0]
  //Lê os bits da variável zero e os coloca nas saídas digitais
  digitalWrite( 3, bitRead( au16data[0], 0 )); // lê o bit 0 da primeira variável do vetor  au16data[0] e coloca no pino 3 do Arduino
  digitalWrite( 4, bitRead( au16data[0], 2 ));
  digitalWrite( 5, bitRead( au16data[0], 3 ));
  //Serial.println("saida digital");
 // Serial.println(au16data[0]);
  
  // entradas digitais -> au16data[1]
   //Lê as entradas digitais e as armazena em bits da primeira variável do vetor
   // (o mesmo que fazer uma máscara)
  bitWrite( au16data[1], 0, digitalRead( 6 )); // lê o pino 6 do Arduino e coloca no bit 0 da primeira variável do vetor  au16data[0] 
  bitWrite( au16data[1], 1, digitalRead( 7 ));
  bitWrite( au16data[1], 2, digitalRead( 8 ));
  bitWrite( au16data[1], 3, digitalRead( 9 ));
  //Serial.println("entrada digital");
  //Serial.println(au16data[1]);

// Muda o valor do PWM
  analogWrite( 10, au16data[2] ); // O valor de au16data[2] é escrito na saída PWM do pino 10 do Arduino. (sendo 0=0% e 255=100%
  analogWrite( 11, au16data[3] );
  //Serial.println(au16data[3]);
  */

   //------------------parte do sensor de corrente------------//
//double Irms = emon1.calcIrms(1480);
current = 1;  // Valor de corrente medido em A
Serial.println(current);

  // Lê as entradas analógicas (ADC)
  //au16data[4] = analogRead( 0 ); //O valor analógico lido no pino A0 é armazenado em au16data[4]. (sendo 0=0v e 1023=5v)
  au16data[0] = 10;
  au16data[1] = 20;
  au16data[2] = 30;
  au16data[3] = 40;
  au16data[4] = 50;
  au16data[5] = 60;
  au16data[6] = 70;
  au16data[7] = 80;
  //Serial.println(au16data[5]);
}
