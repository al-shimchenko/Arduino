#include <iarduino_RTC.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);
iarduino_RTC watch(RTC_DS1302, 8, 6, 7);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  watch.begin();
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(12, OUTPUT);
}

int alarm_H, alarm_M;
int left_alarm_H, left_alarm_M;
int total_time_M, total_alarm_M, left_total_M;

void loop() {
  printTime();
  setTime();
  printAlarm();
  setAlarm();
  alarmControl();
  light();
  delay(100);
}

void printTime()
{
  lcd.setCursor(7,0);
  lcd.print(watch.gettime("H:i"));
}

void setTime()
{
  if (digitalRead(A0) == 0) watch.settime(-1, (watch.minutes+1) - ((watch.minutes+1) / 60)*60);
  if (digitalRead(A1) == 0) watch.settime(-1, -1, (watch.Hours+1) - ((watch.Hours+1) / 24)*24);
}

void printAlarm()
{
  lcd.setCursor(0,2);
  lcd.print("set");
  lcd.setCursor(0, 3);
  if (alarm_H < 10) lcd.print(0);
  lcd.print(alarm_H);
  lcd.print(':');
  if (alarm_M < 10) lcd.print(0);
  lcd.print(alarm_M);
  
  lcd.setCursor(16, 2);
  lcd.print("left");
  total_time_M = watch.Hours * 60 + watch.minutes;
  lcd.setCursor(15, 3);
  //lcd.print(total_time_M);
  total_alarm_M = alarm_H * 60 + alarm_M;
  //lcd.print(total_alarm_M);
  left_total_M = total_alarm_M - total_time_M;
  if (left_total_M < 0)
  {
    left_total_M = total_alarm_M + 24 * 60 - total_time_M;
  }
  //lcd.print(left_total_M);
  left_alarm_H = left_total_M / 60;
  left_alarm_M = left_total_M - left_alarm_H * 60;
  if (left_alarm_H < 10) lcd.print(0);
  lcd.print(left_alarm_H);
  lcd.print(':');
  if (left_alarm_M < 10) lcd.print(0);
  lcd.print(left_alarm_M);
}

void setAlarm()
{
  if (digitalRead(A2) == 0)
  {
    alarm_M = alarm_M + 1;
    if (alarm_M > 59) alarm_M = 0;
    delay(200);
  }
  if (digitalRead(A3) == 0)
  {
    alarm_H = alarm_H + 1;
    if (alarm_H > 23) alarm_H = 0;
    delay(200);
  }
}

void alarmControl()
{
  if ((watch.Hours == alarm_H) and (watch.minutes == alarm_M))
  {
    //tone(12,255);
    music();
  }
  else
  {
    noTone(12);
  }
}

void light()
{
  if (watch.Hours >= 22 or watch.Hours < 8)
  {
    lcd.setBacklight(false);
  }
  else
  {
    lcd.setBacklight(true);
  }
}

void music() {
tone(12, 700, 300);
delay(600);
tone(12, 700, 300);
delay(600);
tone(12, 780, 150);
delay(300);
tone(12, 700, 150);
delay(300);
tone(12, 625, 450);
delay(600);
tone(12, 590, 150);
delay(300);
tone(12, 520, 150);
delay(300);
tone(12, 460, 450);
delay(600);
tone(12, 350, 450);
delay(600);
delay(600);
tone(12, 350, 450);
delay(600);
tone(12, 460, 450);
delay(600);
tone(12, 520, 150);
delay(300);
tone(12, 590, 150);
delay(300);
tone(12, 625, 450);
delay(600);
tone(12, 590, 150);
delay(300);
tone(12, 520, 150);
delay(300);
tone(12, 700, 1350);
delay(1800);
tone(12, 700, 300);
delay(600);
tone(12, 700, 300);
delay(600);
tone(12, 780, 150);
delay(300);
tone(12, 700, 150);
delay(300);
tone(12, 625, 450);
delay(600);
tone(12, 590, 150);
delay(300);
tone(12, 520, 150);
delay(300);
tone(12, 460, 450);
delay(600);
tone(12, 350, 450);
delay(600);
delay(600);
tone(12, 350, 450);
delay(600);
tone(12, 625, 450);
delay(600);
tone(12, 590, 150);
delay(300);
tone(12, 520, 150);
delay(300);
tone(12, 700, 450);
delay(600);
tone(12, 590, 150);
delay(300);
tone(12, 520, 150);
delay(300);
tone(12, 460, 1350);
delay(5000);
}
