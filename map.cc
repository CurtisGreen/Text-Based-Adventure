#ifndef ADVENTURE_H
#include "adventure.h"
#endif

#ifndef MAP_H
#include "map.h"
#endif



Map:: Map(){
    mhealth.resize(10);
    cur_x = 1;
    cur_y = 1;
    
    for (int i = 30; i > 5; i -= 5)
        mhealth[6 - (i/5)] = i;
    
    for (int i = 0; i < 9; i++)
        if (mhealth[i] <= 0)
            mhealth[i] = -1;
    
    int z = 1;
    std::vector <int> temp;
    
    for(int i = 0; i < 3; i++){
		for(int j = z; j < z+3; j++){
		    temp.push_back(j);
		}
		z += 3;
		field.push_back(temp);
		temp.clear();
	}
        
    SetField();
    //FieldInfo();
}

//Moving 
void Map:: Move(std::string dir){//////////////////////////////////////////////////////////////////////////////////////////////////////
    if (dir == "up" || dir == "north"){
        if (cur_y > 0)
            cur_y -= 1;
        else
            std::cout << "Cannot move " << dir << ", please enter a different command." << std::endl;
    }
    else if(dir == "right" || dir == "east"){
        if (cur_x < 2)
            cur_x += 1;
        else
            std::cout << "Cannot move " << dir << ", please enter a different command." << std::endl;
    }
    else if(dir == "down" || dir == "south"){
        if (cur_y < 2)
            cur_y += 1;
        else
            std::cout << "Cannot move " << dir << ", please enter a different command." << std::endl;
    }
    else if(dir == "left" || dir == "west"){
        if (cur_x > 0)
            cur_x -= 1;
        else
            std::cout << "Cannot move " << dir << ", please enter a different command." << std::endl;
    }
    else
        std::cout << "Unrecognized direction" << std::endl;
    
    //std::cout << "You are currently at " << cur_x << ", " << cur_y <<  " and the area type is " << field[cur_x][cur_y] << std::endl; //Bugtesting
}

void Map:: DispInfo(int i){         // Prints the scenario based on an int
    switch(i){
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6: 
        case 7:
        case 8:
        case 9:
        default: std::cout << "Not 1-9." << std::endl; ///////////////////////////////////////////////////////////////////////////////////////////////////////
    }
}

//Creates field
void Map:: SetField(){    // Sets the scenario based on random 1-9
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            int q = i + rand() / (RAND_MAX / (3 - i) + 1);
            int x = j + rand() / (RAND_MAX / (3 - j) + 1);
            int t = field[q][x];
            field[q][x] = field[i][j];
            field[i][j] = t;
        }
    }
}

std::vector <std::vector <int>> Map:: GetField(){     // Returns the 2D vector field
    return field;
}

//Shows field table 
//Problems because the map in adventure.h != the one constructed here
void Map:: FieldInfo(){
    std::cout << "\nField Info:" << std::endl;
    for (int i = 0; i < 3; i++){
        std::cout << "\n____________________________________________\n\n";
        for (int j = 0; j < 3; j++)
            std::cout << "|" << field[i][j] << "|";
    }
}


