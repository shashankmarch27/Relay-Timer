#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define DISPLAY_ADDRESS 0X3C
#define DISPLAY_SDA 18
#define DISPLAY_SCL 19

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1, OLED_RESET);

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

int hour_read;
int minute_read;
int second_read;
int day_read;
int month_read;
int year_read;
int week_read;
int hr_read;
int menu_read = 0;
int option_read = 0;
bool enter_read = 0;

void setup1() {
  Wire1.setSDA(DISPLAY_SDA);
  Wire1.setSCL(DISPLAY_SCL);
  
  display.begin(DISPLAY_ADDRESS, true);
  display.setTextColor(SH110X_WHITE);
  display.clearDisplay();
  
  if(rp2040.fifo.pop()){
    display.setCursor(0,0);
    display.setTextSize(2);
    display.print("Lost power");
    display.display();
    delay(1000);
  }
}

void loop1() {
  if(menu_read == 1){
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(1);
    display.print("Set time");
    if(option_read == 0){
      display.println("*");
    }
    else{
      display.println(" ");
    }
    display.print("Set Turn On time");
    if(option_read == 1){
      display.println("*");
    }
    else{
      display.println(" ");
    }
    display.print("Set Turn Off time");
    if(option_read == 2){
      display.println("*");
    }
    else{
      display.println(" ");
    }
    display.print("Back");
    if(option_read == 3){
      display.println("*");
    }
    else{
      display.println(" ");
    }

    menu_read = rp2040.fifo.pop();
    option_read = rp2040.fifo.pop();
  }

  
  else if(menu_read == 2){
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(2);

    if(hour_read < 10){
      display.print("0");
    }
    display.print(hour_read);
    display.print(":");
    if(minute_read < 10){
      display.print("0");
    }
    display.print(minute_read);
    display.setCursor(65,0);
    display.println(hr_read ? "PM" : "AM");
    if(day_read < 10){
      display.print("0");
    }
    display.print(day_read);
    display.print("/");
    if(month_read < 10){
      display.print("0");
    }
    display.print(month_read);
    display.print("/");
    display.println(year_read);
    display.setTextSize(1);
    display.print("Ok");
    display.println((option_read == 6) ? "*" : " ");
    
    hr_read = rp2040.fifo.pop();
    hour_read = rp2040.fifo.pop();
    minute_read = rp2040.fifo.pop();
    day_read = rp2040.fifo.pop();
    month_read = rp2040.fifo.pop();
    year_read = rp2040.fifo.pop();
    menu_read = rp2040.fifo.pop();
    option_read = rp2040.fifo.pop();
  }

  else if(menu_read == 3){
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(2);
    display.println("Turn On");

    if(hour_read < 10){
      display.print("0");
    }
    display.print(hour_read);
    display.print(":");
    if(minute_read < 10){
      display.print("0");
    }
    display.print(minute_read);
    display.setCursor(65,16);
    display.println(hr_read ? "PM" : "AM");
    display.setTextSize(1);
    display.print("Ok");
    display.println((option_read == 3) ? "*" : " ");
    
    hr_read = rp2040.fifo.pop();
    hour_read = rp2040.fifo.pop();
    minute_read = rp2040.fifo.pop();
    menu_read = rp2040.fifo.pop();
    option_read = rp2040.fifo.pop();
  }
else if(menu_read == 4){
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(2);
    display.println("Turn Off");

    if(hour_read < 10){
      display.print("0");
    }
    display.print(hour_read);
    display.print(":");
    if(minute_read < 10){
      display.print("0");
    }
    display.print(minute_read);
    display.setCursor(65,16);
    display.println(hr_read ? "PM" : "AM");
    display.setTextSize(1);
    display.print("Ok");
    display.println((option_read == 3) ? "*" : " ");
    
    hr_read = rp2040.fifo.pop();
    hour_read = rp2040.fifo.pop();
    minute_read = rp2040.fifo.pop();
    menu_read = rp2040.fifo.pop();
    option_read = rp2040.fifo.pop();
  }
  
  else{
    hr_read = rp2040.fifo.pop();
    hour_read = rp2040.fifo.pop();
    minute_read = rp2040.fifo.pop();
    second_read = rp2040.fifo.pop();
    day_read = rp2040.fifo.pop();
    month_read = rp2040.fifo.pop();
    year_read = rp2040.fifo.pop();
    week_read = rp2040.fifo.pop();
  
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(2);

    if(hour_read < 10){
      display.print("0");
    }
    display.print(hour_read);
    display.print(":");
    if(minute_read < 10){
      display.print("0");
    }
    display.print(minute_read);
    display.print(":");
    if(second_read < 10){
      display.print("0");
    }
    display.print(second_read);
    display.setCursor(100,0);
    display.println(hr ? "PM" : "AM");
    if(day_read < 10){
      display.print("0");
    }
    display.print(day_read);
    display.print("/");
    if(month_read < 10){
      display.print("0");
    }
    display.print(month_read);
    display.print("/");
    display.println(year_read);
    display.println(daysOfTheWeek[week_read]);

    display.setTextSize(1);
    display.setCursor(0,56);
    display.print("Test");
    if(option_read == 0){
      display.print("*");
    }
    else{
      display.print(" ");
    }
    display.print("            Set");
    if(option_read == 1){
      display.print("*");
    }
  
    menu_read = rp2040.fifo.pop();
    option_read = rp2040.fifo.pop();
  }
  display.display();
}
