# PAPA-BOT
Programacion usada en la creacion del brazo robotico de 3 grados de libertad usando el microcontrolador ESP32 y el IDE de arduino junto con MATLAB

En el codigo viene esta linea "TaskHandle_t Task2,Task3,Task4;" Es utilizada para crear la variable o puntero del ciclo en paralelo

Se crea el loop de la siguiente manera,  void "nombre del loop"(void*parameter)

  void loop3(void *parameter){ //Inicio del loop creado
  for(;;){
   Dentro del loop es necesario tener alguna instruccion que genere un ciclo infinito ya sea un for como en este caso o
   con un While(1)
   
   vTaskDelay(10); 
   
 }
   }//fin del loop
   
   Despues en el Void setup viene:
   
     xTaskCreatePinnedToCore(
    loop3, //nombre del loop
    "Task_3", //Nombre de la variable declarada en la linea TaskHandle_t
    1000,
    NULL,
    1, //Este numero indica la prioridad que tiene el ciclo
    &Task3, //nombre del void con la letra &
    0); //numero del nucle en el quue se desea ejecutar el ciclo
    
    Y con eso se estaria ejecutando un cliclo en paralelo 
    
    ES IMPORTANTE QUE DENTRO DE CADA LOOP PARALELO QUE SE HAGA SE AGREGE EL DELAY DE ESTA MANERA vTaskDelay(10);  PARA EVITAR ERRORES
    O REINICIOS DEL MICROCONTROLADOR INESPERADOS
