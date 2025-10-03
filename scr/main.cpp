// Compiler: Microsoft Visual Studio 2022 (MSVC), Standard: C++20
#include "card.h"
#include "deckdealer.h"
#include "utils.h"
#include <iostream>
#include <vector>

using namespace std;

double mean(const vector<int>& v) {
    if (v.empty()) return 0;
    return accumulate(v.begin(), v.end(), 0.0) / v.size();
}

double median(vector<int> v) {
    if (v.empty()) return 0;
    std::sort(v.begin(), v.end());
    size_t n = v.size();
    if (n % 2 == 1) return v[n / 2];
    return (v[n / 2 - 1] + v[n / 2]) / 2.0;
}

int mode(const std::vector<int>& v) {
    map<int, int> freq;
    for (int x : v) freq[x]++;
    return std::max_element(freq.begin(), freq.end(),
        [](auto& a, auto& b) { return a.second < b.second; })->first;
}

map<int, double> percentages(const std::vector<int>& v) {
    map<int, int> freq;
    for (int x : v) freq[x]++;
    map<int, double> result;
    for (auto& [len, count] : freq) {
        result[len] = (100.0 * count) / v.size();
    }
    return result;
}

int main() {
    try {
        int numSuits, numCards;
        cout << "Enter the number of suits: ";
        if (!(cin >> numSuits) || numSuits <= 0) {
            throw std::invalid_argument("Incorrect number of suits.");
        }

        cout << "Enter the number of cards to be dealt: ";
        if (!(cin >> numCards) || numCards <= 0) {
            throw std::invalid_argument("Incorrect number of cards.");
        }

        DeckDealer dealer(numSuits);
        vector<int> pileSizes;

        int currentPile = 0;
        Card prev = dealer(); // first card
        currentPile = 1;

        for (int i = 1; i < numCards; i++) {
            Card next = dealer();
            if (next >= prev) {
                currentPile++;
            }
            else {
                pileSizes.push_back(currentPile);
                currentPile = 1;
            }
            prev = next;
        }
        pileSizes.push_back(currentPile);

        // stat
        auto perc = percentages(pileSizes);
        cout << "\nStack statistics:\n";
        for (auto& [len, p] : perc) {
            std::cout << "Length " << len << " : " << p << "%\n";
        }
        cout << "Most common length: " << mode(pileSizes) << "\n";
        cout << "Average length: " << mean(pileSizes) << "\n";
        cout << "Median lengths: " << median(pileSizes) << "\n";

    }
    catch (const std::exception& ex) {
        cerr << "Error: " << ex.what() << "\n";
    }
    return 0;
}