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

float Minimax::MaxPlayer(const GameTreeNode* node)
{
    if (node->mChildrens.empty()) {
        return GetScore(node->mState);
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
        return GetScore(node->mState);
    }

    float minValue = std::numeric_limits<float>::infinity();
    for (const GameTreeNode* node : node->mChildrens) {
        minValue = std::max(minValue, this->MaxPlayer(node));
    }

    return minValue;
}

float Minimax::GetScore(GameState state)
{
    return 0.0f;
}
