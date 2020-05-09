#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <bits/stdc++.h>
#include "RecordOutput.h"
#include "RecordInput.h"
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

bool compare(int a, int b) {        //reverse sort
  return a > b;
}

void endgame(handcard player[],handcard computer[],handcard publicdeckStructure[], int sizePu, bool &ComWin, bool &PlaWin)
{
	int *checkP = new int[7], *checkC = new int[7], *checkCO = new int[7], *checkPO = new int[7];
	int playerhand[2], comphand[2], *publicdeck = new int[5];
	for (int i = 0; i < 2; i++){
		playerhand[i] = player[i].cardno;
	}
	for (int i = 0; i < 2; i++){
		comphand[i] = computer[i].cardno;
	}
	for (int i = 0; i < 5; i++){
		publicdeck[i] = publicdeckStructure[i].cardno;
	}



	for (int i = 0; i < 7; i++){            //combine hand and publicdeck
		if (i < 2){
			checkP[i] = playerhand[i];
			checkC[i] = comphand[i];
			checkPO[i] = playerhand[i];
			checkCO[i] = comphand[i];
		}
		else{
			checkP[i] = publicdeck[i - 2];
			checkC[i] = publicdeck[i - 2];
			checkPO[i] = publicdeck[i - 2];
			checkCO[i] = publicdeck[i - 2];
		}
	}

	for (int i = 0; i < 2 + sizePu; i++){
		while (checkP[i] > 12){
			checkP[i] -= 13;
		}
		while (checkC[i] > 12){
			checkC[i] -= 13;
		}
	}

	sort(checkP, checkP + 2 + sizePu, compare);             //sorted using STL function
	sort(checkC, checkC + 2 + sizePu, compare);
	sort(checkPO, checkPO + 2 + sizePu, compare);
	sort(checkCO, checkCO + 2 + sizePu, compare);



	map<int, int> CountRepeatP;                // similar to dictionary in python
	map<int, int> CountRepeatC;

	for (int i = 0; i < 2 + sizePu; i++){                 //count reapeat element and store in map
		map<int, int>::iterator targetP;
		map<int, int>::iterator targetC;
		targetP =  CountRepeatP.find(checkP[i]);
		targetC =  CountRepeatC.find(checkC[i]);
		if (targetP == CountRepeatP.end()){
			CountRepeatP[checkP[i]] = 1;
		}
		else{
			CountRepeatP[checkP[i]]++;
		}
		if (targetC == CountRepeatC.end()){
			CountRepeatC[checkC[i]] = 1;
		}
		else{
			CountRepeatC[checkC[i]]++;
		}
	}


	bool straightFlushP = false;
  bool fourOfAKindP = false;
  bool fullHouseP = false;
  bool flushP = false;
  bool straightP = false;
  bool threeOfAKindP = false;
  bool twoPairP = false;
  bool onePairP = false;

	bool straightFlushC = false;
  bool fourOfAKindC = false;
  bool fullHouseC = false;
	bool straightC = false;
  bool flushC = false;
  bool threeOfAKindC = false;
  bool twoPairC = false;
  bool onePairC = false;

  //check straight
	int countSP = 1, countSC = 1;
	int StraightLarP, StraightLarC;
	for (int i = 0; i < 2 + sizePu; i++){
		if (2 + sizePu - i >= 5){
			for (int j = i + 1; j < i + 4; j++){
				if (checkP[i] == checkP[j] + countSP){
					countSP++;
				}
			}
			if (countSP == 5){
				straightP = true;
				StraightLarP = checkP[i];
				break;
			}
		}
	}
	for (int i = 0; i < 2 + sizePu; i++){
		if (2 + sizePu - i >= 5){
			for (int j = i + 1; j < i + 4; j++){
				if (checkC[i] == checkC[j] + countSC){
					countSC++;
				}
			}
			if (countSC == 5){
				straightC = true;
				StraightLarC = checkC[i];
				break;
			}
		}
	}


	//check flush include suit
	int FP, FC;                //suit
	int cS = 0;
	int cC = 0;
	int cH = 0;
	int cD = 0;
	for (int i = 0; i < 2 + sizePu; i++){
		cS = 0;
		cC = 0;
		cH = 0;
		cD = 0;
		for (int j = i + 1; j < 2 + sizePu; j++){
			if (checkPO[i] <= 12){
				cS++;
			}
			if (checkPO[i] >= 13 && checkPO[i] <= 25){
				cC++;
			}
			if (checkPO[i] >= 26 && checkPO[i] <= 38){
				cH++;
			}
			if (checkPO[i] >= 39){
				cD++;
			}
			if (cS >= 5 || cC >= 5 || cH >= 5 || cD >= 5){
				flushP = true;
				if (cS >= 5){
					FP = 3;
				}
				if (cC >= 5){
					FP = 2;
				}
				if (cH >= 5){
					FP = 1;
				}
				if (cD >= 5){
					FP = 0;
				}
			}
		}
	}
	for (int i = 0; i < 2 + sizePu; i++){
		if (2 + sizePu - i >= 5){
			cS = 0;
			cC = 0;
			cH = 0;
			cD = 0;
			for (int j = i + 1; j < 2 + sizePu; j++){
				if (checkCO[i] <= 12){
					cS++;
				}
				if (checkCO[i] >= 13 && checkCO[i] <= 25){
					cC++;
				}
				if (checkCO[i] >= 26 && checkCO[i] <= 38){
					cH++;
				}
				if (checkCO[i] >= 39){
					cD++;
				}
				if (cS >= 5 || cC >= 5 || cH >= 5 || cD >= 5){
					flushC = true;
					if (cS >= 5){
						FC = 3;
					}
					if (cC >= 5){
						FC = 2;
					}
					if (cH >= 5){
						FC = 1;
					}
					if (cD >= 5){
						FC = 0;
					}
				}
			}
		}
	}


	//check three of a kind
	int TOKP, TOKC;
	map<int, int>::reverse_iterator iter;
	for (iter = CountRepeatP.rbegin(); iter != CountRepeatP.rend(); iter++){
		if (iter->second == 3){
			TOKP = iter->first;
			threeOfAKindP = true;
			break;
		}
	}
	for (iter = CountRepeatC.rbegin(); iter != CountRepeatC.rend(); iter++){
		if (iter->second == 3){
			TOKC = iter->first;
			threeOfAKindC = true;
			break;
		}
	}

	//check four of a kind
	int FOKP, FOKC;
	for (iter = CountRepeatP.rbegin(); iter != CountRepeatP.rend(); iter++){
		if (iter->second == 4){
			FOKP = iter->first;
			fourOfAKindP = true;
			break;
		}
	}
	for (iter = CountRepeatC.rbegin(); iter != CountRepeatC.rend(); iter++){
		if (iter->second == 4){
			FOKC = iter->first;
			fourOfAKindC = true;
			break;
		}
	}


	//check Pair
	int checkPairSuitP, checkPairSuitC;
	int countpairP = 0, countpairC = 0;
	vector<int> pP, pC;
	if ((not fourOfAKindC && not fourOfAKindP) || (not threeOfAKindP && not threeOfAKindC)){
		for (iter = CountRepeatP.rbegin(); iter != CountRepeatP.rend(); iter++){
			if (iter->second == 2){
				pP.push_back(iter->first);
				onePairP = true;
				countpairP++;
			}
			if (countpairP == 2){
				twoPairP = true;
				break;
			}
		}
		for (iter = CountRepeatC.rbegin(); iter != CountRepeatC.rend(); iter++){
			if (iter->second == 2){
				pC.push_back(iter->first);
				onePairC = true;
				countpairC++;
			}
			if (countpairC == 2){
				twoPairC = true;
				break;
			}
		}
		for (int i = 0; i < 2 + sizePu; i++){
			if (pP[0] != 0){
				if (checkPO[i] % pP[0] == 0){
					checkPairSuitP = checkPO[i];
					break;
				}
			}
		}
		for (int i = 0; i < 2 + sizePu; i++){
			if (pC[0] != 0){
				if (checkCO[i] % pC[0] == 0){
					checkPairSuitC = checkCO[i];
					break;
				}
			}
		}
	}
	for(int i = 0; i < 2; i++){
		cout<< pP[i] <<endl;
	}






	//Check straightFlush
	int countSFP = 1, countSFC = 1;
	if (flushP && straightP){
		for (int i = 0; i < 2 + sizePu; i++){
			for (int j = i + 1; j < i + 4; j++){
				if (checkPO[i] == checkPO[j] + countSFP){
					countSFP++;
				}
				if (checkCO[i] == checkCO[j] + countSFC){
					countSFC++;
				}
			}
			if (countSFP == 5){
				straightFlushP = true;
				break;
			}
			if (countSFC == 5){
				straightFlushC = true;
				break;
			}
		}
	}


	//check fullHouse
	if (not fourOfAKindP && threeOfAKindP && onePairP){
		fullHouseP = true;
	}
	if (not fourOfAKindC && threeOfAKindC && onePairC){
		fullHouseC = true;
	}



	//check high card
	int highestC, highestP;
	for (iter = CountRepeatC.rbegin(); iter != CountRepeatC.rend(); iter++){
		if (iter->second == 1){
			highestC = iter->second;
			break;
		}
	}
	for (iter = CountRepeatP.rbegin(); iter != CountRepeatP.rend(); iter++){
		if (iter->second == 1){
			highestP = iter->second;
			break;
		}
	}

	for (int i = 0; i < 2 + sizePu; i++){
		if (checkPO[i] % highestP == 0){
			highestP = checkPO[i];
			break;
		}
	}
	for (int i = 0; i < 2 + sizePu; i++){
		if (checkCO[i] % highestC == 0){
			highestC = checkCO[i];
			break;
		}
	}

	delete[] checkP;
	delete[] checkC;
	delete[] checkCO;
	delete[] checkPO;

	//winner
	if (straightFlushP && not straightFlushC){
		PlaWin = true;
	}
	if (straightFlushC && not straightFlushP){
		ComWin = true;
	}
	if (straightFlushP && straightFlushC){
		if (FP > FC){
			PlaWin = true;
		}
		if (FC > FP){
			ComWin = true;
		}
	}
	if (not straightFlushP && not straightFlushC){
		if (fourOfAKindC && not fourOfAKindP){
			ComWin = true;
		}
		if (fourOfAKindP && not fourOfAKindC){
			PlaWin = true;
		}
		if (fourOfAKindC && fourOfAKindP){
			if (FOKP > FOKC){
				PlaWin = true;
			}
			if (FOKC > FOKP){
				ComWin = true;
			}
		}
		if(not fourOfAKindC && not fourOfAKindP){
			if (fullHouseP && not fullHouseC){
				PlaWin = true;
			}
			if (fullHouseC && not fullHouseP){
				ComWin = true;
			}
			if (fullHouseC && fullHouseP){
				if (TOKC > TOKP){
					ComWin = true;
				}
				if (TOKP > TOKC){
					PlaWin = true;
				}
			}
			if (not fullHouseP && not fullHouseC){
				if (flushC && not flushP){
					ComWin = true;
				}
				if (flushP && not flushC){
					PlaWin = true;
				}
				if (flushP && flushC){
					if (FP > FC){
						PlaWin = true;
					}
					if (FC > FP){
						ComWin = true;
					}
				}
				if (not flushC && not flushP){
					if (straightP && not straightC){
						PlaWin = true;
					}
					if (straightC && not straightP){
						ComWin = true;
					}
					if (straightC && straightP){
						if (StraightLarC > StraightLarP){
							ComWin = true;
						}
						if (StraightLarP > StraightLarC){
							PlaWin = true;
						}
					}
					if (not straightC && not straightP){
						if (threeOfAKindC && not threeOfAKindP){
							ComWin = true;
						}
						if (threeOfAKindP && not threeOfAKindC){
							PlaWin = true;
						}
						if (threeOfAKindP && threeOfAKindC){
							if (TOKC > TOKP){
								ComWin = true;
							}
							if (TOKP > TOKC){
								PlaWin = true;
							}
						}
						if(not threeOfAKindC && not threeOfAKindP){
							if (twoPairC && not twoPairP){
								cout << "ispair" << endl;
								ComWin = true;
							}
							if (twoPairP && not twoPairC){
								cout << "ispair" << endl;
								PlaWin = true;
							}
							if (twoPairP && twoPairC){
								cout << "ispair" << endl;
								if (pP[0] > pC[0]){
									PlaWin = true;
								}
								if (pC[0] > pP[0]){
									ComWin = true;
								}
								if (pP[0] == pC[0]){
									if (checkPairSuitC > checkPairSuitP){
										ComWin = true;
									}
									if (checkPairSuitP > checkPairSuitC){
										PlaWin = true;
									}
									if (checkPairSuitP == checkPairSuitC){
										if (highestC > highestP){
											ComWin = true;
										}
										if (highestP > highestC){
											PlaWin = true;
										}
									}
								}
							}
							if (not twoPairP && not twoPairC){
								if (onePairP && not onePairC){
									cout << "ispair" << endl;
									PlaWin = true;
								}
								if (onePairC && not onePairP){
									cout << "ispair" << endl;
									ComWin = true;
								}
								if (onePairC && onePairP){
									cout << "ispair" << endl;
									if (checkPairSuitC > checkPairSuitP){
										ComWin = true;
									}
									if (checkPairSuitP > checkPairSuitC){
										PlaWin = true;
									}
									if (checkPairSuitP == checkPairSuitC){
										if (highestC > highestP){
											ComWin = true;
										}
										if (highestP > highestC){
											PlaWin = true;
										}
									}
								}
								if (not onePairP && not onePairC){
									if (highestC > highestP){
										ComWin = true;
									}
									if (highestP > highestC){
										PlaWin = true;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	//win print
	if (ComWin){
		cout << "Your opponent wins the round" << endl;
	}
	if (PlaWin){
		cout << "Congratulate! You win the round" << endl;
	}
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
		cout<<"**You have withdrawed from this round**\n\n";
		return -1;
	}
	else if (choice==1){
		cout<<"You have checked for this turn\n";
		return 0;
	}
	else if (choice==2){
		cout<<"Please enter the amount of bet that you want to add: \n";
		cin>>bet;
		while (bet<=0 || bet>money){
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
		if (addornot==0 && money>30.0){	//computer add bet with 1/4 of chance
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
	int cardset[52], p_choice, c_choice, sizePu = 0;
	double pool=0;
	handcard player[2], computer[2], publicdeck[5], playerSTR[2], computerSTR[2], publicdeckSTR[5];
	bool ComWin = false;
	bool PlaWin = false;
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
	playerSTR[0].cardimage=inttostr(player[0].cardno);
	playerSTR[1].cardimage=inttostr(player[1].cardno);
	cout<<"Your current hand is "<<playerSTR[0].cardimage<<' '<<playerSTR[1].cardimage<<endl;

	// FIRST ADD BET TURN
	srand(time(NULL));
	// to get srand be ramdom as computer action involves ramdom probability
	p_choice=p_addbetturn(pool, money);
	// p_choice=0: checked
	// p_choice>0: amount of bet
	if (p_choice==-1){
		// player have withdrawed from this round
		ComWin = true;
		cout << "Your opponent wins the round" << endl;
		return 0;
	}
	c_choice=c_addbetturn(pool, money, p_choice, buyin);
	if (c_choice==-1){
		// computer have withdrawed from this round
		PlaWin = true;
		cout << "Congradulate! You win the round" << endl;
		return 0;
	}
	else if (c_choice==1){	// computer raised the bet
		cin>>p_choice;
		if (p_choice==0){
			// player don't follow computer's bet and withdraw
			cout<<"**You have withdrawed from this round**\n\n";
			ComWin = true;
			cout << "Your opponent wins the round" << endl;
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
	sizePu = 3;
	srand(time(NULL));
	for (int i=0; i<5; ++i){
		// store cardimage in publicdeck array
		publicdeckSTR[i].cardimage=inttostr(publicdeck[i].cardno);
	}
	cout<<"The first three cards of the publicdeck is as follow: \n";
	cout<<publicdeckSTR[0].cardimage<<' '<<publicdeckSTR[1].cardimage<<' '<<publicdeckSTR[2].cardimage<<endl;
	p_choice=p_addbetturn(pool, money);
	if (p_choice==-1){
		// player have withdrawed from this round
		ComWin = true;
		cout << "Your opponent wins the round" << endl;
		return 0;
	}
	c_choice=c_addbetturn(pool, money, p_choice, buyin);
	if (c_choice==-1){
		// computer have withdrawed from this round
		PlaWin = true;
		cout << "Congradulate! You win the round" << endl;
		return 0;
	}
	else if (c_choice==1){	// computer raised the bet
		cin>>p_choice;
		if (p_choice==0){
			// player don't follow computer's bet and withdraw
			cout<<"**You have withdrawed from this round**\n\n";
			ComWin = true;
      			cout << "Your opponent wins the round" << endl;
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
	sizePu = 4;
	srand(time(NULL));
	cout<<"The first four cards of the publicdeck is as follow: \n";
	cout<<publicdeckSTR[0].cardimage<<' '<<publicdeckSTR[1].cardimage<<' '<<publicdeckSTR[2].cardimage<<' '<<publicdeckSTR[3].cardimage<<endl;
	p_choice=p_addbetturn(pool, money);
	if (p_choice==-1){
		// player have withdrawed from this round
		ComWin = true;
		cout << "Your opponent wins the round" << endl;
		return 0;
	}
	c_choice=c_addbetturn(pool, money, p_choice, buyin);
	if (c_choice==-1){
		// computer have withdrawed from this round
		PlaWin = true;
		cout << "Congradulate! You win the round" << endl;
		return 0;
	}
	else if (c_choice==1){	// computer raised the bet
		cin>>p_choice;
		if (p_choice==0){
			// player don't follow computer's bet and withdraw
			cout<<"**You have withdrawed from this round**\n\n";
			ComWin = true;
			cout << "Your opponent wins the round" << endl;
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
	sizePu = 5;
	srand(time(NULL));
	cout<<"The all five cards of the publicdeck is as follow: \n";
	cout<<publicdeckSTR[0].cardimage<<' '<<publicdeckSTR[1].cardimage<<' '<<publicdeckSTR[2].cardimage<<' '
	<<publicdeckSTR[3].cardimage<<' '<<publicdeckSTR[4].cardimage<<endl;
	p_choice=p_addbetturn(pool, money);
	if (p_choice==-1){
		// player have withdrawed from this round
		ComWin = true;
		cout << "Your opponent wins the round" << endl;
		return 0;
	}
	c_choice=c_addbetturn(pool, money, p_choice, buyin);
	if (c_choice==-1){
		// computer have withdrawed from this round
		PlaWin = true;
		cout << "Congradulate! You win the round" << endl;
		return 0;
	}
	else if (c_choice==1){	// computer raised the bet
		cin>>p_choice;
		if (p_choice==0){
			// player don't follow computer's bet and withdraw
			cout<<"**You have withdrawed from this round**\n\n";
			ComWin = true;
			cout << "Your opponent wins the round" << endl;
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
	computerSTR[0].cardimage=inttostr(computer[0].cardno);
	computerSTR[1].cardimage=inttostr(computer[1].cardno);
	cout<<computerSTR[0].cardimage<<' '<<computerSTR[1].cardimage<<endl;
	// Result of the round
	endgame(player, computer, publicdeck, sizePu, ComWin, PlaWin);
	return 0;
}

int main(){
	srand(time(NULL));
	double buyin, money, ante;
	// money is the current money of player
	// buyin is initial money of the player
	// ante is a fixed bet to add into pool in each round before game start
	int nextround, mode;
	printrules();
	cout << "Enter 1: Load previous record (Please ensure the standard format record file (record.txt) is in the same folder)\n2: Start a new game!\n";
	cin >> mode;
	if (mode == 1){
		RecordInput(money);
		ante=money*0.01;
	}
	if (mode == 2){
		cout<<"Please enter the buy in amount(>100) :\n";
		cin>>buyin;
		while (buyin<100.0){
			cout<<"Too less buy in amount, please enter again\n";
			cin>>buyin;
		}
		money=buyin;
		ante=buyin*0.01;
	}
	cout<<"***NEW ROUND***\n";
	newroundofgame(money, buyin, ante);
	cout<<"***END OF THIS ROUND***\n"<<"Are you going to play the next round?\n";
	cout<<"Enter 1: continue for next round\n2: quit game and get the record saved\n";
	cin>>nextround;
	while (nextround==1){
		cout<<"***NEW ROUND***\n";
		newroundofgame(money, buyin, ante);
		cout<<"***END OF THIS ROUND***\n"<<"Are you going to play the next round?\n";
		cout<<"Enter 1: continue for next round\n2: quit game and get the record saved\n";
		cin>>nextround;
	}
	RecordOutput(money);
	cout << "Game saving...\nPlease be patient" << endl;
	sleep(3);
	cout<<"Thank you for playing the game, hope you enjoy this simple c++ poker!\n";
	return 0;
}
