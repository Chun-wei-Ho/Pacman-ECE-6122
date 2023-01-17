/***********************************************************************
* FILENAME :        music.cpp
*
* DESCRIPTION :
*       Course: Advanced Programming Techniques for Engineering Applications (ECE-6122)
*       Term: 2022-Fall
*       Problem: Lab3
*
* PUBLIC CLASSES :
*       Music
*          - Handle longer music file
*       Sound
*          - Handle short sound effects
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

# include "music.h"

Music::Music(const filesystem::__cxx11::path& filename): _isplaying(false)
{
    // Consturct of Music
    //     initialize _isplaying and set the music looping
    assert(sf::Music::openFromFile(filename));
    setLoop(true);
}

void Music::play()
{   
    // Overload sf::play()
    //      - Don't do anything when playing 
    if (! _isplaying)
    {
        _isplaying = true;
        sf::Music::play();
    }
}

Sound::Sound(const filesystem::__cxx11::path& filename)
{
    // Constructor of Sound
    //      - Initialize the buffer
    //      - Load the `filename` into buffer
    assert(_buffer.loadFromFile(filename));
    sf::Sound::setBuffer(_buffer);
}