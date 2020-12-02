#include "FingerPrint.h"
#include<sstream>


std::vector<int> FingerPrint::getFingerPrint(std::string pString)
{
   std::vector<int> fingerPrint;
   std::stringstream ss(pString);
   std::istream_iterator<std::string> begin(ss);
   std::istream_iterator<std::string> end;
   std::vector<std::string> tokens(begin, end);
   for (auto const& token : tokens) 
   {
	   if (token.size() > 5) 
	   {
		   if(idWords.find(token) == idWords.end())
				idWords[token] = consecutive++;
		   fingerPrint.push_back(idWords[token]);
	   } 
   }
   return fingerPrint;
}
