//
// Created by mfbut on 3/10/2019.
//

#include <stdexcept>
#include "Cell.h"

char BattleShip::Cell::getContents() const {
    return contents;
}

void BattleShip::Cell::setContents(char contents){
    this->contents=contents;
}

bool BattleShip::Cell::HasBeenFiredAt() const {
    return firedAt;
}

void BattleShip::Cell::setHasBeenFiredAt(bool hasBeenFiredAt) {
    this->firedAt=hasBeenFiredAt;
}

bool BattleShip::Cell::containsShip() const {
    return (!(contents==hiddenMarker));
}

BattleShip::Cell::Cell(char contents):contents(contents),firedAt(false),hiddenMarker('*'),hitMarker('X'),missMarker('O'){}

char BattleShip::Cell::getContentsIfHidden() const {
    if(firedAt){
        return contents;
    }
    return hiddenMarker;
}

char BattleShip::Cell::getContentsIfVisible() const {
    return contents;
}

char BattleShip::Cell::getHitMarker() {
    return hitMarker;
}

char BattleShip::Cell::getMissMarker() {
    return missMarker;
}
