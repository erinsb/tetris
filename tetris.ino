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
#define WIDTH   11

int shape1[4][4] = {{1,1,0,0}, {1,1,0,0}}; //square
int shape2[4][4] = {{1,1,1,1}}; //I shape
int shape3[4][4] = {{1},{1},{1},{0,1}}; //L
int shape4[4][4] = {{1,1},{0,1},{0,1}}; //Z

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

class Shape {

  //int shapeMatrix[4][4];

  public:
    Shape(int shape[4][4]);
    //int shapeMatrix[4][4];
    
    void draw();
    void drop();
    void rotate();

    int startX = STARTX;
    int startY = STARTY;

  private:
    int shapeMatrix[4][4];
};

Shape::Shape(int shape[4][4]){

  for(int i=0; i<4; i++) {
    for(int j=0; j<4; j++){
      shapeMatrix[i][j] = shape[i][j];
    }
  };
 
  for(int i=0; i<4; i++) {
    for(int j=0; j<4; j++) {
      if(shapeMatrix[i][j] == 1) {
        matrix.drawPixel(i + startX, j + startY, matrix.Color333(7, 0, 3));
      }
    }
  };
  
};

void Shape::draw() {
  
    for(int i=0; i<4; i++) {
      for(int j=0; j<4; j++) {
        if(shapeMatrix[i][j] == 1) {
          matrix.drawPixel(i + startX, j + startY, matrix.Color333(7, 0, 3));
      }
    }
  }; 
}

void Shape::drop() {

  for(int i=0; i<4; i++) {
    for(int j=0; j<4; j++) {
      if(shapeMatrix[i][j] == 1) {
        matrix.drawPixel(i + startX, j + startY, matrix.Color333(0, 0, 0));
      }
    }
  }

  delay(50);
  startY++;
  
//   for(int i=0; i<4; i++) {
//    for(int j=0; j<4; j++) {
//      if(shapeMatrix[i][j] == 1) {
//        matrix.drawPixel(i, j + startY, matrix.Color333(7, 0, 3));
//      }
//    }
//  }
};

void Shape::rotate() {

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

//  for(int i=0; i<4; i++) {
//    for(int j=0; j<4; j++) {
//      if(shapeMatrix[i][j] == 1) {
//        matrix.drawPixel(i, j, matrix.Color333(7, 0, 3));
//      }
//    }
//  };
  
}


class Board {

  public:
    //static const int x = 11;
    //static const int y = 20;
    //int gameBoard[x][y];
    Board();

    void draw();

    int x = WIDTH;
    int y = LENGTH;
    
  private:
    int startX = STARTX;
    int startY = STARTY;

//  int x = WIDTH;
//  int y = LENGTH;
    int gameBoard[WIDTH][LENGTH] = {};
};

Board::Board() {};

void Board::draw() {
  matrix.drawLine(startX,startY,startX+x,startY, matrix.Color333(7, 7, 7));
  matrix.drawLine(startX-1+x,startY-1,startX+x,startY-1+y, matrix.Color333(7, 7, 7));
};


//Shape shapeTest(shape4);
Shape *shapeTest  = new Shape(shape3);
Board game;
//int gameBoard[WIDTH][LENGTH];


void setup() {

  //Serial.begin(9600);

  matrix.begin();
  //Serial.println("HERE");

  game.draw();

  shapeTest->draw();

  
  //delay(1000);
  // put your setup code here, to run once:

//  matrix.drawPixel(0, 0, matrix.Color333(7, 0, 3));
//  matrix.drawPixel(1, 0, matrix.Color333(7, 0, 3));
//  matrix.drawPixel(2, 0, matrix.Color333(7, 0, 3));
//  matrix.drawPixel(3, 0, matrix.Color333(7, 0, 3));
  

}


//int array shapes = [shape1, shape2, shape3, shape4];


void loop() {
  // put your main code here, to run repeatedly:
  delay(500);
  //Serial.println("HERE");
 
  shapeTest->rotate();
  shapeTest->drop();
  shapeTest->draw();



}




