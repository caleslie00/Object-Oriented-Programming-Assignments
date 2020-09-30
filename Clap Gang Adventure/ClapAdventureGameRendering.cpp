#include "ClapAdventure.cpp"

int main()
{
	MoveHandler rootCommand;
	TrainHandler train;
	TalkHandler talk;
	ItemHandler pickup;
	KeyHandler key;
	StatsHandler stats;
	TestHandler test;
	HelpHandler help;
	DefaultHandler def;
	rootCommand.add(&train);
	rootCommand.add(&talk);
	rootCommand.add(&pickup);
	rootCommand.add(&key);
	rootCommand.add(&stats);
	rootCommand.add(&test);
	rootCommand.add(&help);
	rootCommand.add(&def);
	
	block("Welcome to the Clap Gang Adventure!! You are an incoming freshman looking forward to a new world of independence and knowledge,\nbut first you need to introduce yourself and declare a major!\nYou know you want somthing with computers but need to pick which specific path you will take.");
	cout << "Enter Name: ";
	string name;
	getline(cin, name);
	Player::getInstance()->setName(name);
	
	
	cout << "\n------------------------------------------------------------------------------------------------------\n";
	cout << "| Good luck to you, " << Player::getInstance()->getName() << "! You've signed up to take programming classes... Oof"; space(); cout << "|" << endl; 
	cout << "| You are a new Freshman technology student at ACU. Your major describes everything about yourself...|\n";
	cout << "| Choose a major:                                                                                    |\n";
	cout << "| A. IS                                                                                              |\n";
	cout << "| B. DET                                                                                             |\n";
	cout << "| C. CS                                                                                              |\n";
	cout << "| D. Double Major in Computer Science and Mathematics                                                |\n";
	cout << "------------------------------------------------------------------------------------------------------";
	cout << endl << endl << "Choice? ";
	string choice;
	bool flag = true;
	getline(cin, choice);
	while (flag) {
		if (choice == "A" || choice == "a") {
			cout << endl;
			cout << "------------------------------------------------------------------------------------------------------------------------------------\n";
			cout << "|As a typical IS major, you aren't too naturally talented at programming. Your skills lie mostly in other areas (to put it nicely).|" << endl;
			cout << "|Since programming is a different monster, you need to spend a lot more time developing your skills.                               |" << endl;
			cout << "|Luckily, you're and IS major... So you got plenty of time.                                                                        |" << endl;
			cout << "|Base stats: non-existant. Number of moves: Plenty.                                                                                |" << endl;
			cout << "------------------------------------------------------------------------------------------------------------------------------------\n";
			Player::getInstance()->setMajor(IS);
			flag = false;
		}
		else if (choice == "B" || choice == "b") {
			cout << endl;
			cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------\n";
			cout << "|As a typical DET major, you are decent at programming you learn, but you're much better at understanding the concepts rather than actual programming.|" << endl;
			cout << "|As such, you may need to spend more time developing your literal programming skills.                                                                 |" << endl;
			cout << "|DET isn't the easiest major time-wise *cough* IS *cough*... But you've still got the time to get the help you need to pass.                          |" << endl;
			cout << "|Base stats: Decent tracing, poor writing, decent data structures, good abstraction. Number of moves: Good.                                           |" << endl;
			cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------\n";
			Player::getInstance()->setMajor(DET);
			flag = false;
		}
		else if (choice == "C" || choice == "c") {
			cout << endl;
			string text = "As a typical CS major, these classes are exactly what you signed up for (what have you done to yourself?).";
			text += "\nFortunately, you have a general knack for these classes, so you won't need as much assistance.";
			text += "\nWhich is good because, being a CS major keeps you busy... You won't have a ton of time to get help in class, but it should be managable.";
			text += "\nBase stats: Generally decent. Number of moves: Fair.";
			block(text);
			Player::getInstance()->setMajor(CS);
			flag = false;
		}
		else if (choice == "D" || choice == "d") {
			cout << endl;
			cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------\n";
			cout << "|Ok, I'm really confused. Why on earth would you pick that answer. You better be a genious or something or else you're toast.                          |" << endl;
			cout << "|Why toast? Well, as a Double Major in Computer Science and Mathematics, you have literally no time to do anything (ok, a little, but practically none)|" << endl;
			cout << "|The only thing keeping you alive is your natural talent from the logical math background,                                                             |" << endl;
			cout << "|but you'll still need to make excellent use of the time you have if you want to make it through these classes. You're good, but not THAT good.        |" << endl;
			cout << "|Base stats: Excellent. Number of moves: Practically 0.                                                                                                |" << endl;
			cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------\n";
			Player::getInstance()->setMajor(CSM);
			flag = false;
		}
		else {
			cout << "As your choice, please enter only \"A\", \"B\", \"C\", or \"D\". Try again." << endl << endl;
			cout << "Choice? ";
			getline(cin, choice);
		}
	}
	
	cout << endl;
	cout << "Input \"help\" for a list of possible commands, or \"quit\" to quit at any time. Enjoy the game!" << endl;
	cout << "Press \'Enter\' to continue: ";
	string empty;
	getline(cin, empty);
	
	cout << endl << endl;
	string output = "You walk into your Programming 1 classroom. At the far opposite corner of the room is Dr. Homer, presenting some amazing animated shapes.\n";
	output += "You think you might've accidentally stepped on a rock as you came in just now, but meh. Probably nothing.";
	block(output);
	cout << "-- Input \"key\" for a guide to what the letters and symbols mean on the current map." << endl;
	
	cout << endl;
	cout << "You have " << Player::getInstance()->getMovesLeft() << " moves until the Athene Final!" << endl;
	Level::getInstance()->render();
	string command = "";
	cout << "--Enter command: ";
	getline(cin, command);
	cout << endl;
	while (command != "quit" && command != "Quit") {
		rootCommand.handle(command);
		cout << endl;
		if (Level::getInstance()->gameOver()) {
			break;
		}
		cout << "--Enter command: ";
		getline(cin, command);
		
		
	}
	cout << endl;
	block("Thank you for playing the Clap Gang Adventure!! We hope you've enjoyed. Never stop clapping.");
}
