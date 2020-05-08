#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#define SPADE "\xE2\x99\xA0"
#define CLUB "\xE2\x99\xA3"
#define HEART "\xE2\x99\xA5"
#define DIAMOND "\xE2\x99\xA6"
using namespace std;

struct handcard{
	int cardno;
	string cardimage;
};

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

void distribute_card(int cardset[], handcard player[], handcard computer[], handcard publicdeck[]){
	int j=0;
	player[0].cardno=cardset[0];
	player[1].cardno=cardset[1];
	computer[0].cardno=cardset[2];
	computer[1].cardno=cardset[3];
	for (int i=4; i<9; ++i){
		publicdeck[j].cardno=cardset[i];
		j++;
	}
}

string inttostr(int card){
	 // This function is used to change the card number into readable string
  string s1;
  switch (card%13) {
    case(0) : s1="A";
    break;
    case(1):  case(2):
    case(3):  case(4):
    case(5):  case(6):
    case(7):  case(8):
    case(9):
    s1=to_string(card%13+1);
    break;
    case(10): s1="J";
    break;
    case(11): s1='Q';
    break;
    case(12): s1='K';
    break;
  }
  if (0<=card && card<=12)
      s1+=SPADE;
  else if (13<=card && card<=25)
      s1+=HEART;
  else if (26<=card && card<=38)
      s1+=CLUB;
  else if (39<=card && card<=51)
      s1+=DIAMOND;
  return s1;
}

int p_addbetturn(double &pool, double &money){
	int choice;
	double bet;
	cout<<"It is your turn to add bet\nPlease enter a integer to proceed\n";
	cout<<"0: Withdraw from this round\n1: Check\n2: Add bet\n";
	cin>>choice;
	while (choice<0 || choice>2){
		cout<<"Invalid choice, please enter again\n";
		cin>>choice;
	}
	if (choice==0){
		cout<<"**You have withdrawed from this round**\n";
		return -1;
	}
	else if (choice==1){
		cout<<"You have checked for this turn\n";
		return 0;
	}
	else if (choice==2){
		cout<<"Please enter the amount of bet that you want to add: \n";
		cin>>bet;
		while (bet<=0){
			cout<<"Invalid bet, please enter again\n";
			cin>>bet;
		}
		pool+=bet;
		money-=bet;
		cout<<"The pool now contains $"<<pool<<endl;
		cout<<"You remains $"<<money<<endl;
		return bet;
	}
	return 0;
}

int c_addbetturn(double &pool, double &money, double bet, double buyin){
	if (bet==0){
		// The player just checked
		// 1/4 chance the computer would add bet
		int addornot=rand()%4;
		if (addornot==0){	//computer add bet with 1/4 of chance
			pool+=money*0.04;
			cout<<"The computer player has added "<<money*0.04<<" to the pool\n";
			cout<<"The pool now contains $"<<pool<<endl;
			cout<<"Are you going to follow the bet?\n";
			cout<<"Enter either 0: Withdraw from this round OR \'any other integer\': Follow the bet\n";
			return 1;
		}
		else{	// computer check
			cout<<"The computer player also checked\n";
			cout<<"The pool now contains $"<<pool<<endl;
			return 2;
		}
	}
	else if (bet>buyin*0.08 && bet<buyin*0.15){
		// player added large amount of bet
		int checkornot=rand()%3;
		if (checkornot==0){
			//computer withdraw from this round with 1/3 of the chance
			cout<<"**The computer player has withdrawed from this round**\n";
			cout<<"The pool now contains $"<<pool<<endl;
			money+=pool;
			pool=0;
			cout<<"After adding the profit of this round, you have $"<<money<<endl;
			return -1;
		}
		else {	// computer check with 2/3 of the chance
			cout<<"The computer player followed your bet\n";
			pool+=bet;
			cout<<"The pool now contains $"<<pool<<endl;
			return 2;
		}
	}
	else if (bet>=buyin*0.15){
		// player added very large amount of bet
		int checkornot=rand()%3;
		if (checkornot==0){	// computer check with 1/3 of the chance
			cout<<"The computer player followed your bet\n";
			pool+=bet;
			cout<<"The pool now contains $"<<pool<<endl;
			return 2;
		}
		else {	// computer withdraw from this round with 2/3 of the chance
			cout<<"**The computer player has withdrawed from this round**\n";
			cout<<"The pool now contains $"<<pool<<endl;
			money+=pool;
			pool=0;
			cout<<"After adding the profit of this round, you have $"<<money<<endl;
			return -1;
		}
	}
	else {
		// player added a small bet and computer follow the bet
		cout<<"The computer player followed your bet\n";
		pool+=bet;
		cout<<"The pool now contains $"<<pool<<endl;
		return 2;
	}
	return 2;
}

int newroundofgame(double &money, double buyin, double ante){
	int cardset[52], p_choice, c_choice;
	double pool=0;
	handcard player[2], computer[2], publicdeck[5];
	// array for handcard to store the cards for this round
	for (int i=0; i<52; ++i){
		// initialize the full 52 non-repeating cards
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
	distribute_card(cardset, player, computer, publicdeck);
	cout<<"Your current money is: $"<<money<<endl;
	pool+=2*ante;
	money-=ante;
	cout<<"After adding the antes from you and the computer, the pool contains $"<<pool<<endl;
	cout<<"You remains $"<<money<<endl;
	player[0].cardimage=inttostr(player[0].cardno);
	player[1].cardimage=inttostr(player[1].cardno);
	cout<<"Your current hand is "<<player[0].cardimage<<' '<<player[1].cardimage<<endl;

	// FIRST ADD BET TURN
	srand(time(NULL));
	// to get srand be ramdom as computer action involves ramdom probability
	p_choice=p_addbetturn(pool, money);
	// p_choice=0: checked
	// p_choice>0: amount of bet
	if (p_choice==-1){
		// player have withdrawed from this round
		//endgame(); ***************
		return 0;
	}
	c_choice=c_addbetturn(pool, money, p_choice, buyin);
	if (c_choice==-1){
		// computer have withdrawed from this round
		//endgame(); ***************
		return 0;
	}
	else if (c_choice==1){	// computer raised the bet
		cin>>p_choice;
		if (p_choice==0){
			// player don't follow computer's bet and withdraw
			cout<<"**You have withdrawed from this round**\n\n";
			//endgame(); ****************
			return 0;
		}
		else{
			cout<<"You followed the bet\n";
			pool+=money*0.04;
			money-=money*0.04;
			cout<<"The pool now contains $"<<pool<<endl;
			cout<<"You remains $"<<money<<endl;
		}
	}

	// SECOND ADD BET TURN
	srand(time(NULL));
	for (int i=0; i<5; ++i){
		// store cardimage in publicdeck array
		publicdeck[i].cardimage=inttostr(publicdeck[i].cardno);
	}
	cout<<"The first three cards of the publicdeck is as follow: \n";
	cout<<publicdeck[0].cardimage<<' '<<publicdeck[1].cardimage<<' '<<publicdeck[2].cardimage<<endl;
	p_choice=p_addbetturn(pool, money);
	if (p_choice==-1){
		// player have withdrawed from this round
		//endgame(); **************
		return 0;
	}
	c_choice=c_addbetturn(pool, money, p_choice, buyin);
	if (c_choice==-1){
		// computer have withdrawed from this round
		//endgame(); ***************
		return 0;
	}
	else if (c_choice==1){	// computer raised the bet
		cin>>p_choice;
		if (p_choice==0){
			// player don't follow computer's bet and withdraw
			cout<<"**You have withdrawed from this round**\n\n";
			//endgame(); *********************
			return 0;
		}
		else{
			cout<<"You followed the bet\n";
			pool+=money*0.04;
			money-=money*0.04;
			cout<<"The pool now contains $"<<pool<<endl;
			cout<<"You remains $"<<money<<endl;
		}
	}

	// THIRD ADD BET TURN
	srand(time(NULL));
	cout<<"The first four cards of the publicdeck is as follow: \n";
	cout<<publicdeck[0].cardimage<<' '<<publicdeck[1].cardimage<<' '<<publicdeck[2].cardimage<<' '<<publicdeck[3].cardimage<<endl;
	p_choice=p_addbetturn(pool, money);
	if (p_choice==-1){
		// player have withdrawed from this round
		//endgame(); *************
		return 0;
	}
	c_choice=c_addbetturn(pool, money, p_choice, buyin);
	if (c_choice==-1){
		// computer have withdrawed from this round
		//endgame(); **************
		return 0;
	}
	else if (c_choice==1){	// computer raised the bet
		cin>>p_choice;
		if (p_choice==0){
			// player don't follow computer's bet and withdraw
			cout<<"**You have withdrawed from this round**\n\n";
			//endgame(); **************
			return 0;
		}
		else{
			cout<<"You followed the bet\n";
			pool+=money*0.04;
			money-=money*0.04;
			cout<<"The pool now contains $"<<pool<<endl;
			cout<<"You remains $"<<money<<endl;
		}
	}

	// LAST ADD BET TURN
	srand(time(NULL));
	cout<<"The all five cards of the publicdeck is as follow: \n";
	cout<<publicdeck[0].cardimage<<' '<<publicdeck[1].cardimage<<' '<<publicdeck[2].cardimage<<' '
	<<publicdeck[3].cardimage<<' '<<publicdeck[4].cardimage<<endl;
	p_choice=p_addbetturn(pool, money);
	if (p_choice==-1){
		// player have withdrawed from this round
		//endgame(); *******************
		return 0;
	}
	c_choice=c_addbetturn(pool, money, p_choice, buyin);
	if (c_choice==-1){
		// computer have withdrawed from this round
		//endgame(); **************
		return 0;
	}
	else if (c_choice==1){	// computer raised the bet
		cin>>p_choice;
		if (p_choice==0){
			// player don't follow computer's bet and withdraw
			cout<<"**You have withdrawed from this round**\n\n";
			//endgame(); ******************
			return 0;
		}
		else{
			cout<<"You followed the bet\n";
			pool+=money*0.04;
			money-=money*0.04;
			cout<<"The pool now contains $"<<pool<<endl;
			cout<<"You remains $"<<money<<endl;
		}
	}
	// Should judge win/lose here **********
	cout<<"The computer hand cards are:\n";
	computer[0].cardimage=inttostr(computer[0].cardno);
	computer[1].cardimage=inttostr(computer[1].cardno);
	cout<<computer[0].cardimage<<' '<<computer[1].cardimage<<endl;
	// Result of the round
	return 0;
}

int main(){
	srand(1);
	double buyin, money, ante;
	// money is the current money of player
	// buyin is initial money of the player
	// ante is a fixed bet to add into pool in each round before game start
	int nextround;
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
	cout<<"***END OF THIS ROUND***\n"<<"Are you going to play the next round?\n";
	cout<<"Enter 1: continue for next round\n2: quit game and get the record saved\n";
	cin>>nextround;
	while (nextround==1){
		newroundofgame(money, buyin, ante);
		cout<<"***END OF THIS ROUND***\n"<<"Are you going to play the next round?\n";
		cout<<"Enter 1: continue for next round\n2: quit game and get the record saved\n";
		cin>>nextround;
	}
	cout<<"Thank you for playing the game, hope you enjoy this simple c++ poker!\n";
	return 0;
}
