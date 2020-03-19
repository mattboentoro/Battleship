//
// Created by mfbut on 3/10/2019.
//

#include <algorithm>
#include <stdexcept>
#include "ShipPlacement.h"

ShipPlacement::ShipPlacement(int rowStart, int colStart, int rowEnd, int colEnd):rowStart(rowStart),colStart(colStart),rowEnd(rowEnd),colEnd(colEnd) {

}

ShipPlacement::ShipPlacement():rowStart(0),colStart(0),rowEnd(0),colEnd(0) {

}
