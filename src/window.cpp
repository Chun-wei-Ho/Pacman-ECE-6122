/***********************************************************************
* FILENAME :        window.cpp
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

# include "window.h"

PacmanWindow::PacmanWindow(const sf::String windowname):
    _gameStatus(GameStatus::BeforeStart),
    _startmusic(START_MUSIC), _losemusic(LOSE_MUSIC), _winmusic(WIN_MUSIC)
{
    /*
        Constructor
            - Load the background, music, and font
            - Initialize the game status
            - Render a window
    */

    // Read in the background
    assert(_currentBackground.loadFromFile(START_BACKGROUND));
    sf::Vector2u backgroundSize = _currentBackground.getSize();
    sf::RenderWindow::create(sf::VideoMode(backgroundSize), windowname);

    // Read in the game map
    ifstream fin(GAME_MAP);
    assert(fin.good());
    fin >> _map;
    fin.close();

    // Read in the font
    assert(_font.loadFromFile(FONT));
}

void PacmanWindow::handleEvent(sf::Event event)
{
    // Handle the event
    //   - Based on the `event`, call the respective event handler
    switch (event.type)
    {
    case sf::Event::Closed:
        // When the user close the window, end the process
        sf::RenderWindow::close();
        break;
    case sf::Event::KeyPressed:
        // When the user press the key, call the respective event handler
        switch (event.key.code)
        {
        case sf::Keyboard::Enter:
            enterHandler();
            break;
        case sf::Keyboard::Left:
        case sf::Keyboard::Right:
        case sf::Keyboard::Up:
        case sf::Keyboard::Down:
            arrowHandler(event.key.code);
            break;
        case sf::Keyboard::Escape:
            escapeHandler();
            break;
        default: break; // Otherwise, do nothing
        }
    default: break;
    }
}

void PacmanWindow::show()
{
    // Render the game instances
    sf::RenderWindow::clear(); // clear the screen in every call

    // draw background
    sf::Sprite sprite;
    sprite.setTexture(_currentBackground);
    sf::RenderWindow::draw(sprite);

    switch (_gameStatus)
    {
    // Render instance based on _gameStatus [BeforeStart|InGame|WinGame|LoseGame]
    case GameStatus::BeforeStart:
    {
        // Display the text "PRESS ENTER TO START"
        sf::Text start_text;
        start_text.setString("PRESS ENTER TO START");
        start_text.setFont(_font);
        start_text.setPosition(sf::Vector2f(20, 350));
        start_text.setFillColor(sf::Color(255, 255, 255, 150));
        start_text.setCharacterSize(50);
        sf::RenderWindow::draw(start_text);

        _startmusic.play(); // play the start music
        break;
    }
    case GameStatus::WinGame:
    case GameStatus::LoseGame:
    {
        string end_message;
        if (_gameStatus == GameStatus::WinGame)
        {
            // Display the ending message
            end_message = "YOU WON (PRESS ESC)";
            _winmusic.play(); // play the _winmusic
        }
        else
        {
            // Display the ending message
            end_message = "YOU LOSS (PRESS ESC)";
            _losemusic.play(); // play the _losemusic
        }
        _startmusic.stop(); // stop the _startmusic

        // Display score
        sf::Text end_text;
        end_text.setString(end_message);
        end_text.setFont(_font);
        end_text.setPosition(sf::Vector2f(20, 350));
        end_text.setFillColor(sf::Color(255, 255, 255, 150));
        end_text.setCharacterSize(50);
        sf::RenderWindow::draw(end_text);

        // Dont break here so we can see the game status
    }
    case GameStatus::InGame:
    {
        // Display the game status
        //     - Display the coins position
        //     - Display the powerups position
        //     - Display the agents position

        // Display coin
        typedef unordered_map<int, sf::Vector2f>::iterator Positer;
        for (Positer it = _map._coins.begin(); it != _map._coins.end(); ++it)
        {
            sf::CircleShape coin(2);
            coin.setFillColor(sf::Color::White);
            coin.setPosition(it -> second);
            coin.setOrigin(sf::Vector2f(1, 1));
            sf::RenderWindow::draw(coin);
        }

        // Display powerup
        for (Positer it = _map._powerups.begin(); it != _map._powerups.end(); ++it)
        {
            sf::CircleShape powerup(5);
            powerup.setFillColor(sf::Color::White);
            powerup.setPosition(it -> second);
            powerup.setOrigin(sf::Vector2f(2.5, 2.5));
            sf::RenderWindow::draw(powerup);
        }

        // Display pacman
        sf::Sprite pacman;
        pacman.setTexture(_map._pacman._texture);
        if (_map._pacman.getPowerUpTime() > 1)
        {
            // When power up, set the color red
            _map._pacman._color = sf::Color::Red;
        }
        else if (_map._pacman.isPowerUp())
        {
            // When the powerup is almost end, blink the color
            _map._pacman.blink();
        }
        else{
            // When the power is not up, set the color yellow
            _map._pacman._color = sf::Color::Yellow;
        }
        pacman.setColor(_map._pacman._color);
        pacman.setPosition(_map.getWindowPos(_map._pacman));
        sf::RenderWindow::draw(pacman);

        // Display the ghosts
        typedef vector<Ghost>::iterator Ghostiter;
        for (Ghostiter it = _map._ghosts.begin(); it != _map._ghosts.end(); ++it)
        {
            sf::Sprite ghost;
            ghost.setTexture(it -> _texture);
            ghost.setPosition(_map.getWindowPos(*it));
            sf::RenderWindow::draw(ghost);
        }

        // Display the score
        sf::Text score_text;
        score_text.setFont(_font);
        score_text.setString(to_string(_map._score));
        score_text.setPosition(sf::Vector2f(180, 660));
        score_text.setFillColor(sf::Color::Yellow);
        score_text.setCharacterSize(50);
        sf::RenderWindow::draw(score_text);

        // When the game the playing, higher the pitch and lower the volume
        _startmusic.setPitch(1.1f);
        _startmusic.setVolume(50.f);
        break;
    }
    default: break;
    }

    sf::RenderWindow::display(); // Display everything
}

void PacmanWindow::enterHandler()
{   
    // Called when enter has been pressed
    if (_gameStatus == GameStatus::BeforeStart)
    {   
        // Before game start, press enter will start the game
        _gameStatus = GameStatus::InGame;

        // Load the background to an empty maze
        assert(_currentBackground.loadFromFile(GAME_BACKGROUND));
    }
}
void PacmanWindow::arrowHandler(sf::Keyboard::Key key)
{   
    // Called when arrow key has been pressed
    //    - Change the pacman direction respectively
    if (_gameStatus == GameStatus::InGame)
    {
        switch (key)
        {
        case sf::Keyboard::Left:
            _map._pacman._direction = Direction::Left;
            break;
        case sf::Keyboard::Right:
            _map._pacman._direction = Direction::Right;
            break;
        case sf::Keyboard::Up:
            _map._pacman._direction = Direction::Up;
            break;
        case sf::Keyboard::Down:
            _map._pacman._direction = Direction::Down;
            break;
        default:
            throw std::runtime_error("Invalid key code");
            break;
        }
    }
}

void PacmanWindow::escapeHandler()
{
    // Called when escape has been pressed
    //  - If in game, lose the game directly
    //  - If post game, close the window and end the process
    switch (_gameStatus)
    {
    case GameStatus::InGame:
        _gameStatus = GameStatus::LoseGame;
        break;
    case GameStatus::LoseGame:
    case GameStatus::WinGame:
        sf::RenderWindow::close();
        break;
    default: break;
    }
}

void PacmanWindow::step()
{
    // Update _map status, helper function to call _map.step()
    if (_gameStatus == GameStatus::InGame)
        _gameStatus = _map.step();
}
