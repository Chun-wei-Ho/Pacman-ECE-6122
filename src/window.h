/***********************************************************************
* FILENAME :        window.h
*
* DESCRIPTION :
*       Course: Advanced Programming Techniques for Engineering Applications (ECE-6122)
*       Term: 2022-Fall
*       Problem: Lab3
*
* PUBLIC CLASSES :
*       PacmanWindow
*          - Manage game display, read in map and show on the screen
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

# ifndef WINDOW_H
# define WINDOW_H

# include <SFML/Graphics.hpp>
# include <iostream>
# include <cassert>
# include <string>
# include <fstream>
# include "map.h"
# include "constants.h"
# include "music.h"

using namespace std;

class PacmanWindow: public sf::RenderWindow
{
    // Manage game display
    // Public method
    //      - show(): display map item on the screen
    //      - handleEvent(event): handle the event
    //      - step(): update game status
public:
    // Constructor, create window object with name `windowname`
    PacmanWindow(const sf::String windowname);
    void show(); // Display game object on the window
    void handleEvent(sf::Event event); // Handle the event, interact with map
    void step(); // Update the game status
private:
    void enterHandler(); // Called when enter has been pressed
    void escapeHandler(); // Called when escape has been pressed
    void arrowHandler(sf::Keyboard::Key key); // Called when arrow key has been pressed
    sf::Texture _currentBackground; // Store the game background, displayed while playing 
    GameStatus _gameStatus; // Store the game status [BeforeStart, InGame, WinGame, LoseGame]
    Map _map; // Map object, store the game status
    sf::Font _font; // Font of the text
    Music _startmusic; // Music played when the game starts
    Music _losemusic; // Music played when the player loses the game
    Music _winmusic; // Music played when the player wins the game
};

# endif