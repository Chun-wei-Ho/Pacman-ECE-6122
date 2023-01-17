/***********************************************************************
* FILENAME :        map.cpp
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

# include "map.h"

istream & operator >> (istream &fin, Map &pacman_map)
{
    /*
        Reader for the map instance
            - Read in char** _map and parse the map
            - Store the game objects into the respective data structure
    */
    fin >> pacman_map._max_x >> pacman_map._max_y; // Store the range of (map coordinate)
    
    // Create and store _map based on (_max_x, _max_y)
    pacman_map._map = new char*[pacman_map._max_y];
    for (int y = 0; y < pacman_map._max_y; ++y)
    {
        pacman_map._map[y] = new char[pacman_map._max_x];
        fin >> pacman_map._map[y]; // Read in a line
    }

    // Parse the _map and store the game objects into the respective data structure
    for (int x = 0; x < pacman_map._max_x; ++x)
    {
        for (int y = 0; y < pacman_map._max_y; ++y)
        {
            switch (pacman_map.get(x, y))
            {
            case MapItem::coin:
                pacman_map._coins[pacman_map.hash(x, y)] = pacman_map.getWindowPos(x, y);
                break;
            case MapItem::powerup:
                pacman_map._powerups[pacman_map.hash(x, y)] = pacman_map.getWindowPos(x, y);
                break;
            case MapItem::pacman:
                pacman_map._pacman.load(PACMAN_BMP, x + 0.5, y);
                break;
            case MapItem::ghost:
                pacman_map._ghosts.push_back(Ghost(PINKGHOST_BMP, x + 0.5, y));
                pacman_map._ghosts.push_back(Ghost(BLUEGHOST_BMP, x + 0.5, y));
                pacman_map._ghosts.push_back(Ghost(ORANGEGHOST_BMP, x + 0.5, y));
                pacman_map._ghosts.push_back(Ghost(REDGHOST_BMP, x + 0.5, y));
                break;
            case MapItem::PortalA:
                pacman_map._portalA = sf::Vector2f(x, y);
                break;
            case MapItem::PortalB:
                pacman_map._portalB = sf::Vector2f(x, y);
                break;
            default: break;
            }
        }
    }
    return fin;
}

Map::~Map()
{
    // Destructor of map
    // If _map isn't 0, release the memory
    if (_map != 0)
    {
        for (int i = 0; i < _max_y ; ++i) delete[] _map[i];
        delete[] _map;
    }
}

sf::Vector2f Map::getWindowPos(float x, float y)
{
    // Transform the (map coordinate) -> (window coordinate)
    float x_bmp = x / _max_x * (MAX_X_BMP - MIN_X_BMP) + MIN_X_BMP;
    float y_bmp = y / _max_y * (MAX_Y_BMP - MIN_Y_BMP) + MIN_Y_BMP;
    return sf::Vector2f(x_bmp, y_bmp);
}

sf::Vector2f Map::getWindowPos(const Agent & agent)
{
    // Transform the (map coordinate) -> (window coordinate)
    // Take the agent size into accout, so that we can center the agent
    sf::Vector2u textureSize = agent._texture.getSize();
    sf::Vector2f halftextureSize = sf::Vector2f(textureSize.x / 2, textureSize.y / 2);
    return getWindowPos(agent._x - 0.5, agent._y - 0.5) - halftextureSize;
}

GameStatus Map::step()
{
    // Update the game status
    //  - Step 1 update the pacman
    //  - Step 2 check the encounter of ghosts
    //  - Step 3 update the ghosts

    sf::Vector2f new_pos = _pacman.peek();
    switch (get(new_pos))
    {
    //  - Step 1 update the pacman
    //        - update the pacman based on the pacman status and current position 
    case MapItem::wall:
        // If encounter wall, stop
        _pacman._direction = Direction::Stop;
        break;
    case MapItem::PortalA:
        // If encounter portal, either teleport or stop 
        _pacman.movePortal(_portalB, new_pos);
        break;
    case MapItem::PortalB:
        // If encounter portal, either teleport or stop 
        _pacman.movePortal(_portalA, new_pos);
        break;
    case MapItem::coin:
        // If encounter coin, remove the coin from the map and add score by 1

        // Remove the coin from the map
        get(new_pos) = MapItem::other;
        _coins.erase(hash(new_pos.x, new_pos.y));

        // Play sound effect
        _chompSound.play();

        // Add score by 1
        _score += 1;

        // If no _coin on the game, end game directly
        if (_coins.empty()) return GameStatus::WinGame;
        _pacman.move(new_pos);
        break;

    case MapItem::powerup:
        // If encounter powerup, set the powerup status to pacman

        // Remove the powerup item from the map
        get(new_pos) = MapItem::other;
        _powerups.erase(hash(new_pos.x, new_pos.y));

        // Play sound effect
        _powerupEatSound.play();

        // Set up power up
        _pacman.setPowerUp();
        _pacman.move(new_pos);
        break;
    default:
        _pacman.move(new_pos);
        break;
    }

    // Step 2, 3 manage ghost
    typedef vector<Ghost>::iterator Ghostiter;
    for (Ghostiter it = _ghosts.begin(); it != _ghosts.end();)
    {   
        // Step 2, check if encounter with ghost
        if (hash(*it) == hash(_pacman))
        {   
            // If encounter with pacman, update status based on is power up
            if (_pacman.isPowerUp())
            {
                // If powerup, eat the ghost, the ghost are gone forever
                _ghosts.erase(it);
                // Play the sound effect
                _ghostEatSound.play();
                // Update score
                _score += 50;
                continue;
            }
            else
            {
                // End the game otherwise
                return GameStatus::LoseGame;
            }
        }

        // Step 3, mvoe ghost
        sf::Vector2f new_pos = it -> peek();
        switch (get(new_pos))
        {
        case MapItem::wall:
            // If encounter with wall, decide direction randomly
            it -> _direction = RandomDirectionGenerator::generate();
            break;
        case MapItem::PortalA:
            // If encounter with portal, decide whether or not to teleport
            it -> movePortal(_portalB, new_pos);
            break;
        case MapItem::PortalB:
            // If encounter with portal, decide whether or not to teleport
            it -> movePortal(_portalA, new_pos);
            break;
        default:
            it -> move(new_pos);
            break;
        }
        ++it;
    }
    return GameStatus::InGame;
}