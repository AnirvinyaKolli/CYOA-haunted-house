#include <iostream> 
#include <string> 
#include <fstream> 
using namespace std;

    
string formatTextFile(string url){
    ifstream inputFile(url); 
    string output = ""; 
    string line;
    while (std::getline(inputFile, line)) {
        output += (line + '\n'); 
    }
    return output;
}
