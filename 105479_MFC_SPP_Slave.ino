char Station = '1' ; // 1 2 3
String inputString = "" ;        
boolean stringComplete = false ; 

#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 rfid(SS_PIN, RST_PIN);

const int CardNum0 = 0xE7 ; // 0xE7 0x5A 0xA7
const int CardNum1 = 0xFA ; // 0xFA 0x66 0x78
const int CardNum2 = 0x74 ; // 0x74 0xDE 0x9A
const int CardNum3 = 0x33 ; // 0x33 0x3F 0x60

bool Check_CardFound  ;
bool Check_CardSerNum ;
bool Command = false ;
bool Pick = false ;
byte State ;

#define LED_R 4
#define LED_G 5

void setup() 
{ 
  Serial.begin(9600);
  inputString.reserve(200);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(LED_R,OUTPUT);
  pinMode(LED_G,OUTPUT);
  digitalWrite(LED_R,HIGH);
  digitalWrite(LED_G,HIGH);
}
 
void loop() 
{ 
  RFID_READ();
  CHECK_CARD();
  DATA_TRANSFER();
  OUTPUT_ACTION();
}

void serialEvent() 
{ 
  while (Serial.available()) 
  {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n') 
    {
      stringComplete = true;
    }
  }
}

void RFID_READ()
{
  if(rfid.PICC_IsNewCardPresent()) 
  {
    Check_CardFound = true ;
    
    if(rfid.PICC_ReadCardSerial()) 
    {
      if( (rfid.uid.uidByte[0] == CardNum0)&&
          (rfid.uid.uidByte[1] == CardNum1)&&
          (rfid.uid.uidByte[2] == CardNum2)&&
          (rfid.uid.uidByte[3] == CardNum3) )
      {
        Check_CardSerNum = true ;
      }

      else
      {
        Check_CardSerNum = false ;
      }
    }
  }
  
  else if(!rfid.PICC_IsNewCardPresent())
  {
    Check_CardFound = false ;
  }
}

void CHECK_CARD()
{
  if(Command == false)
  {
    if     ((Check_CardFound==true)&&(Check_CardSerNum == true )) {State = 1 ;}
    else if((Check_CardFound==true)&&(Check_CardSerNum == false)) {State = 2 ;}
    else if(Check_CardFound==false)                               {State = 3 ;}
  }

  else if(Command == true)
  {
    if((Check_CardFound==true)&&(Check_CardSerNum == true )&&(Pick == false))
    {
      State = 4 ;    
    }

    else if(Check_CardFound==false) 
    {
      State = 5 ; 
      Pick = true ;
    }

    else if((Check_CardFound==true)&&(Check_CardSerNum == false)&&(Pick == true))
    {
      State = 2 ;
    }

    else if((Check_CardFound==true)&&(Check_CardSerNum == true )&&(Pick == true))
    {
      State = 6 ; OUTPUT_ACTION();
      delay(500) ;
      State = 1 ;
      Pick = false ;
      Command = false ;
    }
  }
  
}

void DATA_TRANSFER()
{
  if(stringComplete) 
  {
    if((inputString.charAt(0)=='@')&&((inputString.charAt(1)==Station)))
    {
      Command = true ; 
    }
       
    inputString = "";
    stringComplete = false;
    Serial.flush();
  }
}
void OUTPUT_ACTION()
{
  switch(State)
  {
    case 1 : digitalWrite(LED_R,HIGH); digitalWrite(LED_G,HIGH); break; // สภาวะปกติ : มีการ์ดถูก
    case 2 : digitalWrite(LED_R,LOW ); digitalWrite(LED_G,HIGH); break; // สภาวะปกติ : มีการ์ดผิด
    case 3 : digitalWrite(LED_R,LOW ); digitalWrite(LED_G,HIGH); break; // สภาวะปกติ : ไม่มีมีการ์ด
    case 4 : digitalWrite(LED_R,HIGH); digitalWrite(LED_G,LOW ); break; // สภาวะทำงาน : มีการ์ดถูก
    case 5 : digitalWrite(LED_R,HIGH); digitalWrite(LED_G,HIGH); break; // สภาวะทำงาน : ไม่มีการ์ด
    case 6 : digitalWrite(LED_R,LOW ); digitalWrite(LED_G,LOW ); break; // สภาวะพิเศษ  : คืนการ์ด 
  }
}
