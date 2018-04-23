#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

//#include "tetris.h"

#define CLK 11  // MUST be on PORTB! (Use pin 11 on Mega)
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

#define STARTX  12
#define STARTY  10
#define LENGTH  10
#define WIDTH   9


byte shape1[4][4] = {
                    {0,0,0,0},
                    {0,1,1,0},
                    {0,1,1,0},
                    {0,0,0,0}}; //square
byte shape2[4][4] = {
                    {0,0,0,0},
                    {1,1,1,1},
                    {0,0,0,0},
                    {0,0,0,0}}; //I shape
byte shape3[4][4] = {
                    {0,1,0,0},
                    {0,1,0,0},
                    {0,1,1,0},
                    {0,0,0,0}}; //L
byte shape4[4][4] = {
                    {0,0,0,0},
                    {1,1,0,0},
                    {0,1,1,0},
                    {0,0,0,0}}; //Z

//bool gameBoard[WIDTH][LENGTH];
byte gameBoard[LENGTH+1] = {0,0,0,0,0,0,0,0,0,0,B11111111};

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

void draw(byte shapeMatrix[4][4], int startX, int startY) {
  
    for(int i=0; i<4; i++) {
      for(int j=0; j<4; j++) {
        if(shapeMatrix[i][j] == 1) {
          matrix.drawPixel(i + startX, j + startY, matrix.Color333(7, 0, 3));
      }
    }
  }; 
}

void clearShape(byte shapeMatrix[4][4], int startX, int startY) {

  for(int i=0; i<4; i++) {
    for(int j=0; j<4; j++) {
      if(shapeMatrix[i][j] == 1) {
        matrix.drawPixel(i + startX, j + startY, matrix.Color333(0, 0, 0));
      }
    }
  }
};

void rotate(byte shapeMatrix[4][4], int startX, int startY) {

  if (startX+4 < STARTX + WIDTH and startY+4 < STARTY + LENGTH) {
//
//    for(int i=0; i<4; i++) {
//      for(int j=0; j<4; j++) {
//        if(shapeMatrix[i][j] == 1) {
//          matrix.drawPixel(i + startX, j + startY, matrix.Color333(0, 0, 0));
//        }
//      }
//    }
  
    // Transpose
    for (int i=0; i<4; i++) {
      for (int j=i; j<4; j++) {
        int temp = shapeMatrix[i][j];
        shapeMatrix[i][j] = shapeMatrix[j][i];
        shapeMatrix[j][i] = temp;
      }
    };
  
    // Reverse columns
    for (int i=0; i<4; i++) {
      for (int j=0, k=3; j<k; j++, k--) {
        int temp = shapeMatrix[j][i];
        shapeMatrix[j][i] = shapeMatrix[k][i];
        shapeMatrix[k][i] = temp;
      }
    };
  } else {
  }
}

void addShape(byte shape[4][4], int x, int y) {
  for (int i=0; i<4; i++) {
    for (int j=0; j<4; j++) {
      if (shape[i][j] == 1) {
        matrix.drawPixel(i + x, j + y, matrix.Color333(4, 0, 0));
       // Serial.println(i+x);
      byte mask = B10000000;
       gameBoard[j+y-STARTY] = (mask>>i+x-STARTX | gameBoard[j+y-STARTY]);
       //Serial.print(gameBoard[j+y]);
       //Serial.println(j+y-STARTY);
        //gameBoard[i+x-STARTX][j+y-STARTY] = 1;
        
      }
    }
  }
}

bool checkBoard(byte shape[4][4], int x, int y) {
   for (int i=0; i<4; i++) {
    for (int j=0; j<4; j++) {
      if (shape[i][j] == 1) {
        byte mask = B10000000;
        Serial.print("MASK ");
        Serial.println(mask>>i+x-STARTX);
        Serial.println(gameBoard[j+y-STARTY]);
        Serial.println(j+y-STARTY);
        Serial.println(gameBoard[j+y-STARTY] & (mask>>i+x-STARTX));
        if ((gameBoard[j+y-STARTY] | (mask>>i+x-STARTX) == 0) ){
          return false;
        }
      }
    }
  }
  return true;
}


void setup() {

  Serial.begin(9600);

  matrix.begin();

  matrix.drawLine(STARTX-1,STARTY+LENGTH,STARTX+WIDTH,STARTY+LENGTH, matrix.Color333(7,7,7));
  matrix.drawLine(STARTX-1,STARTY,STARTX-1,STARTY+LENGTH, matrix.Color333(7, 7, 7));
  matrix.drawLine(STARTX+WIDTH,STARTY,STARTX+WIDTH,STARTY+LENGTH, matrix.Color333(7, 7, 7));
  

}


//int array shapes = [shape1, shape2, shape3, shape4];


void loop() {
  int startX = STARTX;
  int startY = STARTY;
  int lastY = STARTY;
  int lastX = STARTX;
  // put your main code here, to run repeatedly:
  delay(500);
  //Serial.println("HERE");
  int shape[4][4];
  
  while (checkBoard(shape4, startX, startY)) {
    
    draw(shape4, startX, startY);
    delay(500);
    clearShape(shape4, startX, startY);
    
    rotate(shape4, startX, startY);
    delay(500);
    lastY = startY;
    lastX = startX;
    startY++;
    //Serial.println(startY);
  }
  //Serial.println(gameBoard);
  addShape(shape4, lastX, lastY);
  //gameBoard[0] = 1;
  Serial.println("HERE");
  



}




