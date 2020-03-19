#include "Controller.h"
#include "Board.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <StandardView.h>

int main(int argc, char** argv) {
  BattleShip::Controller controller=BattleShip::Controller();
  if(argc>=2&&argc<=3){
      if(argc==3){
          controller.setupGame(argv[1],atoi(argv[2]));
      }
      else if(argc==2){
          controller.setupGame(argv[1]);
      }
      controller.playGame();
  }
  else{
      std::cout<<"Not enough arguments, terminating game..."<<std::endl;
  }
  return 0;
}
