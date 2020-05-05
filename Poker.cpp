#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
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

 string inttostr(int card){
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
		srand(time(NULL));
		int addornot=rand()%4;
		if (addornot==0){	//computer add bet
			pool+=money*0.02;
			cout<<"The computer player has added "<<money*0.02<<"to the pool\n";
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
		srand(time(NULL));
		int checkornot=rand()%3;
		if (checkornot==0){	//computer withdraw from this round
			cout<<"**The computer player has withdrawed from this round**\n";
			cout<<"The pool now contains $"<<pool<<endl;
			money+=pool;
			pool=0;
			cout<<"After adding the profit of this round, you have $"<<money<<endl;
			return -1;
		}
		else {	// computer check
			cout<<"The computer player followed your bet\n";
			pool+=bet;
			cout<<"The pool now contains $"<<pool<<endl;
			return 2;
		}
	}
	else if (bet>=buyin*0.15){
		// player added very large amount of bet
		srand(time(NULL));
		int checkornot=rand()%3;
		if (checkornot==0){	// computer check
			cout<<"The computer player followed your bet\n";
			pool+=bet;
			cout<<"The pool now contains $"<<pool<<endl;
			return 2;
			
		}
		else {	// computer withdraw from this round
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
	

int newroundofgame(double money, double buyin, double ante){
	int cardset[52], playerhand[2], comphand[2], publicdeck[5], p_choice, c_choice;
	double pool=0;
	// string format of the card, for printing the iamge of card
	string p0, p1, c0, c1, public0, public1, public2, public3, public4;
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
	cout<<"Your current money is: $"<<money<<endl;
	pool+=2*ante;
	money-=ante;
	cout<<"After adding the antes from you and the computer, the pool contains $"<<pool<<endl;
	p0=inttostr(playerhand[0]);
	p1=inttostr(playerhand[1]);
	cout<<"Your current hand is "<<p0<<' '<<p1<<endl;
	// FIRST ADDBET TURN
	p_choice=p_addbetturn(pool, money);
	if (p_choice==-1){
		// player have withdrawed from this round
		//endgame();
		return 0;
	}
	c_choice=c_addbetturn(pool, money, p_choice, buyin);
	if (c_choice==-1){
		// computer have withdrawed from this round
		//endgame();
		return 0;
	}
	else if (c_choice==1){	// computer raised the bet
		cin>>p_choice;
		if (p_choice==0){
			// player don't follow computer's bet and withdraw
			//endgame();
			return 0;
		}
		else{
			cout<<"You followed the bet\n";
			pool+=money*0.02;
			money-=money*0.02;
			cout<<"The pool now contains $"<<pool<<endl;
			cout<<"You remains $"<<money<<endl;
		}
	}
	// SECOND ADDBET TURN
	return 0;
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
