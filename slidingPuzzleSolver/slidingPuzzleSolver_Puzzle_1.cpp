#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

vector<int> puzzleArray;
vector<int> puzzleMoves;
vector<int> preferedMoves;
vector<int> puzzleSolution;
int puzzleSize;
int zero_pos;

int getPath(int i) {

	int pathTargetIndex = i;

	if(puzzleMoves[i] == 0 or puzzleArray[i] == 0){
		return -1;
	}

	if(i%puzzleSize == puzzleSize - 1 or i%puzzleSize == 0){
		if(abs(puzzleMoves[i]) < puzzleSize and i%puzzleSize == puzzleSize - 1){
			pathTargetIndex += puzzleMoves[i]/abs(puzzleMoves[i]);
			return puzzleArray[pathTargetIndex];
		}
		if(abs(puzzleMoves[i]) < puzzleSize and i%puzzleSize == 0){
			pathTargetIndex = i -puzzleMoves[i]/abs(puzzleMoves[i]);
			if(pathTargetIndex < i && preferedMoves[i] == puzzleArray[i]){
				pathTargetIndex = i + puzzleMoves[i]/abs(puzzleMoves[i]);
				return puzzleArray[pathTargetIndex];
			}
			return puzzleArray[pathTargetIndex];
		}
		pathTargetIndex += puzzleMoves[i]/abs(puzzleMoves[i]) * puzzleSize;
		return puzzleArray[pathTargetIndex];
	}

	if(abs(puzzleMoves[i]) == puzzleSize or abs(puzzleMoves[i]) == 1){
		pathTargetIndex += puzzleMoves[i];
		return puzzleArray[pathTargetIndex];
	}

	if(abs(puzzleMoves[i]) < puzzleSize){
		if(abs(puzzleMoves[i]) > i%puzzleSize){
			pathTargetIndex += -puzzleMoves[i]/abs(puzzleMoves[i]);
			return puzzleArray[pathTargetIndex];
		}
		pathTargetIndex += puzzleMoves[i]/abs(puzzleMoves[i]);
		return puzzleArray[pathTargetIndex];
	}

	if(abs(puzzleMoves[i]) > puzzleSize){
		pathTargetIndex += puzzleMoves[i]/abs(puzzleMoves[i]) * puzzleSize;
		return puzzleArray[pathTargetIndex];
	}

	return -1;
}

int getDesiredPosition(int i) {
	int x = i;

	if(puzzleMoves[i] == 0 or puzzleArray[i] == 0){
		return -1;
	}

	if(abs(puzzleMoves[i]) == puzzleSize or abs(puzzleMoves[i]) == 1){
		x += puzzleMoves[i];
		return puzzleArray[x];
	}

	if(i%puzzleSize == puzzleSize - 1){
		//on the right edge of the board
		x += puzzleMoves[i]/abs(puzzleMoves[i]) * puzzleSize;
		return puzzleArray[x];
	}

	if(abs(puzzleMoves[i]) < puzzleSize){
		x += -puzzleMoves[i]/abs(puzzleMoves[i]);
		return puzzleArray[x];
	}

	if(abs(puzzleMoves[i]) > puzzleSize){
		x += puzzleMoves[i]/abs(puzzleMoves[i]);
		return puzzleArray[x];
	}

	if(abs(puzzleMoves[i]) == puzzleSize){
		x += puzzleMoves[i];
		return puzzleArray[x];
	}

	if(i%puzzleSize == 0 or i == 0){
		//on the left side of the board
		if(abs(puzzleMoves[i]) > puzzleSize){
			x += puzzleMoves[i]/abs(puzzleMoves[i]) * puzzleSize;
			return puzzleArray[x];
		}
	}

	return 0;
}

void getMoves() {
	puzzleMoves.clear();
	for (int i = 0; i < pow(puzzleSize,2); i++){
		if (puzzleArray[i] == 0){
			puzzleMoves.push_back(puzzleArray.size() - 1);
			zero_pos = i;
		} else {
			puzzleMoves.push_back((puzzleArray[i] - 1) - i);
		}
	}

	cout << "Moves -> ";

	for (int i = 0; i < pow(puzzleSize,2); i++){
		cout << puzzleArray[i] << ":" << puzzleMoves[i] << ", ";
	}
	cout << '\n';
}

vector<int> slide_puzzle(const vector<vector<int>> &arr) {

	puzzleArray.clear();
	puzzleMoves.clear();
	preferedMoves.clear();
	puzzleSolution.clear();

	puzzleSize = arr.size();

	cout << "puzzleSize -> " << puzzleSize;
	cout << '\n';

	puzzleArray.reserve(pow(puzzleSize,2));
	preferedMoves.reserve(pow(puzzleSize,2));

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

	getMoves();

	for(int i = 0; i < pow(puzzleSize,2); i++){
		cout << puzzleArray[i] << ":" << getPath(i) << ", ";
		int targetMove = getPath(i);
		if(targetMove == 0){
			cout << puzzleArray[i] << '\n';
			puzzleSolution.push_back(puzzleArray[i]);
			puzzleArray[zero_pos] = puzzleArray[i];
			puzzleArray[i] = 0;
			i = -1;
			getMoves();
		} else {
		}
	}

	cout << '\n';
	cout << "Solution -> ";

	for(int i = 0; i < puzzleSolution.size(); i++){
		cout << puzzleSolution[i] << ", ";
	}

	cout << '\n';

	return vector<int>();
}

int main() {
	vector<vector<vector<int>>> puzzles = {{
		{4,1,3},
		{2,8,0},
		{7,6,5}},
		{{10, 3, 6, 4},
		{ 1, 5, 8, 0},
		{ 2,13, 7,15},
		{14, 9,12,11}},
		{{ 3, 7,14,15,10},
		{ 1, 0, 5, 9, 4},
		{16, 2,11,12, 8},
		{17, 6,13,18,20},
		{21,22,23,19,24}}
	};
	for (size_t i = 0 ; i < puzzles.size() ; i++){
		slide_puzzle(vector<vector<int>>(puzzles[i]));
	}
};
