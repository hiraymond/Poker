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
2. Data structures for storing game status
3. Dynamic memory management
4. File input/output (e.g., for loading/saving game status)
5. Program codes in multiple files

Your implementation should encompass the following coding elements:

1. There would be total of nine different ramdom cards generated in each round. 
   (two for player hand cards, two for computer player hand cards, and five for the public deck)
2. We would be using arrays and struct to store cards for player, computer player, and public deck.
3. We would use dynamic arrays to store hands and clear it after each round. 
   We would also use dynamic arrays to store the win/lose record for the player, 
   the size of the record array is set as two (capable for storing two rounds of game)
   in the beginning, and the size of the record array would double when the limits is met.
4. use .txt file to save current hand of player, computer player, deck and the win/lose record.
5. We will have a file for the computer player, a file for loading/saving game status, a file for user input and a file for the main        body.
