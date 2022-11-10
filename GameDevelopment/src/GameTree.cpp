#include "include/GameTree.h"

const GameState* Minimax::AlphaBetaDecide(const GameState* root, unsigned int depth)
{
    const GameState* choice = nullptr;
    // alpha: determine the lowerbounds of state score
    float alpha = -std::numeric_limits<float>::infinity();
    // beta: determine the upperbounds of state score
    float beta = std::numeric_limits<float>::infinity();

    for (const GameState* nextState : root->GetPossibleMoves()) {
        float value = this->AlphaBetaMin(nextState, depth - 1, alpha, beta);

        if (value > alpha) {
            alpha = value;
            choice = nextState;
        }
    }

    return choice;
}

float Minimax::AlphaBetaMax(const GameState* gameState, unsigned int depth, float alpha, float beta)
{
    if (gameState->IsTerminal() || depth == 0) {
        return gameState->GetScore();
    }

    float maxValue = -std::numeric_limits<float>::infinity();
    for (const GameState* nextState : gameState->GetPossibleMoves()) {
        maxValue = std::max(maxValue, this->AlphaBetaMin(nextState, depth - 1, alpha, beta));

        if (maxValue >= beta) {
            return maxValue;
        }

        alpha = std::max(maxValue, alpha);
    }

    return maxValue;
}

float Minimax::AlphaBetaMin(const GameState* gameState, unsigned int depth, float alpha, float beta)
{
    if (gameState->IsTerminal() || depth == 0) {
        return gameState->GetScore();
    }

    float minValue = std::numeric_limits<float>::infinity();
    for (const GameState* nextState : gameState->GetPossibleMoves()) {
        minValue = std::min(minValue, this->AlphaBetaMax(nextState, depth - 1, alpha, beta));

        if (minValue <= alpha) {
            return minValue;
        }

        beta = std::min(minValue, beta);
    }

    return minValue;
}