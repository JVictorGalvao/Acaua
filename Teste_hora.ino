#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <TimeLib.h>

#define IN1 5 //LOW
#define IN2 4 //LOW
#define IN3 14 //HIGH
#define IN4 12 //HIGH
#define PIN_SENSOR 17 //ANALOGICO

#define R1  30000.0
#define R2  7500.0
#define ARDUINO_V 3.3
#define ANALOG_MAX 1023


  const char *ssid     = "eu";
  const char *password = "senhasenha";
  String payload;
  static char stepTimeUtc[32];
  long sys_sunrise;
  long sys_sunset;
  long timetostep;
  long stepTime;
  long passo;
  const long utcOffsetInSeconds = -10800;
  float inputV = 0.0;
  float averageV = 0.0;
  int readSensor = 0;


// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "a.st1.ntp.br", utcOffsetInSeconds);
String hora;//Váriavel que armazenara o horario do NTP.

float sensorVoltage(int readSensor){
  inputV = (readSensor * ARDUINO_V)/ ANALOG_MAX;
  averageV = inputV/(R2/(R1+R2));
  return averageV;
}
void printS(){
  averageV = sensorVoltage(readSensor = analogRead(PIN_SENSOR));
  Serial.print("Tensão DC medida: ");
  Serial.print( averageV,2); //Imprime com duas casas depois da vírgula
  Serial.println("V");
  delay(1000); 
}

void step1(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,HIGH);
  }

void step2(){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  }

void step3(){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  }

void step4(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  }
 
void callapi (){
    if (WiFi.status() == WL_CONNECTED) 
  {
    HTTPClient http; //Object of class HTTPClient
    http.begin("http://api.openweathermap.org/data/2.5/weather?id=3397277&appid=7d103cfe921d9a5bfcf551a90513f265");
    int httpCode = http.GET();

    if (httpCode > 0) 
    {
      payload = http.getString();
      Serial.println(payload);
    }
    http.end(); //Close connection
  }
}
long timestep(long sys_sunrise, long timetostep){
  long stepTimeUnix = sys_sunrise-10800+timetostep;

  sprintf(stepTimeUtc, "%02d:%02d:%02d", hour(stepTimeUnix), minute(stepTimeUnix), second(stepTimeUnix));
  Serial.println(stepTimeUtc);
  return  stepTimeUnix+10800;
  }

void setup(){
  Serial.begin(115200);
  
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(PIN_SENSOR, INPUT);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay (1000);
    Serial.print ( "Conectando...\n" );
  }

  timeClient.begin();

  callapi();

  String input = payload;
  
  StaticJsonDocument<1024 > doc;

  DeserializationError err = deserializeJson (doc, input);

  if (err){
    Serial.print("ERROR: ");
    Serial.println(err.c_str());
    return;
  }

  float coord_lon = doc["coord"]["lon"]; // -0.13
  float coord_lat = doc["coord"]["lat"]; // 51.51

  JsonArray weather = doc["weather"];

  JsonObject weather_0 = weather[0];
  int weather_0_id = weather_0["id"]; // 301  
  const char* weather_0_main = weather_0["main"]; // "Drizzle"
  const char* weather_0_description = weather_0["description"]; // "drizzle"
  const char* weather_0_icon = weather_0["icon"]; // "09n"

  JsonObject weather_1 = weather[1];  
  int weather_1_id = weather_1["id"]; // 701
  const char* weather_1_main = weather_1["main"]; // "Mist"
  const char* weather_1_description = weather_1["description"]; // "mist"
  const char* weather_1_icon = weather_1["icon"]; // "50n"

  JsonObject weather_2 = weather[2];
  int weather_2_id = weather_2["id"]; // 741
  const char* weather_2_main = weather_2["main"]; // "Fog"
  const char* weather_2_description = weather_2["description"]; // "fog"
  const char* weather_2_icon = weather_2["icon"]; // "50n"

  const char* base = doc["base"]; // "stations"

  JsonObject main = doc["main"];
  float main_temp = main["temp"]; // 281.87
  int main_pressure = main["pressure"]; // 1032
  int main_humidity = main["humidity"]; // 100
  float main_temp_min = main["temp_min"]; // 281.15
  float main_temp_max = main["temp_max"]; // 283.15

  int visibility = doc["visibility"]; // 2900

  float wind_speed = doc["wind"]["speed"]; // 1.5

  int clouds_all = doc["clouds"]["all"]; // 90

  long dt = doc["dt"]; // 1483820400

  JsonObject sys = doc["sys"];
  int sys_type = sys["type"]; // 1
  int sys_id = sys["id"]; // 5091
  float sys_message = sys["message"]; // 0.0226
  const char* sys_country = sys["country"]; // "GB"
  sys_sunrise = sys["sunrise"]; // 1483776245
  sys_sunset = sys["sunset"]; // 1483805443

  long id = doc["id"]; // 2643743
  const char* name = doc["name"]; // "London"
  int cod = doc["cod"]; // 200
  
  Serial.println(sys_sunrise);
  Serial.println(sys_sunset);

  unsigned long sunrise = sys_sunrise-10800;
  unsigned long sunset = sys_sunset-10800;
  
  char srise[32];
  sprintf(srise, "%02d:%02d:%02d", hour(sunrise), minute(sunrise), second(sunrise));
  char sset[32];
  sprintf(sset, "%02d:%02d:%02d", hour(sunset), minute(sunset), second(sunset));

  Serial.println(srise);
  Serial.println(sset);

  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);

  static long test = sys_sunrise;
  long suntime = sys_sunset-sys_sunrise;
  timetostep = suntime/24;

  stepTime = timestep(test, timetostep);
  
}

void loop() {

  printS();
  timeClient.update();
  hora = timeClient.getFormattedTime();
  Serial.println(hora);
  delay(1000);
  Serial.println(stepTime);


  if (hora > stepTimeUtc){
    step1();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    delay(500);
  }
  if(hora == stepTimeUtc){
    step1();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    Serial.println(passo);
  }
  
  if (hora > stepTimeUtc){
    step2();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    delay(500);
  }
  if(hora == stepTimeUtc){
    step2();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    Serial.println(passo);
  }
  
  if (hora > stepTimeUtc){
    step3();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    delay(500);
  }
  if(hora == stepTimeUtc){
    step3();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    Serial.println(passo);
  }
  
  if (hora > stepTimeUtc){
    step4();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    delay(500);
  }
  if(hora == stepTimeUtc){
    step4();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    Serial.println(passo);
  }
    if (hora > stepTimeUtc){
    step1();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    delay(500);
    }
  if(hora == stepTimeUtc){
    step1();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    Serial.println(passo);
  }
  if (hora > stepTimeUtc){
    step2();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    delay(500);
    }
  if(hora == stepTimeUtc){
    step2();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    Serial.println(passo);
  }
  if (hora > stepTimeUtc){
    step3();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    delay(500);
    }
  if(hora == stepTimeUtc){
    step3();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    Serial.println(passo);
  }
  if (hora > stepTimeUtc){
    step4();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    delay(500);
    }
  if(hora == stepTimeUtc){
    step4();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    Serial.println(passo);
  }
  if (hora > stepTimeUtc){
    step1();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    delay(500);
    }
  if(hora == stepTimeUtc){
    step1();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    Serial.println(passo);
  }
  if (hora > stepTimeUtc){
    step2();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    delay(500);
    }
  if(hora == stepTimeUtc){
    step2();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    Serial.println(passo);
  }if (hora > stepTimeUtc){
    step3();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    delay(500);
    }
  if(hora == stepTimeUtc){
    step3();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    Serial.println(passo);
  }
  if (hora > stepTimeUtc){
    step4();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    delay(500);
    }
  if(hora == stepTimeUtc){
    step4();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    Serial.println(passo);
  }
  if (hora > stepTimeUtc){
    step1();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    delay(500);
    }
  if(hora == stepTimeUtc){
    step1();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    Serial.println(passo);
  }
  if (hora > stepTimeUtc){
    step2();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    delay(500);
    }
  if(hora == stepTimeUtc){
    step2();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    Serial.println(passo);
  }
  if (hora > stepTimeUtc){
    step3();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    delay(500);
    }
  if(hora == stepTimeUtc){
    step3();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    Serial.println(passo);
  }
  if (hora > stepTimeUtc){
    step4();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    delay(500);
    }
  if(hora == stepTimeUtc){
    step4();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    Serial.println(passo);
  }
  if (hora > stepTimeUtc){
    step1();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    delay(500);
    }
  if(hora == stepTimeUtc){
    step1();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    Serial.println(passo);
  }
  if (hora > stepTimeUtc){
    step2();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    delay(500);
    }
  if(hora == stepTimeUtc){
    step2();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    Serial.println(passo);
  }
  if (hora > stepTimeUtc){
    step3();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    delay(500);
    }
  if(hora == stepTimeUtc){
    step3();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    Serial.println(passo);
  }
  if (hora > stepTimeUtc){
    step4();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    delay(500);
    }
  if(hora == stepTimeUtc){
    step4();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    Serial.println(passo);
  }
  if (hora > stepTimeUtc){
    step1();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    delay(500);
    }
  if(hora == stepTimeUtc){
    step1();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    Serial.println(passo);
  }
  if (hora > stepTimeUtc){
    step2();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    delay(500);
    }
  if(hora == stepTimeUtc){
    step2();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    Serial.println(passo);
  }
  if (hora > stepTimeUtc){
    step3();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    delay(500);
    }
  if(hora == stepTimeUtc){
    step3();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    Serial.println(passo);
  }
  if (hora > stepTimeUtc){
    step4();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    delay(500);
    }
  if(hora == stepTimeUtc){
    step4();
    passo = timestep(stepTime, timetostep);
    timestep(stepTime, timetostep);
    stepTime = passo;
    Serial.println(passo);
  }

  if(hora == "00:10:00"){
    setup();
  }
}
