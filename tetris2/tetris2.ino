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
#define LENGTH  20
#define WIDTH   11

int shape1[4][4] = {{1,1,0,0}, {1,1,0,0}}; //square
int shape2[4][4] = {{1,1,1,1}}; //I shape
int shape3[4][4] = {{1},{1},{1},{0,1}}; //L
int shape4[4][4] = {{1,1},{0,1},{0,1}}; //Z
int gameBoard[WIDTH][LENGTH] = {};

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

void draw(int shapeMatrix[4][4], int startX, int startY) {
  
    for(int i=0; i<4; i++) {
      for(int j=0; j<4; j++) {
        if(shapeMatrix[i][j] == 1) {
          matrix.drawPixel(i + startX, j + startY, matrix.Color333(7, 0, 3));
      }
    }
  }; 
}

void clearShape(int shapeMatrix[4][4], int startX, int startY) {

  for(int i=0; i<4; i++) {
    for(int j=0; j<4; j++) {
      if(shapeMatrix[i][j] == 1) {
        matrix.drawPixel(i + startX, j + startY, matrix.Color333(0, 0, 0));
      }
    }
  }
};

void rotate(int shapeMatrix[4][4], int startX, int startY) {

  for(int i=0; i<4; i++) {
    for(int j=0; j<4; j++) {
      if(shapeMatrix[i][j] == 1) {
        matrix.drawPixel(i + startX, j + startY, matrix.Color333(0, 0, 0));
      }
    }
  }

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
  
}


void setup() {

  //Serial.begin(9600);

  matrix.begin();
  matrix.drawLine(STARTX-1,STARTY,STARTX-1,STARTY+LENGTH, matrix.Color333(7, 7, 7));
  matrix.drawLine(STARTX-2,STARTY,STARTX-2,STARTY+LENGTH, matrix.Color333(7, 7, 7));
  matrix.drawLine(STARTX+WIDTH,STARTY,STARTX+WIDTH,STARTY+LENGTH, matrix.Color333(7, 7, 7));
  matrix.drawLine(STARTX+WIDTH+1,STARTY,STARTX+WIDTH+1,STARTY+LENGTH, matrix.Color333(7, 7, 7));
  

}


//int array shapes = [shape1, shape2, shape3, shape4];


void loop() {
  int startX = STARTX;
  int startY = STARTY;
  // put your main code here, to run repeatedly:
  delay(500);
  //Serial.println("HERE");
  for (int i=0; i<10; i++) {

    draw(shape4, startX, startY);
    delay(500);
    clearShape(shape4, startX, startY);
    rotate(shape4, startX, startY);
    startY++;
  }



}




