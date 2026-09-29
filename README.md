# PathFinding
Editor to visualise pathfinding algorithms on a 2D grid. Contains A* and Dijkstra Algorithm.<br/>
Dijkstra does a OneToAll when executing for the first time and will keep all the paths unless the start or the terrain is changed.<br/>
A* is the unsual A* algorithm.<br/>

## Launching
You can launch the application by pressing the green arrrow on Visual Studio<br/>
There is also an executable in the Pathfinding/Binaries/ folder<br/>

## Inputs
S -> Set start point on the grid<br/>
G -> Set goal point on the grid<br/>
X -> Execute algorithm and display path<br/>
R -> Switch algorithm (functional but each algortihm has it's own grid)<br/>
MOUSE LEFT CLICK -> change weight on the grid<br/>

There is a reminder of these in the application<br/>

## Colors
Green -> Easy path (weight of 1)<br/>
Brown -> Challenging path (weight of 2)<br/>
Yellow -> Difficult path (weight of 3)<br/>
Black -> Wall (Cannot go through)<br/>

## Known issues and improvements
 - Switching algorithms should work with the same grid
 - Could have an animation that shows open and closed nodes as it gets calculated
 - It detects if the path to the goal is blocked but not the closest it can get to
 - width and height of the grid can only be changed in the source file Pathfinding.cpp
