# Text Based Adventure
A text based adventure game

### Compile
`g++ -std=c++11 main.cc adventure.cc map.cc -o adventure`

### Run
`./adventure`

### Current Status
Move around a 3x3 grid interacting with monsters in various ways to increase stats

### TODO
* Change to NxN grid or a fixed grid of a much larger size
* Add certain tasks, quests, storyline, etc.
* Make a makefile

### Known bugs
 * Inventory does not work properly
 * Debug function FieldInfo() should take in adventure class as an argument rather than creating a new one
