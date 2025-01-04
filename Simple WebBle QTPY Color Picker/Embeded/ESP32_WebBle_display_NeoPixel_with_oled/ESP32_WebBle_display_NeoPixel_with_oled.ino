#include <Adafruit_SSD1327.h>
#define OLED_RESET -1
// I2C
Adafruit_SSD1327 display(128, 128, &Wire1, OLED_RESET, 1000000);
#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

///////////


#include <Adafruit_NeoPixel.h>
#define NUMPIXELS        1
Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);



const int buttonPin = 0; //MO
int buttonState = 0;  // variable for reading the pushbutton status



#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLEServer *pServer = NULL;
BLECharacteristic * pTxCharacteristic;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint8_t txValue = 0;

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"


class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};


class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    String rxValue = pCharacteristic->getValue();

    if (rxValue.length() > 0) {
      //Serial.println("*********");
      //Serial.print("Received Value: ");

      String rxv="";
      for (int i = 0; i < rxValue.length(); i++) {
        //Serial.print(rxValue[i]);
        rxv=rxv+rxValue[i];
      }


  display.clearDisplay();
  display.display();


    display.setCursor(0,0);

       display.setTextSize(2);
    display.setTextColor(SSD1327_WHITE);
    display.println(rxv);
    display.display();
      


  int i1 = rxv.indexOf(',');
  int i2 = rxv.indexOf(',', i1+1);
  
  //Serial.println(i1);
  //Serial.println(i2);

  String r = rxv.substring(0, i1);
  String g = rxv.substring(i1 + 1, i2);
  String b = rxv.substring(i2 + 1);

/*
  Serial.println(r);
  Serial.println(g);
  Serial.println(b);
*/

        pixels.setPixelColor(0, pixels.Color(r.toInt(), g.toInt(), b.toInt()));
        pixels.show();

      //Serial.println();
      //Serial.println("*********");
    }
  }
};


void setup() {
  Serial.begin(115200);
  
  
  pinMode(buttonPin, INPUT_PULLUP);


#if defined(NEOPIXEL_POWER)
  // If this board has a power control pin, we must set it to output and high
  // in order to enable the NeoPixels. We put this in an #if defined so it can
  // be reused for other boards without compilation errors
  pinMode(NEOPIXEL_POWER, OUTPUT);
  digitalWrite(NEOPIXEL_POWER, HIGH);
#endif

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(20); // not so bright






  // Create the BLE Device
  //BLEDevice::init("UART Service");
  BLEDevice::init("DKC BLE 1"); // bel name

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pTxCharacteristic = pService->createCharacteristic(
										CHARACTERISTIC_UUID_TX,
										BLECharacteristic::PROPERTY_NOTIFY
									);
                      
  pTxCharacteristic->addDescriptor(new BLE2902());

  BLECharacteristic * pRxCharacteristic = pService->createCharacteristic(
											 CHARACTERISTIC_UUID_RX,
											BLECharacteristic::PROPERTY_WRITE
										);

  pRxCharacteristic->setCallbacks(new MyCallbacks());

  // Start the service
  pService->start();

  // Start advertising
  pServer->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...");


// blinking white to show active
   pixels.setPixelColor(0, 55,55,55);
  pixels.show();
  delay(250);
  pixels.setPixelColor(0, 0,0,0);
  pixels.show();
  delay(250);
   pixels.setPixelColor(0, 55,55,55);
  pixels.show();
  delay(250);

  //oled stuff
  if ( ! display.begin(0x3D) ) {
     Serial.println("Unable to initialize OLED");
     while (1) yield();
  }
  display.clearDisplay();
  display.setRotation(1);
  display.display();

}

void loop() {


  buttonState = digitalRead(buttonPin);

/*
  if (buttonState == HIGH) {

        pixels.fill(0x00FF00);
        pixels.show();
  } else {

    //button  pressed
    pixels.fill(0x0000FF);
        pixels.show();
  }
  */


    if (deviceConnected) {
       /*
        pTxCharacteristic->setValue(&txValue, 1);
        pTxCharacteristic->notify();
        txValue++;
        */


        //pixels.fill(0x00FF00);
        //pixels.show();

        //uint8_t buf3[10]; 
        //String s3 = String("c");
        //s3.getBytes(buf3, sizeof(buf3));




        if (buttonState != HIGH){
          // use GND + GPIO 0 pin to triggger this
         
                uint8_t buf[4]; 
                String s1 = "Dan"; // sending string Dan
                s1.getBytes(buf, sizeof(buf));
                pTxCharacteristic->setValue(buf, 4);
                pTxCharacteristic->notify();

             

        }

		    delay(2); // bluetooth stack will go into congestion, if too many packets are sent
	}else{

    //not connected 

  display.clearDisplay();
  display.display();


    display.setCursor(0,0);
    

     display.setTextSize(2);
    display.setTextColor(SSD1327_WHITE);
    display.println("Waiting to connect ...");
    display.display();


        if (buttonState != HIGH){
          // use GND + GPIO 0 pin to triggger this
         
              pixels.setPixelColor(0, pixels.Color(0, 0, 255));
              pixels.show();
              delay(250);

              pixels.setPixelColor(0, pixels.Color(0, 0, 0));
              pixels.show();

        }

  }

    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        Serial.println("start advertising");
        oldDeviceConnected = deviceConnected;

        //pixels.fill(0xFF0000);
        //pixels.show();
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) {
		// do stuff here on connecting
        oldDeviceConnected = deviceConnected;
    }

   
}
