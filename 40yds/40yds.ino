#include "Ultrasonic.h" //INCLUSÃO DA BIBLIOTECA NECESSÁRIA PARA FUNCIONAMENTO DO CÓDIGO

const int echoPin = 7; //PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO(RECEBE)
const int trigPin = 6; //PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG(ENVIA)
int teste=0;
int contagem=0;
int inicio=0;
int distancia=300;
float tempoInicial=0;
float tempoFinal=0;
float resultado=0;
int led1=3;
int led2=4;
int led3=5;

Ultrasonic ultrasonic(trigPin,echoPin); //INICIALIZANDO OS PINOS DO ARDUINO

int dist; //VARIÁVEL DO TIPO INTEIRO
String result; //VARIÁVEL DO TIPO STRING

void setup(){
  
  pinMode(led1, OUTPUT);
  digitalWrite(led1, LOW);
  pinMode(led2, OUTPUT);
  digitalWrite(led2, LOW);
  pinMode(led3, OUTPUT);
  digitalWrite(led3, LOW);
  
  pinMode(echoPin, INPUT); //DEFINE O PINO COMO ENTRADA (RECEBE)
  pinMode(trigPin, OUTPUT); //DEFINE O PINO COMO SAIDA (ENVIA)
  Serial.begin(9600); //INICIALIZA A PORTA SERIAL
  }
void loop(){
  
   // FAZ A CHAMADA DO MÉTODO "hcsr04()"
  //Serial.print("Distancia "); //IMPRIME O TEXTO NO MONITOR SERIAL
  //Serial.print(result); ////IMPRIME NO MONITOR SERIAL A DISTÂNCIA MEDIDA
  //Serial.println("cm"); //IMPRIME O TEXTO NO MONITOR SERIAL

  
  while(teste<10){
    Serial.println("Iniciando...");
    hcsr04();
    distancia=result.toInt();
    teste++;
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    delay(500);
  }
  while(teste==10){
    
    while(inicio==0){
      digitalWrite(led3, LOW);
      hcsr04();
      distancia=result.toInt();
      if(distancia<30){
        Serial.println("Alinhado");
        digitalWrite(led1, LOW);
        digitalWrite(led2, HIGH);
        
        contagem++; 
      }else{
        Serial.println("Alinhar para iniciar");
        digitalWrite(led1, HIGH);
        digitalWrite(led2, LOW);
        contagem=0;
      }
      if(contagem>10){
        inicio=1;
      }
    delay(200);  
    break;  
    }
    while(inicio==1){
      hcsr04();
      distancia=result.toInt();
      if(distancia<30){
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, HIGH);
        Serial.println("Pronto");
      }
      if(distancia>100){
        digitalWrite(led3, LOW);
        Serial.println("Start!!");
        tempoInicial=millis();
        inicio=2;    
      }
      break;
    }
    while(inicio==2){
      tempoFinal=millis();
      resultado=(tempoFinal-tempoInicial)/1000;
      Serial.println(resultado,3);
      break;
    }
  }
}
//MÉTODO RESPONSÁVEL POR CALCULAR A DISTÂNCIA
void hcsr04(){
    digitalWrite(trigPin, LOW); //SETA O PINO 6 COM UM PULSO BAIXO "LOW"
    delayMicroseconds(2); //INTERVALO DE 2 MICROSSEGUNDOS
    digitalWrite(trigPin, HIGH); //SETA O PINO 6 COM PULSO ALTO "HIGH"
    delayMicroseconds(10); //INTERVALO DE 10 MICROSSEGUNDOS
    digitalWrite(trigPin, LOW); //SETA O PINO 6 COM PULSO BAIXO "LOW" NOVAMENTE
    //FUNÇÃO RANGING, FAZ A CONVERSÃO DO TEMPO DE
    //RESPOSTA DO ECHO EM CENTIMETROS, E ARMAZENA
    //NA VARIAVEL "distancia"
    dist = (ultrasonic.Ranging(CM)); //VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA
    result = String(dist); //VARIÁVEL GLOBAL DO TIPO STRING RECEBE A DISTÂNCIA(CONVERTIDO DE INTEIRO PARA STRING)
    delay(5); //INTERVALO DE 500 MILISSEGUNDOS
 }
