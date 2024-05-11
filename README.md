# Randochess
This is a fork of chess, which has random made up rules applied each game. This adds a bit of refreshing fun to chess, and helps bridge skill issues for the sake of fun.

## Design Philosophies
Rules will be able to modify traits of pieces. These traits include the following:

* Valid movement spaces
* Valid capture spaces (these are different on pawns)
* Pieces the piece can promote (or demote) to
* Whether the piece can be in check

A rule can modify one of these traits (movement and capture spaces are considered one trait), and there will only be one rule per piece per trait. This means that there would only be one rule that can modify pawn movement, and one rule that modifies pawn promotion. The goal with this is to keep the mystery in which rules are active, not what the rule does.
