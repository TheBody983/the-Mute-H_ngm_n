// Avec ce script, Billy reconnait les couleurs de la boîte Pixy et affiche un message si la signature 2 est "au dessus" de la signature 1

#include <Pixy2.h>

// This is the main Pixy object 
Pixy2 pixy;

int redLed = 7;
int greenLed = 8;
int redLed2 = 12;
int greenLed2 = 13;

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
    pixy.changeProg("color_connected_components");

}

void loop()
{ 
    int i; 
    // grab blocks!
    pixy.ccc.getBlocks();

    /*
    // Affiche les blocs détectés 
    if (pixy.ccc.numBlocks)
    {
        Serial.print("Cycle :");
        for (i=0; i<pixy.ccc.numBlocks; i++)
        {
            Serial.println(pixy.ccc.numBlocks);
            for (i=0; i<pixy.ccc.numBlocks; i++)
            {
                Serial.print("  block ");
                Serial.print(i);
                Serial.print(": ");
                pixy.ccc.blocks[i].print();
            }
        }
    }
    */
    if (pixy.ccc.numBlocks == 1){
        if(pixy.ccc.blocks[0].m_signature == 2){
            digitalWrite(greenLed, HIGH);
            digitalWrite(redLed, LOW);
        }
        else if(pixy.ccc.blocks[0].m_signature == 1){
            digitalWrite(greenLed, LOW);
            digitalWrite(redLed, HIGH);
        }
        if(pixy.ccc.blocks[0].m_signature == 10){
            digitalWrite(greenLed, HIGH);
            digitalWrite(redLed, HIGH);
            if(pixy.ccc.blocks[0].m_angle < 90 && pixy.ccc.blocks[0].m_angle > -90){
                Serial.println("Vert à Gauche");
            }
            else{
                Serial.println("Vert à Droite");       
            }

            
        }

    }

    if (pixy.ccc.numBlocks == 2 && pixy.ccc.blocks[0].m_signature == 1 && pixy.ccc.blocks[1].m_signature == 2)// Pixy détecte les signatures 1 et 2
    {
        
        digitalWrite(greenLed, HIGH);
        digitalWrite(redLed, HIGH);
        /*
        if(pixy.ccc.blocks[0].m_x < pixy.ccc.blocks[1].m_x)
        {
            Serial.print("vert à droite\n");   
        }
        else{
            Serial.print("vert à gauche\n");
        }
        */
        
       
    }
    delay(100);
  
    lampState = digitalRead(lampButtonPin);
    pixy.setLamp(lampState, 0);
  
    
}
