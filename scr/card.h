#pragma once
#include <iostream>
#include <compare>

class Card {
private:
    int rank; 
    int suit; 

public:
    Card(int r = 1, int s = 0) : rank(r), suit(s) {}

    auto operator<=>(const Card& other) const noexcept {
        return rank <=> other.rank; // порівнюємо тільки за рангом
    }

    bool operator==(const Card& other) const noexcept {
        return rank == other.rank;
    }

    friend std::ostream& operator<<(std::ostream& os, const Card& card) {
        os << "Card: Rank " << card.rank << ", suit " << card.suit;
        return os;
    }
};
