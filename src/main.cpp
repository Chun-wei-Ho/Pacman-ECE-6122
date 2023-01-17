/***********************************************************************
* FILENAME :        main.cpp
*
* DESCRIPTION :
*       Course: Advanced Programming Techniques for Engineering Applications (ECE-6122)
*       Term: 2022-Fall
*       Problem: Lab3
*
* PUBLIC FUNCTIONS :
*       int main()
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

# include <SFML/Graphics.hpp>

# include "window.h"

using namespace std;

int main()
{
    // Main function
    // Create a window and manage the main loop

    PacmanWindow window("pacman"); // Create a window for the pacman game
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) // Listen for events
            window.handleEvent(event); // Call the event handler
        window.show(); // Update the screen
        window.step(); // Update the game status
    }

    return 0;
}
