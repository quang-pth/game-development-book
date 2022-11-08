#pragma once

#include<vector>

struct GameState {
	enum SquareState{Empty, X, O};
	SquareState mBoard[3][3];
	float GetScore() const {
		if (IsTerminal) {
			// Return state score
		}
		else {
			// Calculate Heuristic score 
		}
	};
	bool IsTerminal() const {
		// Determine whether or not the state is an end state
	};
	std::vector<GameState*> GetPossibleMoves() const {
		// Return possible next moves after the current state
	};
};

struct GameTreeNode {
	std::vector<GameTreeNode*> mChildrens;
	GameState* mState;
};

class Minimax {
public:
	Minimax() = default;
	const GameTreeNode* MinimaxDecide(const GameTreeNode* root);
private:
	float MaxPlayerLimit(const GameState* gameState, unsigned int depth);
	float MinPlayerLimit(const GameState* gameState, unsigned int depth);
	float MaxPlayer(const GameTreeNode* node);
	float MinPlayer(const GameTreeNode* node);
};