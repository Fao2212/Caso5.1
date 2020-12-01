#include "Word.h"

std::vector<std::pair<int, int>> Word::getCoincidences()//No estoy satisfecho con la eficiencia
{
    std::vector<std::pair<int, int>> coincidences;
    for (auto const& appOne : textOneAppareances) {
        for (auto const& appTwo : textTwoAppareances) {
            if (compareWeights(appOne->getWeight(), appTwo->getWeight()))
                coincidences.push_back(std::pair<int, int>(appOne->getPos(),appTwo->getPos()));
        }
    }
    return coincidences;
}

bool Word::compareWeights(int pWeightOne, int pWeightTwo)
{
    //Agregar al vector de coincidencia solamente si sus pesos tienen una diferencia mayor al 75%
    //Menor entre mayor por 100
    double mayor;
    double menor;
    if (pWeightOne >= pWeightTwo) {
        mayor = pWeightOne;
        menor = pWeightTwo;
    }
    else {
        mayor = pWeightTwo;
        menor = pWeightOne;
    }
    return ((menor / mayor) * 100) >= 99;
}

void Word::addToTextPositions(std::string pText, Appareance* pPos)
{
    if (pText == "text1")
        textOneAppareances.insert(pPos);
    else
        textTwoAppareances.insert(pPos);
}
