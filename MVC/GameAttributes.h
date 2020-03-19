//
// Created by mfbut on 3/9/2019.
//

#ifndef BATTLESHIP_GAMEATTRIBUTES_H
#define BATTLESHIP_GAMEATTRIBUTES_H
#include <istream>
#include <map>
namespace BattleShip {
class GameAttributes {
 public:
  GameAttributes()= default;
  GameAttributes(int numRows, int numCols);

  int getNumRows() const;
  int getNumCols() const;
  void addShip(char ShipChar, int ShipSize);

  int getShipSize(const char ShipChar) const;
  const std::map<char, int>& getShipAttributes() const;

 private:
  int numRows, numCols;
  std::map<char, int> shipAttributes;
};

std::istream& operator>>(std::istream& in, GameAttributes& gameAttributes);

}
#endif //BATTLESHIP_GAMEATTRIBUTES_H
