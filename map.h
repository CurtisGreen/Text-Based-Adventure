
#ifndef MAP_H
#define MAP_H

class Map{
    public:
        Map();
        
        void Move( std::string dir );
        ////////////////////////////////////////////////////////
        
        void DispInfo( int );
        void SetField();
        std::vector <std::vector <int>> GetField();
        std::vector <int> GetMhealth(){ return mhealth;}
        void FieldInfo();                   //for debugging
        
        int GetX(){ return cur_x;}
        int GetY(){ return cur_y;}
        void SetMhealth( int a, int b ){ mhealth[a] = b;}
        
    private:
        std::vector <std::vector <int>> field;
        std::vector <int> mhealth;
        int cur_x;
        int cur_y;
};


#endif