// Avec ce script, Billy reconnait les couleurs de la boîte Pixy et affiche un message si la signature 2 est "au dessus" de la signature 1

#include <Pixy2.h>

// This is the main Pixy object 
Pixy2 pixy;

int redLed = 7;
int greenLed = 8;

int lampButtonPin = 2;
int lampState = 0;

void setup()
{
    Serial.begin(115200);
    Serial.print("Demarrage...\n");
  
    pinMode(lampButtonPin, INPUT);
    pinMode(redLed, OUTPUT);
    pinMode(greenLed, OUTPUT);
    
    pixy.init();
}

void loop()
{ 
    int i; 
    // grab blocks!
    pixy.ccc.getBlocks();

    /*
    // If there are detect blocks, print them!
    if (pixy.ccc.numBlocks && 0)
    {
      Serial.print("Detected ");
      Serial.println(pixy.ccc.numBlocks);
      for (i=0; i<pixy.ccc.numBlocks; i++)
      {
        Serial.print("  block ");
        Serial.print(i);
        Serial.print(": ");
        pixy.ccc.blocks[i].print();
      }
    }  */
    if (pixy.ccc.numBlocks == 2 && pixy.ccc.blocks[0].m_signature == 1 && pixy.ccc.blocks[1].m_signature == 2)// Pixy détecte les signatures 1 et 2
    {
        if(pixy.ccc.blocks[0].m_x < pixy.ccc.blocks[1].m_x)
        {
            Serial.print("vert à droite\n");
            digitalWrite(greenLed, HIGH);            
            digitalWrite(redLed, LOW);             

            
  
        }
        else{
            Serial.print("vert à gauche\n"); 
            digitalWrite(redLed, HIGH);             
            digitalWrite(greenLed, LOW);

        }

       
    }
    delay(100);
  
    lampState = digitalRead(lampButtonPin);
    pixy.setLamp(lampState, 0);
  
    
}
