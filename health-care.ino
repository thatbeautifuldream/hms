#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DFRobot_MAX30102.h>
#include <DHT.h>  
#define bppin 35
#define DHTPIN 15      
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

#include <SoftwareSerial.h>
SoftwareSerial SIM900(2,4);
String long_lat;
static void smartdelay(unsigned long ms);  //dalay function for gps
String Link;
String SMS;

#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#include <TinyGPS++.h>

TinyGPSPlus gps;


static const uint32_t GPSBaud = 9600;

float latitude;
float longitude;

//sda D21, scl D122
DFRobot_MAX30102 particleSensor;

int ecgsensor=34; 
BlynkTimer timer; 

char auth[] = " __7Gs_z34KE9PqEP1R39RWuKCjkD_T__";

char ssid[] = "HMS";
char pass[] = "123456789";
 
int32_t SPO2; //SPO2
int8_t SPO2Valid; //Flag to display if SPO2 calculation is valid
int32_t heartRate; //Heart-rate
int8_t heartRateValid; //Flag to display if heart-rate calculation is valid 



void heartoxygen()
{
  Serial.println(F("Wait about four seconds"));
  particleSensor.heartrateAndOxygenSaturation(/**SPO2=*/&SPO2, /**SPO2Valid=*/&SPO2Valid, /**heartRate=*/&heartRate, /**heartRateValid=*/&heartRateValid);
  //Print result 
  Serial.print(F("heartRate="));
  Serial.print(heartRate, DEC);
  Serial.print(F(", heartRateValid="));
  Serial.print(heartRateValid, DEC);
  Serial.print(F("; SPO2="));
  Serial.print(SPO2, DEC);
  Serial.print(F(", SPO2Valid="));
  Serial.println(SPO2Valid, DEC);


   long_lat = String(float(latitude))+","+String(float(longitude));
   Blynk.virtualWrite(V5,long_lat);
   Link = "https://www.google.com/maps/search/?api=1&query="+String(long_lat);
   SMS = "Heart Rate is abnormal "+ long_lat + " " + Link;//////////////////////////////SMS message
  
  if(heartRateValid==1 && SPO2Valid == 1){

  String HR = "HeartRate: "+String(int32_t(heartRate))+" SPO2: "+String(int32_t(SPO2));
  String HR1 = "R:"+String(int32_t(heartRate))+" O:"+String(int32_t(SPO2))+"  ";
  Blynk.virtualWrite(V0,HR);
  lcd.setCursor(6,1);
  lcd.println(HR1);
  
if(heartRate<50)///////////////Change the range heartRate<(*yourValue) to set the abnormal value
{
  get_location(SMS);
    Blynk.notify("Heart Rate is abnormal");
  }
  else 
  {
    Blynk.notify("Heart Rate is normal");
  }
}
  
}

 

void ecg()
{
int ec=analogRead(ecgsensor);
Serial.println(ec);
delay(200); 
Blynk.virtualWrite(V1,ec);
lcd.setCursor(0,0);
lcd.print("E:");
lcd.print(ec);
lcd.print("    ");
}

void temp(){
    int h = dht.readHumidity();
    int f = dht.readTemperature(); 
    String state = "T "+String((int)f)+"c H "+String((int)h) +"%";
    Serial.println(state);
    Blynk.virtualWrite(V2,state);
    String state1 = "T"+String((int)f)+" H"+String((int)h)+"     ";
    lcd.setCursor(7,0);
    lcd.print(state1);    
}



int get_location(String message){

  SIM900.print("AT+CMGF=1\r");     // AT command to set SIM900 to SMS mode
  delay(100);
  SIM900.print("AT+CNMI=2,2,0,0,0\r");       // Set module to send SMS data to serial out upon receipt
  delay(100);
    
  SIM900.println("AT+CMGF=1"); // Replace x with mobile number
  delay(1000);
  SIM900.println("AT+CMGS= \"+918709090098\"\r"); // Replace Number with mobile number
  delay(1000); 
  SIM900.println(message);// The SMS text you want to send
  delay(100);
  SIM900.println((char)26);// ASCII code of CTRL+Z
  
}

void bp(){
  int bpRval = analogRead(bppin);
  int bpval = (bpRval * 5.0) / 1024.0;
  Serial.print(bpval);
  Blynk.virtualWrite(V4,bpval);
  lcd.setCursor(0,1);
  lcd.print("P:");
  lcd.print(bpval);
}


void GPS()
{
if (gps.charsProcessed() < 10)
  {
    //Serial.println("No GPS detected: check wiring.");
    //Blynk.virtualWrite(V4, "GPS ERROR");         // Value Display widget  on V4 if GPS not detected
  }
}
void displaygpsInfo()
{ 
  if (gps.location.isValid() ) 
  {  
    latitude = (gps.location.lat());      //Storing the Lat. and Lon. 
    longitude = (gps.location.lng());     //Storing the Lat. and Lon.
    Serial.print("LAT:  ");
    Serial.println(latitude, 6);          // float to x decimal places
    Serial.print("LONG: ");
    Serial.println(longitude, 6);          
  }
}

void locate()
{
  while (Serial.available() > 0) 
    {
      // sketch displays information every time a new sentence is correctly encoded.
      if (gps.encode(Serial.read()))
        displaygpsInfo();
  }
}

 
void setup()
{
  //Init serial
  Serial.begin(115200); 
  SIM900.begin(9600); 
  Blynk.begin(auth, ssid, pass);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("HEALTH");
  lcd.setCursor(0,1);
  lcd.print("MONITORING");
  delay(1000);
  lcd.clear();
  while (!particleSensor.begin()) {
    Serial.println("MAX30102 was not found");
    delay(1000);
  }

  dht.begin();
  pinMode(ecgsensor,INPUT);

  particleSensor.sensorConfiguration(/*ledBrightness=*/50, /*sampleAverage=*/SAMPLEAVG_4, \
                        /*ledMode=*/MODE_MULTILED, /*sampleRate=*/SAMPLERATE_100, \
                        /*pulseWidth=*/PULSEWIDTH_411, /*adcRange=*/ADCRANGE_16384);
//timer.setInterval(1000L, heartoxygen); 

}


void loop()
{
Blynk.run();
locate();
timer.run();
bp();
temp();
heartoxygen();
ecg();
}