// définition des broches et variables utilisées
int trig = 5;
int echo = 4;
int lecture_echo;
int ledPin = 13;
float Passage;

#include <ESP8266WiFi.h>
#include <WiFiClient.h>


const char* ssid="your_ssid";
const char* password = "password";


void setup(){
  
        pinMode(ledPin,OUTPUT);
        digitalWrite(ledPin,LOW);

        //initialisation de la transmission
        Serial.begin(115200);
        Serial.println();
        Serial.print("Wifi connecting to ");
        Serial.println( ssid );

        //connexion au WIFI
        WiFi.begin(ssid,password);
        Serial.println();
        Serial.print("Connection au Wifi...");
 
        //status du WIFI
        while( WiFi.status() != WL_CONNECTED ){
            delay(500);
            Serial.print(".");        
        }


        //signal lumineux quand la liaison WIFI est OK
        digitalWrite( ledPin , HIGH);
        delay(200);
        digitalWrite( ledPin , LOW);
        delay(200);
        digitalWrite( ledPin , HIGH);
        delay(200);
        digitalWrite( ledPin , LOW);
        delay(200);
        digitalWrite( ledPin , HIGH);
        delay(200);
        digitalWrite( ledPin , LOW);
        delay(200);
        
        Serial.println();

        //message pour confirmer la connexion + afficher l'adresse ip locale      
        Serial.println("Wifi Connected Success!");
        Serial.print("NodeMCU IP Address : ");
        Serial.println(WiFi.localIP() );
      
        pinMode(5, OUTPUT);
        digitalWrite(5, LOW);
        pinMode(4, INPUT);
        pinMode(13, OUTPUT);
}





void loop(){


                //lecture de l'echo du signal
                digitalWrite(5, HIGH);
                delayMicroseconds(10);
                digitalWrite(5, LOW);
                lecture_echo = pulseIn(4, HIGH);
        
                // La doc constructeur dit que si on veut une distance en cm, il faut diviser l'echo par 58
                Passage = lecture_echo / 58;
                // Il est possible d'afficher la distance en cm. Décommenter les lignes du dessous.
                Serial.print("Distance en cm : ");
                Serial.println(Passage);
        
                if (Passage < 90) {
                  digitalWrite(ledPin, HIGH);
                  delay(100);
                }
              
                if (Passage > 90) {
                  digitalWrite(ledPin, LOW);
                  delay(100);
                }

    //connexion au serveur
    IPAddress server(adresse_ip_du_serveur);
    
    WiFiClient client;
    const int httpPort = 80;
    if (client.connect(server, 80)) {
      Serial.println("connection WIFI OK");
    } else {
      Serial.println("connection WIFI échouée");
      return;
    }


    //envoi de la requête au serveur
    Serial.println("envoi de la requête...");
     client.print(String("GET http://your_host/connect2.php") + 
                       ("?Passage=") + Passage +
                         " HTTP/1.1\r\n" +
                         "Host: " + httpPort + "\r\n" +
                         "Connection: close\r\n\r\n");     
    Serial.println("envoi de la requête HTTP DONE!");


    //retour du serveur
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 1000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }

    Serial.println("closing connection");
    Serial.println();
    delay(100);
}
