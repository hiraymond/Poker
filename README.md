# Poker
Name: Lau Wai Hang  UID: 3035693155
Name: Leung Yui Hung  UID: 3035689752

A game description with basic game rules:
We proposed to make a one-player poker game, which the player would play with one computer player.
The game start with the player but-in amount(the total money he/she would have to enjoy the poker game)
Then, for each round, both player and computer would recevie two ramdom generated cards,
And player can add bet or withdraw from that round according to general poker rules.
Our program would determine who is winner after the final bet has been added in each round.
Player can choose to end game when he/she withdraw or finish each round.

Code Requirement:

1. Generation of random game sets or events
2. Data structures for storing game status (using struct to store cards)
3. Dynamic memory management (dynamic array)
4. File input/output (loading/saving game status)
5. Program codes in multiple files (using Makefile and .h file)

Non-standard C/C++ libraries:
  Windows.h/unistd.h
  Function: Easter egg, creating fake loading time using sleep function.

Instructions:

1. Player should first generate a Poker file using "make Poker" command.
2. Player should see a game instruction after running the Poker file.
3. Follow the instruction to play the game.
