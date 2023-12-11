#include "deck_generator.h"
#include "card_container.h"
#include <memory>
#include <vector>
#include <algorithm>
#include <iterator>
#include <random>
#include "numeric_card.h"
#include "jump_card.h"
#include "plus_2_card.h"
#include "reverse_card.h"
using namespace MyUno;
using namespace std;
void GenerateNumerics(Color color, vector<shared_ptr<Card>>& vec);
void Generate2Plus(Color color, vector<shared_ptr<Card>>& vec);
void GenerateReverse(Color color, vector<shared_ptr<Card>>& vec);
void GenerateJump(Color color, vector<shared_ptr<Card>>& vec);
void GenerateColor(Color color, vector<shared_ptr<Card>>& vec);

CardContainer DeckGenerator::Generate()
{
    vector<shared_ptr<Card>> cards;
    GenerateColor(Red, cards);
    GenerateColor(Green, cards);
    GenerateColor(Blue, cards);
    GenerateColor(Yellow, cards);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
    CardContainer container;
    for (auto i = 0; i < cards.size(); i++)
    {
        auto current = cards[i];
        container.Add(current);
    }
    return container;
}

void GenerateColor(Color color, vector<shared_ptr<Card>>& vec)
{
    GenerateNumerics(color, vec);
    Generate2Plus(color, vec);
    GenerateReverse(color, vec);
    GenerateJump(color, vec);
}
void GenerateNumerics(Color color, vector<shared_ptr<Card>>& vec)
{
    for (int i = 0; i <= 9; i++)
    {
        shared_ptr<Card> card1 = std::make_shared<NumericCard>(color, i);
        vec.push_back(card1);
        shared_ptr<Card> card2 = std::make_shared<NumericCard>(color, i);
        vec.push_back(card2);
    }
}
void Generate2Plus(Color color, vector<shared_ptr<Card>>& vec)
{
    shared_ptr<Card> card1 = std::make_shared<Plus2Card>(color);
    vec.push_back(card1);
    shared_ptr<Card> card2 = std::make_shared<Plus2Card>(color);
    vec.push_back(card2);
}

void GenerateReverse(Color color, vector<shared_ptr<Card>>& vec)
{
    shared_ptr<Card> card1 = std::make_shared<ReverseCard>(color);
    vec.push_back(card1);
    shared_ptr<Card> card2 = std::make_shared<ReverseCard>(color);
    vec.push_back(card2);
}

void GenerateJump(Color color, vector<shared_ptr<Card>>& vec)
{
    shared_ptr<Card> card1 = std::make_shared<JumpCard>(color);
    vec.push_back(card1);
    shared_ptr<Card> card2 = std::make_shared<JumpCard>(color);
    vec.push_back(card2);
}