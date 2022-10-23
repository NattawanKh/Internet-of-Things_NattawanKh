// My WiFi --------------------------------------------------------------------------
#include <WiFi.h>
#define SERVER_PORT 9999
const char* ssid = "Nhahee family 2.4G"; // So Rude ID
const char* password = "69696969";       // So Rude Password
WiFiServer my_server(SERVER_PORT);
//NeoPixel --------------------------------------------------------------------------
#include <Adafruit_NeoPixel.h>
#define NeoPixel_PIN 18
#define NUMPIXELS 1
Adafruit_NeoPixel pixels(NUMPIXELS, NeoPixel_PIN, NEO_GRB + NEO_KHZ800);
//String define Color----------------------------------------------------------------
String color_one;    //Check first Color
String color_two;    //Check Secound Color
String color_three;  //Check Third Color
//String define Value----------------------------------------------------------------
String sval_one;   // Check String Value
String sval_two;    
String sval_three;  
int  val_one = 0;  // Convert Value to Integer
int  val_two = 0;
int  val_three = 0;
int str_L = 0; 
//-----------------------------------------------------------------------------------
void setup() {
  pixels.begin();
  Serial.begin(115200);
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  my_server.begin();
  Serial.println("Server started");
}

void loop() {
  WiFiClient my_client = my_server.available();
  // Pixel Off -----------------------------------------
        pixels.setPixelColor(0, pixels.Color(0, 0, 0));
        pixels.show();
  //----------------------------------------------------
  if(my_client){
    Serial.println("New client connected");
    Serial.println("=======================================");
    Serial.println("[Read Me]");
    Serial.println("Neo Pixel Color Control");
    Serial.println("Set Your Color With R,G,B or H,S,V");
    Serial.println("Set Your Color Value With [000-255]");
    Serial.println("|Ex1 : RGB| R:010,G:200,B:003 ");
    Serial.println("|Ex2 : HSV| H:010,S:200,V:003 ");
    Serial.println("=======================================");
    while(true){
      while(my_client.available()){
        String msg = my_client.readString();
        //  Check Number of String ---------------------------------
        str_L = msg.length();
        //String Get Color -----------------------------------------
        color_one = msg[0];
        color_two = msg[6];
        color_three = msg[12];    //0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
        //------------------------- G : 0 2 0 , B : 0 3 4  ,  G  :  0  5  6
        //String Get Value -----------------------------------------
        sval_one = msg.substring(2,5);
        sval_two = msg.substring(8,11);
        sval_three = msg.substring(14,17);
        // Convert Value to Int-----------
        val_one = sval_one.toInt();
        val_two = sval_two.toInt();
        val_three = sval_three.toInt();
        //--------------------------------
        if(str_L == 17){ if(val_one <= 255 && val_two <= 255 && val_three <= 255){
        Serial.println("[Data Correct]");
        Serial.print("Your Neo Pixel Color : ");
        Serial.println(msg);
        // RGB============================================================================================================  
        if(color_one == "R" && color_two == "G" && color_three == "B")     // 123
        {
          pixels.setPixelColor(0, pixels.Color(val_one, 0, 0));   pixels.show();  delay(500);
          pixels.setPixelColor(0, pixels.Color(0, val_two, 0));   pixels.show();  delay(500);
          pixels.setPixelColor(0, pixels.Color(0, 0, val_three)); pixels.show();  delay(500);
        }
        else if(color_one == "R" && color_two == "B" && color_three == "G") // 132
        {
          pixels.setPixelColor(0, pixels.Color(val_one, 0,0));    pixels.show();  delay(500);
          pixels.setPixelColor(0, pixels.Color(0, val_three, 0)); pixels.show();  delay(500);
          pixels.setPixelColor(0, pixels.Color(0, 0, val_two));   pixels.show();  delay(500);
        }
        else if(color_one == "G" && color_two == "B" && color_three == "R") //312
        {
          pixels.setPixelColor(0, pixels.Color(val_three, 0, 0)); pixels.show();  delay(500);
          pixels.setPixelColor(0, pixels.Color(0, val_one, 0));   pixels.show();  delay(500);
          pixels.setPixelColor(0, pixels.Color(0, 0, val_two));   pixels.show();  delay(500);
        }
        else if(color_one == "G" && color_two == "R" && color_three == "B") //213
        { 
          pixels.setPixelColor(0, pixels.Color(val_two, 0, 0));   pixels.show();  delay(500);
          pixels.setPixelColor(0, pixels.Color(0, val_one, 0));   pixels.show();  delay(500);
          pixels.setPixelColor(0, pixels.Color(0, 0, val_three)); pixels.show();  delay(500);
        }
        else if(color_one == "B" && color_two == "G" && color_three == "R") //321
        {
          pixels.setPixelColor(0, pixels.Color(val_three, 0, 0)); pixels.show();  delay(500);
          pixels.setPixelColor(0, pixels.Color(0, val_two, 0));   pixels.show();  delay(500);
          pixels.setPixelColor(0, pixels.Color(0, 0, val_one));   pixels.show();  delay(500);
        }
        else if(color_one == "B" && color_two == "R" && color_three == "G") //231
        {
          pixels.setPixelColor(0, pixels.Color(val_two, 0, 0));   pixels.show();  delay(500);
          pixels.setPixelColor(0, pixels.Color(0, val_three, 0)); pixels.show();  delay(500);
          pixels.setPixelColor(0, pixels.Color(0, 0, val_one));   pixels.show();  delay(500);
        }
        //=================================================================================================================
        // HSV============================================================================================================
        else if(color_one == "H" && color_two == "S" && color_three == "V")     // 123
        {
          pixels.setPixelColor(0, pixels.Color(val_one*257, val_two*257, val_three*257));   pixels.show();  delay(1000);
        }
        else if(color_one == "H" && color_two == "V" && color_three == "S") // 132
        {
          pixels.setPixelColor(0, pixels.Color(val_one*257, val_three*257,val_two*257));    pixels.show();  delay(1000);
        }
        else if(color_one == "S" && color_two == "V" && color_three == "H") //312
        {
          pixels.setPixelColor(0, pixels.Color(val_three*257, val_one*257, val_two*257)); pixels.show();  delay(1000);
        }
        else if(color_one == "S" && color_two == "H" && color_three == "V") //213
        { 
          pixels.setPixelColor(0, pixels.Color(val_two*257, val_one*257,val_three*257));   pixels.show();  delay(1000);
        }
        else if(color_one == "V" && color_two == "S" && color_three == "H") //321
        {
          pixels.setPixelColor(0, pixels.Color(val_three*257, val_two*257, val_one*257)); pixels.show();  delay(1000);
        }
        else if(color_one == "V" && color_two == "H" && color_three == "S") //231
        {
          pixels.setPixelColor(0, pixels.Color(val_two*257, val_three*257, val_one*257));   pixels.show();  delay(1000);
        }
        //=================================================================================================================   
    }} else {Serial.println("[Invalid!!] : Check Your Message");
             Serial.println("=================================");
             Serial.println("Set Your Color With R,G,B or H,S,V");
             Serial.println("Set Your Color Value With [000-255]");
             Serial.println("|Example:RGB| R:010,G:200,B:003 ");
             Serial.println("|Example:HSV| V:000,S:255,H:255 ");
             Serial.println(" ");}          
    // Client disconnected----------------------------------------------
    }if(my_server.hasClient())
    {
       Serial.println("Client disconnected");
       return;
    }
    // Pixel Off -----------------------------------------
        pixels.setPixelColor(0, pixels.Color(0, 0, 0));
        pixels.show();
    //------------------------------------------------------------------
    }}} 
