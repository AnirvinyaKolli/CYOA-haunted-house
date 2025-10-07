#include <string> 
#include <fstream> 
#include "text_formating.h"

using namespace std;

string TextFormatter::formatTextFile(std::string url){
    ifstream inputFile(url); 
    string output = ""; 
    string line;
    while (std::getline(inputFile, line)) {
        output += (line + '\n'); 
    }
    return output;
}
