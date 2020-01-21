
//For LCD
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

//For Temperature Sensors
#include <OneWire.h>
#include <DallasTemperature.h>


//For Humidity Sensors
#include <DHT.h>
//Humidity Sensor Pin
#define DHTPIN 2

//LCD Variables
boolean backlight = true;
int page = 1;
int contrast=50;

//Sensor Variables
int temp1 = 60;
int threshold = 60;



//Temperatuer Sensor Pin
//OneWire ds(6);  //Set to the pin on mcu

// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 6

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);  

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

int deviceCount = 0;
int tempC;

//LCD Pins
Adafruit_PCD8544 display = Adafruit_PCD8544( 10, 9, 8);


//Button Variables
volatile boolean up = false;
volatile boolean down = false;
volatile boolean middle = false;
int downButtonState = 0;
int upButtonState = 0;  
int selectButtonState = 0;          
int lastDownButtonState = 0;
int lastSelectButtonState = 0;
int lastUpButtonState = 0;

volatile boolean pos1 = true;
volatile boolean pos2 = false;
volatile boolean pos3 = false;
int pos = 1;

//Other Variables
byte i;
byte present = 0;
byte data[2];
byte addr[8];

#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


void setup() {

  //Pushbuttons
  pinMode(5, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

  //LCD Screen
  pinMode(7,OUTPUT);

  //Backlight
  digitalWrite(7,LOW); //Turn Backlight ON

  Serial.begin(9600);

  sensors.begin();
  dht.begin();
  display.begin();      
  display.setContrast(contrast); //Set contrast to 50
  display.clearDisplay(); 
  display.display();  


  //locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  deviceCount = sensors.getDeviceCount();
  Serial.print(deviceCount, DEC);
  Serial.println(" devices.");
  Serial.println("");



   
}

void loop() {
  //Update LCD Screen
  drawMenu();

  //Check Push Buttons
  downButtonState = digitalRead(5);
  selectButtonState = digitalRead(4);
  upButtonState =   digitalRead(3);
 
  checkIfDownButtonIsPressed();
  checkIfUpButtonIsPressed();
  checkIfSelectButtonIsPressed();  


///////////////////////////////////////////////////////////////////
// Button Configuration 
///////////////////////////////////////////////////////////////////

if(page == 1){
  //Position 1
  if(up && pos == 1){
    up=false;
    pos = 2;
  }
  if(down && pos == 1){
    down=false;
    pos = 3;
  }
  if(middle && pos == 1){
    middle=false;
    page = 2;
    pos = 1;
  }
  //Position 2
  if(up && pos == 2){
    up = false;
    pos = 3;
  }
  if(middle && pos == 2){
    middle = false;
    page = 4;
    pos = 1;
  }
  if(down && pos == 2){
    down = false;
    pos = 1;
  }
  //Position 3
  if(up && pos == 3){
    up = false;
    pos = 1;
  }
  if(middle && pos == 3){
    middle = false;
    pos = 1;
    threshold = 60;
  }
  if(down && pos == 3){
    down = false;
    pos = 2;
  } 
}

//First Sensor Page
if(page == 2){
  //Position 1
  if(up && pos == 1){
    up=false;
    pos = 2;
  }
  if(down && pos == 1){
    down=false;
    pos = 5;
  }
  if(middle && pos == 1){
    middle = false;
    page = 1;
    pos = 1;
  }

  //Position 2
  if(up && pos == 2){
    up = false;
    pos = 3;
  }
  if(down && pos == 2){
    down = false;
    pos = 1;
  }
  
  //Position 3
  if(up && pos == 3){
    up = false;
    pos = 4;
  }
  if(down && pos == 3){
    down = false;
    pos = 2;
  } 

  //Position 4
  if(up && pos == 4){
    up = false;
    pos = 5;
  }
  if(down && pos == 4){
    down = false;
    pos = 3;
  } 

  //Position 5
  if(up && pos == 5){
    up = false;
    pos = 1;
  }
  if(down && pos == 5){
    down = false;
    pos = 4;
  }
  if(middle && pos == 5){
    middle = false;
    page = 3;
    pos = 1; 
  } 
}

//Second Sensor Page
if(page == 3){
  //Position 1
  if(up && pos == 1){
    up=false;
    pos = 2;
  }
  if(down && pos == 1){
    down=false;
    pos = 5;
  }
  if(middle && pos == 1){
    middle = false;
    page = 2;
    pos = 1;
  }

  //Position 2
  if(up && pos == 2){
    up = false;
    pos = 3;
  }
  if(down && pos == 2){
    down = false;
    pos = 1;
  }
  
  //Position 3
  if(up && pos == 3){
    up = false;
    pos = 4;
  }
  if(down && pos == 3){
    down = false;
    pos = 2;
  } 

  //Position 4
  if(up && pos == 4){
    up = false;
    pos = 5;
  }
  if(down && pos == 4){
    down = false;
    pos = 3;
  } 

  //Position 5
  if(up && pos == 5){
    up = false;
    pos = 1;
  }
  if(down && pos == 5){
    down = false;
    pos = 4;
  }
  if(middle && pos == 5){
    middle = false;
    page = 1;
    pos = 1; 
  }   
}

if(page == 4){
  //Position 1
  if(up && pos == 1){
    up=false;
    pos = 2;
  }
  if(down && pos == 1){
    down=false;
    pos = 3;
  }
  if(middle && pos == 1){
    middle=false;
    threshold++;
  }
  //Position 2
  if(up && pos == 2){
    up = false;
    pos = 3;
  }
  if(middle && pos == 2){
    middle = false;
    threshold--;
  }
  if(down && pos == 2){
    down = false;
    pos = 1;
  }
  //Position 3
  if(up && pos == 3){
    up = false;
    pos = 1;
  }
  if(middle && pos == 3){
    middle = false;
    page = 1;
    pos = 1;
  }
  if(down && pos == 3){
    down = false;
    pos = 2;
  }  
}


////////////////////////////////////////////////////////////////////

//  OLD
//  //Read Temp Sensor Data
//  if(!ds.search(addr)) {
//     //Serial.print("No more addresses.\n");
//     ds.reset_search();
//     return;
//    }
//  ds.reset();
//  ds.select(addr);
//  ds.write(0x44,1);
//  //delay(1000);
//  ds.reset();
//  ds.select(addr);
//  ds.write(0xBE);
//  data[0] = ds.read();
//  data[1] = ds.read();
//  temp1 = data[1];
//  temp1 <<= 8;   
//  temp1 += data[0]; 
//  temp1 >>= 4;

  // Send command to all the sensors for temperature conversion
  sensors.requestTemperatures(); 
  
  // Display temperature from each sensor
  for (int i = 0;  i < deviceCount;  i++)
  {
    Serial.print("Sensor ");
    Serial.print(i+1);
    Serial.print(" : ");
    tempC = sensors.getTempCByIndex(i);
    Serial.print(tempC);
    Serial.print("\n");

  }
  


  // Reading humidity data
  int h = dht.readHumidity();
  Serial.print("Humidity: ");
  Serial.print(h, DEC);
  Serial.print("\n");
  }


  
void drawMenu()
  {    
  //Main Page
  if(page == 1){
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(18, 0);
    display.print("MEDIVAC"); 
    display.drawFastHLine(0,10,83,BLACK);
    
    if(pos == 1){
      display.setTextColor(WHITE, BLACK);
      }
    else{
      display.setTextColor(BLACK, WHITE);
    }
    display.setCursor(0, 15);
    display.print("Sensor Data");

    if(pos == 2){
      display.setTextColor(WHITE, BLACK);
      }
    else{
      display.setTextColor(BLACK, WHITE);
    }    
    display.setCursor(0,25);
    display.print("Set Temp: ");
    display.setCursor(55, 25);
    display.print(threshold);
    display.setCursor(70, 25);
    display.print("C"); 
    if(pos == 3){
      display.setTextColor(WHITE, BLACK);
      }
    else{
      display.setTextColor(BLACK, WHITE);
    } 
    display.setCursor(0,35);
    display.print("Reset");
    display.display();
    }

  //Sensor Page 1
  if(page == 2){
    display.setTextSize(1);
    display.clearDisplay();
    if(pos == 1){
      display.setTextColor(WHITE, BLACK);
      }
    else{
      display.setTextColor(BLACK, WHITE);
    }
    display.setCursor(0, 0);
    display.print("<<<"); 
    if(pos == 2){
      display.setTextColor(WHITE, BLACK);
      }
    else{
      display.setTextColor(BLACK, WHITE);
    }    
    display.setCursor(0, 10);
    display.print("T. Sensor 1:");
    if(pos == 3){
      display.setTextColor(WHITE, BLACK);
      }
    else{
      display.setTextColor(BLACK, WHITE);
    }
    display.setCursor(0,20);
    display.print("T. Sensor 2:");
    if(pos == 4){
      display.setTextColor(WHITE, BLACK);
      }
    else{
      display.setTextColor(BLACK, WHITE);
    }
    display.setCursor(0,30);
    display.print("T. Sensor 3:");
    if(pos == 5){
      display.setTextColor(WHITE, BLACK);
      }
    else{
      display.setTextColor(BLACK, WHITE);
    }
    display.setCursor(0,40);
    display.print(">>>");
    display.display();
    }

  //Sensor Page 2
  if(page == 3){
    display.setTextSize(1);
    display.clearDisplay();
    if(pos == 1){
      display.setTextColor(WHITE, BLACK);
      }
    else{
      display.setTextColor(BLACK, WHITE);
    }
    display.setCursor(0, 0);
    display.print("<<<"); 
    if(pos == 2){
      display.setTextColor(WHITE, BLACK);
      }
    else{
      display.setTextColor(BLACK, WHITE);
    }    
    display.setCursor(0, 10);
    display.print("Humidity: ");
    if(pos == 3){
      display.setTextColor(WHITE, BLACK);
      }
    else{
      display.setTextColor(BLACK, WHITE);
    }
    display.setCursor(0,20);
    display.print("Current Draw: ");
    if(pos == 4){
      display.setTextColor(WHITE, BLACK);
      }
    else{
      display.setTextColor(BLACK, WHITE);
    }
    display.setCursor(0,30);
    display.print("Battery: ");
    if(pos == 5){
      display.setTextColor(WHITE, BLACK);
      }
    else{
      display.setTextColor(BLACK, WHITE);
    }
    display.setCursor(0,40);
    display.print(">>>");
    display.display();
    }

  //Set Temp Threshold Page
  if(page == 4){
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(40, 0);
    display.print(threshold); 
    display.drawFastHLine(0,10,83,BLACK);
    if(pos == 1){
      display.setTextColor(WHITE, BLACK);
      }
    else{
      display.setTextColor(BLACK, WHITE);
    }
    display.setCursor(0, 15);
    display.print("Increase");

    if(pos == 2){
      display.setTextColor(WHITE, BLACK);
      }
    else{
      display.setTextColor(BLACK, WHITE);
    }    
    display.setCursor(0,25);
    display.print("Decrease");

    if(pos == 3){
      display.setTextColor(WHITE, BLACK);
      }
    else{
      display.setTextColor(BLACK, WHITE);
    }    
    display.setCursor(0,35);
    display.print("<<<");
    display.display();
    }
  
  }


void checkIfDownButtonIsPressed(){
  if(downButtonState != lastDownButtonState) {
    if(downButtonState == 0) {
      down=true;
      }
    delay(50);
    }
  lastDownButtonState = downButtonState;
  }

void checkIfUpButtonIsPressed(){
  if(upButtonState != lastUpButtonState) {
    if (upButtonState == 0) {
      up=true;
      }
    delay(50);
    }
   lastUpButtonState = upButtonState;
  }

void checkIfSelectButtonIsPressed(){
  if(selectButtonState != lastSelectButtonState) {
    if(selectButtonState == 0) {
      middle=true;
      }
    delay(50);
    }
  lastSelectButtonState = selectButtonState;
  }
