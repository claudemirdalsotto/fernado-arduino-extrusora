//Programa : Medidor de energia elétrica com Arduino e SCT-013
//https://www.filipeflop.com/blog/medidor-de-energia-eletrica-com-arduino/
 
//Carrega as bibliotecas
#include "EmonLib.h" 

EnergyMonitor emon1;
 
//Tensao da rede eletrica
int rede = 220.0;
 
//Pino do sensor SCT
int pino_sct = 1;

 
void setup() 
{

  Serial.begin(9600);  
  //Pino, calibracao - Cur Const= Ratio/BurdenR. 1800/62 = 29. 
  emon1.current(pino_sct, 29);
} 
  
void loop() 
{

   //Calcula a corrente  
  double Irms = emon1.calcIrms(1480);
  //Mostra o valor da corrente
  Serial.print("Corrente : ");
  Serial.print(Irms) ; // Irms 
  Serial.print("\n");
   
  //saida PWM 0 a 5V pino 9
  
  delay(1000);
}
