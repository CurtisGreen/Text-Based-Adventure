#ifndef ADVENTURE_H
#include "adventure.h"
#endif

#ifndef MAP_H
#include "map.h"
#endif

//Constructor
Adventurous::Adventurous( std::string nm ){
    inventory = 0;
    trapped.resize(7);
    items.resize(10);
    peace.resize( 7 );
    for ( int i = 0; i < peace.size(); i++ )
	    peace[i] = 0;
    std::cout << "Creating your character..." << std::endl;
    name = nm;
    DetermineStats();
    std::cout << "Agility = " << agility << " strength = " << strength << " health = " << stamina << " charisma = " << charisma <<" intellect = " << intellect << std::endl;
    
    // create map
    std::cout << "\nCreating map..." << std::endl;
    Map mapp;
    map = mapp; 
    RunGame();
}

//Create player stats
void Adventurous:: DetermineStats(){
    
    srand ( time(NULL) );
    int total = 0;
    while ( total != 50 ){ //Update to new code
        agility = rand() % 20 + 1;
        strength = rand() % 20 + 1;
        stamina = rand() % 20 + 1;
        charisma = rand() % 20 + 1;
        intellect = rand() % 20 + 1;
        total = agility + strength + stamina + charisma + intellect;
    }
    if ( rand() % 100 >= 50) std::swap( agility, stamina );
    if ( rand() % 100 >= 50) std::swap( strength, charisma );
    if ( rand() % 100 >= 50) std::swap( stamina, intellect );
    if ( rand() % 100 >= 50) std::swap( charisma, agility );
    if ( rand() % 100 >= 50) std::swap( intellect, strength );
    health = stamina;
}

//Modifying stats
void Adventurous:: ChangeStats( int type, int stat ){
    double multiplier = double(type+1)/7;
    
    switch( stat ){
        case 1: 
            agility += 5 + double(agility) * multiplier * double(-1)/10;
            break;
        case 2: 
            strength += 5 + double(strength) * multiplier * double(-1)/10;
            break;
        case 3: 
            health = 5 + double(stamina) * multiplier * double(-1)/10;
            stamina += 5 + double(stamina) * multiplier * double(-1)/10;
            break;
        case 4: 
            charisma += 5 + double(charisma) * multiplier * double(-1)/10;
            break;
        case 5: 
            intellect += 5 + double(intellect) * multiplier * double(-1)/10;
            break;
    }
            
}

void Adventurous:: PrintStats(){
    std::cout << "Agility = " << agility << " strength = " << strength << " health = " << health << "/" << stamina << " charisma = " << charisma <<" intellect = " << intellect << std::endl;
}

//Input item or enemy and return their number
int Adventurous:: GetType( std::string tgt ){
    if ( tgt == "ogre" || tgt == "club" )
        return 1;
    else if ( tgt == "troll" || tgt == "sword" )
        return 2;
    else if ( tgt == "bear" || tgt == "claw" )
        return 3;
    else if ( tgt == "bandit" || tgt == "bandits" || tgt == "group of bandits" || tgt == "dagger" )
        return 4;
    else if ( tgt == "badger" || tgt == "heart" )
        return 5;
    else if ( tgt == "lemur" || tgt == "beach ball" || tgt == "ball" )
        return 6;
    else{
        std::cout << "No correct type found: " << tgt << std::endl;
        return 0;
    }
}

//Inventory
void Adventurous:: PrintInventory(){
    switch ( inventory ){
        case 1: std::cout << "You have a club." << std::endl;
            break;
        case 2: std::cout << "You have a sword." << std::endl;
            break;
        case 3: std::cout << "You have a claw." << std::endl;
            break;
        case 4: std::cout << "You have a dagger." << std::endl;
            break;
        case 5: std::cout << "You have a heart." << std::endl;
            break;
        case 6: std::cout << "You have a beach ball." << std::endl;
            break;
        default: std::cout << "Nothing is in your inventory" << std::endl;
    }
}

//Damage output
int Adventurous:: CalcDmg( std::string tgt ){
    int mtype;
    mtype = GetType( tgt );
    map.SetMhealth( mtype, map.GetMhealth()[mtype] - strength );
    if ( map.GetMhealth()[mtype] < 0 )
        map.SetMhealth( mtype, 0 );
    return mtype;
        
}

//Damage taking
void Adventurous:: PlayerDmg( std::string tgt, int dmg = 0 ){
    int mtype;
    if (dmg == 0){
        mtype = GetType( tgt );
        dmg =  7 - ( mtype );
    }
    if ( !trapped[mtype] ){
        health -= dmg;
        std::cout << "You take " << dmg << " damage. " << std::endl;
    }
    else{
        std::cout << "The " << tgt << " is trapped this turn so it cannot attack." << std::endl;
        trapped[mtype] = false;
    }
    std::cout << "You have  " << health << " health left." << std::endl;
    if ( health > 0){
        std::cout << "Congrats you didn't die!" << std::endl;
    }
        
}

//Attacking 
void Adventurous:: Attack( std::string tgt ){
    int mtype = GetType( tgt );
    if ( mtype > 0 && mtype == map.GetField()[map.GetX()][map.GetY()] && map.GetMhealth()[mtype] ){
        if ( peace[mtype] == true ){
	        char answer;
	        std::cout << "You are at peace with the " << tgt << ", are you sure you want to attack?" << std::endl;
	        std::cin >> answer;
	        std::cin.ignore(255,'\n' );
	       if ( answer == 'y' || answer == 'Y' ){
		       peace[mtype] = false;
		       Attack( tgt );
	        }
        }
        else{
            std::cout << "You attack the " << tgt << "!" << std::endl;
            int dtype = CalcDmg( tgt );
            if ( map.GetMhealth()[dtype] <= 0 ){
                std::cout << "You killed the " << tgt << "!" << std::endl;
                Drop( tgt );
                ChangeStats ( mtype, 2 );
                ChangeStats( mtype, 3 ); 
            }
            else{
                //std::cout << "You damaged the " << tgt << "!" << std::endl;
                std::cout << "The monster has " << map.GetMhealth()[mtype]  << " left." << std::endl;
                std::cout << "The " << tgt << " attacks back!" << std::endl;
                PlayerDmg( tgt );
                
            }
        }
    }
    else if ( map.GetMhealth()[GetType( tgt )] == 0 )
        std::cout << "Cannot attack the " << tgt << ". It is dead." << std::endl;
    else
        std::cout << "There is no " << tgt << "." << std::endl;
    /*
        ogre- 35
        troll- 30
        bear- 25
        bandit group- 20
        badger-15 
        lemur-10 
    */
    //Item drops
    /*
        bear- bear claw
        ogre- club
        troll- random (club, money, hat, bones, sword, cloak, sheep cloth)
        bandit group- random (sword, dagger, cloak, shoes, hat, armor, money)
        badger- heart of a badger
        lemur- random (rope, tent, canteen, beach ball)
    */
}

//Picking up items
void Adventurous:: PickUp( std::string tgt ){
    if ( tgt == "claw" || tgt == "club" || tgt == "sword" || tgt == "dagger" || tgt == "heart" || tgt == "beach ball" || tgt == "ball" ){
        if ( items[ map.GetField()[map.GetX()][map.GetY()] ] > 1 && inventory == 0 ){
            int numtgt;
            numtgt = GetType( tgt );
            inventory = items[numtgt];
            items[ map.GetField()[map.GetX()][map.GetY()] ] = 0;
            std::cout << "You picked up the " << tgt << std::endl;
        }
        else if ( items[ map.GetField()[map.GetX()][map.GetY()] ] > 1 && inventory > 0 ){
            char temp;
            std::cout << "You can only hold one item at a time, would you like to drop what you have currently?" << std::endl;
            std::cin >> temp;
            std::cin.ignore(255,'\n' );
            if ( temp == 'y' || temp == 'Y' ){
                int numtgt;
                numtgt = GetType( tgt );
                inventory = items[numtgt];
                items[ map.GetField()[map.GetX()][map.GetY()] ] = 0;
            }
        }
        else 
            std::cout << "There is no " << tgt << " here." << std::endl;
        
    }
    else{
        std::cout << tgt << " is not an item you can pick up." << std::endl;
    }
}

//Items
std::string Adventurous:: EnemyDrop( std::string tgt ){
    if ( tgt == "ogre" )
        return "club";
    else if ( tgt == "troll" )
        return "sword";
    else if ( tgt == "bandit" || tgt == "bandits" || tgt == "bandits group" )
        return "dagger";
    else if ( tgt == "badger" )
        return "heart";
    else if ( tgt == "lemur" )
        return "beach ball";
    else if ( tgt == "bear" )
         return "claw";
    else
        return tgt;
}

//Dropping items
void Adventurous:: Drop( std::string enemy ){
    std::string tgt = EnemyDrop( enemy );
    if ( tgt == "claw" || tgt == "club" || tgt == "sword" || tgt == "dagger" || tgt == "heart" || tgt == "beach ball" ){
        std::cout << "Dropped " << tgt << '.' << std::endl;
        int numtgt;
        numtgt = GetType( tgt );
        items[ map.GetField()[map.GetX()][map.GetY()] ] = numtgt;
    }
    else{
        std::cout << "This is not an item you can drop" << std::endl;
        std::cout << tgt << std::endl;
    }
}

//Trapping/stunning
void Adventurous:: Trap( std::string tgt ){
    int multiplyer, temptype, type;
    
        temptype = GetType( tgt );
        switch ( temptype ){
            case 1: type = 2;
                    multiplyer = 3.25;
                    break;
            case 2: type = 4;
                    multiplyer = 5.75;
                    break;
            case 3: type = 3;
                    multiplyer = 4;
                    break;
            case 4: type = 1;
                    multiplyer = 2.5;
                    break;
            case 5: type = 5;
                    multiplyer = 5.5;
                    break;
            case 6: type = 6;
                    multiplyer = 6.25;
                    break;
            default: 
                    std::cout << "unrecognized target for trapping." << std::endl;
        }
    if ( .6 * intellect * multiplyer >= rand() % 100 + 1 ){
        trapped[GetType( tgt )] = true;
        ChangeStats(type, 5);
        std::cout << "You successfully trapped the " << tgt << "." << std::endl;
    }
        
    else{
        std::cout << "You failed to trap the " << tgt << "." << std::endl;
        PlayerDmg( tgt );
    }
}

//Talking 
void Adventurous:: TalkTo( std::string tgt ){
	int type, temptype;

	temptype = GetType( tgt );
	if ( temptype > 0 && GetType( tgt ) == map.GetField()[map.GetX()][map.GetY()] && map.GetMhealth()[GetType( tgt )] ){
		switch ( temptype ){
			case 1: 
				type = 6;
				break;
			case 2:
				type = 5;
				break;
			case 3:
				type = 3;
				break;
			case 4:
				type = 4;
				break;
			case 5:
				type = 1;
				break;
			case 6:
				type = 2;
				break;
			default:
				std::cout << "There is no " << tgt << "." << std::endl;
		}
		if ( (rand() % 100 + 1) >  (type * .56 * charisma) ){
			std::cout << "The " << tgt << " is annoyed by you and attacks." << std::endl;
			PlayerDmg ( tgt );
		}
		else{
			if ( type == 1 ){
				std::cout << "The badger is quite impressed with your prose as well as your ability to speak with him. He suggests that tea is in order." << std::endl;
				std::cout << "You two sit down and chat for a while and drink tea as he marvels you with tales of his past bravery. " << std::endl;
				std::cout << "You both decide that due to your mutual respect you declare a truce and go on your way." << std::endl;
				Heal ( stamina - health );
			}
			else
				std::cout << "You and the " << tgt << " have a quaint talk about the important things in life and decide a truce is the best decision for both parties." << std::endl;
			peace[temptype] = true;
			ChangeStats ( type, 4 ); 
		}
	}
	else 
	    std::cout << "There is no " << tgt << "." << std::endl;
    /*
    Ogre 6
    Troll 5
    Bear 3
    Bandit 4
    Badger 1
    Lemur 2
    */
}

//Running away
void Adventurous:: Run( int tgt, std::string dir = "" ){
    int multiplyer;
    if ( tgt == 1)
        multiplyer = 2.5;
    else if ( tgt == 2 )
        multiplyer = 3.25;
    else if ( tgt == 3 )
        multiplyer = 4;
    else if ( tgt == 4 )
        multiplyer = 4.75;
    else if ( tgt == 5 )
        multiplyer = 5.5;
    else if ( tgt == 6 )
        multiplyer = 6.25;
    else
        std::cout << "unrecognized run target" << std::endl;
  
    if ( ((rand() % 100 + 1 ) <= multiplyer * agility ||  trapped[tgt] == true ) ){
        if ( dir == "north" || dir == "south" || dir == "east" || dir == "west" || dir == "up" || dir == "down" || dir == "left" || dir == "right" ){
            map.Move( dir );
            ChangeStats( tgt, 1 );
        }
        else{
            std::cout << "Run which direction?" << std::endl;
            std::string s;
            std::cin >>  s;
            std::cin.ignore(255,'\n' );
            map.Move( s );
            //trapped[tgt] = false;
            ChangeStats( tgt, 1 );
        }
            
    }
    else{
        std::cout << "You failed to run away." << std::endl;
        PlayerDmg( " ", 7 - ( tgt ) );
    }
    
    /*
        bear *2.50
        troll *3.25
        ogre *4
        bandit group *4.75
        lemur *5.50
        badger *6.25
    */
}

//Area text     
void Adventurous:: CheckArea(){
    switch ( map.GetField()[map.GetX()][map.GetY()] ){
        case 1:
            if ( map.GetMhealth()[1] > 5 )
                std::cout << "You see an ogre." << std::endl;
            else if ( map.GetMhealth()[1] == 0 )
                std::cout << "You see the dead body of an ogre." << std::endl;
            else
                std::cout << "You see an injured ogre." << std::endl;
            break;
        case 2: 
            if ( map.GetMhealth()[2] > 5 )
                std::cout << "You see a troll." << std::endl;
            else if ( map.GetMhealth()[2] == 0 )
                std::cout << "You see the dead body of a troll." << std::endl;
            else
                std::cout << "You see an injured troll." << std::endl;
            break;
        case 3: 
            if ( map.GetMhealth()[3] > 5 )
                std::cout << "You see a bear." << std::endl;
            else if ( map.GetMhealth()[3] == 0 )
                std::cout << "You see the dead body of a bear." << std::endl;
            else
                std::cout << "You see an injured bear." << std::endl;
            break;
        case 4:
            if ( map.GetMhealth()[4] > 5 )
                std::cout << "You see a group of bandits." << std::endl;
            else if ( map.GetMhealth()[4] == 0 )
                std::cout << "You see the dead body of a group of bandits." << std::endl; 
            else
                std::cout << "You see an injured group of bandits." << std::endl;
            break;
        case 5: 
            if ( map.GetMhealth()[5] >= 5 )
                std::cout << "You see a badger." << std::endl;
            else if ( map.GetMhealth()[5] == 0 )
                std::cout << "You see the dead body of a badger." << std::endl;
            else
                std::cout << "You see an injured badger." << std::endl;
            break;
        case 6:
            if ( map.GetMhealth()[6] > 5 )
                std::cout << "You see a lemur." << std::endl;
            else if ( map.GetMhealth()[6] == 0 )
                std::cout << "You see the dead body of a lemur." << std::endl;
            else
                std::cout << "You see an injured lemur." << std::endl;
            break;
        default:
            std::cout << "This area is empty " << std::endl;
    }       
}


//Healing
void Adventurous:: Heal( int amt = 2 ){
    health += amt;
    if ( health > stamina )
        health = stamina;
}

//Parsing input
void Adventurous:: DecypherText( std::string& command1, std::string& command2, std::string& fulltext ){
    std::string temp;
    int pos = fulltext.find( " " ) +1;
        if ( pos != 0 ) {           
            command1 = fulltext.substr( 0, fulltext.find(" ") );
            command2 = fulltext.substr( pos, fulltext.length() );
        }
        else{ 
            command1 = fulltext;
            command2 = " ";
        }
        pos = command2.find( " " ) + 1;
        if ( pos != 0 )
            temp = command2.substr( 0, pos -1 );
        if ( temp == "with" || temp == "to" || temp == "against" || temp == "the" || temp == "a" ) 
            command2 = command2.substr( pos, command2.length() );
        if ( temp == "up" ){
            command1 = command1 + temp;
            command2 = command2.substr( pos, command2.length() );
        }
            
        //std::cout << "com1 = " << command1 << " com2 = " << command2 << " pos = " << pos << " temp = " << temp << std::endl;
        
        std::transform( command1.begin(), command1.end(), command1.begin(), ::tolower);
        std::transform( command2.begin(), command2.end(), command2.begin(), ::tolower);
}


void Adventurous:: RunGame(){/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::string command1, command2, s;
    char chartemp;
    
    std::cout << '\n';
    CheckArea();
    std::cin.ignore( 255,'\n' );
    
    std::cout << "\n_______________________________________________" << std::endl;
    std::cout << "               " << name << "- ";
    
    while ( getline( std::cin, s ) && s != "quit" ){
        
        DecypherText( command1, command2, s ); 
        
        //Check if they only put the direction
        if ( command1 == "north" || command1 == "south" || command1 == "east" || command1 == "west" || command1 == "up" || command1 == "down" || command1 == "left" || command1 == "right" ){
            if ( atoi(command2.c_str()) > 1 ){
                std::cout << "Cannot move more than one space at a time. Would you still like to move " << command1 << "?" << std::endl;
                std::cin >> chartemp;
                std::cin.ignore( 255,'\n' );
                if ( chartemp == 'y' || chartemp == 'Y' ){
                    command2 = command1;
                    command1 = "move";
                }
            }
            else{ 
                command2 = command1;
                command1 = "move";
            }
        }   
        
        //Moving
        if ( command1 == "move" ){
            int mtype = map.GetField()[map.GetX()][map.GetY()];
            
            if ( !trapped[mtype] && map.GetMhealth()[mtype] > 0 ){
                std::cout << "Cannot move there is an enemy in this area." << std::endl;
                std::cout << "Do you want to try to run?" << std::endl;
                char s;
                std::cin >> s;
                std::cin.ignore( 255,'\n' );
                if ( s == 'Y' || s == 'y' ){
                    Run( map.GetField()[map.GetX()][map.GetY()], command2 );
                    CheckArea();
                    Heal();
                }
            }
            else{
                map.Move( command2 );
                CheckArea();
                Heal();
            }
        }
        
        //Attacking monsters   
        else if ( command1 == "attack" || command1 == "fight" || command1 == "hit" || command1 == "kill" || command1 == "punch"){
            if ( command2 == " " )
                std::cout << "Specify a target." << std::endl;
            else
                Attack( command2 );
        }
        
        //Running away
        else if ( command1 == "run" || command1 == "Run" ){
            int tempx = map.GetX();
            int tempy = map.GetY();
            Run (map.GetField()[map.GetX()][map.GetY()], command2 );
            if ( tempx != map.GetX() || tempy != map.GetY() ){
                CheckArea();
                Heal();
            }
        }
        
        //Trapping
        else if ( command1 == "trap" ){
            Trap( command2 );
        }
        
        //Dropping an item
        else if ( command1 == "drop" ){
            Drop( command2 );
        }
        
        //Picking up an item
        else if ( command1 == "pick up" || command1 == "pickup" || command1 == "pick-up" || command1 == "pick" ){
            PickUp( command2 );
        }
        
        //Printing out inventory
        else if ( command1 == "inventory" || command2 == "inventory" ){
            PrintInventory();
        }
        //Printing out stats
        else if ( command1 == "stats" || command2 == "stats" ){
            PrintStats();
        }
        
        //Talking
        else if ( command1 == "negotiate" ||  command1 == "talk" || command1 == "say" || command1 == "say hello to" || command1 == "persuade"  || command1 == "say hi" || command1 == "say hello" ){
            TalkTo ( command2 );
        }
        
        //They didn't specify an action
        else if ( command1 == "ogre" || command1 == "troll" || command1 == "bear" || command1 == "bandit" || command1 == "bandits" || command1 == "badger" || command1 == "lemur" )
            std::cout << "Specify an action." << std::endl;
        else
            std::cout << "You cannot do that" << std::endl;
            
        if ( health <= 0 ){
            std::cout << "You died :'(" << std::endl;
            break;
        }
            
    std::cout << "\n_______________________________________________" << std::endl;
    std::cout << "               " << name << "- ";
    }
}


