#include <ThingSpeak.h>

// Información del Canal y Campos de ThingSpeak
char thingSpeakAddress[] = "api.thingspeak.com";
unsigned long channelID = 1980516;
char* readAPIKey = (char*)"N3BTS38GAU2WYJ19";
char* writeAPIKey = (char*)"TL3HD3M45XUVSHQ6";
const unsigned long postingInterval = 15L * 1000L;
unsigned int dataFieldOne = 1;                       
unsigned int dataFieldTwo = 2;                       
unsigned int dataFieldThree = 3;                     
unsigned int dataFieldFour = 4;                      
//*************** Fin Conección ThinkSpeak *******

//------------------------- Activar WIFI ESP8266 -----------------------
#include <ESP8266WiFi.h>
char ssid[] = "5073CA";
char password[] = "L23103809616525";
WiFiClient client;              //Cliente Wifi para ThingSpeak
//-------------------------- Fin Configuración WIFI ESP8266 --------------

//pines
const int Temperatura = D2;    //Fotocelda Grove
const int Presencia = D8;      //Simulado con un led 13 en Arduino
const int Gas = A0;    //Relay del ventilador
const int Perilla = D9;  //Temperatura Grove 

//vaeiables con los valores medidos
int Temperatura_val = 0;
int Presencia_val = 0;
int Gas_val  = 0;
int Perilla_val = 0;

void LeerSensores(void)
{
  Temperatura_val = random(0, 100);
  Presencia_val = random(0, 100);
  Gas_val = random(0, 100);
  Perilla_val = random(0, 100);
}

void ImprimirValoresSensores(void)
{
  Serial.println("========================================");
  Serial.print("Temperatura");
  Serial.print(Temperatura_val);
  Serial.print(" °C");
  Serial.println(" ");

  Serial.print("Presencia: ");
  Serial.print(Presencia_val);
  Serial.print("Cm");



  Serial.println("Gas: ");
  Serial.print(Gas_val);
  Serial.print("ppm");


  Serial.println("Perilla: ");
  Serial.print(Perilla_val);
  Serial.print("°");

}


// Use this function if you want to write a single field
int writeTSData( long TSChannel, unsigned int TSField, float data ){
  int  writeSuccess = ThingSpeak.writeField( TSChannel, TSField, data, writeAPIKey ); // Write the data to the channel
  if ( writeSuccess ){
    //lcd.setCursor(0, 1);
    //lcd.print("Send ThinkSpeak");
    Serial.println( String(data) + " written to Thingspeak." );
    }
    
    return writeSuccess;
}

//use this function if you want multiple fields simultaneously
int write2TSData( long TSChannel, unsigned int TSField1, 
                  float field1Data,unsigned int TSField2, long field2Data,
                  unsigned int TSField3, long field3Data ,
                  unsigned int TSField4, long field4Data ){

  ThingSpeak.setField( TSField1, field1Data );
  ThingSpeak.setField( TSField2, field2Data );
  ThingSpeak.setField( TSField3, field3Data );
  ThingSpeak.setField( TSField4, field4Data );

  int printSuccess = ThingSpeak.writeFields( TSChannel, writeAPIKey );
  return printSuccess;
}

//metodo cliente para controlar los eventos R1 y R2
void setup()
{
  //Abrir el puerto de lectura en el PC para mensajes
  Serial.begin(115200);
  randomSeed(analogRead(0));

  //----------- Comando para Conectarse a la WIFI el ESP8266 ---------
  Serial.println("Conectandose a la WIFI!");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi conectada");
  Serial.println(WiFi.localIP());
  //----------- Fin de conecciÃ³n ESP8266 -----------------------------

  //Establecer los modos de los puertos
  //pinMode(sensorluzpin, INPUT);
 
  //************ Conectar Cliente ThinkSpeak *******
    ThingSpeak.begin( client );
  //************ Fin Conectar Cliente ThingSpeak ***
  
}

//metodo repetitivo
unsigned long lastConnectionTime = 0;
long lastUpdateTime = 0;

void loop()                    
{
  
  // Only update if posting time is exceeded
  if (millis() - lastUpdateTime >=  postingInterval) {
    lastUpdateTime = millis();
    LeerSensores();
    ImprimirValoresSensores();

    //Verificar los umbrales
   

    //Enviar los Datos a ThinkSpeak
    write2TSData( channelID , dataFieldOne , Temperatura_val , 
                      dataFieldTwo , Presencia_val,
                      dataFieldThree , Gas_val,
                      dataFieldFour, Perilla_val);     
    }
}