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
static char sunsetUtc[32];
static char stepTimeUtc[32];
static char back[32];
long sys_sunrise;
long sys_sunset;
long timetostep;
long stepTime;
long passo;
int timezone;
long utcOffsetInSeconds = -10800;
float inputV = 0.0;
float averageV = 0.0;
int readSensor = 0;
char input;
String mensagem;
int tatual = 0;
int tvoltagem = 0;


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
  if(millis()-tvoltagem > 600000){
    //Serial.print("Tensão DC medida: ");
    Serial.println( averageV,2); //Imprime com duas casas depois da vírgula
    //Serial.println("V");
    tvoltagem = millis();
  }  
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

void returnto0(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  delay(500);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  delay(500); 
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  delay(500);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,HIGH);
  delay(500);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  delay(500);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  delay(500); 
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  delay(500);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,HIGH);
  delay(500);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  delay(500);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  delay(500); 
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  delay(500);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,HIGH);
  delay(500);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  delay(500);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  delay(500); 
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  delay(500);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,HIGH);
  delay(500);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  delay(500);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  delay(500); 
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  delay(500);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,HIGH);
  delay(500);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  delay(500);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  delay(500); 
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  delay(500);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,HIGH);
  delay(500);
}
 
void callapi (){
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;  //Object of class HTTPClient
    http.begin("http://api.openweathermap.org/data/2.5/weather?id=3435789&appid=7d103cfe921d9a5bfcf551a90513f265");
    int httpCode = http.GET();

    if (httpCode > 0) {
      payload = http.getString();
      Serial.println(payload);
    }
    http.end(); //Close connection
  }
}
void deserializejson(){
  String input = payload;
  
  StaticJsonDocument<1024 > doc;

  DeserializationError err = deserializeJson (doc, input);

  if (err){
    Serial.print("ERROR: ");
    Serial.println(err.c_str());
    return;
  }

  float coord_lon = doc["coord"]["lon"]; //Longitude
  float coord_lat = doc["coord"]["lat"]; //Latitude

  JsonArray weather = doc["weather"];

  JsonObject weather_0 = weather[0];
  int weather_0_id = weather_0["id"];   
  const char* weather_0_main = weather_0["main"]; 
  const char* weather_0_description = weather_0["description"]; 
  const char* weather_0_icon = weather_0["icon"]; 

  JsonObject weather_1 = weather[1];  
  int weather_1_id = weather_1["id"]; 
  const char* weather_1_main = weather_1["main"];
  const char* weather_1_description = weather_1["description"]; 
  const char* weather_1_icon = weather_1["icon"];

  JsonObject weather_2 = weather[2];
  int weather_2_id = weather_2["id"]; 
  const char* weather_2_main = weather_2["main"]; 
  const char* weather_2_description = weather_2["description"]; 
  const char* weather_2_icon = weather_2["icon"]; 

  const char* base = doc["base"]; 

  JsonObject main = doc["main"];
  float main_temp = main["temp"]; 
  int main_pressure = main["pressure"]; 
  int main_humidity = main["humidity"]; 
  float main_temp_min = main["temp_min"];
  float main_temp_max = main["temp_max"];

  int visibility = doc["visibility"]; 

  float wind_speed = doc["wind"]["speed"];

  int clouds_all = doc["clouds"]["all"]; 

  long dt = doc["dt"];

  JsonObject sys = doc["sys"];
  int sys_type = sys["type"]; 
  int sys_id = sys["id"]; 
  float sys_message = sys["message"];
  const char* sys_country = sys["country"];
  sys_sunrise = sys["sunrise"]; 
  sys_sunset = sys["sunset"];

  timezone = doc["timezone"];
  long id = doc["id"]; 
  const char* name = doc["name"]; 
  int cod = doc["cod"];
  
  //Serial.println(timezone);     //Imprime o fuso horário Unix
  //Serial.println(sys_sunrise);  //Imprime o nascente Unix
  //Serial.println(sys_sunset);   //Imprime o poente Unix
}

void atualizahora(){
  timeClient.update();
  hora = timeClient.getFormattedTime();
  if(millis()-tatual > 1000){
   // Serial.println(hora);
    tatual = millis();
  }  
}
long timestep(long sys_sunrise, long timetostep){
  long stepTimeUnix = sys_sunrise + timezone + timetostep;
  sprintf(stepTimeUtc, "%02d:%02d:%02d", hour(stepTimeUnix), minute(stepTimeUnix), second(stepTimeUnix));
 // Serial.println(stepTimeUtc);
  return  stepTimeUnix-timezone;
  }

void convertsunsetUtc(){
  long sunsetUnix = sys_sunset+timezone;
  sprintf(sunsetUtc, "%02d:%02d:%02d", hour(sunsetUnix), minute(sunsetUnix), second(sunsetUnix));
  //Serial.println(sunsetUtc);
}

void backtostart(){
  long backto = sys_sunset+timezone+120;
  sprintf(back, "%02d:%02d:%02d", hour(backto), minute(backto), second(backto));
  //Serial.println(back);
}

void serial(){
  if(Serial.available()>0)
    {
      input=Serial.read();
      mensagem = input;
            
      Serial.print(mensagem);
    }
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
  deserializejson();
 

  unsigned long sunrise = sys_sunrise+timezone; //Variável pra converter nascente
  unsigned long sunset = sys_sunset+timezone;   //Variável pra converter poente
  
  char srise[32];
  sprintf(srise, "%02d:%02d:%02d", hour(sunrise), minute(sunrise), second(sunrise));
  char sset[32];
  sprintf(sset, "%02d:%02d:%02d", hour(sunset), minute(sunset), second(sunset));

  Serial.println(srise);
  Serial.println(sset);

  step4();

  static long test = sys_sunrise;
  long suntime = sys_sunset-sys_sunrise;
  timetostep = suntime/24;

  stepTime = timestep(test, timetostep);
  convertsunsetUtc();
  backtostart();
  
}

void loop() {

  //serial();
 
  printS();
  atualizahora();
  //Serial.println(stepTime);

  if (hora > stepTimeUtc && hora < sunsetUtc){
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
    //Serial.println(passo);
  }
  
  if (hora > stepTimeUtc && hora < sunsetUtc){
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
    //Serial.println(passo);
  }
  
  if (hora > stepTimeUtc && hora < sunsetUtc){
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
    //Serial.println(passo);
  }
  
  if (hora > stepTimeUtc && hora < sunsetUtc){
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
    //Serial.println(passo);
  }
  if (hora > stepTimeUtc && hora < sunsetUtc){
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
    //Serial.println(passo);
  }
  if (hora > stepTimeUtc && hora < sunsetUtc){
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
    //Serial.println(passo);
  }
  if (hora > stepTimeUtc && hora < sunsetUtc){
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
    //Serial.println(passo);
  }
  if (hora > stepTimeUtc && hora < sunsetUtc){
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
    //Serial.println(passo);
  }
  if (hora > stepTimeUtc && hora < sunsetUtc){
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
    //Serial.println(passo);
  }
  if (hora > stepTimeUtc && hora < sunsetUtc){
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
    //Serial.println(passo);
  }
  if (hora > stepTimeUtc && hora < sunsetUtc){
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
    //Serial.println(passo);
  }
  if (hora > stepTimeUtc && hora < sunsetUtc){
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
    //Serial.println(passo);
  }
  if (hora > stepTimeUtc && hora < sunsetUtc){
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
    //Serial.println(passo);
  }
  if (hora > stepTimeUtc && hora < sunsetUtc){
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
    //Serial.println(passo);
  }
  if (hora > stepTimeUtc && hora < sunsetUtc){
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
    //Serial.println(passo);
  }
   if (hora > stepTimeUtc && hora < sunsetUtc){
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
    //Serial.println(passo);
  }
  if (hora > stepTimeUtc && hora < sunsetUtc){
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
    //Serial.println(passo);
  }
  if (hora > stepTimeUtc && hora < sunsetUtc){
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
    //Serial.println(passo);
  }
  if (hora > stepTimeUtc && hora < sunsetUtc){
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
    //Serial.println(passo);
  }
  if (hora > stepTimeUtc && hora < sunsetUtc){
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
    //Serial.println(passo);
  }
  if (hora > stepTimeUtc && hora < sunsetUtc){
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
    //Serial.println(passo);
  }
  if (hora > stepTimeUtc && hora < sunsetUtc){
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
    //Serial.println(passo);
  }
  if (hora > stepTimeUtc && hora < sunsetUtc){
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
    //Serial.println(passo);
  }
  if (hora > stepTimeUtc && hora < sunsetUtc){
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
    //Serial.println(passo);
  }
  if (hora == back){
    returnto0();
  }
  
  if(hora == "00:10:00"){
    setup();
  }
}
