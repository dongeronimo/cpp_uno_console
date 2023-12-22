#include <iostream>
#include "game_manager.h"
using namespace std;
using namespace MyUno;

int main(){
    GameManager::GetInstance().GameLoop();
    return 0;    
}