#pragma once

#include<vector>

struct GameState {
	enum SquareState{Empty, X, O};
	SquareState mBoard[3][3];
};

struct GameTreeNode {
	std::vector<GameTreeNode*> mChildrens;
	GameState mState;
};

class Minimax {
public:
	Minimax() = default;
	const GameTreeNode* MinimaxDecide(const GameTreeNode* root);
private:
	float MaxPlayer(const GameTreeNode* node);
	float MinPlayer(const GameTreeNode* node);
	float GetScore(GameState state);
};