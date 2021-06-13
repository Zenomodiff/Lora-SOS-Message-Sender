/*feel free to contact
 * sreeramaj53@gmail.com
 * www.youtube.com/ZenoModiff
 * last updated - time 11:50am - date 12 may 2021
 */

#include <Wire.h> 
#include <SPI.h>
#include <LoRa.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int BUTTON1_PIN = 7;
const int BUTTON2_PIN = 4;
int CONVERTERBUTTON = 3;
int RED_LED = 5;
const int GREEN_LED =  8; 

int val = 0; 
int lightON = 0;
int pushed = 0;
int button1State = 0; 
int button2State = 0;
int Converter = 0;


void setup()
{
  Serial.begin(115200);

  lcd.begin();
  lcd.setCursor(0,0);
  lcd.print("LoRa SOS");
  lcd.setCursor(0,3);
  lcd.print("Device");
  delay(2000);
  lcd.clear();
  lcd.print("By");
  lcd.setCursor(0,3);
  lcd.print("Zeno Modiff");
  delay (2000);
  lcd.clear();
  
   while (!Serial);
 Serial.println("LoRa Sender");
 if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(CONVERTERBUTTON, INPUT_PULLUP);
}

void loop() 
{
  
  button1State = digitalRead(BUTTON1_PIN);
  button2State = digitalRead(BUTTON2_PIN);
  val = digitalRead(CONVERTERBUTTON);

   if(button1State == LOW) 
  {   
    digitalWrite(RED_LED, HIGH); 
    digitalWrite(GREEN_LED, LOW);  
    lcd.clear();
    lcd.print("Emergency !!");
    Serial.print("Emergency !!");
    Serial.println();
    LoRa.beginPacket();
    LoRa.print("Emergency !!");
    LoRa.endPacket();
    delay(3000);
      lcd.clear();
  }
  else                       
    digitalWrite(RED_LED, LOW); 
    digitalWrite(GREEN_LED, LOW);  

  if(button2State == LOW) 
  {   
    digitalWrite(RED_LED, HIGH); 
    digitalWrite(GREEN_LED, LOW);  
    Serial.print("Fire Detected !!");
    lcd.clear();
    lcd.print("Fire Detected !!");
    Serial.println();
    LoRa.beginPacket();
    LoRa.print("Fire Detected !!");
    LoRa.endPacket();
    delay(3000);
    lcd.clear();
  }
  else                       
    digitalWrite(RED_LED, LOW); 
    digitalWrite(GREEN_LED, LOW); 

  if(val == HIGH && lightON == LOW){

    pushed = 1-pushed;
    delay(100);
  }    

  lightON = val;

      if(pushed == HIGH){
        Serial.println("Reciever Mode ON");
        lcd.clear();
        lcd.print("Reciever ON");
        lcd.setCursor(0,1);
        lcd.print("Please Help");
        delay(500);
        digitalWrite(GREEN_LED, HIGH);  
        int packetSize = LoRa.parsePacket();
        Serial.println();
        Serial.print(packetSize);
        lcd.setCursor(0,1);
        lcd.print(packetSize);
        while (LoRa.available()) {
        Serial.print((char)LoRa.read());
    }     
      }
      else
      {
            Serial.println("Transmitter Mode ON");
            lcd.clear();
            lcd.print("Transmitter Mode");
            lcd.setCursor(0,1);
            lcd.print("      ON");
            delay(500);
            digitalWrite(RED_LED, HIGH);  
            LoRa.beginPacket();
            LoRa.print("Please Help-Emergency");
            LoRa.endPacket();
   
      }     
      }
