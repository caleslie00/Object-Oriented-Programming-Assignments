#include "ClapAdventure.h"
#include <unistd.h>

using namespace std;

// List of majors for reference when printing
string majorList[5] = {"IS", "DET", "CS", "Double Major in Computer Science and Mathematics", "None"};

// Makes text look cool.
void block(string s)
{
	// Initialize variables
	int longest = 0;
	string line = "", dashes = "";
	string text = "";
	stringstream ss1(s);
	
	// Find longest line
	while(getline(ss1, line)) {
		int length = 0;
		while (line[length] != 0) {
			length++;
		}
		
		if (length > longest)
			longest = length;
	}
	
	// Put each line the proper length with | surrounding
	stringstream ss2(s);
	getline(ss2, text);
	int lineLength = 0;
	while (text[lineLength] != 0) {
		lineLength++;
	}
	for (int i = lineLength; i < longest; i++) {
		text = text + " ";
	}
	text = "|" + text + "|";
	while (getline(ss2, line)) {
		lineLength = 0;
		while (line[lineLength] != 0) {
			lineLength++;
		}
		for (int i = lineLength; i < longest; i++) {
			line = line + " ";
		}
		text += "\n|" + line + "|";
	}
	
	// Gets the correct number of dashes
	longest += 2;
	for(int i = 0; i < longest; i++)
		dashes = dashes + '-';
	
	// cout result in a block
	cout << endl << dashes << endl;
	cout << text;
	cout << endl << dashes << endl << endl;
};

// Item implementations
Item* Item::make_Item(int choice, int x, int y)
{
 	if (choice == 1)
    	return new razerMouse(x, y);
	else if (choice == 2)
    	return new rgbKeyboard(x, y);
    else if (choice == 3)
    	return new DDR3(x, y);
    else if (choice == 4)
    	return new Fan(x, y);
    else if (choice == 5)
    	return new Tree(x, y);
    else if (choice == 6)
    	return new Boxes(x, y);
}

// Specific item implementations
void razerMouse::pickup() {
	block("You picked up a razorMouse!\nTracing Skill +5!");
	Player::getInstance()->addItem(this);
	Player::getInstance()->addTracingSkill(5);
}
void razerMouse::drop() {
	block("You lost your razorMouse!\nTracing Skill -5!");
	Player::getInstance()->addTracingSkill(-5);
}
void rgbKeyboard::pickup() {
	block("You picked up a RGB Keyboard!\nWriting Skill +5!");
	Player::getInstance()->addItem(this);
	Player::getInstance()->addWritingSkill(5);
}
void rgbKeyboard::drop() {
	block("You lost your RGB Keyboard!\nWriting Skill -5!");
	Player::getInstance()->addTracingSkill(-5);
}
void DDR3::pickup() {
	block("You picked up a DDR3!\nTracing Skill +3!\nWritingSkill +2!");
	Player::getInstance()->addItem(this);
	Player::getInstance()->addTracingSkill(3);
	Player::getInstance()->addWritingSkill(2);
}
void DDR3::drop() {
	block("You lost your DDR3!\nTracing Skill -3!\nWritingSkill -2!");
	Player::getInstance()->addTracingSkill(-3);
	Player::getInstance()->addWritingSkill(-2);
}
void Fan::pickup() {
	block("You picked up a Fan!\nAbstraction Skill +5!");
	Player::getInstance()->addItem(this);
	Player::getInstance()->addAbstractionSkill(5);
}
void Fan::drop() {
	block("You lost your Fan!\nAbstraction Skill -5!");
	Player::getInstance()->addAbstractionSkill(-5);
}
void Tree::pickup() {
	block("You picked up a Tree!\nAbstraction Skill +5!");
	Player::getInstance()->addItem(this);
	Player::getInstance()->addAbstractionSkill(5);
}
void Tree::drop() {
	block("You lost your Tree!\nAbstraction Skill -5!");
	Player::getInstance()->addAbstractionSkill(-5);
}
void Boxes::pickup() {
	block("You picked up a stack of Boxes!\nData Structure Skill +5!");
	Player::getInstance()->addItem(this);
	Player::getInstance()->addDataStructureSkill(5);
}
void Boxes::drop() {
	block("You lost your stack of Boxes!\nData Structure Skill -5!");
	Player::getInstance()->addDataStructureSkill(-5);
}

// Player implementations
Player::~Player() {
	for (vector<Item*>::iterator it = inventory.begin(); it != inventory.end(); it++) {
		delete (*it);
	}
}
void Player::move(int x, int y) {
	xLocation += x;
	yLocation += y;
	movesLeft--;
}
void Player::renderStats() {
	cout << getName() << "\'s Stats:" << endl;
	cout << "Major:                " << majorList[getMajor()] << endl;
	cout << "Code Tracing Skill:   " << getCodeTracingSkill() << endl;
	cout << "Code Writing Skill:   " << getCodeWritingSkill() << endl;
	cout << "Data Structure Skill: " << getDataStructureSkill() << endl;
	cout << "Abstraction Skill:    " << getAbstractionSkill() << endl;
	cout << "Moves per class:      " << getNumMoves() << endl;
	cout << "Moves Left:           " << getMovesLeft() << endl;
	cout << "Stuff: ";
	if (inventory.begin() != inventory.end()) {
		vector<Item*>::iterator itEnd = inventory.end() - 1;
		for (vector<Item*>::iterator it = inventory.begin(); it != itEnd; it++) {
			cout << (*it)->getName() << ", ";
		}
		
		cout << (*itEnd)->getName() << endl;
	}
	else {
		cout << "Nada! Ziltch! You have NOTHING!!!" << endl;
	}
	
	
}
Player* Player::getInstance() {
	if (!p_instance) {
		p_instance = new Player();
	}
	return p_instance;
}
void Player::setStats(int traceSkill, int writeSkill, int dataSkill, int abSkill, int moves) {
	CodeTracingSkill = traceSkill;
	CodeWritingSkill = writeSkill;
	DataStructureSkill = dataSkill;
	AbstractionSkill = abSkill;
	numMoves = moves;
	movesLeft = moves;
}
void Player::setMajor(Major m) {
	maj = m;
	if (m == IS) {
		setStats(0, 0, 0, 0, 16);
	}
	else if (m == DET) {
		setStats(2, 0, 2, 3, 12);
	}
	else if (m == CS) {
		setStats(3, 3, 2, 2, 10);
	}
	else if (m == CSM) {
		setStats(10, 8, 6, 6, 6);
	}
}
bool Player::hasItem(Item* i) {
	for (vector<Item*>::iterator it = inventory.begin(); it != inventory.end(); it++) {
		if ((*it) == i) {
			return true;
		}
	}
	
	return false;
}
void Player::addItem(Item* i) {
	if (!hasItem(i)) {
		inventory.push_back(i);
	}
}
void Player::removeItem(Item* i) {
	for (vector<Item*>::iterator it = inventory.begin(); it != inventory.end(); it++) {
		if ((*it) == i) {
			inventory.erase(it);
			return;
		}
	}
}
void Player::talk() const {
	block("Look at you... Talking to yourself... Loser.");
}
void Player::pickup() {
	// Hidden Cheater Pen
	if (getLocation() == 0 && Level::getInstance()->currentLevel() == 1) {
		string result = "You go down to the floor for literally no reason because you're crazy, but you notice a very small pen on the ground.\n";
		result += "You collected a Cheater Pen! Looking down, you see another one that wasn't there before! Are they infinite in supply?"; // Yes
		result += "Tracing Skill +10!\n";
		result += "Writing Skill +10!\n";
		addTracingSkill(10);
		addWritingSkill(10);
		block(result);
		return;
	}
	
	block("You picked yourself up cause you were feeling down. Now you're ready to rumble! (There is no item on your current spot)");
}
void Player::reset() {
	xLocation = 0;
	yLocation = 0;
	movesLeft = numMoves;
}

int Player::nameSize()
{
	int i = 0;
	while( name[i] != 0 )
	{
		i++;	
	}
	return i;
}

// NPC implementations:
NPC* NPC::make_NPC(int choice, int x, int y) {
	if (choice == 1)
		return new Homer(x, y);
	else if (choice == 2)
		return new Prather(x, y);
	else if (choice == 3)
		return new Reeves(x, y);
	else if (choice == 4)
		return new Nathan(x, y);
	else if (choice == 5)
		return new Seth(x, y);
	else if (choice == 6)
		return new Caleb(x, y);
}

// Specific NPC implementations
void Homer::talk()
{
	if(getNumTalks() == 0 && Level::getInstance()->currentLevel() == 1)		
	{	
		block("Dr. Homer: I like cows, people, and sheep :) I dream in binary, just by talking to me you got smarter!\nTracing Skill + 2! \nWriting Skill + 2!");
		incrementTalks();
		Player::getInstance()->addTracingSkill(2);
		Player::getInstance()->addWritingSkill(2);
		
	}
	else if (getNumTalks() == 0 && Level::getInstance()->currentLevel() == 2) {
		block("Dr. Homer: (points at board) Here's what a map is! Here's a quiz on it! You'll do fine.\nYou take the quiz and actually seem to understand it. Huh. What a pleasant surprize!\nData Structure Skill +3.");
		incrementTalks();
		Player::getInstance()->addDataStructureSkill(3);
	}
	else if(getNumTalks() == 1)
	{
		string saying = "Dr. Homer: Ah, the smart student always returns and asks for more. How can I help?\n";
		saying += "A. Improve my tracing.\n";
		saying += "B. Improve my writing.\n";
		saying += "C. Improve my Data Structures skill.";
		block(saying);
		
		cout << endl << endl << "Choice? ";
		string choice;
		bool flag = true;
		getline(cin, choice);
		while (flag) {
			if (choice == "A" || choice == "a") {
				block("Dr. Homer does an excellent job explaining what several examples of code do, and helps you trace through a couple quizzes\nTracing Skill +3");
				Player::getInstance()->addTracingSkill(3);
				flag = false;
			}
			else if (choice == "B" || choice == "b") {
				block("Dr. Homer gives you an exercise of short mim-programs to write.\nYou complete it, and several things begin to make more sense.\nWriting Skill +3");
				Player::getInstance()->addWritingSkill(3);
				flag = false;
			}
			else if (choice == "C" || choice == "c") {
				block("Dr. Homer proudly presents several slides of information on queues, stacks, maps, and more using amazing shape animations.\nData Structures Skill +5");
				Player::getInstance()->addDataStructureSkill(5);
				flag = false;
			}
			else {
				cout << "As your choice, please enter only \"A\", \"B\", or \"C\". Try again." << endl << endl;
				cout << "Choice? ";
				getline(cin, choice);
			}
		}
		
		
		incrementTalks();
	}
	else {
		block("Dr. Homer: I already bestowed on you my power and knowledge, now GO, I must tend to my sheep.");
		incrementTalks();
	}
}
void Prather::talk()
{
	if(getNumTalks() == 0)
	{
		block("Dr. Prather: I stayed up too late playing WoW classic, lets watch some Star Wa... haha jk design patters! :(\nAbstraction Skill + 3!");
		incrementTalks();
		Player::getInstance()->addAbstractionSkill(3);
	}
	else if (getNumTalks() == 2) {
		block("Dr. Prather: Ha! I'm not just going to give you the answer to Tuple...\nWell...\nit is kinda hard...\nAnd has some things I never told you about...\nOk fine.\nAbstraction Skill + 2!\nWriting Skill + 1!");
		incrementTalks();
		Player::getInstance()->addAbstractionSkill(2);
		Player::getInstance()->addWritingSkill(1);
	}
	else if (getNumTalks() == 4) {
		block("Dr. Prather: Hey, you coming to prayer chapel today?");
		incrementTalks();
	}
	else if (getNumTalks() <= 9 && getNumTalks() != 1) {
		block("Dr. Prather: Ok, you've talked to me a lot recently, give me a second...");
		incrementTalks();
	}
	else if (getNumTalks() == 10) {
		string result = "Dr. Prather: FINALLY everyone else is gone, now I can talk to you!\nJust so you know... I'm secretly part of the Clap Gang!\n";
		result += "*Dr. Prather claps loudly. Suddenly you feel a great rush as everything in OOP suddenly makes perfect sense...*\n";
		result += "Couldn't do that with everyone else around, but that magical clap will give you the knowledge to pass the test.\n";
		result += "Tracing Skill + 100!\n";
		result += "Writing Skill + 100!\n";
		result += "Data Structure Skill + 100!\n";
		result += "Abstraction Skill + 100!";
		block(result);
		Player::getInstance()->addTracingSkill(100);
		Player::getInstance()->addWritingSkill(100);
		Player::getInstance()->addDataStructureSkill(100);
		Player::getInstance()->addAbstractionSkill(100);
		incrementTalks();
	}
	else if (getNumTalks() > 10) {
		block("Dr. Prather: Just take the test already, now that I've clapped all is said and done.");
		incrementTalks();
	}
	else
	{
		block("Dr. Prather: You turned in your program late? That's rough buddy.");
		incrementTalks();
	}
}
void Reeves::talk()
{
	if(getNumTalks() == 0)
	{
		block("Dr. Reeves: Type Faster... You're Fired\nTracing Skill + 2!\nWriting Skill + 2!");
		incrementTalks();
		Player::getInstance()->addTracingSkill(2);
		Player::getInstance()->addWritingSkill(2);
	}
	else
	{
		block("Dr. Reeves: Okay if you show me 100wpm I'll re-hire you, but not today, as of now you're still fired.");
		incrementTalks();
	}
}
void Nathan::talk()
{
	if(getNumTalks() == 0 && Level::getInstance()->currentLevel() == 1)
	{
		block("Nathan: *looks at code* What are you even doing here... lets think about this...\nTracing Skill + 2!\nWriting Skill + 2!");
		incrementTalks();
		Player::getInstance()->addTracingSkill(2);
		Player::getInstance()->addWritingSkill(2);
	}
	else if(getNumTalks() == 1 && Level::getInstance()->currentLevel() == 1)
	{
		block("Nathan: Nested for loops? Fun times! So let's walk through this...\nTracing Skill +3!\nWriting Skill +2!");
		incrementTalks();
		Player::getInstance()->addTracingSkill(3);
		Player::getInstance()->addWritingSkill(2);
	}
	else if(getNumTalks() == 0 && Level::getInstance()->currentLevel() == 2)
	{
		block("Nathan: *looks at code* So, what data structure would be best to use here?... lets think about this...\nTracing Skill + 1!\nWriting Skill + 2!\nData Structure Skill +2!");
		incrementTalks();
		Player::getInstance()->addTracingSkill(1);
		Player::getInstance()->addWritingSkill(2);
		Player::getInstance()->addDataStructureSkill(2);
	}
	else if(getNumTalks() == 1 && Level::getInstance()->currentLevel() == 2)
	{
		block("Nathan: Recursion? Fun times! So let's walk through this...\nTracing Skill +2!\nData Strcture Skill +2!\nAbstraction Skill +1!");
		incrementTalks();
		Player::getInstance()->addTracingSkill(2);
		Player::getInstance()->addDataStructureSkill(2);
		Player::getInstance()->addAbstractionSkill(1);
	}
	else if(getNumTalks() == 0 && Level::getInstance()->currentLevel() == 3)
	{
		block("Nathan: *looks at code* Yeah, Tuple is pretty rough...\nIt might help to think of it in this way.\nTracing Skill + 1!\nWriting Skill + 2!\nAbstraction +2!");
		incrementTalks();
		Player::getInstance()->addTracingSkill(1);
		Player::getInstance()->addWritingSkill(2);
		Player::getInstance()->addAbstractionSkill(2);
	}
	else if(getNumTalks() == 1 && Level::getInstance()->currentLevel() == 3)
	{
		block("Nathan: Classes? Fun times! So let's think about how this works...\nTracing Skill +1!\nAbstraction Skill +3!");
		incrementTalks();
		Player::getInstance()->addTracingSkill(1);
		Player::getInstance()->addAbstractionSkill(3);
	}
	else
	{
		block("Nathan: I need to help somone else now. You got your 5 minutes!");
		incrementTalks();
	}
}
void Seth::talk()
{
	if(getNumTalks() == 0)
	{
		block("Seth: *eminates cool guy vibes*\nWriting Skill + 1 ");
		incrementTalks();
		Player::getInstance()->addWritingSkill(1);
	}
	else
	{
		block("Seth: *still eminating cool guy vibes but this time you feel unwelcome*");
		incrementTalks();
	}
}
void Caleb::talk()
{
	if(getNumTalks() == 0)
	{ 
		block("Caleb: DUDE, send me your computer specs later?! Here are some more RGB ideas!\nWriting Skill + 1!");
		incrementTalks();
		Player::getInstance()->addWritingSkill(1);
	}
	else
	{
		block("Caleb: I'll have to get back to you my dude, my residents are going nuts right now! CYA!");
		incrementTalks();
	}
}

// Level implementations
Level::Level() : _gameOver(false) {
	lvlNum = 1; // Start at level 1, P1
	
	for (int i = 0; i < 16; i++) {
		map[i] = '*';
	}
	
	// Add NPC's and items for P1 Level Here
	npcs.push_back(NPC::make_NPC(1,3,3)); // Dr. Homer at (3,3)
	npcs.push_back(NPC::make_NPC(4,3,0)); // Nathan at (3,0)
	npcs.push_back(NPC::make_NPC(6,0,3)); // Calab at (0,3)
	
	items.push_back(Item::make_Item(1,1,1)); // razerMouse at (1,1)
	items.push_back(Item::make_Item(2,1,3)); // rgbkeyboard at (1,3)
}
Level::~Level() {
	for (vector<NPC*>::iterator it = npcs.begin(); it != npcs.end(); it++) {
		delete (*it);
	}
	for (vector<Item*>::iterator it = items.begin(); it != items.end(); it++) {
		if (Player::getInstance()->hasItem(*it))
			delete (*it);
	}
}
Level* Level::getInstance() {
	if (!l_instance) {
		l_instance = new Level();
	}
	return l_instance;
}
void Level::talkResult() {
	// Get the player and location
	Player* p = Player::getInstance();
	int playerLocation = p->getLocation();
	
	// Talk to the NPC if on the same space
	for (vector<NPC*>::iterator it = npcs.begin(); it != npcs.end(); it++) {
		if ((*it)->getLocation() == playerLocation) {
			(*it)->talk();
			return;
		}
	}
	
	// Talk to yourself if no one on the same space
	p->talk();
}
void Level::pickupResult() {
	// Get the player and location
	Player* p = Player::getInstance();
	int playerLocation = p->getLocation();
	
	// Pickup Item if on the same space
	for (vector<Item*>::iterator it = items.begin(); it != items.end(); it++) {
		if ((*it)->getLocation() == playerLocation) {
			(*it)->pickup();
			items.erase(it);
			return;
		}
	}
	
	// Talk to yourself if no one on the same space
	p->pickup();
}
void Level::renderKey() {
	// Output the player
	cout << "Key: U = You, the player" << endl;
	
	// Output the NPCs
	for (vector<NPC*>::iterator it = npcs.begin(); it != npcs.end(); it++) {
		cout << "     " << (*it)->getSymbol() << " = " << (*it)->getName() << endl;
	}
	
	// Output the floor things
	cout << "     ! = Mystery Item" << endl;
	cout << "     * = Empty space (Or is it? ... )" << endl;
}
void Level::render() {
	// Fill map
	for (int i = 0; i < 16; i++) {
		map[i] = '*';
	}
	
	// Place Objects/NPC's
	for (vector<NPC*>::iterator it = npcs.begin(); it != npcs.end(); it++) {
		map[(*it)->getLocation()] = (*it)->getSymbol();
	}
	for (vector<Item*>::iterator it = items.begin(); it != items.end(); it++) {
		map[(*it)->getLocation()] = '!';
	}
	
	// Place player (on top of NPC's and objects if necessary).
	Player* p = Player::getInstance();
	map[p->getLocation()] = 'U';
	
	// Render map
	for (int i = 0; i < 16; i++ ) {
		cout << map[i];
		if (i%4 == 3) {
			cout << endl;
		}
	}
}
void Level::setLevel(bool newLevel) { // Accepts a boolean, is true if a new level needs to be created
	// If a new level does not need to be created (they didn't pass), don't do anything except reset the Player
	if (!newLevel) {
		Player::getInstance()->reset();
	}
	// If they passed and the new current level is level 2, P2 (add more flavor here)
	else if (lvlNum == 2) {
		// Flavor Text
		block("Great job passing an entry level class :)\nNow its time to learn a little bit more about behind the scences and everything that Dr.Homer said we would talk about later is now being talked about!\nAlthough it's exciting its more challenging.");
		
		// Clear the current board
		for (vector<NPC*>::iterator it = npcs.begin(); it != npcs.end(); it++) {
			delete (*it);
		}
		npcs.clear();
		for (vector<Item*>::iterator it = items.begin(); it != items.end(); it++) {
			if (Player::getInstance()->hasItem(*it))
				delete (*it);
		}
		items.clear();
		
		// Reset Player
		Player::getInstance()->reset();
		
		// Fill map with empty spaces
		for (int i = 0; i < 16; i++) {
			map[i] = '*';
		}
		
		// Add NPC's and items for P2 Level Here
		npcs.push_back(NPC::make_NPC(3,3,3)); // Dr. Reeves at (3,3)
		npcs.push_back(NPC::make_NPC(4,0,3)); // Nathan at (0,3)
		npcs.push_back(NPC::make_NPC(1,3,0)); // Dr.Homer at (3,0)
		npcs.push_back(NPC::make_NPC(5,2,2)); // Seth at (2,2)
		
		items.push_back(Item::make_Item(3,3,1)); // DDR3 at (3,2)
		items.push_back(Item::make_Item(6,1,2)); // A stack of boxes at (1,2)
	}
	// If they passed and the new current level is level 3, OOP (add more flavor here)
	else {
		// Clear the current board
		for (vector<NPC*>::iterator it = npcs.begin(); it != npcs.end(); it++) {
			delete (*it);
		}
		npcs.clear();
		for (vector<Item*>::iterator it = items.begin(); it != items.end(); it++) {
			if (Player::getInstance()->hasItem(*it))
				delete (*it);
		}
		items.clear();
		
		// Reset Player
		Player::getInstance()->reset();
		
		// Fill map with empty spaces
		for (int i = 0; i < 16; i++) {
			map[i] = '*';
		}
		
		// Add NPC's and items for P1 Level Here
		npcs.push_back(NPC::make_NPC(2,3,3)); // Dr. Prather at (3,3)
		npcs.push_back(NPC::make_NPC(4,2,2)); // Nathan at (2,2)
		
		items.push_back(Item::make_Item(4,0,1)); // Fan at (0,1)
		items.push_back(Item::make_Item(5,2,0)); // Tree at (2,0)
	}
}
void Level::takeTest() {
	// If current level is level 1, P1
	if (lvlNum == 1) {
		// For P1 likely focus on tracing and writing.
		Player* p = Player::getInstance();
		string results = "";
		bool passed = true;
		results += "Code Tracing Ability? ";
		if (p->getCodeTracingSkill() < 5) {
			results += "insufficient\n";
			passed = false;
		}
		else if (p->getCodeTracingSkill() < 12) {
			results += "sufficient... to pass... this time\n";
		}
		else {
			results += "Excellent!\n";
		}
		
		results += "Code Writing Ability? ";
		if (p->getCodeWritingSkill() < 4) {
			results += "insufficient\n";
			passed = false;
		}
		else if (p->getCodeWritingSkill() < 10) {
			results += "sufficient... to pass... this time\n";
		}
		else {
			results += "Excellent!";
		}
		
		block(results);
		sleep(1);
		
		// Determine if passed or failed and respond appropriately
		if (!passed) {
			block("Oof. You went in to take that test and got clapped bro.\nOuch.\nGoing to have to try taking P1 again...\nMaybe try using the \"train\" command for struggling subjects.");
			setLevel(false);
			cout << endl << "You have " << Player::getInstance()->getMovesLeft() << " moves until the Athene Final!" << endl;
			render();
			return;
		}
		
		block("Phew, you passed! That Athene Test was something else wasn't it?\nBut, you ain't finished yet! You still got at least 2 more years of this stuff!\nOn to P2!");
		cout << endl;
		sleep(1);
		lvlNum++;
		setLevel(true); // Also prints something
		sleep(1);
		string intro = "You walk into the Programming II classroom to find, to your surprize, two professors: Dr. Homer and Dr. Reeves.\n";
		intro += "You also notice Nathan is back as your tutor again. He sure is helpful for leaning many things.\n";
		intro += "You also heard this strange sound come from right above you... Might be nothing, but you have no time to waste! The P2 final will be soon!";
		block(intro);
		sleep(2);
		cout << "You have " << Player::getInstance()->getMovesLeft() << " moves until the Athene Final!" << endl;
		render();
		return;
	}
	// If current level is level 2, P2
	else if (lvlNum == 2) {
		// For P2 likely focus on tracing, writing, and Data Structures.
		Player* p = Player::getInstance();
		string results = "";
		bool passed = true;
		results += "Code Tracing Ability? ";
		if (p->getCodeTracingSkill() < 12) {
			results += "insufficient\n";
			passed = false;
		}
		else if (p->getCodeTracingSkill() < 25) {
			results += "sufficient... to pass... this time\n";
		}
		else {
			results += "Excellent!\n";
		}
		
		results += "Code Writing Ability? ";
		if (p->getCodeWritingSkill() < 10) {
			results += "insufficient\n";
			passed = false;
		}
		else if (p->getCodeWritingSkill() < 20) {
			results += "sufficient... to pass... this time\n";
		}
		else {
			results += "Excellent!\n";
		}
		
		results += "Data Structures Ability? ";
		if (p->getDataStructureSkill() < 10) {
			results += "insufficient\n";
			passed = false;
		}
		else if (p->getDataStructureSkill() < 12) {
			results += "sufficient... to pass... this time\n";
		}
		else {
			results += "Excellent!";
		}
		
		block("Phew, you passed! And you thought P1 was hard!?\nBut, you still aren't finished yet! You still got the most dreaded class of all...!\nOOP...");
		cout << endl;
		sleep(1);
		lvlNum++;
		setLevel(true);
		string intro = "You hesitantly walk in to Object Oriented Programming.\n";
		intro += "You first notice Nathan is back as your tutor again. Thank goodness, you'll need him.\n";
		intro += "You look over ar your professor, Dr. Prather. He seems like an approachable nice fellow... He's probably worth talking to... A lot";
		block(intro);
		sleep(2);
		cout << "You have " << Player::getInstance()->getMovesLeft() << " moves until the Athene Final!" << endl;
		render();
		return;
	}
	// If current level is level 3, OOP: The final level
	else {
		// For OOP likely focus on tracing, writing, and Abstraction.
		block("Alright everyone times up lockdown should be closing soon so get those final answers in, let's see the results!");
		sleep(2);
		cout << "\nSUMMING YOUR SCORE\n";
		for(int i = 0; i < 5; i++)
		{
			sleep(1); //the programs waits 1 second
			cout << "||";
		}
		cout << "\nLOADING SCORES\n";
		for(int i = 0; i < 5; i++)
		{
			sleep(1); //the programs waits 1 second
			cout << "||";
		}
		
		Player* p = Player::getInstance();
		bool passed = true;
		if (p->getAbstractionSkill() < 10) {
			passed = false;
		}
		int skillSum = p->getCodeTracingSkill() + p->getCodeWritingSkill() + p->getDataStructureSkill() + p->getAbstractionSkill();
		if (skillSum < 50 || !passed) {
			block("Oof. You went in to take that test and got clapped bro and since Carter got a 89 there isn't much curve.\nOuch.\nGoing to have to try taking OOP again...");
			setLevel(false);
			cout << endl << "You have " << Player::getInstance()->getMovesLeft() << " moves until the Athene Final!" << endl;
			render();
			return;
		}
	
		block("Phew, holy gUaCaMoLe you passed!\nIn fact you got the highest score! Everyone else is sad because the curve won't help them now BUT You won the game!\nCongrats!");
		_gameOver = true;
		sleep(3);
		return;
	}
}

// Base and handler implementations:
string Base::toLower(string s) {
	string ret = "";
	int i = 0;
	while(s[i] != 0) {
		ret += tolower(s[i]);
		i++;
	}
	return ret;
}

void MoveHandler::handle(string input) {
	// Gets the first word, makes sure it matching a move command, if not it gets passed
	stringstream ss(input);
	string command, direction;
	ss >> command;
	if (toLower(command) == "move") {
		Player* p = Player::getInstance();
		Level* l = Level::getInstance();
		int currentLocation = p->getLocation();
		
		if (p->getMovesLeft() <= 0) {
			block("You have no time to move! It's time to take the final! Type \"test\" to take the final.(Yikes)");
			return;
		}
		
		ss >> direction;
		if (toLower(direction) == "left") {
			if (currentLocation%4 == 0) {
				block("*thump* Cannot move left: There is a wall there. Try a different command.");
				return;
			}
			else {
				p->move(-1,0);
			}
		}
		else if (toLower(direction) == "right") {
			if (currentLocation%4 == 3) {
				block("*thump* Cannot move right: There is a wall there. Try a different command.");
				return;
			}
			else {
				p->move(1,0);
			}
		}
		else if (toLower(direction) == "up") {
			// Hidden Clap on P2 level.
			if (currentLocation == 0 && l->currentLevel() == 2) {
				string result = "You followed the noise back outside the classroom.\nSuddenly, you feel the urge -- You clap as loud as you can.\n";
				result += "You suddenly feel like you know everything P2 has to offer.\nTracing Skill +50!\nWriting Skill +50!\nData Structure Skill +50!";
				block(result);
				p->addTracingSkill(50);
				p->addWritingSkill(50);
				p->addDataStructureSkill(50);
				block("You then return to the classroom, feeling like a champ.\nYou can follow the noise again anytime you wish. [Nothing has changed, the map or your number of moves.]");
				return;
			}
			
			if (currentLocation < 4) {
				block("*thump* Cannot move up: There is a wall there. Try a different command.");
				return;
			}
			else {
				p->move(0,-1);
			}
		}
		else if (toLower(direction) == "down") {
			if (currentLocation > 11) {
				block("*thump* Cannot move down: There is a wall there. Try a different command.");
				return;
			}
			else {
				p->move(0,1);
			}
		}
		else {
			cout << "\"" << input << "\" is moving in an unknown direction. The known directions are: \"left\", \"right\", \"up\", \"down\"." << endl;
			return;
		}
		cout << endl << "You have " << p->getMovesLeft() << " moves until the Athene Final!" << endl;
		// If that was their last move of the level
		if (p->getMovesLeft() <= 0) {
			cout << "You can still use any commands such as \"pickup\" or \"talk\", but you cannot move (or train)! It is time for the test! Type \"test\" to take the test." << endl;
			return;
		}
		
		// Otherwise, render the map and return
		l->render();
		return;
	}
	
	// If it was not the move command, we pass to next handler
	Base::handle(input);
}

void TrainHandler::handle(string input) {
	// Gets the first word, makes sure it matching a train command, if not it gets passed
	stringstream ss(input);
	string command, skill;
	ss >> command;
	if (toLower(command) == "train") {
		Player* p = Player::getInstance();
		Level* l = Level::getInstance();
		
		if (p->getMovesLeft() <= 0) {
			block("You have no time to train! It's time to take the final! Type \"test\" to take the final.(Yikes)");
			return;
		}
		
		ss >> skill;
		if (toLower(skill) == "tracing") {
			if (p->getMajor() == CSM || p->getMajor() == CS) {
				p->addTracingSkill(1);
				block("You went back through some old code, and found the errors pretty quick, resulting in a small improvement.\nTracing Skill +1");
			}
			else {
				p->addTracingSkill(2);
				block("You worked through several quizzes you previously got 0 on, but its starting to make sense...\nTracing Skill +2");
			}
		}
		else if (toLower(skill) == "writing") {
			if (p->getMajor() == CSM || p->getMajor() == CS) {
				p->addWritingSkill(1);
				block("You decided to do a couple practice homeworks... They were PURE CHEESE, but you still improved some.\nWriting Skill +1");
			}
			else {
				p->addWritingSkill(2);
				block("You decided to do a couple practice homeworks... You struggled quite a bit with it, but it begins to make more sense.\nWriting Skill +2");
			}
		}
		else if (toLower(skill) == "data") {
			if (p->getMajor() == CSM || p->getMajor() == CS) {
				p->addDataStructureSkill(2);
				block("Now this is the stuff you enjoy doing! You could mess with Data Structures all day. All the enthusiasm better improves your training.\nData Structures Skill +2");
			}
			else {
				p->addDataStructureSkill(1);
				block("Finally, something that seems a bit easier conceptually. You don't remain as focused as you should when studying though.\nData Structures Skill +1");
			}
		}
		else if (toLower(skill) == "abstraction") {
			if (p->getMajor() == CSM || p->getMajor() == CS) {
				p->addDataStructureSkill(2);
				block("Ah, now Abstraction picks your brain a bit, but you find thinking in this way generally helpful.\nAbstraction Skill +2");
			}
			else {
				p->addDataStructureSkill(1);
				block("Abstraction is a bit weirder than you originally thought. But, studying still gets some things accomplished.\nAbstraction Skill +1");
			}
		}
		else {
			cout << "\"" << input << "\" is training in an unknown skill. The known directions are: \"tracing\", \"writing\", \"data\", \"abstraction\"." << endl;
			return;
		}
		p->decrementMovesLeft();
		cout << endl << "You have " << p->getMovesLeft() << " moves until the Athene Final!" << endl;
		// If that was their last move/train of the level
		if (p->getMovesLeft() <= 0) {
			cout << "You can still use any commands such as \"pickup\" or \"talk\", but you cannot move (or train)! It is time for the test! Type \"test\" to take the test." << endl;
			return;
		}
		
		// Otherwise, render the map and return
		l->render();
		return;
	}
	
	// If it was not the move command, we pass to next handler
	Base::handle(input);
}

void TalkHandler::handle(string input) {
	if (toLower(input) == "talk") {
		Level* l = Level::getInstance();
		l->talkResult();
		return;
	}
	
	// If talk is not entered, it gets passed
	Base::handle(input);
}

void ItemHandler::handle(string input) {
	if (toLower(input) == "pickup") {
		Level* l = Level::getInstance();
		l->pickupResult();
		return;
	}
	
	// If pickup is not entered, it gets passed
	Base::handle(input); 
}

void KeyHandler::handle(string input) {
	if (toLower(input) == "key") {
		Level::getInstance()->renderKey();
		return;
	}
	
	// If key is not entered, it gets passed
	Base::handle(input);
}

void StatsHandler::handle(string input) {
	if (toLower(input) == "stats") {
		Player::getInstance()->renderStats();
		return;
	}
	
	// If stats is not entered, it gets passed
	Base::handle(input);
}

void TestHandler::handle(string input) {
	if (toLower(input) == "test") {
		if (Player::getInstance()->getMovesLeft() > 0) {
			string answer = "";
			bool flag = true;
			block("You still have moves left! Are you sure you want to take the test now? Y or N: ");
			while (flag) {
				getline(cin, answer);
				if (toLower(answer) == "yes" || toLower(answer) == "y") {
					flag = false;
				}
				else if (toLower(answer) == "no" || toLower(answer) == "n") {
					return;
				}
				else {
					block("It's a yes or no question... Enter Y or N: ");
				}
			}
		}
		
		Level::getInstance()->takeTest();
		return;
	}
	
	// If test is not entered, it gets passed
	Base::handle(input);
}

void HelpHandler::handle(string input) {
	if (toLower(input) == "help") {
		cout << "Here is a list of commands: " << endl;
		cout << "	move [left, right, up, down]" << endl;
		cout << "	train [tracing, writing, data, abstraction]" << endl;
		cout << "	talk" << endl;
		cout << "	pickup" << endl;
		cout << "	key" << endl;
		cout << "	stats" << endl;
		cout << "	test" << endl;
		cout << "	help (duh, you just used it)" << endl;
		cout << "	quit" << endl;
		return;
	}
	
	// If they're not asking for help, it gets passed
	Base::handle(input);
}

void DefaultHandler::handle(string input) {
	cout << "\"" << input << "\" is an unknown command. Type \"help\" for a list of known commands." << endl;
}

// So the player can enter any (reasonable) length name and the text wrapper still works
void space()
{
	for(int k = 0; k < 28-(Player::getInstance()->nameSize()); k++)
		cout << " ";
}
