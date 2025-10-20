# CS 3503 Project 1 - BitBoard Checkers Game

## Author
Kris Sheridan
## Description
My implementation of a checkers game using a bitboard.
## Build Instructions
‘‘‘ bash
gcc -o convert convert . c main . c
./ convert
‘‘‘
## Directions
The checkers game requires two people (or one if playing against yourself) at the computer.
Each of you should choose a color (black or white) and remember what color you are.

**1. Select your piece** <br>
Enter the row (A-H) first then the colum (1-8) without a space to select the piece that you want to move.

**2. Moving your pieces** <br>
Entering "L" and "R" for normal pieces and kings will move the piece based on the player perspective
(typing "L" for a black piece will move it down to the left while it will move it up to the left for a white piece)

Entering "LB" and "RB" will move kings backwards and is also based on perspective. (This only works on kings)

**3. Capturing enemy pieces** <br>
Moving a piece on to an enemy piece with nothing behind the enemy piece will cause you to capture it and vice versa.
(To capture multiple piece, go again and move your piece onto another enemy piece)

**4. Promoting to King** <br>
Moving you piece to the other side of the board will promote you piece.

**5. Winning** <br>
To win, capture all of your enemies pieces.