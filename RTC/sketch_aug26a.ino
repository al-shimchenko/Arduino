#include <iarduino_RTC.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);
iarduino_RTC watch(RTC_DS1302, 8, 6, 7);

bool b, prb;
long t, t1;

int param_set;
int s, i, H, d, w, m, Y;

int alarm_param_set;
int alarm_H, alarm_M;
bool alarm_ON, alarm, led;

bool short_press, long_press;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  watch.begin();
  pinMode(A0, INPUT_PULLUP);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  param_set = 1;
}

void loop() {
  btn_state();
  set_time();

  if (param_set == 0 and alarm_param_set == 0)
  {
    if (short_press)
    {
      if ((millis() - t1) < 1000)
      {
        if (alarm_ON) alarm_ON = false;
        else alarm_ON = true;
      }
      t1 = millis();
    }
  }

  if (alarm_ON and long_press) alarm_param_set++;
  if (alarm_param_set > 2) alarm_param_set = 0;

  if (short_press and alarm_param_set > 0)
  {
    switch(alarm_param_set){
      case 1:
        alarm_M += 1;
        if (alarm_M > 59) alarm_M = 0;
        break;
      case 2:
        alarm_H += 1;
        if (alarm_H > 23) alarm_H = 0;
        break;
    }
  }

  alarm = (watch.Hours == alarm_H) and (watch.minutes == alarm_M) and alarm_ON and (alarm_param_set == 0);

  if (alarm) 
  {
    tone(12, 255);
    led = (millis() % 2000) < 1000;
    digitalWrite(13, !led);
    lcd.setBacklight(led);
  }
  else
  {
    noTone(12);
    digitalWrite(13, LOW);
    lcd.setBacklight(true);
  }

  printAlarm(alarm_ON, alarm_param_set);
  
  printTime();
  delay(10);
}

void printTime()
{
  lcd.setCursor(6,0);
  lcd.print(watch.gettime("H:i:s"));
  lcd.setCursor(4,1);
  lcd.print(watch.gettime("d M Y"));
  lcd.setCursor(8,2);
  lcd.print(watch.gettime("D"));
}

void btn_state()
{
  b = digitalRead(A0);
  long_press = false;
  short_press = false;
  if (b == 0) {
    if (prb == 1) t = millis();
    if ((millis() - t) > 2000) {t = millis(); long_press = true;}
  }
  if (b == 1 and prb == 0) {
    if ((millis() - t) < 2000) short_press = true;
  }
  prb = b;
}

void set_time()
{
  if (long_press and param_set != 0) param_set = param_set + 1;
  if (param_set > 7) param_set = 0;
  watch.blinktime(param_set);

  s = watch.seconds;
  i = watch.minutes;
  H = watch.Hours;
  d = watch.day;
  w = watch.weekday;
  m = watch.month;
  Y = watch.year;
  if (short_press and param_set > 0){
    switch (param_set) {
    case 1:
      s += 1;
      if (s > 59) s = 0;
      break;
    case 2:
      i += 1;
      if (i > 59) i = 0;
      break;
    case 3:
      H += 1;
      if (H > 23) H = 0;
      break;
    case 4:
      d += 1;
      if (d > 31) d = 1;
      break;
    case 5:
      m += 1;
      if (m > 12) m = 1;
      break;
    case 6:
      Y += 1;
      if (Y > 30) Y = 21;
      break;
    case 7:
      w += 1;
      if (w > 6) w = 0;
      break;
  }
  watch.settime(s, i, H, d, m, Y, w);
  }
}

void printAlarm(bool state, int param)
{
  char alarm_time[] = "00:00";
  if (state)
  {
    alarm_time[0] = alarm_H / 10 + 48;
    alarm_time[1] = alarm_H % 10 + 48;
    alarm_time[3] = alarm_M / 10 + 48;
    alarm_time[4] = alarm_M % 10 + 48;
  }
  else
  {
    for(int i = 0; alarm_time[i] != 0; i++) alarm_time[i] = ' ';
  }
  if (param == 1)
  {
    if ((millis() % 1000) < 500)
    {
      alarm_time[3] = ' ';
      alarm_time[4] = ' ';
    }
  }
  if (param == 2)
  {
    if ((millis() % 1000) < 500)
    {
      alarm_time[0] = ' ';
      alarm_time[1] = ' ';
    }
  }
  lcd.setCursor(15, 3);
  lcd.print(alarm_time);
}
