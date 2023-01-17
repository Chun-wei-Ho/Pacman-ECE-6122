/***********************************************************************
* FILENAME :        constants.h
*
* DESCRIPTION :
*       Course: Advanced Programming Techniques for Engineering Applications (ECE-6122)
*       Term: 2022-Fall
*       Problem: Lab3
*       Only contain useful constants
*
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

# ifndef CONSTANTS_H
# define CONSTANTS_H

// Map size boarder
# define MIN_X_BMP 20
# define MAX_X_BMP 635
# define MIN_Y_BMP 36
# define MAX_Y_BMP 671

// Load image
# define PACMAN_BMP "graphics/pacman.bmp"
# define PINKGHOST_BMP "graphics/pink_ghost.bmp"
# define REDGHOST_BMP "graphics/red_ghost.bmp"
# define BLUEGHOST_BMP "graphics/blue_ghost.bmp"
# define ORANGEGHOST_BMP "graphics/orange_ghost.bmp"
# define START_BACKGROUND "graphics/pac-man.bmp"
# define GAME_BACKGROUND "graphics/maze.bmp"

// Map file txt
# define GAME_MAP "map/pac-man.txt"

// Font
# define FONT "fonts/Arial.ttf"

// Musics & Sound
# define START_MUSIC "sound/start.wav"
# define LOSE_MUSIC "sound/lose.wav"
# define WIN_MUSIC "sound/win.wav"
# define CHOMP_SOUND "sound/chomp.wav"
# define POWERUPEAT_SOUND "sound/powerup_eat.wav"
# define GHOSTEAT_SOUND "sound/ghost_eat.wav"

// Game speed
# define GHOST_SPEED 0.025
# define PACMAN_SPEED 0.02

// Record the current direction of agents
enum Direction
{
    Up, Down, Left, Right, Stop
};

// Record the status of the current game
enum GameStatus
{
    BeforeStart,
    InGame,
    WinGame,
    LoseGame
};

// Define notation in `GAME_MAP`
enum MapItem
{
    ghost = (int) 'g',
    pacman = (int) 'o',
    powerup = (int) 'x',
    coin = (int) '.',
    wall = (int) '|',
    PortalA = (int) 'A',
    PortalB = (int) 'B',
    other = (int) '-'
};

# endif