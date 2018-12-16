#ifndef ADVENTURE_H
#include "adventure.h"
#endif

#ifndef MAP_H
#include "map.h"
#endif


using namespace std;

int main() {
    string name;
    
    cout << "Adventure is out there!" << endl;
    cout << "Enter in your name: ";
    cin >> name;

    Adventurous adv(name);
}
