/***********************************************************************
* FILENAME :        map.h
*
* DESCRIPTION :
*       Course: Advanced Programming Techniques for Engineering Applications (ECE-6122)
*       Term: 2022-Fall
*       Problem: Lab3
*
* PRIVSTE CLASSES :
*       Map
*          - Store map item, the position of pacman, ghosts, coins, and powerup
*          - Implement game algorithm
*
* NOTES :
*       Copyright Chun-wei Ho, 2022.  All rights reserved.
*
* AUTHOR :    Chun-wei Ho        START DATE :    22 Oct. 22
*
* CHANGES :
*
* VERSION DATE    WHO     DETAIL
* 1.0.0   22Oct22 CH      First edition
*
*/

# ifndef MAP_H
# define MAP_H

# include <iostream>
# include <SFML/Graphics.hpp>
# include "agents.h"
# include "constants.h"
# include "music.h"

using namespace std;

class PacmanWindow;

class Map
{
    /*
        Private data members:
            - _pacman: store the only pacman object on the map
            - _ghosts: use vector to store the remaining ghosts on the map
            - _coins, _powerups, use unordered_map to store the remaining map and coins
            - char** _map: store other information (wall, protal, empty pathway, etc)
        Implementation:
            - Use hash to store the coins and powerup, when the pacman encounters a powerup or a coin,
            -      remove the coin or the powerup based on the hash key
            - The hash function: (map coordinate) -> (hash key)
            - Transform the (map coordinate) to (window coordinate) (For display)
    */
private:
    Map(): _max_x(0), _max_y(0), _map(0), _score(0), _pacman(),
        _chompSound(CHOMP_SOUND), _powerupEatSound(POWERUPEAT_SOUND),
        _ghostEatSound(GHOSTEAT_SOUND) {}
    ~Map();

    // Update the game status
    GameStatus   step();
    
    // Mapper (map coordinate) -> (game instance)
    char&        get(int x, int y) {return _map[y][x];}
    char&        get(sf::Vector2f v) {return get(v.x, v.y);}
    
    // Hash function (map coordinate) -> (window coordinate)
    sf::Vector2f getWindowPos(float x, float y);
    sf::Vector2f getWindowPos(const Agent & agent);
    
    // hash function (map coordinate) -> (hash key)
    int          hash(int x, int y) {return x * _max_y + y;}
    int          hash(const Agent& ag) {return hash(ag._x, ag._y);}
    
    friend class PacmanWindow;
    friend istream & operator >> (istream &fin, Map &pacman_map);

    // Map coordinate related
    int _max_x, _max_y;
    char** _map;

    // Game object related
    Pacman _pacman;
    vector<Ghost> _ghosts;
    sf::Vector2f _portalA, _portalB;
    unordered_map<int, sf::Vector2f> _powerups;
    unordered_map<int, sf::Vector2f> _coins;

    // Score and sound
    int _score;
    Sound _chompSound;
    Sound _powerupEatSound;
    Sound _ghostEatSound;
};
# endif