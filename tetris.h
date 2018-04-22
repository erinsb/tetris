class Shape {

  public:
    Shape(int shape[4][4]);
};

Shape::Shape(int shape[4][4]){
  
}


class Board {

  public:
    int x = 32;
    int y = 32;
    int board[x][y];
    Board();
};
