
//ESP32 board: MH ET LIVE ESP32DEVKit

// Supporting Arduino Forum Topics:
// Waveshare e-paper displays with SPI: http://forum.arduino.cc/index.php?topic=487007.0
// Good Dispay ePaper for Arduino : https://forum.arduino.cc/index.php?topic=436411.0

// mapping suggestion for ESP32, e.g. LOLIN32, see .../variants/.../pins_arduino.h for your board
// NOTE: there are variants with different pins for SPI ! CHECK SPI PINS OF YOUR BOARD
// BUSY -> 4, RST -> 16, DC -> 17, CS -> SS(5), CLK -> SCK(18), DIN -> MOSI(23), GND -> GND, 3.3V -> 3.3V

// include library, include base class, make path known
#include <GxEPD.h>

// select the display class to use, only one
// #include <GxGDEW0583T7/GxGDEW0583T7.h>    // 5.83" b/w   600x448px
#include <GxGDEW042T2/GxGDEW042T2.h>      // 4.2" b/w       400x300px

#include GxEPD_BitmapExamples
#include <WiFi.h>
#include <PubSubClient.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>

// FreeFonts from Adafruit_GFX
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeMono12pt7b.h>
#include <Fonts/FreeMono18pt7b.h>
#include <Fonts/FreeMono24pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSansBold18pt7b.h>
#include <Fonts/FreeSansBold24pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeSans24pt7b.h>

//#include GxEPD_BitmapExamples
#include "image.h"

#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

// for SPI pin definitions see e.g.:
// C:\Users\xxx\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.4.2\variants\generic\common.h

//ESP32 with E-paper Hat
GxIO_Class io(SPI, /*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16); // arbitrary selection of 17, 16
GxEPD_Class display(io, /*RST=*/ 16, /*BUSY=*/ 4); // arbitrary selection of (16), 4

//Set Input Pins
#include "driver/rtc_io.h"
const int DisplayOnPin = 15;
const int PageSelectPin = 2;

int DisplayOnState = 0;
int PageSelectState = 0;
int DisplayOnPinState = 0;
int PageSelectPinState = 0;

//----------------------------------------------------------------------------
//----------------- Define all Variables -------------------------------------
String latestUpdate;

//Page1
String col1row1;
String col2row1;
String col3row1;
String col4row1;
String col1row2;
String col2row2;
String col3row2;
String col4row2;
String col1row3;
String col2row3;
String col3row3;
String col4row3;
String col1row4;
String col2row4;
String col3row4;
String col4row4;
String col1row5;
String col2row5;
String col3row5;
String col4row5;
String col1row6;
String col2row6;
String col3row6;
String col4row6;
String col1row7;
String col2row7;
String col3row7;
String col4row7;
String col1row8;
String col2row8;
String col3row8;
String col4row8;
String col1row9;
String col2row9;
String col3row9;
String col4row9;

//Page2
String p2col1row1;
String p2col2row1;
String p2col3row1;
String p2col4row1;
String p2col1row2;
String p2col2row2;
String p2col3row2;
String p2col4row2;
String p2col1row3;
String p2col2row3;
String p2col3row3;
String p2col4row3;
String p2col1row4;
String p2col2row4;
String p2col3row4;
String p2col4row4;
String p2col1row5;
String p2col2row5;
String p2col3row5;
String p2col4row5;
String p2col1row6;
String p2col2row6;
String p2col3row6;
String p2col4row6;
String p2col1row7;
String p2col2row7;
String p2col3row7;
String p2col4row7;
String p2col1row8;
String p2col2row8;
String p2col3row8;
String p2col4row8;
String p2col1row9;
String p2col2row9;
String p2col3row9;
String p2col4row9;

// --------------------------------------------
// Col and row settings
int col1 = 2;
int col2 = 150;
int col3 = 204;
int col4 = 350;

int row1 = 75;
int row2 = 100;
int row3 = 125;
int row4 = 150;
int row5 = 175;
int row6 = 200;
int row7 = 225;
int row8 = 250;
int row9 = 275;

//----------------------------------------------------------------------------
//----------------- Wifi Settings --------------------------------------------

// Change the credentials below, so your ESP8266 connects to your router
const char * ssid = "**REPLACE_WITH_SSID**";       // your WLAN ssid
const char * password = "**REPLACE_WITH_PASSS**"; // your WLAN password

//Alt Wifi
const char* ssid2 = "**REPLACE_WITH_SSID**";
const char* password2 = "**REPLACE_WITH_PASS**";

// Change the variable to your Raspberry Pi IP address, so it connects to your MQTT broker
#define mqtt_server "**REPLACE_WITH_MQTTSERVER**"
#define mqtt_user "**REPLACE_WITH_USER**"
#define mqtt_password "**REPLACE_WITH_PASS**"


//----------------- Wifi Settings --------------------------------------------
//----------------------------------------------------------------------------

WiFiClient espClient;
PubSubClient client(espClient);
AsyncWebServer server(80);

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");

  pinMode(DisplayOnPin, INPUT_PULLUP);
  pinMode(PageSelectPin, INPUT_PULLUP);
  rtc_gpio_pullup_en(GPIO_NUM_15);
  rtc_gpio_pulldown_dis(GPIO_NUM_15);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_15,0);

  display.init(115200); // enable diagnostic output on Serial
  drawBooting();
  display.update();
  display.powerDown();
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  //Setup OTA
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
  request->send(200, "text/plain", "Hi! I am ESP32. For OTA update, go to: xxx.xxx.xxx.xxx/update");
  });
  AsyncElegantOTA.begin(&server);    // Start ElegantOTA
  server.begin();
  Serial.println("HTTP server started");

  PageSelectState = digitalRead(PageSelectPin);

  //Prepare text and then draw it to the display!
  drawStarted();
  display.update();
  display.powerDown();

  Serial.println("setup done");
}

void loop() {
    if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
    client.connect("EInk_Display");

  DisplayOnPinState = digitalRead(DisplayOnPin);
  if(DisplayOnPinState != DisplayOnState)
    {
      DisplayOnState = DisplayOnPinState;
      if(DisplayOnState == 0)
      {
        createLayout();
        display.update();
        display.powerDown();
      }
      else
      {
        display.fillScreen(GxEPD_WHITE);
        display.update();
        display.powerDown();
        esp_deep_sleep_start();
      }
    }

  PageSelectPinState = digitalRead(PageSelectPin);
  if(PageSelectPinState != PageSelectState)
    {
      Serial.print("Page Select, new mode before: ");
      Serial.println(PageSelectState);
      PageSelectState = PageSelectPinState;
      createLayout();
      display.update();
      display.powerDown();
      Serial.print("Page Select, new mode after: ");
      Serial.println(PageSelectState);
    }
  }

const char Started[] = "Started!";
const char Booting[] = "Booting...";
const char Waiting[] = "Waiting for first message...";

void drawBooting()
{
  display.setRotation(0);
  display.setFont(&FreeMonoBold24pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(Booting, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center bounding box by transposition of origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.fillScreen(GxEPD_WHITE);
  display.setCursor(x, y);
  display.println(Booting);
  display.setFont(&FreeSansBold9pt7b);
  display.setCursor(5, 290);
  display.print("Compiled: " __DATE__ ", " __TIME__);
  

  display.drawBitmap(sealine_logo, 2, 2, 110, 40, GxEPD_BLACK);
}

void drawStarted()
{
  display.setRotation(0);
  display.setFont(&FreeMonoBold24pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(Started, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center bounding box by transposition of origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.fillScreen(GxEPD_WHITE);
  display.setCursor(x, y);
  display.println(Started);

  display.setFont(&FreeSansBold9pt7b);
  display.getTextBounds(Waiting, 0, 0, &tbx, &tby, &tbw, &tbh);
  x = ((display.width() - tbw) / 2) - tbx;
  y = (((display.height() - tbh) / 2) - tby) + 50;
  display.setCursor(x, y);
  display.println(Waiting);
  
  display.setFont(&FreeSans9pt7b);
  display.setCursor(270, 20);;
  display.println(WiFi.localIP());

  display.drawBitmap(sealine_logo, 2, 2, 110, 40, GxEPD_BLACK);

  display.setCursor(270, 40);
  display.print("Page:");
  display.setCursor(346, 40);
  if(PageSelectState == 0)
  {
    display.print("1");
  }
  else
  {
    display.print("2");
  }
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// This functions is executed when some device publishes a message to a topic that your ESP32 is subscribed to
// Change the function below to add logic to your program, so when a device publishes a message to a topic that 
// your ESP32 is subscribed you can actually do something

 void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  String tempTopic = String(topic);
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  
  int index = messageTemp.indexOf(';');
  int totallength = messageTemp.length();

  //Search for column/row data
  extractData(tempTopic,messageTemp);
 
  if(String(topic)=="eink/update"){
      Serial.print("Update Received ");
      latestUpdate = messageTemp;
      createLayout();
      display.update();
      display.powerDown();
      
  } 
  if(String(topic)=="eink/clear"){
      Serial.print("Update Recieved ");
      if(messageTemp == "clear"){
          display.fillScreen(GxEPD_WHITE);
          display.update();
          display.powerDown();
      }
  }
  Serial.println();
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// This functions reconnects your ESP32 to your MQTT broker
// Change the function below if you want to subscribe to more topics with your ESP32

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect

    //Use if no User + Password:    if (client.connect("EInk_Display")) {
    if (client.connect("EInk_Display", mqtt_user, mqtt_password)) {
      Serial.println("connected");  
      // Subscribe or resubscribe to a topic
	  
      // All topics for Page 1
      client.subscribe("eink/update");
      client.subscribe("eink/clear");
      client.subscribe("eink/c1r1");
      client.subscribe("eink/c2r1");
      client.subscribe("eink/c3r1");
      client.subscribe("eink/c4r1");
      client.subscribe("eink/c1r2");
      client.subscribe("eink/c2r2");
      client.subscribe("eink/c3r2");
      client.subscribe("eink/c4r2");
      client.subscribe("eink/c1r3");
      client.subscribe("eink/c2r3");
      client.subscribe("eink/c3r3");
      client.subscribe("eink/c4r3");
      client.subscribe("eink/c1r4");
      client.subscribe("eink/c2r4");
      client.subscribe("eink/c3r4");
      client.subscribe("eink/c4r4");
      client.subscribe("eink/c1r5");
      client.subscribe("eink/c2r5");
      client.subscribe("eink/c3r5");
      client.subscribe("eink/c4r5");
      client.subscribe("eink/c1r6");
      client.subscribe("eink/c2r6");
      client.subscribe("eink/c3r6");
      client.subscribe("eink/c4r6");
      client.subscribe("eink/c1r7");
      client.subscribe("eink/c2r7");
      client.subscribe("eink/c3r7");
      client.subscribe("eink/c4r7");
      client.subscribe("eink/c1r8");
      client.subscribe("eink/c2r8");
      client.subscribe("eink/c3r8");
      client.subscribe("eink/c4r8");
      client.subscribe("eink/c1r9");
      client.subscribe("eink/c2r9");
      client.subscribe("eink/c3r9");
      client.subscribe("eink/c4r9");

	  
	  // All topics for Page 2
	  client.subscribe("eink/p2c1r1");
      client.subscribe("eink/p2c2r1");
      client.subscribe("eink/p2c3r1");
      client.subscribe("eink/p2c4r1");
      client.subscribe("eink/p2c1r2");
      client.subscribe("eink/p2c2r2");
      client.subscribe("eink/p2c3r2");
      client.subscribe("eink/p2c4r2");
      client.subscribe("eink/p2c1r3");
      client.subscribe("eink/p2c2r3");
      client.subscribe("eink/p2c3r3");
      client.subscribe("eink/p2c4r3");
      client.subscribe("eink/p2c1r4");
      client.subscribe("eink/p2c2r4");
      client.subscribe("eink/p2c3r4");
      client.subscribe("eink/p2c4r4");
      client.subscribe("eink/p2c1r5");
      client.subscribe("eink/p2c2r5");
      client.subscribe("eink/p2c3r5");
      client.subscribe("eink/p2c4r5");
      client.subscribe("eink/p2c1r6");
      client.subscribe("eink/p2c2r6");
      client.subscribe("eink/p2c3r6");
      client.subscribe("eink/p2c4r6");
      client.subscribe("eink/p2c1r7");
      client.subscribe("eink/p2c2r7");
      client.subscribe("eink/p2c3r7");
      client.subscribe("eink/p2c4r7");
      client.subscribe("eink/p2c1r8");
      client.subscribe("eink/p2c2r8");
      client.subscribe("eink/p2c3r8");
      client.subscribe("eink/p2c4r8");
      client.subscribe("eink/p2c1r9");
      client.subscribe("eink/p2c2r9");
      client.subscribe("eink/p2c3r9");
      client.subscribe("eink/p2c4r9");

      // All topics for Column and row settings
      client.subscribe("eink/col1");
      client.subscribe("eink/col2");
      client.subscribe("eink/col3");
      client.subscribe("eink/col4");
      client.subscribe("eink/row1");
      client.subscribe("eink/row2");
      client.subscribe("eink/row3");
      client.subscribe("eink/row4");
      client.subscribe("eink/row5");
      client.subscribe("eink/row6");
      client.subscribe("eink/row7");
      client.subscribe("eink/row8");            
      client.subscribe("eink/row9");            

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void setup_wifi() {
  int index = 0;
  bool failed = false;
  delay(20);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED && failed == false)  {
    index = index + 1;
    delay(500);
    Serial.print(".");
    if (index > 20)
    {
      failed = true;
    }
  }
  //IF WiFi Fails to connect, try alt SSID
  if(failed == true)
  {
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println(" failed, trying secondary SSID");
    Serial.print("Connecting to ");
    Serial.println(ssid2);
    WiFi.begin(ssid2, password2);
    while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
    }
  }
  Serial.println("");
  Serial.print("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());
}
