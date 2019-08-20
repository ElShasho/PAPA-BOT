#include "BluetoothSerial.h"
#include <Separador.h>
#include <Servo.h>

Servo Garra;
BluetoothSerial ESP_BT;
Separador s;

TaskHandle_t Task2,Task3,Task4;


int retardo=5;          // Tiempo de retardo en milisegundos (Velocidad del Motor)
int retardo1 = 2;
int dato_rx;            // valor recibido en grados
int numero_pasos = 0;   // Valor en grados donde se encuentra el motor
int dato_rx2;            // valor recibido en grados
int numero_pasos2 = 0;   // Valor en grados donde se encuentra el motor
int dato_rx3;            // valor recibido en grados
int numero_pasos3 = 0;   // Valor en grados donde se encuentra el motor
int AG = 90;

String AGS;
String AM1;
String AM2;
String AM3;
String leeCadena;       // Almacena la cadena de datos recibida

void paso_der(){         // Pasos a la derecha
  digitalWrite(23, HIGH); //Direccion 
 
 digitalWrite(22, HIGH);
 delay(retardo1); 
 digitalWrite(22, LOW);  
 delay(retardo1);
}

void paso_izq() {        // Pasos a la izquierda
 digitalWrite(23, LOW); //Direccion
 
 digitalWrite(22, HIGH);
 delay(retardo1); 
 digitalWrite(22, LOW);  
 delay(retardo1); 
}
        
void apagado() {         // Apagado del Motor
 digitalWrite(22, LOW); 

 }
 void paso_der2(){         // Pasos a la derecha
  digitalWrite(15, LOW); //Direccion 
 
 digitalWrite(4, HIGH);
 delay(retardo1); 
 digitalWrite(4, LOW);  
 delay(retardo1);
}

void paso_izq2() {        // Pasos a la izquierda
 digitalWrite(15, HIGH); //Direccion
 
 digitalWrite(4, HIGH);
 delay(retardo1); 
 digitalWrite(4, LOW);  
 delay(retardo1); 
}
        
void apagado2() {         // Apagado del Motor
 digitalWrite(4, LOW); 

 }
void paso_der3(){         // Pasos a la derecha
  digitalWrite(18, LOW); //Direccion 
 
 digitalWrite(5, HIGH);
 delay(retardo1); 
 digitalWrite(5, LOW);  
 delay(retardo1);
}

void paso_izq3() {        // Pasos a la izquierda
 digitalWrite(18, HIGH); //Direccion
 
 digitalWrite(5, HIGH);
 delay(retardo1); 
 digitalWrite(5, LOW);  
 delay(retardo1); 
}
        
void apagado3() {         // Apagado del Motor
 digitalWrite(5, LOW); 

 }

void loop2(void *parameter){
  for(;;){

      
   while (dato_rx2>numero_pasos2){   // Girohacia la izquierda en grados
       paso_izq2();
       numero_pasos2 = numero_pasos2 + 1;
   }
   while (dato_rx2<numero_pasos2){   // Giro hacia la derecha en grados
        paso_der2();
        numero_pasos2 = numero_pasos2 -1;
   }
     
    
  //leeCadena = "";   // Inicializamos la cadena de caracteres recibidos 
  apagado2();         // Apagado del Motor para que no se caliente
    
     
     vTaskDelay(10); 

  }
 }

  void loop3(void *parameter){
  for(;;){

      
   while (dato_rx3>numero_pasos3){   // Girohacia la izquierda en grados
       paso_izq3();
       numero_pasos3 = numero_pasos3 + 1;
   }
   while (dato_rx3<numero_pasos3){   // Giro hacia la derecha en grados
        paso_der3();
        numero_pasos3 = numero_pasos3 -1;
   }
     
    
  //leeCadena = "";   // Inicializamos la cadena de caracteres recibidos 
  apagado3();         // Apagado del Motor para que no se caliente
    
     
     vTaskDelay(10); 

  }
 }

   void loop4(void *parameter){
  for(;;){

    Garra.write(AG);

     vTaskDelay(10); 

  }
 }
void setup() {
Serial.begin(9600);
Garra.attach(14);

  xTaskCreatePinnedToCore(
    loop2,
    "Task_2",
    1000,
    NULL,
    1,
    &Task2,
    0);

  xTaskCreatePinnedToCore(
    loop3,
    "Task_3",
    1000,
    NULL,
    1,
    &Task3,
    0);

      xTaskCreatePinnedToCore(
    loop4,
    "Task_4",
    1000,
    NULL,
    1,
    &Task4,
    0);

   pinMode(22, OUTPUT);    // Pin 22 PASOS BASE
   pinMode(23, OUTPUT);    // Pin 23 DIRECCION BASE
   pinMode(4,OUTPUT);      // pin 4 PASOS 2do MOTOR
   pinMode(15,OUTPUT);     // pin 15 DIRECCION 2do MOTOR
   pinMode(5,OUTPUT);      // pin 5 PASOS 3er MOTOR
   pinMode(18,OUTPUT);     // pin 18 DIRECCION 3er MOTOR

   ESP_BT.begin("ESP32_LED_Control");
  
}

void loop() {
  if(Serial.available()) {    // Leer el valor enviado por el Puerto serial
    
    String c  = Serial.readString();     // Lee los caracteres
       leeCadena = c;
     }  
  if (leeCadena.length()>0){       

         AM1 = s.separa(leeCadena, ',', 0);
         AM2 = s.separa(leeCadena, ',', 1);  
         AM3 = s.separa(leeCadena, ',', 2);
         AGS = s.separa(leeCadena, ',', 3);
         
         Serial.print("M1 = ");
         Serial.println(AM1);
         Serial.print("M2 = ");
         Serial.println(AM2);
         Serial.print("M3 = ");
         Serial.println(AM3);
         
        dato_rx = AM1.toInt();   // Convierte Cadena de caracteres a Enteros
        dato_rx2 = AM2.toInt();
        dato_rx3 = AM3.toInt();
        AG = AGS.toInt();
        
         //Serial.print(c);         // Envia valor en Grados 
        delay(retardo);
        dato_rx = (dato_rx*66.6); // Ajuste de 512 vueltas a los 360 grados
        dato_rx2 = (dato_rx2 * 66.6);
        dato_rx3 = (dato_rx3 * 44.4);
        
  }  

   while (dato_rx>numero_pasos){   // Girohacia la izquierda en grados
       paso_izq();
       numero_pasos = numero_pasos + 1;
   }
   while (dato_rx<numero_pasos){   // Giro hacia la derecha en grados
        paso_der();
        numero_pasos = numero_pasos -1;
   }
  leeCadena = "";   // Inicializamos la cadena de caracteres recibidos 
  apagado();         // Apagado del Motor para que no se caliente  
  

}
