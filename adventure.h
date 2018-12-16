
#ifndef ADVENTURE_H
#define ADVENTURE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <time.h>

#ifndef MAP_H
#include "map.h"
#endif

class Adventurous{

    public:
        Adventurous( std::string nm );
        
    //Helper functions
        void ChangeStats( int, int );
        int GetType( std::string tgt );
        
    //Commands
        int CalcDmg( std::string tgt );
        void PlayerDmg( std::string tgt, int );
        void Attack( std::string tgt );
        void PickUp( std::string tgt );
        std::string EnemyDrop( std::string tgt );
        void Drop( std::string tgt );
        void Trap( std::string tgt);
        void TalkTo( std::string tgt );
        void Run( int tgt, std::string dir);
        void CheckArea();
        void Heal( int );
        
    //Main game
        void DecypherText( std::string& command1, std::string& command2, std::string& fulltext );
        void RunGame();
        
    private:
        std::string name;
        Map map;
        
    //Stats (1-20 initially)
        int agility;
        int strength;
        int stamina;
        int charisma;
        int intellect;
        int health;
        void DetermineStats();
        
        std::vector<bool> trapped;
        
        std::vector<bool> peace;
        
    //Inventory
        enum itemlist { club = 1, sword, claw, dagger, heart, beach_ball };
        std::vector<int> items;
        int inventory;
        void PrintInventory();
        void PrintStats();
            
        /*
    Health
        ogre- 70
        troll- 60
        bear- 50
        bandit group- 40
        badger-30 
        lemur-20 
    Item drops
    
        bear- bear claw
        ogre- club
        troll- random (club, money, hat, bones, sword, cloak, sheep cloth)
        bandit group- random (sword, dagger, cloak, shoes, hat, armor, money)
        badger- heart of a badger
        lemur- random (rope, tent, canteen, beach ball)
        */
};
#endif //ADVENTURE_H