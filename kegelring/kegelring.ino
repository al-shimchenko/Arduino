#include <Ultrasonic.h>// подключаем библиотеку ультрасоник
// Trig - 11, Echo - 12

// настраеваем пины мотора и датчика. их нужно настроить только здесь один раз, дальше все функции движения заполнятся автоматически
#define M_Left_Forward 5
#define M_Left_Backward 4
#define M_Right_Forward 3
#define M_Right_Backward 2
#define M_Left_Speed 6
#define M_Right_Speed 7
#define S_line1 8
#define S_line2 9

Ultrasonic ultrasonic(11, 12);


void setup()
{
  pinMode(M_Left_Forward, OUTPUT);
  pinMode(M_Right_Forward, OUTPUT);
  pinMode(M_Left_Backward, OUTPUT);
  pinMode(M_Right_Backward, OUTPUT);
  pinMode(M_Left_Speed, OUTPUT);
  pinMode(M_Right_Speed, OUTPUT);
  pinMode(S_line1, INPUT);
  pinMode(S_line2, INPUT);
  //pinMode(9, INPUT);
  Serial.begin(9600);
}

void loop()
{
  // код для проверки работы датчиков
  /*Serial.print("Sensor1: ");
  Serial.print(digitalRead(S_line1));
  Serial.print(" Sensor2: ");
  Serial.println(digitalRead(S_line2));
  */ 
  
  /*
   Serial.print("distance: ")
   Serial.println(ultrasonic.Read())
   */
  scan_area(35); // здесь можно настроить расстояние до срабатывания датчика
  push_out();
}
