
#include <Adafruit_NeoPixel.h>

int pixelpin = 1;
int greenButton = 0;
int whiteButton = 2;

Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, pixelpin);

void setup() {
  // put your setup code here, to run once:
  pixel.begin();
  pixel.setPixelColor(0, 255,0,0);
  pixel.show();

  pinMode(greenButton, INPUT_PULLUP);
  pinMode(whiteButton, INPUT_PULLUP);

}

int greenState = HIGH;
int whiteState = HIGH;

int greenScore = 0;
int whiteScore = 0;

int competingTime = 10000;

int gameState = 0;

unsigned long startTime = 0;
void loop() {


  if(gameState == 0)
  {
    //vänta på knapptryck för att starta
    if(digitalRead(greenButton) == LOW || digitalRead(whiteButton) == LOW)
    {
      gameState = 1;
    }

  }
  else if(gameState == 1)
  {
     pixel.setPixelColor(0, 155,0,0);
     pixel.show();
     delay(1000);
     pixel.setPixelColor(0,155 ,155,51);
     pixel.show();
     delay(1000);
     pixel.setPixelColor(0,0,155,0);
     pixel.show();
     gameState = 2;


  }
  else if(gameState == 2)
  {
    //hur lång tid det gått sen vi startade
    startTime = millis();

    while( millis() - startTime < competingTime )
    {
      int greenNewState = digitalRead(greenButton);

      if( greenNewState != greenState)
      {
        greenState = greenNewState;
        greenScore++;
      }

      int whiteNewState = digitalRead(whiteButton);

      if( whiteNewState != whiteState)
      {
        whiteState = whiteNewState;
        whiteScore++;
      }
    }
    gameState = 3;
  }
  else if(gameState == 3)
  {
     pixel.setPixelColor(0, 255,0,0);
     pixel.show();
     delay(1000);
     if(whiteScore > greenScore)
     {
           pixel.setPixelColor(0, 155,155,155);
           pixel.show();
     }
     if(greenScore > whiteScore)
     {
            pixel.setPixelColor(0, 0,155,0);
            pixel.show();
     }

     if(greenScore == whiteScore)
     {
       pixel.setPixelColor(0, 0,0,155);
       pixel.show();
     }
     greenScore = 0;
     whiteScore = 0;
     gameState = 0;
  }


}

