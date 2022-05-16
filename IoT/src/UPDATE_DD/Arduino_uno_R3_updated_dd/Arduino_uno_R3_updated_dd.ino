#include <SPI.h> // SERIAL PERIPHERAL INTERFACE
#include <MFRC522.h> //RFID LIBRARY
#include <SoftwareSerial.h> // ARDUINO WITH ESP COMMUNICATION

SoftwareSerial Arduino_SoftSerial(2,3); //RX, TX Pin for software serial communication

/*Global variable for data storage in serial communication */

char Reg_c;
static String bufferStorage;

/* System Lights & Sound Configuration */

//#define Response_status 4
#define Rfid_status 5
#define Attendance_status 6
#define Internet_status 7
#define buzzerPin 8 


/*Rfid configuration */

#define SS_PIN 10 // SDA pin of rfid reader
#define RST_PIN 9 // Reset pin of rfid reader

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

static String Rfid_tag_ID= ""; // for storing read tag ID

void setup() {

/*Open Serial Communication (Arduino-PC) */
Serial.begin (9600);

/*Open Serial communication (Arduino-Esp8266) */
Arduino_SoftSerial.begin(9600);

/* Start RFID Reader to read RFID tags */

SPI.begin(); // Initiate SPI bus
mfrc522.PCD_Init(); // Initiate MFRC522

/* System start Indication */

Serial.println(" ");
Serial.println("RFID Reader is ready to scan cards…"); // we can change to LED/LCD Print
Serial.println(" ");

/*System lights & sound configuration */

pinMode(Attendance_status,OUTPUT);
digitalWrite(Attendance_status,LOW);

pinMode(Rfid_status,OUTPUT);
digitalWrite(Rfid_status,LOW);

pinMode(Internet_status,OUTPUT);
digitalWrite(Internet_status,LOW);

pinMode(buzzerPin,OUTPUT);
digitalWrite(buzzerPin,LOW);

//pinMode(Response_status ,OUTPUT);
//digitalWrite(Response_status ,LOW);

}
bool readTagId()
{
  //Serial.println("read tag id is running...");
  
  if(!mfrc522.PICC_IsNewCardPresent())
  {
    return false ;
  } // Look for new cards
  
  if(!mfrc522.PICC_ReadCardSerial())
  {
    return false;
  }   // Select one of the cards

  Serial.print("Read UID tag :"); // Show UID on serial monitor===Debug statement
  
  for(byte i = 0; i < mfrc522.uid.size; i++)
  {
    Rfid_tag_ID.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    Rfid_tag_ID.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
   Rfid_tag_ID.toUpperCase(); //Read ID Convert to upperCase 
   Serial.println(Rfid_tag_ID); //Debug statement

   if(Rfid_tag_ID!="")
   {
    return true;
   }
}

void sendTagId()
{
  Arduino_SoftSerial.print(Rfid_tag_ID + "\n" );
}

void GetResponseAboutID(String Response)
{ 
  Serial.println(" ");
  Serial.print("waiting for reponse from esp8266");

//  while(digitalRead(Response_status)!=HIGH)
//  {
//    Serial.print(".");
//    delay(1000);
//  }

  delay(5000);
  //digitalWrite(Response_status,LOW);
    
      Serial.println(" ");

      while(Arduino_SoftSerial.available() >0)
      {
          Reg_c= Arduino_SoftSerial.read();
          if(Reg_c=='\n')
          {
           break; 
          }
          else
          {
          bufferStorage+=Reg_c; 
          }
          
      }

    if(Reg_c=='\n')
    {
  
      Serial.println(String("Received Response from Esp8266 : "+bufferStorage));

      if(bufferStorage==Response)
      {
          digitalWrite(Attendance_status,HIGH);
          delay(3000);
          digitalWrite(Attendance_status,LOW);
      }
      else if(bufferStorage=="Invalid ID !")
      {
        // do nothing or we can put extra indicating light about invalid ID readed
         Serial.println(String("Received Response from Esp8266 : "+bufferStorage));
      }
      else
      {
        // here system is down !!!! we need to fix this ASAP !
      }
    }
    
  //Reset the buffer storage area
   Reg_c=0;
   bufferStorage="";
   Rfid_tag_ID="";
   
}

void loop() 
{

 while(digitalRead(Internet_status)==LOW)
 {
  if(readTagId())
  {
  sendTagId();
  GetResponseAboutID(String(Rfid_tag_ID+"==OK"));
  }
  else
  {
    Serial.println("Scan for New card…"); 
    delay(1000);
  }
 }
 
 
 if(digitalRead(Internet_status)==HIGH)
 {
  Serial.println("Esp8266:Internet service down !!! ");
 }

}
