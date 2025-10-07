#include <string> 
#include <fstream> 
#include "text_formating.h"

using namespace std;

string TextFormatter::formatTextFile(string url){
    ifstream inputFile(url); 
    string output = ""; 
    string line;
    while (getline(inputFile, line)) {
        output += (line + '\n'); 
    }
    return output;
}
