/***********************************************************************
* FILENAME :        music.h
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

# ifndef MUSIC_H
# define MUSIC_H

# include <SFML/Audio.hpp>
# include <cassert>

using namespace std;

class Music: public sf::Music
{
    // Helper class to sf::Music
    //     Public Method
    //          - play(): the same as sf::Music,
    //                    but it doesn't do anything when the music is playing
public:
    Music(const filesystem::__cxx11::path& filename);
    void play();
private:
    bool _isplaying; // Helper bool to record whether the music is playing
};

class Sound: public sf::Sound
{
    // Helper class to sf::Sound
    // The different is that this manage buffer in the class,
    //    the users don't need to hander buffer themself again
public:
    Sound(const filesystem::__cxx11::path& filename);
private:
    sf::SoundBuffer _buffer; // The buffer to store the sound effects
};

# endif