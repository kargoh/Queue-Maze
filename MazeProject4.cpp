#include <iostream>
#include <list>
#include <iterator>
#include <vector>
#include <queue>
#include <Windows.h> //you need this header to use Sleep()

using namespace std;

// template class
template <class T, class Container = deque<T> > class queue;

// declare global functions
void printMap();
void printQueue();
bool checkPath(int, int, int);
int getValue(int, int);
void setValue(int, int, int);
std::queue<vector<int>> popBackQueue(std::queue<vector<int>>);

// declare global variables
const int tileSize = 3;
const int rows = 5;
const int cols = 5;
int map[rows][cols] = {
	{2,1,0,0,0},
	{0,0,0,1,0},
	{1,0,1,1,0},
	{1,0,1,0,0},
	{1,3,1,1,1}
};

std::queue<std::vector<int>> coorQueue;


string mapString = "";

int main()
{
	cout << "Start!\n";
	coorQueue.push({0,0});
	cout << coorQueue.size();
	checkPath(0, 0, 0); // path starts at { 0, 0 }
	cout << "\nFinished!\n";
}

bool checkPath(int startValue, int row, int col) {
	printMap();
	cout << "\nQueue: ";
	printQueue();
	Sleep(250);

	// define value value to be set
	int endValue = 0;
	if (startValue == 4) endValue = 5;

	// check each direction for specific value
	if (
		getValue(row - 1, col) == 3 || getValue(row, col + 1) == 3 ||
		getValue(row + 1, col) == 3 || getValue(row, col - 1) == 3) {
		// finish recursion
	}
	else if (getValue(row - 1, col) == startValue || getValue(row - 1, col) == 0) { // top
		if (getValue(row - 1, col) == 0) {
			endValue = 4;
			coorQueue.push({ row - 1, col });
		}
		else {
			coorQueue = popBackQueue(coorQueue);
		}
		setValue(endValue, row - 1, col);
		checkPath(startValue, row - 1, col);
	}
	else if (getValue(row, col + 1) == startValue || getValue(row, col + 1) == 0) { // right
		if (getValue(row, col + 1) == 0) {
			endValue = 4;
			coorQueue.push({ row, col + 1 });
		}
		else {
			coorQueue = popBackQueue(coorQueue);
		}
		setValue(endValue, row, col + 1);
		checkPath(startValue, row, col + 1);
	}
	else if (getValue(row + 1, col) == startValue || getValue(row + 1, col) == 0) { // bottom
		if (getValue(row + 1, col) == 0) {
			endValue = 4;
			coorQueue.push({ row + 1, col });
		}
		else {
			coorQueue = popBackQueue(coorQueue);
		}
		setValue(endValue, row + 1, col);
		checkPath(startValue, row + 1, col);
	}
	else if (getValue(row, col - 1) == startValue || getValue(row, col - 1) == 0) { // left
		if (getValue(row, col - 1) == 0) {
			endValue = 4;
			coorQueue.push({ row, col - 1 });
		}
		else {
			coorQueue = popBackQueue(coorQueue);
		}
		setValue(endValue, row, col - 1);
		checkPath(startValue, row, col - 1);
	}
	else { // switch start value to previously checked coordinates
		setValue(5, row, col);
		checkPath(4, row, col);
		coorQueue = popBackQueue(coorQueue);
	}
	return false;
}

int getValue(int row, int col) { // returns the value in the array
	int value = -1;
	if (row >= 0 && row < rows && col >= 0 && col < cols) value = map[row][col];
	return value;
}

void setValue(int value, int row, int col) { // set the value of the index of the array
	if (row >= 0 && row < rows && col >= 0 && col < cols) map[row][col] = value;
}

void printMap() {
	int value = -1;
	for (int row = 0; row < rows; row++) { // to iterate through the rows of the maze
		for (int a = 0; a < tileSize; a++) { // to create the 3x3 tilesize
			for (int col = 0; col < cols; col++) { // to iterate throught the columns of the maze
				for (int b = 0; b < tileSize; b++) { // to create the 3x3 tilesize
					value = map[row][col]; // set value to equal the value of index
					if (value == 0) { // create path
						mapString += ".";
					}
					else if (value == 1) { // wall
						mapString += "x";
					}
					else if (value == 2) { // start
						if (a == 1 && b == 1) mapString += "S"; // center point
						else mapString += ".";
					}
					else if (value == 3) { // finish
						if (a == 1 && b == 1) mapString += "F"; // center point
						else mapString += ".";
					}
					else if (value == 4) { // first check
						if (a == 1 && b == 1) mapString += "+"; // center point
						else mapString += ".";
					}
					else if (value == 5) { // second check
						if (a == 1 && b == 1) mapString += "-"; // center point
						else mapString += ".";
					}
					else { // create walls
						mapString += "x";
					}
				}
			}
			mapString += "\n"; // create line break
		}
	}
	cout << mapString;
}

void printQueue() {
	std::queue<vector<int>> tempQueue = coorQueue;

	cout << "\n";
	while (!tempQueue.empty()){
		vector<int> tempCoor = tempQueue.front();
		for (int i = 0; i < tempCoor.size(); i++) {
			if (i == 0) {
				cout << "{" << tempCoor[i];
			}
			else {
				cout << ", " << tempCoor[i] << "}";
			}
		}
		tempQueue.pop();
		if (tempQueue.size() > 0) cout << ", ";
	}
}

// create new queue with one less vector
std::queue<vector<int>> popBackQueue(std::queue<vector<int>> tempQueue){ 
	std::queue<vector<int>> newQueue;
	for (int i = 0; i < coorQueue.size() - 1; i++) {
		newQueue.push(tempQueue.front());
		tempQueue.pop();
	}
	return newQueue;
}
