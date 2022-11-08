#include "include/GameTree.h"

const GameTreeNode* Minimax::MinimaxDecide(const GameTreeNode* root)
{
    // Find subtree with the max value and save the choice
    const GameTreeNode* choice = nullptr;
    float maxValue = -std::numeric_limits<float>::infinity();
    
    for (const GameTreeNode* node : root->mChildrens) {
        float minValue = this->MinPlayer(node);
    
        if (minValue > maxValue) {
            maxValue = minValue;
            choice = node;
        }
    }

    return choice;
}

float Minimax::MaxPlayerLimit(const GameState* gameState, unsigned int depth)
{
    if (gameState->IsTerminal() || depth == 0) {
        return gameState->GetScore();
    }

    float maxValue = -std::numeric_limits<float>::infinity();
    for (const GameState* nextState : gameState->GetPossibleMoves()) {
        maxValue = std::max(maxValue, this->MinPlayerLimit(nextState, depth - 1));
    }

    return maxValue;
}

float Minimax::MinPlayerLimit(const GameState* gameState, unsigned int depth)
{
    if (gameState->IsTerminal() || depth == 0) {
        return gameState->GetScore();
    }

    float minValue = std::numeric_limits<float>::infinity();
    for (const GameState* nextState : gameState->GetPossibleMoves()) {
        minValue = std::min(minValue, this->MaxPlayerLimit(nextState, depth - 1));
    }

    return minValue;
}

float Minimax::MaxPlayer(const GameTreeNode* node)
{
    if (node->mChildrens.empty()) {
        return node->mState->GetScore();
    }

    float maxValue = -std::numeric_limits<float>::infinity();
    for (const GameTreeNode* node : node->mChildrens) {
        maxValue = std::max(maxValue, this->MinPlayer(node));
    }

    return maxValue;
}

float Minimax::MinPlayer(const GameTreeNode* node)
{
    if (node->mChildrens.empty()) {
        return node->mState->GetScore();
    }

    float minValue = std::numeric_limits<float>::infinity();
    for (const GameTreeNode* node : node->mChildrens) {
        minValue = std::max(minValue, this->MaxPlayer(node));
    }

    return minValue;
}