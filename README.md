# 2D Space Invaders
A simplified version of the famous chicken invaders game. This game was created using the OpenGL which is a famous C/C++ Library for making 2D games.



![](https://github.com/Khaledayman9/2D-Space-Invaders/blob/master/layout.gif)



# Models

1- The Player Model (Space ship model).

2- The Enemy Model (Chicken model).

3- The Power Up Model.

4- The Bullet Model for the spaceship.

5- The Bullet Model for the chicken (Egg).

6- The Moon Model.

7- The Sun Model.


# Rules

- The Player Has 3 Lives.
- The health of the Chicken is 100.
- Each bullet deals 1 damage, either it is from the spaceship or it is from the chicken.
- If the player has 0 lives then he loses (Defeat).
- If the chicken has 0 health then the player wins (Victory).
- Powerups are generated at random positions and in random times.
- Whenever the player collides with the powerup, the spaceship changes color and he becomes bullet immune for a random amount of time.
- The player can move in all directions in the middle of the screen.
- The chicken is always at the top of the screen and can only move from left to right and vice versa. 

# Controls

* W => Move upwards.
* S => Move downwards.
* A => Move left.
* D => Move right.
* F => Fire bullet.
* R => Restart the game.
* Controls are displayed in the bottom left part of the screen as shown:

![controls](https://user-images.githubusercontent.com/105018459/202916101-a0a08779-db1c-4fe6-940b-544fe04e3597.PNG)


# Layout

1- The number of lives of the player is displayed at the bottom right of the screen.

2- The Health of the chicken is displayed at the bottom left of the screen.

3- The Controls are displayed in the bottom left of the screen.

4- The Player/Spaceship is centered in the middle of the screen.

5- The Chicken is displayed at the top of the screen.


![Layout](https://user-images.githubusercontent.com/105018459/202916440-c5fd6dba-59c3-41af-a728-0ed4345f3f2f.PNG)


6- The Powerup model is generated randomly at any position in the screen and at random times.


![powerup](https://user-images.githubusercontent.com/105018459/202916938-f6add0bb-105a-4805-97b9-0b7ced173a3c.PNG)


7- Whenever the player gains the powerup, the spaceship turns to green and the screen displays "You are now immune to bullets".

![powerup on](https://user-images.githubusercontent.com/105018459/202917038-5e0397f5-10e6-4028-a991-6985587bec4b.PNG)


8- Whenever the player/spaceship wins and kills the chicken, the screen displays "Victory".

![victory](https://user-images.githubusercontent.com/105018459/202916898-14142f5e-bc68-4129-8f7b-10e799c81acd.PNG)


9- Whenever the player/spaceship loses and gets killed by the chicken, the screen display "Defeat". 


![Defeat](https://user-images.githubusercontent.com/105018459/202916768-9b053c73-4d04-429d-a8ba-ef260e535b3a.PNG)




# Technologies

* Microsoft Visual Studio 2019
* C/C++
* OpenGL



# OpenGL

========================================================================
    CONSOLE APPLICATION : OpenGL3DTemplate Project Overview
========================================================================

AppWizard has created this OpenGL3DTemplate application for you.

This file contains a summary of what you will find in each of the files that
make up your OpenGL3DTemplate application.


OpenGL3DTemplate.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

OpenGL3DTemplate.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

OpenGL3DTemplate.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named OpenGL3DTemplate.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
