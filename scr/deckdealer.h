#pragma once
#include "card.h"
#include <vector>
#include <random>
#include <algorithm>

class DeckDealer {
private:
    int numSuits;           
    std::vector<Card> deck; 
    size_t index;           
    std::mt19937 rng;       

    void refillDeck() {
        deck.clear();
        for (int s = 0; s < numSuits; ++s) {
            for (int r = 1; r <= 13; ++r) {
                deck.emplace_back(r, s);
            }
        }
        std::shuffle(deck.begin(), deck.end(), rng);
        index = 0;
    }

public:
    DeckDealer(int suits)
        : numSuits(suits), index(0), rng(std::random_device{}()) {
        if (suits <= 0) throw std::invalid_argument("Number of suits must be > 0");
        refillDeck();
    }

    Card operator()() {
        if (index >= deck.size()) {
            refillDeck(); 
        }
        return deck[index++];
    }
};