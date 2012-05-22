//=============FiveOhOne Darts=============//


#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>

using namespace std;

const int boardpoints[20] =  {20, 1, 18, 4, 13, 6, 10, 15, 2, 17, 3, 19, 7, 16, 8, 11, 14, 9, 12, 5};
//  Doubles and trebles generated in run-time

const int BULLSEYE = 50;
const int BULL = 25;

enum settings {playernumber, gamepoints, playerone, randomstarter, gamestoplay, displaytext, playertothrow};

class Player {

public:
	Player();
	void SetInitialValues(int accuracy, int points, string name);
	
	void TakeTurn(int displaytext);
	void TakeAShot(int displaytext);
	void ResetForNextGame(int points);
	void ResetThrowOfThreeCount();
	int ThrowOfThreeCount();

	int GetPoints();
	int GetThrows();
	string GetName();

	int matchwins;
	int setwins;
	int legwins;
	int windensity[7];

private:
	int p_target;
	int p_hit;
	int p_accuracy;
	int p_points;
	int p_throws;
	int p_targetindex;
	int p_targettype;
	//bool p_AI;
	int p_throwofthree;

	string p_name;

	void TargetSelect(int);	

	void Inaccuracy();
	void BullsEye();
	void Bull();
	void Single();
	void Double();
	void Treble();
	
	bool CheckLegality(int);
};

class Leg {
public:
	Leg(bool playerthrow = 1, int set = 0);
	void Play(Player players[], int settings[]);
	int setnumber;
	bool playertothrow;
	
};

class Set {
public:
	Set(bool playerstart = 1, int set = 0);
	void Play(Player players[], int settings[]);
	void PlayTieBreaker(Player players[], int settings[]);
	int setnumber;
private:
	Leg legs[5];
	Leg tiebreaker[11];
	bool playertostart;
};

class Match {
public:
	Match();
	void Play(Player players[], int settings[]);
private:
	Set sets[13];
	bool playertostart;
};





void SetUpGame(int settings[], Player players[]);
void RunAMatch(int settings[], Player players[]);
void RunASet(int settings[], Player players[]);
void RunALeg(int settings[], Player players[], int starter);



void main() {

	int gamesettings[7] = {0};
	Player players[2] = {Player(), Player()};
	Match match;
	match = Match();

	SetUpGame(gamesettings, players);

	for (int i = gamesettings[gamestoplay]; i > 0; i--) {
		match.Play(players, gamesettings);
	}

	cout << players[0].GetName() << "\t:\t" << players[1].GetName() << endl << endl;
	cout << players[0].matchwins << "\t:\t" << players[1].matchwins << endl << endl;
	for (int i = 0; i < 7; i++) {
		cout << "7\t:\t" << i << "\t:\t" << (float)(players[0].windensity[i]*100)/gamesettings[gamestoplay] << "%" << endl;
	}
	for (int i = 0; i < 7; i++) {
		cout << i << "\t:\t7\t:\t" << (float)(players[1].windensity[i]*100)/gamesettings[gamestoplay] << "%" << endl;
	}

	while(true){}



}

void SetUpGame(int settings[], Player players[]){

	int holder_gametype = 1;
	int holder_points = 501;
	int holder_starter = 1;
	int holder_gamestoplay = 1;

	string holder_p1name = "Default";
	string holder_p2name = "Default";
	int holder_p1accuracy = 100;
	int holder_p2accuracy = 100;

	cout << "\t\t\tDarts Five Oh One Simulator" << endl << endl;
	do {
		if (holder_gametype != 1 && holder_gametype != 2) {
			cout << holder_gametype << " not a a valid number of players, please enter One [1] or Two [2]: ";
		} else {
			cout << "Choose One [1] or Two [2] player game: ";
		}
		cin >> holder_gametype;
		cout << endl << endl;
	} while (holder_gametype != 1 && holder_gametype != 2);

	settings[playernumber] = holder_gametype;

	do {
		if (holder_points < 2) {
			cout << "Games must end on a double or a bull, impossible to complete a game starting at " << holder_points << " points" << endl;
		}
		cout << "Enter number of points from which to play [501 is standard]: ";
		cin >> holder_points;
		cout << endl << endl;
	} while (holder_points < 2);

	settings[gamepoints] = holder_points;

	if (holder_gametype == 1) {
		cout << "Enter Name for Player: ";
	} else {
		cout << "Enter Name for Player One: ";
	}
	cin >> holder_p1name;
	cout << endl ;
	cout << "Enter " << holder_p1name << "'s Accuracy on Bullseye: ";
	cin >> holder_p1accuracy;
	cout << endl;

	if (holder_gametype == 2) {
		cout << "Enter Name for Player Two: ";
		cin >> holder_p2name;
		cout << endl << "Enter " << holder_p2name << "'s Accuracy on Bullseye: ";
		cin >> holder_p2accuracy;
		cout << endl;
	}

	cout << endl;

	players[0].SetInitialValues(holder_p1accuracy, holder_points, holder_p1name);
	players[1].SetInitialValues(holder_p2accuracy, holder_points, holder_p2name);

	if (holder_gametype == 2) {
		do {
			if (holder_starter != 1 && holder_starter != 2 && holder_starter != 3) {
				cout << "Invalid options, please select [1], [2] or [3]: ";
			} else {			
				cout << "Who is to go first? " << players[0].GetName() << " [1], " << players[1].GetName() << " [2], or 50:50 then alternate [3]: ";
			}
				cin >> holder_starter;
				cout << endl << endl;
			
		} while (holder_starter != 1 && holder_starter != 2 && holder_starter != 3);
		if (holder_starter == 3) {
			settings[randomstarter] = 1;
		}
	} 

	if (holder_starter == 1) {
		settings[playerone] = 1;
	}

	do {
		if (holder_gamestoplay < 1) {
			cout << "Number of games must be a positive integer" << endl;
		}
		cout << "Enter number of matches to play: ";
		cin >> holder_gamestoplay;
		cout << endl;
	} while (holder_gamestoplay < 1);

	settings[gamestoplay] = holder_gamestoplay;
	
	if (holder_gamestoplay > 1) {
		settings[displaytext] = 0;
	} else {
		settings[displaytext] = 0;
	}

		
}

void RunAMatch(int settings[], Player players[]) {
	bool playmatch = true;
	players[0].setwins = 0;
	players[1].setwins = 0;

	if (settings[playernumber] == 2 && settings[playerone] == 0) {
		settings[playertothrow] = 1;
	}

	if (settings[randomstarter] = 1) {
		settings[playertothrow] = rand()%2;
	}

	while(playmatch) {
		RunASet(settings, players);
		if (players[0].setwins == 7) {
			players[0].matchwins++;
			players[0].windensity[players[1].setwins]++;
			playmatch = false;
		} else if (players[1].setwins == 7) {
			players[1].matchwins++;
			players[1].windensity[players[0].setwins]++;
			playmatch = false;
		}

	}
}

void RunASet(int settings[], Player players[]) {
	bool playset = true;
	players[0].legwins = 0;
	players[1].legwins = 0;

	int starter = settings[playertothrow];

	while(playset) {
		RunALeg(settings, players, starter);
		if (players[0].legwins == 3) {
			players[0].setwins++;
			//cout << players[0].GetName() << "SetWin" << endl;
			playset = false;
		} else if (players[1].legwins == 3) {
			players[1].setwins++;
			//cout << players[1].GetName() << "SetWin" << endl;
			playset = false;
		}

	}
}

void RunALeg(int settings[], Player players[], int starter) {
//  Plays a single 'leg' until one of the players hits 0 points
	
	
	players[0].ResetForNextGame(settings[gamepoints]);
	players[1].ResetForNextGame(settings[gamepoints]);
	

	bool rungame = true;
	


	while (rungame) {
		players[starter].TakeAShot(settings[displaytext]);
		
		if (players[starter].GetPoints() == 0) {
			rungame = false;
			players[starter].legwins++;
			//cout << players[starter].GetName() << "LegWin";
		} else if (players[starter].ThrowOfThreeCount() == 0) {
			players[starter].ResetThrowOfThreeCount();
			if (starter == 0 && settings[playernumber] == 2) {
				starter = 1;	
			} else {
				starter = 0;
			}

		}
	}
	

}

Player::Player(){}

void Player::SetInitialValues(int accuracy, int points, string name) {
	p_accuracy = accuracy;
	p_points = points;
	p_name = name;
	p_throws = 0;
	p_hit = 0;
	matchwins = 0;
	setwins = 0;
	legwins = 0;
	p_throwofthree = 3;
	for (int i = 0; i < 7; i++) {
		windensity[i] = 0;
	}
}

void Player::TakeTurn(int displaytext) {
	int throws = 3;
	int wait = 0;
	int turnstartpoints = p_points;
	
	while (throws > 0 && p_points > 0) {	
		if (throws > 0 && p_points > 0) {	
			TakeAShot(displaytext);		
			p_throws++;
			throws--;
		}
		
	}
}

void Player::TakeAShot(int displaytext){
//  Throws a single dart, displays text if set to debug

	TargetSelect(0);

	if (displaytext == 1) {
		cout << GetName() << " takes aim at " << p_target;
	}
	Inaccuracy();
	if (displaytext == 1) {
		cout << " and hit " << p_hit << ".";
		cout << endl << endl;
	}

	if (CheckLegality(p_hit)) {
		p_points -= p_hit;
		if (displaytext == 1) {
			cout << GetName() << "'s points: " << p_points << endl << endl;
		}
	} else if (displaytext == 1) {
		cout << p_points-p_hit << " is an illegal score, points reset to " << p_points << endl << endl;
	}
	p_throws++;
}

void Player::ResetForNextGame(int points){
	p_points = points;
	p_throws = 0;
	p_throwofthree = 3;
}

int Player::GetPoints(){
	return p_points;
}

string Player::GetName(){
	return p_name;
}

//  Choose what to aim for; heuristic is to aim for highest number that yields a legal result, if it somehow selects a target that
//  is illegal it reruns with an arbitrary modifier to offset it
void Player::TargetSelect(int push){
	p_target = 0;
	p_targetindex = 0;
	p_targettype = 0;
	if (push > 1) {
		push = 0;
	}
	

	for (int i = 0; i < 20; i++) {
		if (boardpoints[i]+push < p_points && boardpoints[i] > p_target) {
			p_target = boardpoints[i];
			p_targetindex = i;
			p_targettype = 0;
			
		}
	}

	if (BULL+2 < p_points && BULL > p_target) {

		p_target = BULL;
		p_targettype = 1;
	}

	for (int i = 0; i < 20; i++) {
		if ((boardpoints[i]*2) == p_points && p_target != p_points) {
			p_target = boardpoints[i]*2;
			p_targetindex = i;
			p_targettype = 2;
		} else if ((boardpoints[i]*2)+push < p_points && ((boardpoints[i])*2) > p_target) {
			p_target = boardpoints[i]*2;
			p_targetindex = i;
			p_targettype = 2;
		}
	}

	for (int i = 0; i < 20; i++) {

		if ((boardpoints[i]*3)+push < p_points && ((boardpoints[i])*3) > p_target) {
			p_target = boardpoints[i]*3;
			p_targetindex = i;
			p_targettype = 3;
		}
	}

	if (BULLSEYE == p_points && p_target != p_points) {
		p_target = BULLSEYE;
		p_targettype = 4;
	} else if (BULLSEYE+push < p_points && BULLSEYE > p_target) {
		p_target = BULLSEYE;
		p_targettype = 4;
	}

	if (p_points < 180 && p_points % 2 == 1 && push == 0) {
		p_target = 0;
		
		for (int i = 0; i < 20; i++) {
			if ((boardpoints[i]*3) < p_points && ((boardpoints[i])*3) > p_target && (boardpoints[i]%2) == 1) {
				p_target = boardpoints[i]*3;
				p_targetindex = i;
				p_targettype = 3;
			}
		}	
		for (int i = 0; i < 20; i++) {
			if (boardpoints[i] < p_points && boardpoints[i] > p_target && (boardpoints[i]%2) == 1) {
				p_target = boardpoints[i];
				p_targetindex = i;
				p_targettype = 0;
			}
		}			
	}

	if (!CheckLegality(p_target)){
		TargetSelect(push + 1);
	}
}


void Player::Inaccuracy(){
//  Run necessary inaccuracy functions
	switch (p_targettype) {
		case 0: Single(); break;
		case 1: Single(); break;
		case 2: Double(); break;
		case 3: Treble(); break;
		case 4: Bull(); break;
	}
}

void Player::Bull(){
	//  Throw for the bull with accuracy p%  (20<p<85)
	
	int r = rand()%100;
	
	if(r<(p_accuracy-20)) {
		p_hit = 50;
		p_targettype = 4;
	} else if(r<85)	{
		p_hit = 25;
		p_targettype = 1;
	} else {
		p_hit = 1+rand()%20;
		p_targettype = 0;
	}
}
void Player::Single(){
	//  return result of throwing for single d with accuracy 88% (or 80% for the outer)
	
	// Board neighbours ignoring slot zero
	int bd[2][21]={{0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
		       {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1}};
	int r = rand()%100;
	
	if(p_target==25){		// outer  80%
		if(r<80) {
			p_hit = 25;
			p_targettype = 1;
		} else if (r<90) {
			p_hit = 50;
			p_targettype = 4;
		} else {
			p_hit = 1+rand()%20;
		}
	}
	else			// 1 to 20 single
		if(r<88) {
			p_hit = p_target;
			p_targettype = 0;
		} else if(r<92) {
			p_hit = bd[0][p_target];
			p_targettype = 0;
			if (p_targetindex == 0) {
				p_targetindex = 19;
			} else {
				p_targetindex--;
			}			
		} else if(r<96) {
			p_hit = bd[1][p_target];
			p_targettype = 0;
			if (p_targetindex == 19) {
				p_targetindex = 0;
			} else {
				p_targetindex++;
			}				
		} else if (r<98) {
			p_hit = 3*p_target;
			p_targettype = 3;
		} else {
			p_hit = 2*p_target;
			p_targettype = 2;
		}
}
void Player::Double(){
	//  return result of throwing for double d with accuracy 80%
	
	// Board neighbours ignoring slot zero
	int bd[2][21]={{0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
		       {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1}};
	int r = rand()%100;
	
	if(r<80) {
		p_hit = p_target;
		p_targettype = 2;
	} else if(r<85) {
		p_hit = 0;
		p_targettype = 5;
	} else if(r<90) {
		p_hit = p_target/2;
		p_targettype = 0;		
	} else if (r<93) {
		p_hit = 2*bd[0][p_target/2];
		p_targettype = 2;
		if (p_targetindex == 0) {
			p_targetindex = 19;
		} else {
			p_targetindex--;
		}	
	} else if(r<96) {
		p_hit = 2*bd[1][p_target/2];
		p_targettype = 2;
		if (p_targetindex == 19) {
			p_targetindex = 0;
		} else {
			p_targetindex++;
		}			
	} else if (r<98) {
		p_hit = bd[0][p_target/2];
		if (p_targetindex == 0) {
			p_targetindex = 19;
		} else {
			p_targetindex--;
		}			
	} else {
		p_hit = bd[1][p_target/2];
		if (p_targetindex == 19) {
			p_targetindex = 0;
		} else {
			p_targetindex++;
		}			
	}
}
void Player::Treble(){
	//  return result of throwing for treble d with accuracy p%  (o<90)
	
	// Board neighbours ignoring slot zero
	int bd[2][21]={{0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
		       {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1}};
	
	int r = rand()%100;
	
	if(r<p_accuracy) {
		p_hit = p_target;
		p_targettype = 3;
	} else if(r<90) {
		p_hit = p_target/3;
		p_targettype = 0;
	} else if(r<93) {
		p_hit = 3*bd[0][p_target/3];
		p_targettype = 3;
		if (p_targetindex == 0) {
			p_targetindex = 19;
		} else {
			p_targetindex--;
		}	
	} else if (r<96) {
		p_hit = 3*bd[1][p_target/3];
		p_targettype = 3;
		if (p_targetindex == 19) {
			p_targetindex = 0;
		} else {
			p_targetindex++;
		}				
	} else if(r<98) {
		p_hit = bd[0][p_target/3];
		p_targettype = 0;
		if (p_targetindex == 0) {
			p_targetindex = 19;
		} else {
			p_targetindex--;
		}			
		
	} else {
		p_hit = bd[1][p_target/3];
		p_targettype = 0;
		if (p_targetindex == 19) {
			p_targetindex = 0;
		} else {
			p_targetindex++;
		}			
	}
}

//  Checks legality by ensuring that there is a points value on the board
//  that can be chosen next time round
bool Player::CheckLegality(int hit){
	
	bool legality = false;
	
	if ((p_points - hit == 0 && (p_targettype == 2 || p_targettype == 4))|| p_points - hit > 1) {
		legality = true;
	} else {
		legality = false;
	}
	
	return legality;	
}



void Player::ResetThrowOfThreeCount(){
	p_throwofthree = 3;
}
int Player::ThrowOfThreeCount() {
	return --p_throwofthree;
}

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////  Leg Set Match ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


Leg::Leg(bool playerthrow, int set):
	playertothrow(playerthrow),
	setnumber(set)
{}


// Play a single leg, resetting all necessary numbers before doing so.
void Leg::Play(Player players[], int settings[]) {
	
	players[0].ResetForNextGame(settings[gamepoints]);
	players[1].ResetForNextGame(settings[gamepoints]);

	bool running = true;

	//  Game loop
	//  flip-flop between players 1 and 2, after each turn check for a winner
	while (running)
	{		
		playertothrow = !playertothrow;
		players[playertothrow].TakeTurn(settings[displaytext]);
		if (players[playertothrow].GetPoints() == 0) {
			running = false;
		}
	}

	players[playertothrow].legwins++;	
	
}

Set::Set(bool playerstart, int set):
	playertostart(playerstart),
	setnumber(set)
{
	bool temp = playertostart;
	
	for (int i = 0; i < 5; i++) {
		legs[i] = Leg(playertostart, setnumber);
		playertostart = !playertostart;
	}
	playertostart = temp;
	for (int i = 0; i < 11; i++) {
		tiebreaker[i] = Leg(playertostart, setnumber);
		playertostart = !playertostart;
	}
	playertostart = legs[4].playertothrow;
}

//  Play a single Set and record winner then display a screen showing who won
void Set::Play(Player players[], int settings[]) {
	bool running = true;
	int leg = 0;
	bool lastthrow = 0;

	players[0].legwins = 0;
	players[1].legwins = 0;
	
	while (running) {
		legs[leg].Play(players, settings);
		leg++;
		if (players[0].legwins == 3 || players[1].legwins == 3) {
			running = false;
			
		}
	
	}
	
	if (players[0].legwins == 3) {
		lastthrow = 0;
	} else {
		lastthrow = 1;
	}
	players[lastthrow].setwins++;
	//cout << players[lastthrow].GetName() << "SETWIN" << endl;
}

//  Plays a special set for tiebreaker situations, requires a clear lead of 2 sets to win, or plays first to 6, unlike normal sets which
//  play best of 5 legs
void Set::PlayTieBreaker(Player players[], int settings[]) {
	bool running = true;
	int leg = 0;
	bool lastthrow = 0;
	players[0].legwins = 0;
	players[1].legwins = 0;

	
	while (running) {
		tiebreaker[leg].Play(players, settings);
		leg++;
		
		
		if (players[0].legwins == 6) {
			running = false;
			lastthrow = 0;
			
		}
		if (players[1].legwins == 6) {
			running = false;
			lastthrow = 1;
		}
		if (players[0].legwins - players[1].legwins >= 2 && players[0].legwins > 2) {
			running = false;
			lastthrow = 0;
		}
		if (players[1].legwins - players[0].legwins >= 2 && players[1].legwins > 2) {
			running = false;
			lastthrow = 1;
		}
	
	}
	players[lastthrow].setwins++;	

}

Match::Match()
{
	playertostart = true;
	for (int i = 0; i < 13; i++) {
		sets[i] = Set(playertostart, i);
		playertostart = !playertostart;
	}
}

//  Play a full championship match (13 set) and display winner and table of results at end
void Match::Play(Player players[], int settings[]) {
	bool running = true;
	int set = 0;
	players[0].setwins = 0;
	players[1].setwins = 0;
	
	while(running) {
	
		if (set < 12) {
			sets[set].Play(players, settings);
		} else {
			sets[set].PlayTieBreaker(players, settings);
		}
		set++;
		
		if (players[0].setwins == 7) {
			running = false;
			players[0].matchwins++;
			players[0].windensity[players[1].setwins]++;
			
		}
		if (players[1].setwins == 7) {
			running = false;
			players[1].matchwins++;
			players[1].windensity[players[0].setwins]++;
		}
	}	
};
	











