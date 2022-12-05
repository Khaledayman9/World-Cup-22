# World Cup 22
A 3D scene. The scene has different 3D objects themed as the world cup decorations/environment that could be a stadium or a football field. The goal is to score a goal before the time ends, This was created using OpenGL3D.



![](https://github.com/Khaledayman9/World-Cup-22/blob/master/worldcupgif.gif)



# Models

1- The Ground.

2- The Player (Footballer model).

3- The Football.

4- The World Cup.

5- The Scoreboard.

6- The Flag (German flag, French flag, Italian flag).

7- The Goal Nets.

8- The Stadium lights.

9- The player Benches.


# Rules

- The player can move only inside the boundaries of the green field.
- The player has to score a goal before 22 seconds (approx.) which is the timer.
- The player wins if he scores a goal before the timer runs out, otherwise the referee whistles indicating end of time and he loses.
- The scoreboard gets updated only if the player scores a goal before the timer runs out.

# Movement

- The player can move with keys (1,2,3,4).
- The camera can move with keys (W,S,A,D,Q,E,Left Arrow, Right Arrow, Up Arrow, Down Arrow).
- The Mouse can move the camera in only 2 directions front and back. 

# Controls

* W => Move camera upwards.
* S => Move camera downwards.
* A => Move camera left.
* D => Move camera right.
* Q => Camera Zoom in.
* E => Camera Zoom Out
* Left Arrow => Rotate camera left.
* Right Arrow => Rotate camera right.
* Up Arrow => Rotate camera up.
* Down Arrow => Rotate camera down.
* 1 => Move player downwards.
* 2 => Move player upwards.
* 3 => Move player left.
* 4 => Move player right.
* T => Camera top view.
* F => Camera front view.
* U => Camera side view.
* B => Camera default view. 
* R => Restart the game.
* Mouse click in => Camera Zoom in.
* Mouse click out => Camera Zoom out.



# Layout

* Default view:

![world up](https://user-images.githubusercontent.com/105018459/205693766-43ee2040-2b40-40e4-9c4f-08e1bb280726.PNG)


* Top view: 

![top view](https://user-images.githubusercontent.com/105018459/205694537-a77899c3-8040-47ce-a704-cedc2b7af951.PNG)


* Front view:

![frontview](https://user-images.githubusercontent.com/105018459/205694569-205ac294-4b4d-42ed-86a5-b5398dc9d753.PNG)


* Side view:

![side view](https://user-images.githubusercontent.com/105018459/205694610-4f659c4c-560d-475a-b659-17e0d86ef179.PNG)


* Winning Screen:

![Winning sreen](https://user-images.githubusercontent.com/105018459/205694821-fdc8b066-853f-46de-a246-f7dadab3f6d6.PNG)


* Losing Screen:

![losing screen](https://user-images.githubusercontent.com/105018459/205694862-d51f7d88-c3b1-472b-a200-f300d9bccb4f.PNG)


* And you can move the camera using keys and mouse to get to a different view.


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
