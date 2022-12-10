#include <Wire.h>
#include "RTClib.h"

#define RELAY 27
#define BTN 13
#define CLK 11
#define DT 12

RTC_DS3231 rtc;

int menu = 0;
int option = 0;

int hr;
int hour;
int minute;
int second;
int day;
int month;
int year;
int week;

int hour_al1 = 6;
int minute_al1 = 30;
int hr_al1 = 1;
int hour_al2 = 12;
int minute_al2 =0;
int hr_al2 = 0;
int on_time;
int off_time;
int now_time;

int *ptr = NULL;

bool enter = 0;
bool editing = 0;
bool first = 0;


void setup(){
  pinMode(RELAY,OUTPUT);
  pinMode(BTN,INPUT_PULLUP);
  pinMode(CLK,INPUT);
  pinMode(DT,INPUT);

  attachInterrupt(digitalPinToInterrupt(BTN),btn,FALLING);
  attachInterrupt(digitalPinToInterrupt(CLK),twist,CHANGE);

  digitalWrite(RELAY,HIGH);
  
  rtc.begin();
  rp2040.fifo.push(rtc.lostPower());
  if(hr_al1){
    if(hour_al1 != 12){
      hour_al1 = hour_al1 + 12;
    }
  }
  else{
    if(hour_al1 == 12){
      hour_al1 = 0;
    }
  }
  if(hr_al2){
    if(hour_al2 != 12){
      hour_al2 = hour_al2 + 12;
    }
  }
  else{
    if(hour_al2 == 12){
      hour_al2 = 0;
    }
  }
}

void loop(){
  if(menu == 1){
    ptr = &option;
    if(option == 0){
      if(enter){
        menu = 2;
        enter = 0;
        option = 0;
      }
    }
    else if(option == 1){
      if(enter){
        menu = 3;
        enter = 0;
        option = 0;
        first = 1;
      }
    }
    else if(option == 2){
      if(enter){
        menu = 4;
        enter = 0;
        option = 0;
        first = 1;
      }
    }
    else if(option == 3){
      if(enter){
        option = 0;
        enter = 0;
        menu = 0;
      }
    }
    else if(option < 0){
      option = 3;
    }
    else{
      option = 0;
    }
    rp2040.fifo.push(menu);
    rp2040.fifo.push(option);
  }
  else if (menu == 2){
    if(hr < 0){
      hr = 1;
    }

    if(hr > 1){
      hr = 0;
    }
    
    if(hour < 1){
      hour = 12;
    }
    
    if(hour > 12){
      hour = 1;
    }

    if(minute < 0){
      minute = 59;
    }
    
    if(minute > 59){
      minute = 0;
    }

    if(second < 0){
      second = 59;
    }
    
    if(second > 59){
      second = 0;
    }
    
    if(day >31){
      day = 1;
    }

    if(day < 1){
      day = 31;
    }

    if(month >12){
      month = 1;
    }

    if(month < 1){
      month = 12; 
    }

    if(year < 2022){
      year = 2022;
    }

    if(option == 0){
      if(editing){
        ptr = &hour;
        if(enter){
          enter = 0;
          editing = 0;
          ptr = &option;
        }
      }
      else{
        if(enter){
          enter = 0;
          editing = 1;
          ptr = &hour;
        }
      }
    }
    else if(option == 1){
      if(editing){
        ptr = &minute;
        if(enter){
          enter = 0;
          editing = 0;
          ptr = &option;
        }
      }
      else{
        if(enter){
          enter = 0;
          editing = 1;
          ptr = &minute;
        }
      }
    }
    else if(option == 2){
      if(editing){
        ptr = &hr;
        if(enter){
          enter = 0;
          editing = 0;
          ptr = &option;
        }
      }
      else{
        if(enter){
          enter = 0;
          editing = 1;
          ptr = &hr;
        }
      }
    }
    else if(option == 3){
      if(editing){
        ptr = &day;
        if(enter){
          enter = 0;
          editing = 0;
          ptr = &option;
        }
      }
      else{
        if(enter){
          enter = 0;
          editing = 1;
          ptr = &day;
        }
      }
    }
    else if(option == 4){
      if(editing){
        ptr = &month;
        if(enter){
          enter = 0;
          editing = 0;
          ptr = &option;
        }
      }
      else{
        if(enter){
          enter = 0;
          editing = 1;
          ptr = &month;
        }
      }
    }
    else if(option == 5){
      if(editing){
        ptr = &year;
        if(enter){
          enter = 0;
          editing = 0;
          ptr = &option;
        }
      }
      else{
        if(enter){
          enter = 0;
          editing = 1;
          ptr = &year;
        }
      }
    }
    else if(option == 6){
      if(enter){
        enter = 0;
        option = 0;
        menu = 1;
        if(hr){
          if(hour != 12){
            hour = hour + 12;
          }
        }
        else{
          if(hour == 12){
            hour = 0;
          }
        }
        rtc.adjust(DateTime(year, month, day, hour, minute, 0));
      }
    }
    else if(option < 0){
      option = 6;
    }
    else{
      option = 0;
    }
    rp2040.fifo.push(hr);
    rp2040.fifo.push(hour);
    rp2040.fifo.push(minute);
    rp2040.fifo.push(day);
    rp2040.fifo.push(month);
    rp2040.fifo.push(year);
    rp2040.fifo.push(menu);
    rp2040.fifo.push(option);
    
  }


  else if (menu == 3){
    if(first){
      first = 0;
      if(hr_al1){
        if (hour_al1 != 12){
          hour_al1 = hour_al1 - 12;
        }
      }
      else{
        if(hour_al1 == 0){
          hour_al1 = 12;
        }
      }
    }
    
    if(hr_al1 < 0){
      hr_al1 = 1;
    }

    if(hr_al1 > 1){
      hr_al1 = 0;
    }
    
    if(hour_al1 < 1){
      hour_al1 = 12;
    }
    
    if(hour_al1 > 12){
      hour_al1 = 1;
    }

    if(minute_al1 < 0){
      minute_al1 = 59;
    }
    
    if(minute_al1 > 59){
      minute_al1 = 0;
    }

    if(option == 0){
      if(editing){
        ptr = &hour_al1;
        if(enter){
          enter = 0;
          editing = 0;
          ptr = &option;
        }
      }
      else{
        if(enter){
          enter = 0;
          editing = 1;
          ptr = &hour_al1;
        }
      }
    }
    else if(option == 1){
      if(editing){
        ptr = &minute_al1;
        if(enter){
          enter = 0;
          editing = 0;
          ptr = &option;
        }
      }
      else{
        if(enter){
          enter = 0;
          editing = 1;
          ptr = &minute_al1;
        }
      }
    }
    else if(option == 2){
      if(editing){
        ptr = &hr_al1;
        if(enter){
          enter = 0;
          editing = 0;
          ptr = &option;
        }
      }
      else{
        if(enter){
          enter = 0;
          editing = 1;
          ptr = &hr_al1;
        }
      }
    }
    else if(option == 3){
      if(enter){
        enter = 0;
        option = 0;
        menu = 1;
        if(hr_al1){
          if(hour_al1 != 12){
            hour_al1 = hour_al1 + 12; 
          }
        }
        else{
          if(hour_al1 == 12){
            hour_al1 = 0;
          }
        }
      }
    }
    else if(option < 0){
      option = 3;
    }
    else{
      option = 0;
    }
    rp2040.fifo.push(hr_al1);
    rp2040.fifo.push(hour_al1);
    rp2040.fifo.push(minute_al1);
    rp2040.fifo.push(menu);
    rp2040.fifo.push(option);
  }
  else if (menu == 4){
    if(first){
      first = 0;
      if(hr_al2){
        if (hour_al2 != 12){
          hour_al2 = hour_al2 - 12;
        }
      }
      else{
        if(hour_al2 == 0){
          hour_al2 = 12;
        }
      }
    }
    
    if(hr_al2 < 0){
      hr_al2 = 1;
    }

    if(hr_al2 > 1){
      hr_al2 = 0;
    }
    
    if(hour_al2 < 1){
      hour_al2 = 12;
    }
    
    if(hour_al2 > 12){
      hour_al2 = 1;
    }

    if(minute_al2 < 0){
      minute_al2 = 59;
    }
    
    if(minute_al2 > 59){
      minute_al2 = 0;
    }

    if(option == 0){
      if(editing){
        ptr = &hour_al2;
        if(enter){
          enter = 0;
          editing = 0;
          ptr = &option;
        }
      }
      else{
        if(enter){
          enter = 0;
          editing = 1;
          ptr = &hour_al2;
        }
      }
    }
    else if(option == 1){
      if(editing){
        ptr = &minute_al2;
        if(enter){
          enter = 0;
          editing = 0;
          ptr = &option;
        }
      }
      else{
        if(enter){
          enter = 0;
          editing = 1;
          ptr = &minute_al2;
        }
      }
    }
    else if(option == 2){
      if(editing){
        ptr = &hr_al2;
        if(enter){
          enter = 0;
          editing = 0;
          ptr = &option;
        }
      }
      else{
        if(enter){
          enter = 0;
          editing = 1;
          ptr = &hr_al2;
        }
      }
    }
    else if(option == 3){
      if(enter){
        enter = 0;
        option = 0;
        menu = 1;
        if(hr_al2){
          if(hour_al2 != 12){
            hour_al2 = hour_al2 + 12; 
          }
        }
        else{
          if(hour_al2 == 12){
            hour_al2 = 0;
          }
        }
      }
    }
    else if(option < 0){
      option = 3;
    }
    else{
      option = 0;
    }
    rp2040.fifo.push(hr_al2);
    rp2040.fifo.push(hour_al2);
    rp2040.fifo.push(minute_al2);
    rp2040.fifo.push(menu);
    rp2040.fifo.push(option);
  }

  
  else{
    ptr = &option;
    DateTime now = rtc.now();
  
    hour = now.hour();
    minute = now.minute();
    second = now.second();
    day = now.day();
    month = now.month();
    year = now.year();
    week = now.dayOfTheWeek();
    if(hour > 12){
      hour = hour - 12;
      hr = 1;
    }
    else if(hour == 12){
      hr = 1;
    }
    else if(hour == 0){
      hour = 12;
      hr = 0;
    }
    else{
      hr = 0;
    }
    rp2040.fifo.push(hr);
    rp2040.fifo.push(hour);
    rp2040.fifo.push(minute);
    rp2040.fifo.push(second);
    rp2040.fifo.push(day);
    rp2040.fifo.push(month);
    rp2040.fifo.push(year);
    rp2040.fifo.push(week);
    if(option == 0){
      if(enter){
        enter = 0;
        digitalWrite(RELAY,LOW);
        delay(6000);
        digitalWrite(RELAY,HIGH);
      } 
    }
    else if(option == 1){
        if(enter){
          menu = 1;
          enter = 0;
          option = 0;
        }
    }
    else if(option < 0){
      option = 1;
    }
    else{
      option = 0;
    }
    rp2040.fifo.push(menu);
    rp2040.fifo.push(option);
  }
  DateTime now = rtc.now();
  on_time = (hour_al1 * 100) + minute_al1;
  off_time = (hour_al2 * 100) + minute_al2;
  now_time = (now.hour() * 100) + now.minute();
  if(on_time > off_time){
    if(now_time >= off_time && now_time < on_time){
      digitalWrite(RELAY,HIGH);
    }
    else{
      digitalWrite(RELAY,LOW);
    }
  }
  else{
    if(now_time <= off_time && now_time >= on_time){
      digitalWrite(RELAY,LOW);
    }
    else{
      digitalWrite(RELAY,HIGH);
    }
  }
}

void btn(){
  enter = 1;
}

void twist(){
  bool clk = digitalRead(CLK);
  bool dt = digitalRead(DT);
  if((clk && !dt) || (!clk && dt)){
    *ptr = *ptr + 1;
  }
  if((clk && dt) || (!clk && !dt)){
    *ptr = *ptr - 1;
  }
}
