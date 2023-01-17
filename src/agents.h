/***********************************************************************
* FILENAME :        agents.h
*
* DESCRIPTION :
*       Course: Advanced Programming Techniques for Engineering Applications (ECE-6122)
*       Term: 2022-Fall
*       Problem: Lab3
*
* PUBLIC CLASSES :
*       RandomDirectionGenerator
*          - Helper class to generate random direction
* PRIVSTE CLASSES :
*       Agent
*          - Helper class for Map and Window to manage game instances
*       Pacman(Agent)
*       Ghost(Agent)
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

# ifndef AGENTS_H
# define AGENTS_H

# include <SFML/Graphics.hpp>
# include <cassert>
# include <iostream>
# include <cstdlib>
# include <time.h>
# include "constants.h"

using namespace std;

class PacmanWindow;
class Map;

class RandomDirectionGenerator
{
    // Helper class to generate random direction
    // Candidate: up, down, left, right
public:
    static Direction generate(); // helper function
private:
    static const vector<Direction> options; // candidates
    static bool nosrand; // helper bool for setting random seed, true if srand has been executed
};

class Agent
{
    // Template class for the agents (Picman and ghosts)
    // Only accessible for windows and map
    // Store the map coordinates and interact with map
    // Store the moving directions
protected:
    Agent(); // Default constructor
    Agent(filesystem::path filename, float x, float y);

    // inialize the location and texture
    void load(filesystem::path filename, float x, float y);

    // return the position based on the direction and the position
    sf::Vector2f peek();

    void move(sf::Vector2f new_pos); // move the the assigned position

    // move to the assigned position or move to other portal
    // (Based on _lockportal)
    void movePortal(sf::Vector2f portal_pos, sf::Vector2f new_pos);

    sf::Texture _texture; // Store the texture
    Direction _direction; // Store the current direction
    float _x, _y; // Store the current position
    float _speed; // Store the current speed
    bool _lockportal; // If true, cannot access to portal

    friend PacmanWindow;
    friend Map;
    friend istream & operator >> (istream &fin, Map &pacman_map);
};

class Ghost: public Agent
{
    // Helper class for the ghost agent
    // Nothing more special than speed difference
    Ghost(filesystem::path filename, float x, float y);
    friend PacmanWindow;
    friend Map;
    friend istream & operator >> (istream &fin, Map &pacman_map);
};

class Pacman: public Agent
{
    // Helper class for the pacman agent
    // - use _powerTime to implement eat-ghost function
    Pacman(): _powerTime(0), _color(sf::Color::Yellow)
            {_speed = PACMAN_SPEED;} // Initialize powerTime
    
    // Set up power up
    void setPowerUp() {_powerTime = time(0) + 5;} // Setup power up for 5 seconds
    bool isPowerUp() {return getPowerUpTime() > 0;} 
    time_t getPowerUpTime() {return _powerTime - time(0);} // Get powerup remaining time
    void blink(); // Change color (for blinking behavior)

    friend PacmanWindow;
    friend Map;
    friend istream & operator >> (istream &fin, Map &pacman_map);
    time_t _powerTime; // if current_time < powerTime, Pacman can eat ghosts
    sf::Color _color; // store the pacman color (for powerup color changing)
};

# endif