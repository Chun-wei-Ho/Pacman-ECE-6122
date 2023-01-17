/***********************************************************************
* FILENAME :        agents.cpp
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

# include "agents.h"

// setup static variable for RandomDirectionGenerator
// including up, down, left and right
const vector<Direction> RandomDirectionGenerator::options = \
{Direction::Left, Direction::Right, Direction::Down, Direction::Up};

// initialize srand
bool RandomDirectionGenerator::nosrand = false;

Direction RandomDirectionGenerator::generate()
{
    // Static function
    // Randomly sample direction from options
    if (nosrand)
    {
        // setup random seed for the first run
        nosrand = true;
        srand(time(NULL));
    }
    int idx = rand() % 4; // determin the idx randomly
    return options[idx]; // output the sampled direction
}

Agent::Agent(): _speed(0), _lockportal(false)
{
    // Constructor for Agent classes
    // - Initialize speed
    // - Initialize direction randomly
    _direction = RandomDirectionGenerator::generate();
}

Agent::Agent(filesystem::path filename, float x, float y): Agent()
{
    // Alternate constructor of agent
    // - call the default constructor of Agent
    // - load the texture directly from `filename`
    load(filename, x, y);
}

void Agent::load(filesystem::path filename, float x, float y)
{
    // Load texture from filename
    // - Set position of the agent to Map.coordinate(x, y)
    _x = x;
    _y = y;
    assert(_texture.loadFromFile(filename));
}

sf::Vector2f Agent::peek()
{
    // Get the next position based on current direction and speed
    switch (_direction)
    {
    case Direction::Up:
        return sf::Vector2f(_x, _y - _speed);
        break;
    case Direction::Down:
        return sf::Vector2f(_x, _y + _speed);
        break;
    case Direction::Left:
        return sf::Vector2f(_x - _speed, _y);
        break;
    case Direction::Right:
        return sf::Vector2f(_x + _speed, _y);
        break;
    case Direction::Stop:
        return sf::Vector2f(_x, _y);
        break;
    default:
        throw invalid_argument("ERROR: invalid direction");
        break;
    }
}

void Agent::move(sf::Vector2f new_pos)
{
    // Update the direction to new_pos
    // - Unlock portal when the agent is not on the portal
    _x = new_pos.x;
    _y = new_pos.y;
    _lockportal = false; // unlock the portal
}

void Agent::movePortal(sf::Vector2f portal_pos, sf::Vector2f current_pos)
{
    // When the agent is on the portal, teleport to another portal
    // - Lock the portal temporily to avoid infinitely teleporting
    // Input:
    //    portal_pos: the position of the another portal
    //    current_pos: current position

    // Determine whether to teleport or not based on _lockportal
    sf::Vector2f new_pos = (_lockportal ? current_pos : portal_pos);
    move(new_pos);
    _lockportal = true; // lock the portal temporily
}

Ghost::Ghost(filesystem::path filename, float x, float y):
    Agent(filename, x, y)
{
    // Constructor of Ghost
    // The only difference is _speed is set to be GHOST_SPEED
    _speed = GHOST_SPEED;
}

void Pacman::blink(){
    // Change the current pacman color
    // between Yellow and Red
    _color = (_color == sf::Color::Yellow)? sf::Color::Red : sf::Color::Yellow;
}
