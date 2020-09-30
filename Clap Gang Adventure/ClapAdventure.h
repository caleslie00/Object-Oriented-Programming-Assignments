#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Includes an enumerated list of majors for anti-typo measures.
enum Major { IS, DET, CS, CSM, NONE };

// Will make text look cool.
void block(string s);

class Item
{
	private:
		std::string name;
		int xLocation;
		int yLocation;
    public:
        Item(std::string n, int x, int y) : name(n), xLocation(x), yLocation(y) {}
        static Item* make_Item(int choice, int x, int y);
		
		std::string getName() const { return name; }
		int getX() const { return xLocation; }
		int getY() const { return yLocation; }
		int getLocation() { return 4 * yLocation + xLocation; }
		
		virtual void pickup() = 0;
		virtual void drop() = 0;
};
class razerMouse : public Item {
	public:
		razerMouse(int x, int y) :  Item("razorMouse", x, y) {}
		void pickup();
		void drop();
};
class rgbKeyboard : public Item {
	public:
		rgbKeyboard(int x, int y) :  Item("rgbKeyboard", x, y) {}
		void pickup();
		void drop();
};
class DDR3 : public Item {
	public:
		DDR3(int x, int y) :  Item("DDR3", x, y) {}
		void pickup();
		void drop();
};
class Boxes : public Item {
	public:
		Boxes(int x, int y) : Item("A Stack of Boxes", x, y) {}
		void pickup();
		void drop();
};
class Fan : public Item {
	public:
		Fan(int x, int y) :  Item("Fan", x, y) {}
		void pickup();
		void drop();
};
class Tree : public Item {
	public:
		Tree(int x, int y) : Item("Tree", x, y){}
		void pickup();
		void drop();
};

class Player {
	private:
		std::string name;
		Major maj;
		
		// Will keep an ongoing track of each programming skill.
		int CodeTracingSkill;
		int CodeWritingSkill;
		int DataStructureSkill;
		int AbstractionSkill;
		
		int numMoves;
		int movesLeft;
		std::vector<Item*> inventory;
		int xLocation;
		int yLocation;
		
		static Player* p_instance;
		Player() : name(""), maj(NONE), CodeTracingSkill(0), CodeWritingSkill(0), DataStructureSkill(0), AbstractionSkill(0), xLocation(0), yLocation(0), numMoves(0), movesLeft(0) {}
		
	
	public:
		~Player();
		
		std::string getName() const { return name; }
		Major getMajor() const { return maj; }
		int getCodeTracingSkill() const { return CodeTracingSkill; }
		int getCodeWritingSkill() const { return CodeWritingSkill; }
		int getDataStructureSkill() const { return DataStructureSkill; }
		int getAbstractionSkill() const { return AbstractionSkill; }
		int getNumMoves() const { return numMoves; }
		int getMovesLeft() const { return movesLeft; }
		int getLocation() const { return 4 * yLocation + xLocation; }
		void renderStats();
		int nameSize();
		
		bool hasItem(Item* i);
		void addItem(Item* i);
		void removeItem(Item* i);
		
		// For creation and referance of player
		static Player* getInstance();
		void setStats(int traceSkill, int writeSkill, int dataSkill, int abSkill, int moves);
		void setMajor(Major m);
		void setName(std::string n) { name = n; }
		void addTracingSkill(int added) { CodeTracingSkill += added; }
		void addWritingSkill(int added) { CodeWritingSkill += added; }
		void addDataStructureSkill(int added) { DataStructureSkill += added; }
		void addAbstractionSkill(int added) { AbstractionSkill += added; }
		
		// Functions for player actions
		void move(int x, int y);
		void decrementMovesLeft() { movesLeft--; }
		void talk() const;
		void pickup();
		
		// Function for resetting a level
		void reset();
};
// Allocating and initializing Player's static data member.
Player* Player::p_instance = 0;


class NPC
{
	private:
		std::string name;
		char symbol;
		int xLocation;
		int yLocation;
		int numTalks;

    public:
    	NPC(std::string n, char s, int x, int y) : name(n), symbol(s), xLocation(x), yLocation(y), numTalks(0) {}
        static NPC* make_NPC(int choice, int x, int y);
		
		std::string getName() const { return name; }
		char getSymbol() const { return symbol; }
		int getLocation() { return 4 * yLocation + xLocation; }
		
		virtual void talk() = 0;
		void incrementTalks() {	numTalks++; }
		int getNumTalks() const { return numTalks; }
};

class Homer : public NPC 
{
	public:
		Homer(int x, int y) : NPC("Dr. Homer", 'H', x, y) {}
		void talk();
};

class Prather : public NPC 
{
	public:
		Prather(int x, int y) : NPC("Dr. Prather", 'P', x, y) {}
		void talk();
};

class Reeves : public NPC 
{
	public:
		Reeves(int x, int y) : NPC("Dr. Reeves", 'R', x, y) {}
		void talk();
};

class Nathan : public NPC 
{
	public:
		Nathan(int x, int y) : NPC("Nathan", 'N', x, y) {}
		void talk();
};

class Seth : public NPC 
{
	public:
		Seth(int x, int y) : NPC("Seth", 'S', x, y) {}
		void talk();
};

class Caleb : public NPC 
{
	public:
		Caleb(int x, int y) : NPC("Caleb", 'C', x, y) {}
		void talk();
};



// Each level likely needs a map layout
class Level {
	private:
		// NPC and Item vector
		std::vector<NPC*> npcs;
		std::vector<Item*> items;
		
		char map[16];
		int lvlNum;
		bool _gameOver;
		static Level* l_instance;
		Level();
		
	public:
		~Level();
		
		// For creation and referance of player
		static Level* getInstance();
		bool gameOver() { return _gameOver; }
		int currentLevel() { return lvlNum; }
		void talkResult();
		void pickupResult();
		void renderKey();
		void render();
		
		// Functions for testing and going to the each level
		void setLevel(bool newLevel);
		void takeTest();
};
// Allocating and initializing Player's static data member.
Level* Level::l_instance = 0;



// Example chain, simple linked list always adding to tail, handlers will handle commands
class Base {
	Base *next;
	public:
		// Functions for chain functionality
		Base() { next = 0; }
		void setNext(Base *n) { next = n; }
		void add(Base *n) {
			if (next)
				next->add(n);
			else
				next = n;
		}
		virtual void handle(std::string input) { next->handle(input); }
		
		// Helpful function for ignoring case.
		std::string toLower(std::string s);
};

// Handles move commands
class MoveHandler : public Base {
	public:
		void handle(std::string input);
};

class TrainHandler : public Base {
	public:
		void handle(std::string input);
};

class TalkHandler : public Base {
	public:
		void handle(std::string input);
};

class ItemHandler : public Base {
	public:
		void handle(std::string input);
};

class StatsHandler : public Base {
	public:
		void handle(std::string input);
};

class KeyHandler : public Base {
	public:
		void handle(std::string input);
};

class TestHandler : public Base {
	public:
		void handle(std::string input);
};

class HelpHandler : public Base {
	public:
		void handle(std::string input);
};

class DefaultHandler : public Base {
	public:
		void handle(std::string input);
};
