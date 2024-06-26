# Randochess
This is a fork of chess, which has random made up rules applied each game. This adds a bit of refreshing fun to chess, and helps bridge skill issues for the sake of fun.

# Rules

## OOPS! All Knights
All pieces have the same movement as a knight

## PREPARE THYSELF
Pawns can move 4 spaces forward on their first move.
note: they still cannot take on this move

## Have a plan to kill everyone you meet
Bishops now move like a king. When they take a piece, they can do so diagonally and without line of sight.
note: they cannot take a piece cardinally, even if it is next to them

## Knook
Rooks can now move like a knight if they wish.
note: knights are unchanged

# Gameplay Information
Rules will be able to modify traits of pieces. These traits include the following:

* Valid movement spaces
* Valid capture spaces (these are different on pawns)
* Pieces the piece can promote (or demote) to
* Whether the piece can be in check

A rule can modify one of these traits (movement and capture spaces are considered one trait), and there will only be one rule per piece per trait. The goal of the rules is to add mystery to what rules are in play, not what each rule does.<br>
For example, there would only be one rule that can modify pawn movement, and one rule that modifies pawn promotion.

# Technical Info

## Endpoints

### Init game
Send back a join code to a game for the opponent, and a host code for the host

### Join game
Check if join code is valid, if so the relevane info of the game is returned

### Send move
Sends: start position, end position
Receives: Is valid move

### Fetch Move
Was there another move played by the opponent (server keeps track of if the move was propogated or not)

### IsValidMove
Since the movable spots can be undetermined, this move takes two spots and determines if the piece at p1 can move to p2

## Info Loop
```
Join game
 |
 \/
Fetch <--------------------------------------------------------------------------------------+
 | (assuming it is player's turn)                                                            |
 \/                                                                                          |
Player sends move  <-------------+    (Player can now see where piece can move)              | 
 |                             GetValidMoves                                                 | 
 \/                              /\                                                          |
IsValidMove ----------------------+                                                          | 
 | (valid)      (invalid)                                                                    |
 \/                                                                                          |
Send Move                                                                                    |
 | (is valid)                                                                                |
 \/                                                                                          |
GetValidMoves -------------------------------------------------------------------------------+
```
