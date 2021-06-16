#include <Pixy2.h>

// This is the main Pixy object 
Pixy2 pixy;

char lettrePrec = ' ';

bool GUESSING = false, GUESSED = true, state = false;

int cpt = 0;
int INDEX = 1, AURICULAIRE = 2, POUCE = 3;

void setup(){
    Serial.begin(115200);
      
    pixy.init();
    pixy.changeProg("color_connected_components");

}

char traiter(bool sig[8]){

    // Traitement du signal
    if(sig[POUCE]&&sig[INDEX]&&sig[AURICULAIRE]){
      return 'a';
    }
    if(sig[POUCE]&&!sig[INDEX]&&sig[AURICULAIRE]){
      return 'g'; // ou S
    }
    if(sig[POUCE]&&!sig[INDEX]&&!sig[AURICULAIRE]){
      return 't'; // ou I
    }
    if(!sig[POUCE]&&sig[INDEX]&&sig[AURICULAIRE]){
      return 'm'; // ou N
    }
    
    return ' ';
}

char getLettre(){
    char lettre = ' ';
    while(state == GUESSING){
        bool sig[8];
        for(int i = 0; i<8; i++){
            sig[i] = false;
        }
        
        // grab blocks!
        pixy.ccc.getBlocks();
    
        for(int i = 0; i<pixy.ccc.numBlocks; i++)sig[pixy.ccc.blocks[i].m_signature] == true;
    
        lettre = traiter(sig);
          
        lettrePrec == lettre? cpt++: cpt = 0;
        
        if(cpt>=5 && lettre != ' ') state = GUESSED;
    
        if(state)Serial.println(lettre);
    
        Serial.println(state);
        lettrePrec = lettre;
        delay(500);
    }
    return lettre;
}

void loop(){ 
    // console.log(getLettre());
    bool test[8] = {true, true, true, true, true, true, true, true};
    Serial.println(traiter(test) == 'a');
}
