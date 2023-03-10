void forward()
{
  digitalWrite(M_Left_Forward, HIGH);
  digitalWrite(M_Right_Forward, HIGH);
  digitalWrite(M_Left_Backward, LOW);
  digitalWrite(M_Right_Backward, LOW);
  analogWrite(M_Left_Speed, 255);
  analogWrite(M_Right_Speed, 255);
}

void backward()
{
  digitalWrite(M_Left_Forward, LOW);
  digitalWrite(M_Right_Forward, LOW);
  digitalWrite(M_Left_Backward, HIGH);
  digitalWrite(M_Right_Backward, HIGH);
  analogWrite(M_Left_Speed, 255);
  analogWrite(M_Right_Speed, 255);
}

void left()
{
  digitalWrite(M_Left_Forward, LOW);
  digitalWrite(M_Right_Forward, HIGH);
  digitalWrite(M_Left_Backward, HIGH);
  digitalWrite(M_Right_Backward, LOW);
  analogWrite(M_Left_Speed, 255);
  analogWrite(M_Right_Speed, 255);
}

void right()
{
  digitalWrite(M_Left_Forward, HIGH);
  digitalWrite(M_Right_Forward, LOW);
  digitalWrite(M_Left_Backward, LOW);
  digitalWrite(M_Right_Backward, HIGH);
  analogWrite(M_Left_Speed, 255);
  analogWrite(M_Right_Speed, 255);
}

void stopm()
{
  digitalWrite(M_Left_Forward, LOW);
  digitalWrite(M_Right_Forward, LOW);
  digitalWrite(M_Left_Backward, LOW);
  digitalWrite(M_Right_Backward, LOW);
  analogWrite(M_Left_Speed, 0);
  analogWrite(M_Right_Speed, 0);
}



int search_pin(int R) //функция поиск кегли (радиус поиска) возвращает значение 1 или 0 
{ 
  int dist = ultrasonic.read(); 
  if ((dist < R) && (dist!=0)) //данным условием избавляемся от ошибки 
  { 
    return(1); 
  } 
  else 
  { 
    return(0); 
  } 
 }


void scan_area(int R) //функция сканирования (радиус поиска) 
{ 
  while(!search_pin(R)) //пока не нашли кеглю вращаемся
  { 
    left(); 
    delay(10);
  } 
  stopm(); 
}


void push_out()//функция выталкивания кеглей 
{ 
  int t0 = millis();
   
  while(digitalRead(S_line1) == 0 && digitalRead(S_line2) == 0) 
  { 
    forward(); 
  } 
  int t1 = millis();
  int dt = t1 - t0;
  stopm();
  backward();
  delay(dt);
  stopm();
}
