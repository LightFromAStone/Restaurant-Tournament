/*
Peter Fakkel, Section 02, pfakkel@gmail.com
Description: This program simulates a tournament to help the user determine which restaurant to vist.
The user can add and remove restaurants from the list, shuffle and cut the order of the restaurants,
and of course run the tournament to find the winning restaurant based on the user's selections.

*/

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cmath>
#include <fstream>
using namespace std;

const int RESTAURANT_NOT_FOUND = -1;

int FindExistingRestaurant(string userEntry, const vector<string> currentList) {
	int foundAtPosition = RESTAURANT_NOT_FOUND;

	for (int i = 0; i < currentList.size(); ++i) {
		if (currentList.at(i) == userEntry) {
			foundAtPosition = i;
		}
	}
	return foundAtPosition;
}
void AddRestaurant(vector<string>& addingRestaurant) {
	const string END_INPUT = "stop";
	string userEntry;

	cout << endl << "Please enter the restaurant(s) you want to add. Type 'stop' to end entry: " << endl;

	while (userEntry != END_INPUT) {
		getline(cin, userEntry);
		if (userEntry == END_INPUT) {
			break;
		}
		else if (FindExistingRestaurant(userEntry, addingRestaurant) > RESTAURANT_NOT_FOUND) {
			cout << "That restaurant is already on the list, you can not add it again." << endl;
		}
		else {
			addingRestaurant.push_back(userEntry);
			cout << userEntry << " has been added." << endl;
		}
	}
	return;
}
void DisplayRestaurants(const vector<string> displayVector) {
	cout << endl << "Here are the current restaurants: " << endl << endl;
	for (int i = 0; i < displayVector.size(); ++i) {
		cout << "\t\"" << displayVector.at(i) << "\"" << endl;
	}
	return;
}
void RemoveRestaurants(vector<string>& removingRestaurant) {
	string userEntry;
	int restaurantLocation = 0;

	cout << endl << "What is the name of the restaurant you want to remove?" << endl;
	//cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, userEntry);
	restaurantLocation = FindExistingRestaurant(userEntry, removingRestaurant);
	if (restaurantLocation == RESTAURANT_NOT_FOUND) {
		cout << "That restaurant is not on the list, you can not remove it." << endl;
	}
	else {
		removingRestaurant.erase(removingRestaurant.begin() + restaurantLocation);
		cout << userEntry << " has been removed." << endl;
	}
	return;
}
vector<string> CutRestaurantList(const vector<string> listToCut) {
	vector<string> newList(listToCut.size());
	int numToCut = 0;
	const int MIN_TO_CUT = 0;
	bool obtainingInput = true;

	// Obtain Number to Cut //
	while (obtainingInput) {
		cout << endl << "How many restaurants should be taken from the top and put on the bottom?" << endl;
		cin >> numToCut;
		if (cin.fail() || numToCut < MIN_TO_CUT || numToCut > listToCut.size()) {
			cin.clear();
			cout << "The cut number must be between " << MIN_TO_CUT << " and " << listToCut.size() << endl;
		}
		else {
			obtainingInput = false;
		}
	}
	// Create New List //
	for (int i = numToCut; i < listToCut.size(); ++i) {
		newList.at(i - numToCut) = listToCut.at(i);
	}
	newList.resize(listToCut.size() - numToCut);
	for (int j = 0; j < numToCut; ++j) {
		newList.push_back(listToCut.at(j));
	}
	return newList;
}
vector<string> ShuffleRestaurants(const vector<string> listToShuffle) {
	vector<string> newList;
	vector<string> deckOne(listToShuffle.size() / 2);
	vector<string> deckTwo(listToShuffle.size() / 2);

	// Initialize Decks One and Two //
	for (int i = 0; i < deckOne.size(); ++i) {
		deckOne.at(i) = listToShuffle.at(i);
	}
	for (int j = deckTwo.size(); j < listToShuffle.size(); ++j) {
		deckTwo.at(j - deckTwo.size()) = listToShuffle.at(j);
	}
	// Shuffle Decks Together //
	for (int k = 0; k < deckOne.size(); ++k) {
		newList.push_back(deckTwo.at(k));
		newList.push_back(deckOne.at(k));
	}
	return newList;
}
int IsPowerOfTwo(const vector<string> listToCount) {
	const double FLOAT_COMPARISON = 0.0001;
	double listSize = 0.0;
	double powerOfTwo = 0.0;
	int powerNum = -1;

	listSize = listToCount.size();
	powerOfTwo = log10(listSize) / log10(2); // used to convert to base 2
	if (fabs(floor(powerOfTwo) - powerOfTwo) < FLOAT_COMPARISON) {
		powerNum = powerOfTwo;
	}
	return powerNum;
}
vector<string> BeginBattle(const vector<string> listOfContestants) {
	const int CHOICE_ONE = 1;
	const int CHOICE_TWO = 2;
	vector<string> winningContestants;
	bool obtainingInput = true;
	int userChoice = 0;

	for (int i = 0; i < listOfContestants.size() / 2; ++i) {
		while (obtainingInput) {
			cout << "Type \"" << CHOICE_ONE << "\" if you prefer " << listOfContestants.at(i + i) << " or" << endl;
			cout << "type \"" << CHOICE_TWO << "\" if you prefer " << listOfContestants.at(i + i + 1) << endl;
			cout << "Choice: " << endl << endl;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cin >> userChoice;
			if (cin.fail() || userChoice < CHOICE_ONE || userChoice > CHOICE_TWO) {
				cin.clear();
				cout << "Invalid choice" << endl;
			}
			else {
				obtainingInput = false;
			}
		}
		if (userChoice == CHOICE_ONE) {
			winningContestants.push_back(listOfContestants.at(i + i));
		}
		else {
			winningContestants.push_back(listOfContestants.at(i + i + 1));
		}
		obtainingInput = true;
	}
	return winningContestants;
}
void SaveRestaurantList(vector<string> vectorListToSave) {
	ofstream outFS;
	outFS.open("restaurantListFile.txt");
	if (!outFS.is_open()) {
		cout << "Could not open restaurantListFile.txt" << endl;
	}
	for (int i = 0; i < vectorListToSave.size(); ++i) {
		outFS << vectorListToSave.at(i);
		if (i < vectorListToSave.size() - 1) {
			outFS << endl;
		}
	}
	outFS.close();
	return;
}

int main() {
	const int INVALID_POWER = -1;
	bool isSelectingAction = true;
	bool isInvalid = false;
	int numOfRounds = 0;
	ifstream inFS;
	vector<string> restaurantList;
	vector<string> winningRestaurant;
	string userMenuAction;
	string addToList;
	string quitAction = "quit";
	string displayAction = "display";
	string addAction = "add";
	string removeAction = "remove";
	string cutAction = "cut";
	string shuffleAction = "shuffle";
	string battleAction = "battle";
	string optionsAction = "options";

	cout << "Welcome to the restaurant battle!  Enter \"options\" to see options." << endl;
// Load Restaurant List //
	inFS.open("restaurantListFile.txt");
	if (!inFS.is_open()) {
		cout << "Could not open restaurantListFile.txt" << endl;
		return 1;
	}
	while (!inFS.eof()) {
		getline(inFS, addToList);
		restaurantList.push_back(addToList);
	}
	inFS.close();
// Main Loop //
	while (isSelectingAction) {
		if (!isInvalid) {
			cout << endl;
			cout << "Enter your selection: ";
			cin >> userMenuAction;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}
		isInvalid = false;

		// Exit Main Loop //
		if (userMenuAction == quitAction) {
			cout << endl << "Goodbye!";
			isSelectingAction = false;
		}
		// Display Restaurants //
		else if (userMenuAction == displayAction) {
			DisplayRestaurants(restaurantList);
		}
		// Add Restaurant // 
		else if (userMenuAction == addAction) {
			AddRestaurant(restaurantList);
			SaveRestaurantList(restaurantList);
		}
		// Remove Restaurant //
		else if (userMenuAction == removeAction) {
			RemoveRestaurants(restaurantList);
			SaveRestaurantList(restaurantList);
		}
		// Cut Vector //
		else if (userMenuAction == cutAction) {
			restaurantList = CutRestaurantList(restaurantList);
			SaveRestaurantList(restaurantList);
		}
		// Shuffle Vector //
		else if (userMenuAction == shuffleAction) {
			// Check if list size is power of 2 //
			numOfRounds = IsPowerOfTwo(restaurantList);
			if (numOfRounds > INVALID_POWER) {
				restaurantList = ShuffleRestaurants(restaurantList);
			}
			else {
				cout << "The current tournament size (" << restaurantList.size() << ") is not a power ";
				cout << "of two (2, 4, 8...)." << endl;
				cout << "A shuffle is not possible. Please add or remove restaurants." << endl;
			}
			SaveRestaurantList(restaurantList);
		}
		// Start Tournament //
		else if (userMenuAction == battleAction) {
			/*
			FIXME:

			if (restaurantList.size() % 2 == 1) {
				isOddList = true;
				oddContestant = restaurantList.back();
				restaurantList.pop_back();
			}
			*/

			numOfRounds = IsPowerOfTwo(restaurantList);
			if (numOfRounds > INVALID_POWER) {
				winningRestaurant = restaurantList;
				for (int i = 1; i < numOfRounds + 1; ++i) {
					cout << endl << "Round: " << i << endl << endl;
					winningRestaurant = BeginBattle(winningRestaurant);
				}
				cout << "The winning restaurant is " << winningRestaurant.at(0) << "." << endl;
			}
			else {
				cout << "The current tournament size (" << restaurantList.size() << ") is not a power ";
				cout << "of two (2, 4, 8...)." << endl;
				cout << "A battle is not possible. Please add or remove restaurants." << endl;
			}
		}
		// Show Options Menu //
		else if (userMenuAction == optionsAction) {
			cout << endl;
			cout << "Please select one of the following options: " << endl << endl;
			cout << "quit  - Quit the program" << endl;
			cout << "display -  Display all restaurants" << endl;
			cout << "add - Add a restaurant" << endl;
			cout << "remove - Remove a restaurant" << endl;
			cout << "cut - \"Cut\" the list of restaurants" << endl;
			cout << "shuffle - \"Shuffle\" the list of restaurants" << endl;
			cout << "battle - Begin the tournament" << endl;
			cout << "options - Print the options menu" << endl;
		}
		// Invalid User Entry //
		else {
			cout << endl << "Invalid Selection" << endl;
			cin.clear();
			userMenuAction = optionsAction;
			isInvalid = true;
		}
	}

	system("pause");
	return 0;
}
