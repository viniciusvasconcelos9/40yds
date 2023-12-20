//Carrega a biblioteca do sensor ultrassonico e LCD
#include <Ultrasonic.h>
#include <LiquidCrystal.h>
 
//Define os pinos para o trigger e echo
#define pino_trigger1 6
#define pino_echo1 7
#define pino_trigger2 8
#define pino_echo2 9
 
//Inicializa o sensor nos pinos definidos acima e inicializa o LCD
Ultrasonic ultrasonic1(pino_trigger1, pino_echo1);
Ultrasonic ultrasonic2(pino_trigger2, pino_echo2); 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  //Serial.println("Lendo dados do sensor...");

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Iniciando..");
  delay(3000);
  //lcd.clear();
}

int teste, contagem;
float sen1, sen2, distancia, tempoInicial, tempo;
int select=0;


void loop (){
    if (select==0){
      yds40();
    }
  
}

void yds40(){

  
      contagem = 0;
      teste=0;
      
      while(teste==0){
         while(contagem<10){ 
            distancia = sensor_1(); 
            if(distancia<50){
              lcd.clear();
              lcd.setCursor(1, 0);
              lcd.print("20/40 yds dash");
              lcd.setCursor(2, 1);
              lcd.print("- Alinhando -");
              //Serial.println("Alinhado");     
              contagem++;
              if (contagem==10){
                lcd.clear();
                lcd.setCursor(1, 0);
                lcd.print("20/40 yds dash");
                lcd.setCursor(3, 1);
                lcd.print("- Pronto -");   
              }
            }else{
              lcd.clear();
              lcd.setCursor(1, 0);
              lcd.print("20/40 yds dash");
              lcd.setCursor(2, 1);
              lcd.print("- Preparar -");
              //Serial.println("Alinhar para iniciar");
              contagem=0;
            }
            delay(300); 
          }
       
        distancia = sensor_1(); 
          
        if (distancia>20){
          lcd.clear();
          lcd.setCursor(1, 0);
          lcd.print("20/40 yds dash");
          lcd.setCursor(3, 1);
          lcd.print("---------");
          //Serial.println("Inicio");
          teste=1;
          tempoInicial=millis();
        }  
     }
     while(teste==1){
        distancia = sensor_2();
        if (distancia<100){
          tempo = millis() - tempoInicial;
          lcd.clear();
          lcd.setCursor(1, 0);
          lcd.print("- Tempo Final -");
          lcd.setCursor(6, 1);
          lcd.print(tempo/1000);
          delay(5000);
          break;
        }
     }
}

float sensor_1()
{
  //Le as informacoes do sensor, em cm e pol
  float cmMsec;
  long microsec = ultrasonic1.timing();
  cmMsec = ultrasonic1.convert(microsec, Ultrasonic::CM);
  return cmMsec;
}

float sensor_2()
{
  //Le as informacoes do sensor, em cm e pol
  float cmMsec;
  long microsec = ultrasonic2.timing();
  cmMsec = ultrasonic2.convert(microsec, Ultrasonic::CM);
  return cmMsec;
}
