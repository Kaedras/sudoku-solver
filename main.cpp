#include <iostream>

using namespace std;

bool valid(int a[9][9], int val, int posY, int posX) {
  // check current column
  for (int i = 0; i < 9; i++) {
    if (a[i][posX] == val) {
      return false;
    }
  }

  // check current row
  for (int i = 0; i < 9; i++) {
    if (a[posY][i] == val) {
      return false;
    }
  }
  // check current subgrid
  int maxY, maxX;
  switch (posX) {
  case 0:
  case 1:
  case 2:
    if (posY <= 2) {
      maxY = 2;
      maxX = 2;
    } else if (posY <= 5) {
      maxY = 5;
      maxX = 2;
    } else if (posY <= 8) {
      maxY = 8;
      maxX = 2;
    }
    break;
  case 3:
  case 4:
  case 5:
    if (posY <= 2) {
      maxY = 2;
      maxX = 5;
    } else if (posY <= 5) {
      maxY = 5;
      maxX = 5;
    } else if (posY <= 8) {
      maxY = 8;
      maxX = 5;
    }
    break;
  case 6:
  case 7:
  case 8:
    if (posY <= 2) {
      maxY = 2;
      maxX = 8;
    } else if (posY <= 5) {
      maxY = 5;
      maxX = 8;
    } else if (posY <= 8) {
      maxY = 8;
      maxX = 8;
    }
    break;
  default:
    cerr << "invalid subgrid!" << endl;
    return false;
  }

  for (int i = maxY - 2; i <= maxY; i++) {
    for (int j = maxX - 2; j <= maxX; j++) {
      if (a[i][j] == val)
        return false;
    }
  }
  return true;
}

bool solve(int a[9][9], int posY, int posX) {
  if (posY == 8 && posX == 8) { // done
    return true;
  }
  int val = 0;
  if (a[posY][posX] == 0) { // empty field
    for (int i = 1; i <= 9; i++) {
      if (valid(a, i, posY, posX)) {
        val = i;
        a[posY][posX] = val;
        if (posY < 8 && posX == 8) { // end of row
          if (!solve(a, posY + 1, 0)) {
            val = 0;
            a[posY][posX] = 0;
          }
        } else {
          if (!solve(a, posY, posX + 1)) {
            val = 0;
            a[posY][posX] = 0;
          }
        }
      }
    }
    if (val == 0) {
      return false;
    }
  } else {                       // prefilled field
    if (posY < 8 && posX == 8) { // end of row
      if (!solve(a, posY + 1, 0)) {
        return false;
      }
    } else if (posY == 8 && posX == 8) { // done
      return true;
    } else {
      if (!solve(a, posY, posX + 1)) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  int sudoku[9][9] = {{0, 2, 0, 0, 0, 0, 0, 9, 0}, {0, 0, 0, 7, 0, 4, 0, 0, 0},
                      {0, 0, 1, 0, 3, 0, 8, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {6, 0, 0, 9, 0, 1, 0, 0, 3}, {3, 0, 9, 4, 0, 2, 7, 0, 6},
                      {0, 0, 2, 0, 0, 0, 5, 0, 0}, {0, 6, 0, 8, 7, 3, 0, 4, 0},
                      {8, 0, 0, 0, 2, 0, 0, 0, 1}};

  solve(sudoku, 0, 0);
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      cout << sudoku[i][j] << " ";
    }
    cout << endl;
  }

  return 0;
}
