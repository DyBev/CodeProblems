#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

vector<int> puzzleArray;
vector<int> oldPuzzleArray;
vector<vector<int>> preferedMoves;
vector<vector<int>> oldPreferedMoves;
vector<int> puzzleSolution;
vector<vector<int>> targetMoves;
vector<vector<int>> routes;
vector<int> moves;
vector<int> longestChainMoves;
vector<int> oldLongestChain;
vector<int> currentChainMoves;
vector<bool> visited;
int puzzleSize;
int previousMove = 0;
bool solved = true;

void movePuzzleAlongPath();
void findPuzzlePath();
void tryNewPath();

vector<int> getTileMoves(int i, vector<int> tileTargetLocations){
	int puzzleMove = tileTargetLocations[i];

	if(puzzleMove == 0 || puzzleArray[i] == 0){
		moves.push_back(-1);
		return moves;
	}

	if(i%puzzleSize == puzzleSize - 1 && puzzleMove > 0){
		moves.push_back(i - puzzleMove/abs(puzzleMove));
	}else if(i%puzzleSize == puzzleSize - 1 && puzzleMove < 0){
		moves.push_back(i + puzzleMove/abs(puzzleMove));
	}

	if(i%puzzleSize == 0 && puzzleMove > 0){
		moves.push_back(i + puzzleMove/abs(puzzleMove));
	}else if(i%puzzleSize == 0 && puzzleMove < 0){
		moves.push_back(i - puzzleMove/abs(puzzleMove));
	}

	if(i < puzzleSize && puzzleMove > 0 && abs(puzzleMove) > i%puzzleSize){
		moves.push_back(i + puzzleSize * puzzleMove/abs(puzzleMove));
	}else if(i > puzzleSize * (puzzleSize - 1) - 1 && puzzleMove < 0 && abs(puzzleMove) > i%puzzleSize){
		moves.push_back(i + puzzleSize * puzzleMove/abs(puzzleMove));
	}else if(abs(puzzleMove) > i%puzzleSize && ((i > puzzleSize * (puzzleSize - 1) - 1 && puzzleMove < 0) || (i < puzzleSize && puzzleMove > 0) || (i > puzzleSize - 1 && i < puzzleSize * (puzzleSize - 1)))){
		moves.push_back(i + puzzleSize * puzzleMove/abs(puzzleMove));
	}

	if((abs(puzzleMove) > i%puzzleSize && puzzleMove < 0) && !(i%puzzleSize == 0 || i%puzzleSize == puzzleSize - 1)){
		moves.push_back(i - puzzleMove/abs(puzzleMove));
	}else if((abs(puzzleMove) > puzzleSize - 1 - i%puzzleSize && puzzleMove > 0) && !(i%puzzleSize == 0 || i%puzzleSize == puzzleSize - 1)){
		moves.push_back(i + puzzleMove/abs(puzzleMove));
	}else if(abs(puzzleMove) <= i%puzzleSize && !(i%puzzleSize == 0 || i%puzzleSize == puzzleSize - 1)){
		moves.push_back(i + puzzleMove/abs(puzzleMove));
	}

	return moves;
}

//int getDesiredPosition(int i) {
//	int x = i;
//
//	if(puzzleMoves[i] == 0 or puzzleArray[i] == 0){
//		return -1;
//	}
//
//	if(abs(puzzleMoves[i]) == puzzleSize or abs(puzzleMoves[i]) == 1){
//		x += puzzleMoves[i];
//		return puzzleArray[x];
//	}
//
//	if(i%puzzleSize == puzzleSize - 1){
//		//on the right edge of the board
//		x += puzzleMoves[i]/abs(puzzleMoves[i]) * puzzleSize;
//		return puzzleArray[x];
//	}
//
//	if(abs(puzzleMoves[i]) < puzzleSize){
//		x += -puzzleMoves[i]/abs(puzzleMoves[i]);
//		return puzzleArray[x];
//	}
//
//	if(abs(puzzleMoves[i]) > puzzleSize){
//		x += puzzleMoves[i]/abs(puzzleMoves[i]);
//		return puzzleArray[x];
//	}
//
//	if(abs(puzzleMoves[i]) == puzzleSize){
//		x += puzzleMoves[i];
//		return puzzleArray[x];
//	}
//
//	if(i%puzzleSize == 0 or i == 0){
//		//on the left side of the board
//		if(abs(puzzleMoves[i]) > puzzleSize){
//			x += puzzleMoves[i]/abs(puzzleMoves[i]) * puzzleSize;
//			return puzzleArray[x];
//		}
//	}
//
//	return 0;
//}

//void getMovePath() {
//	puzzleMoves.clear();
//	for (int i = 0; i < pow(puzzleSize,2); i++){
//		if (puzzleArray[i] == 0){
//			puzzleMoves.push_back(puzzleArray.size() - 1);
//			zero_pos = i;
//		} else {
//			puzzleMoves.push_back((puzzleArray[i] - 1) - i);
//		}
//	}
//
//	cout << "Moves -> ";
//
//	for (int i = 0; i < pow(puzzleSize,2); i++){
//		cout << i << ":" << puzzleArray[i] << ":" << puzzleMoves[i] << ", ";
//	}
//	cout << '\n';
//}
//
//
//void getPath(int currentPos) {
//	visited[currentPos] = true;
//	currentChainMoves.push_back(currentPos);
//
//	for (int nextPos : preferedMoves[currentPos]) {
//		if (!visited[nextPos]) {
//			getPath(nextPos);
//		}
//	}
//
//	if (currentChainMoves.size() > longestChainMoves.size()) {
//		longestChainMoves = currentChainMoves;
//	}
//
//	visited[currentPos] = false;
//	currentChainMoves.pop_back();
//
//}
//
//void findPuzzlePath() {
//
//	solved = true;
//
//	getMovePath();
//	getAllTileMoves();
//
//	for(int i = 0; i < pow(puzzleSize,2); i++) {
//		cout << i << ":" << puzzleArray[i] << " -> ";
//		for(const auto& move : preferedMoves[i]) {
//			cout << move << " & ";
//		}
//		cout << '\n';
//	}
//
//	visited.resize(pow(puzzleSize,2), false);
//	longestChainMoves.clear();
//	getPath(zero_pos);
//	longestChainMoves.erase(longestChainMoves.begin());
//
//	for(const auto& number : puzzleArray) {
//		if(number != 0 && number != puzzleArray[number - 1]){
//			solved = false;
//			break;
//		}
//	}
//
//	if(longestChainMoves.size() == 0 && !solved){
//		tryNewPath();
//	} else if(!solved) {
//		movePuzzleAlongPath();
//	}
//
//}
//
//void movePuzzleAlongPath() {
//
//	oldPuzzleArray = puzzleArray;
//	oldLongestChain = longestChainMoves;
//	oldPreferedMoves = preferedMoves;
//
//	cout << "longestChain: ";
//	for(int move : longestChainMoves){
//		puzzleArray[zero_pos] = puzzleArray[move];
//		puzzleArray[move] = 0;
//		zero_pos = move;
//		cout << move << " ";
//	}
//	cout << '\n';
//
//	findPuzzlePath();
//
//}
//
//void tryNewPath() {
//	int previousIndex;
//	int nextIndex = -1;
//	bool moveAdded = false;
//
//	puzzleArray = oldPuzzleArray;
//	longestChainMoves = oldLongestChain;
//
//	for(int i = oldLongestChain.size() - 1; i >= 0; i--) {
//		int currentIndex = oldLongestChain[i];
//
//		if(oldPreferedMoves[currentIndex].size() > 1) {
//			if(i != 0) {
//				nextIndex = oldLongestChain[i - 1];
//			}
//			cout << oldPreferedMoves[currentIndex].size() << ":" << currentIndex << ":" << previousIndex << ":" << nextIndex <<'\n';
//			for(const auto& move : oldPreferedMoves[currentIndex]) {
//				if(move != previousIndex && move != nextIndex) {
//					oldLongestChain.push_back(move);
//					moveAdded = true;
//					break;
//				}
//			}
//			if(moveAdded) {
//				longestChainMoves = oldLongestChain;
//				movePuzzleAlongPath();
//				break;
//			}
//			previousIndex = currentIndex;
//			oldLongestChain.pop_back();
//		} else {
//			previousIndex = currentIndex;
//			oldLongestChain.pop_back();
//		}
//	}
//
//}

vector<vector<int>> getPaths(int currentPos, vector<vector<int>> puzzleTileMoves) {
	vector<vector<int>> puzzlePaths;

	for(const auto& move : puzzleTileMoves[currentPos]) {
		vector<int> puzzlePath;
		puzzlePath.push_back(move);
		puzzlePaths.push_back(puzzlePath);
	}

	return puzzlePaths;
}

vector<int> movePuzzle(vector<int> puzzle, vector<vector<int>> puzzleTileMoves) {
	int zero_pos;

	for(int i = 0; i < puzzle.size(); i++) {
		if(puzzle[i] == 0){
			zero_pos = i;
			break;
		}
	}

	vector<vector<int>> puzzlePaths = getPaths(zero_pos, puzzleTileMoves);

	for(const auto& pathVector : puzzlePaths) {
		for(const auto& move : pathVector) {
			cout << move << " -> ";
		}
		cout << '\n';
	}

	return puzzle;

//	for(int i = 0; i < puzzlePaths.size(); i++) {
//		vector<int> puzzlePath = puzzlePaths[i];
//		for(int i = 0; i < puzzlePath.size(); i++) {
//			int indexToSwap = puzzlePath[i];
//			puzzle[zero_pos] = puzzle[indexToSwap];
//			puzzleSolution.push_back(puzzle[indexToSwap]);
//			puzzle[indexToSwap] = 0;
//			zero_pos = indexToSwap;
//		}
//		for(const auto& number : puzzle) {
//			if(number != puzzle[number - 1] || number == 0 && puzzle[puzzle.size() - 1] != 0) {
//				puzzleSolved = false;
//				break;
//			}
//		}
//		if(!puzzleSolved) {
//			for(const auto& move : solvePuzzle(puzzle)) {
//				puzzleSolution.push_back(move);
//			}
//		} else if (puzzleSolved) {
//			return puzzleSolution;
//		}
//	}
}

vector<int> targetLocations(vector<int> puzzle) {
	vector<int> puzzleMoves;

	for (int i = 0; i < puzzle.size(); i++){
		if (puzzle[i] == 0){
			puzzleMoves.push_back(puzzle.size() - 1);
		} else {
			puzzleMoves.push_back((puzzle[i] - 1) - i);
		}
	}

	return puzzleMoves;
}

vector<vector<int>> getAllTileMoves(vector<int> puzzle, vector<int> tileTargetLocations) {

	vector<vector <int>> preferedMoves;
	preferedMoves.reserve(puzzle.size());
	preferedMoves.resize(puzzle.size());

	for(int i = 0; i < puzzle.size(); i++) {
		for(const auto& move : getTileMoves(i, tileTargetLocations)){
			if(move != -1){
				preferedMoves[move].push_back(i);
			}
		}
	}

	for(int i = 0; i < preferedMoves.size(); i++){
		cout << i << ":";
		for(const auto& moveRequest : preferedMoves[i]){
			cout << moveRequest << ",.";
		}
		cout << '\n';
	}

	return preferedMoves;

}

vector<int> solvePuzzle(vector<int> puzzle) {

	vector<int> tileTargets = targetLocations(puzzle);

	for(int i = 0; i < tileTargets.size(); i++){
		cout << puzzle[i] << "-> " << tileTargets[i] << " ";
	}
	cout << '\n';

	vector<vector<int>> puzzleTileMoves = getAllTileMoves(puzzle, tileTargets);

	for(int i = 0; i < puzzleTileMoves.size(); i++){
		cout << i << " -> ";
		for(const auto& move : puzzleTileMoves[i]){
			cout << move << ", ";
		}
		cout << '\n';
	}
	cout << '\n';
	vector<int> puzzleSolution = movePuzzle(puzzle, puzzleTileMoves);

	return puzzleSolution;
}


vector<int> slide_puzzle(const vector<vector<int>> &arr) {

	puzzleArray.clear();

	puzzleSize = arr.size();

	cout << "puzzleSize -> " << puzzleSize;
	cout << '\n';

	puzzleArray.reserve(pow(puzzleSize,2));
	preferedMoves.reserve(pow(puzzleSize,2));
	targetMoves.reserve(pow(puzzleSize,2));

	preferedMoves.resize(pow(puzzleSize,2));
	targetMoves.resize(pow(puzzleSize,2));

	for(const auto& row : arr){
		cout << "row -> ";
		for(int i = 0; i < row.size(); i++){
			cout << row[i] << ", ";
		}
		cout << '\n';
		puzzleArray.insert(puzzleArray.end(), row.begin(), row.end());
	}

	cout << "puzzleArray -> ";

	for (int i = 0; i < pow(puzzleSize,2); i++){
		cout << puzzleArray[i] << ",";
	}
	cout << '\n';

	solvePuzzle(puzzleArray);

	return vector<int>();
}

int main() {
	vector<vector<vector<int>>> puzzles = {{
		{4,1,3},
		{2,8,0},
		{7,6,5}},
//		{{10, 3, 6, 4},
//		{ 1, 5, 8, 0},
//		{ 2,13, 7,15},
//		{14, 9,12,11}},
		//{{ 3, 7,14,15,10},
		//{ 1, 0, 5, 9, 4},
		//{16, 2,11,12, 8},
		//{17, 6,13,18,20},
		//{21,22,23,19,24}}
	};
	for (size_t i = 0 ; i < puzzles.size() ; i++){
		slide_puzzle(vector<vector<int>>(puzzles[i]));
	}
};
