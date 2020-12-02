#include "Word.h"

std::vector<std::pair<int, int>> Word::getCoincidences()
{
    std::vector<std::pair<int, int>> coincidences;
    for (auto const& appOne : textOneAppareances) {
        for (auto const& appTwo : textTwoAppareances) {
            if (compareFingerPrints(appOne->getFingerPrint(), appTwo->getFingerPrint()))
                coincidences.push_back(std::pair<int, int>(appOne->getPos(),appTwo->getPos()));
        }
    }
    return coincidences;
}

bool Word::compareWeights(int pWeightOne, int pWeightTwo)//YA NO SE UTILIZARA
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

bool Word::compareFingerPrints(std::vector<int> pFingerPrintOne, std::vector<int> pFingerPrintTwo)
{
    //Si los elementos del vector coinciden en mas de la mitad entonces puede ser un indicio de plagio
    std::vector<int> biggestVector;
    std::vector<int> workVector;
    double coincideces = 0;
    if (pFingerPrintOne.size() > pFingerPrintTwo.size())
    {
        biggestVector = pFingerPrintOne;
        workVector = pFingerPrintTwo;
    }
    else
    {
        biggestVector = pFingerPrintTwo;
        workVector = pFingerPrintTwo;
    }

    for (auto const& value : workVector) {
        if (std::find(biggestVector.begin(), biggestVector.end(), value) != biggestVector.end())
            coincideces++;
    }

    //100% = workVector.size() 
    double size = workVector.size();
    return ((coincideces / workVector.size()) * 100.0) >= 50;//Tentativo a convertir a todo en double

}

void Word::addToTextPositions(std::string pText, Appareance* pPos)
{
    bool found = false;
    if (pText == "text1")
    {
        for (auto const& ap : textOneAppareances)
        {
            if (pPos->getPos() == ap->getPos())
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            textOneAppareances.push_back(pPos);
        }
    }
    else
    {
        for (auto const& ap : textTwoAppareances)
        {
            if (pPos->getPos() == ap->getPos())
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            textTwoAppareances.push_back(pPos);
        }
    }
}

std::vector<Appareance*> Word::getTextOneAppareances()
{
    return textOneAppareances;
}
