#include <iostream>
#include <cstdlib>
#include <ctime>
#define SPADE "\xE2\x99\xA0"
#define CLUB "\xE2\x99\xA3"
#define HEART "\xE2\x99\xA5"
#define DIAMOND "\xE2\x99\xA6"
using namespace std;

void printrules(){
	cout<<"*****Welcome the c++ poker game*****\n"<<"Game flow:\n"<<
    "In each round, you and the computer player would fist add a fixed ante to the pool\n"<<
    "Then, you and the computer player would receive two ramdom cards(hand cards)\n"<<
    "It would be a add bet turn after you have viewed your\n"<<
    "In each add bet turn, you can choose to withdrawl from this round,\n"<<
    "Or add bet into the pool with a amount no more than 10% of your buy in amount\n"<<
    "Once a bet has added,\nanother must add at least the same amount of bet in order to proceed the game\n"<<
    "Or simply \'check\', when you do not want to add bet\n"<<
    "It would be computer add bet turn when you have chosen one of the three choice above\n"<<
    "Similarly, the computer would choose from those three choice\n"<<
    "If neither you nor computer have withdraw from the game, the game would continue\n"<<
    "After the first add bet turn, three cards of the public deck would be shown\n"<<
    "And it is followed a add bet turn\n"<<
    "After the second add bet turn, one more card of the public deck would be shown\n"<<
    "And it is followed a add bet turn\n"<<
    "Similarly, the final card of the public deck would be shown\n"<<
    "And it comes to the final add bet turn\n"<<
    "Victory or Defeat:\n"<<
    "1. If anyone withdraw from the game, another player would be treated as winner\n"<<
    "And the winner would take all money inside the pool(including the ante)\n"<<
    "2. If no one has withdram from the game, after the final add bet turn,\n"<<
    "Both your hand card and computer hand card would combine with the 5 public cards\n"<<
    "And consider only 5 cards of the combined hand cards,\n"<<
    "The player have the higher ranking of card combination would win\n"<<
    "Details of the definition of \'higher ranking\' can be found in the Wikipedia of \'list of poker hand\'\n\n";
}

void distribute_card(int cardset[], int playerhand[], int comphand[], int publicdeck[]){
	playerhand[0]=cardset[0];
	playerhand[1]=cardset[1];
	comphand[0]=cardset[2];
	cardset[1]=cardset[3];
	for (int i=4; i<9; ++i){
		publicdeck[i]=cardset[i];
	}
}

void newroundofgame(double money, double buyin, double ante){
	int cardset[52], playerhand[2], comphand[2], publicdeck[5];
	double pool;
	for (int i=0; i<52; ++i){
		cardset[i]=i;
	}
	for (int i=51; i>0; --i){
    //get swap index
    int j = rand()%i;
    //swap cardset[i] with cardset[j]
    int temp = cardset[i];
    cardset[i] = cardset[j];
    cardset[j] = temp;
  }
	distribute_card(cardset, playerhand, comphand, publicdeck);
	cout<<"Your current money is: "<<money<<endl;
	cout<<"After adding the antes from you and the computer, the pool contains $"<<2*ante<<endl;
	cout<<"Your current hand is "<<playerhand[0]<<' '<<playerhand[1]<<endl;
}

int main(){
	srand(1);
	double buyin, money, ante;	//money is the current money of player
	printrules();
	cout<<"Please enter the buy in amount(>100) :\n";
	cin>>buyin;
	while (buyin<100.0){
		cout<<"Too less buy in amount, please enter again\n";
		cin>>buyin;
	}
	money=buyin;
	ante=buyin*0.01;
	cout<<"***NEW ROUND***\n";
	newroundofgame(money, buyin, ante);
	
}
