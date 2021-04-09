String inputString = "" ;        
boolean stringComplete = false ; 

#include <SPI.h>
#include <RFID.h>
#define SS_PIN 10
#define RST_PIN 9
RFID rfid(SS_PIN, RST_PIN); 

int ReadNum0 ;
int ReadNum1 ;
int ReadNum2 ;
int ReadNum3 ;
int ReadNum4 ;

const int CardStation[3][5] = {{0xE7,0xFA,0x74,0x33,0x5A} ,
                               {0x5A,0x66,0xDE,0x3F,0xDD} ,
                               {0xA7,0x78,0x9A,0x60,0x25} } ;

bool Check_CardFound  ;
bool Check_CardSerNum ;
byte Command = 4 ;
byte State ;

#define LED_R 4
#define LED_G 5

void setup()
{ 
  Serial.begin(9600);
  inputString.reserve(200);
  SPI.begin(); 
  rfid.init();

  pinMode(LED_R,OUTPUT);
  pinMode(LED_G,OUTPUT);
  digitalWrite(LED_R,HIGH);
  digitalWrite(LED_G,HIGH);
}

void loop()
{
  DATA_TRANSFER();
  RFID_READ();
  CHECK_CARD();
  OUTPUT_ACTION();
}

void serialEvent() 
{ 
  while(Serial.available()) 
  {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n') 
    {
      stringComplete = true;
    }
  }
}

void DATA_TRANSFER()
{
  if(stringComplete) 
  {
    if((inputString.charAt(0)=='@')&&((inputString.charAt(1)=='1')))
    {
      Command = 0 ; 
    }

    else if((inputString.charAt(0)=='@')&&((inputString.charAt(1)=='2')))
    {
      Command = 1 ; 
    }

    else if((inputString.charAt(0)=='@')&&((inputString.charAt(1)=='3')))
    {
      Command = 2 ; 
    }
       
    inputString = "";
    stringComplete = false;
    Serial.flush();
  }
}

void RFID_READ()
{
  if(rfid.isCard()) 
  {
    Check_CardFound = true ;
    
    if(rfid.readCardSerial()) 
    {
      ReadNum0 = rfid.serNum[0];
      ReadNum1 = rfid.serNum[1];
      ReadNum2 = rfid.serNum[2];
      ReadNum3 = rfid.serNum[3];
      ReadNum4 = rfid.serNum[4];
    }
  }

  else
  {
    Check_CardFound = false ;
  }
  
  rfid.halt();
}

void CHECK_CARD()
{
  if(Check_CardFound == true)
  {
    if( (CardStation[Command][0] == ReadNum0) &&
        (CardStation[Command][1] == ReadNum1) &&
        (CardStation[Command][2] == ReadNum2) &&
        (CardStation[Command][3] == ReadNum3) &&
        (CardStation[Command][4] == ReadNum4)  )
    {
      State = 1 ;
    }

    else
    {
      State = 2 ;
    }
  }
  
  else if(Check_CardFound == false)
  {
    State = 3 ;
  } 
}

void OUTPUT_ACTION()
{
  switch(State)
  {
    case 1 : digitalWrite(LED_R,HIGH); digitalWrite(LED_G,LOW ); break; // สภาวะปกติ : มีการ์ดถูก
    case 2 : digitalWrite(LED_R,LOW ); digitalWrite(LED_G,HIGH); break; // สภาวะปกติ : มีการ์ดผิด
    case 3 : digitalWrite(LED_R,HIGH); digitalWrite(LED_G,HIGH); break; // สภาวะปกติ : ไม่มีมีการ์ด
  }
}
