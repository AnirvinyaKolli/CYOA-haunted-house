#include <iostream> 
#include <string> 
#include <fstream> 
using namespace std;

    
string formatTextFile(string url){
    ifstream inputFile(url); 
    string output = ""; 
    string line; 
    while (getline(inputFile, line)) {
        output += (line + '\n'); 
    }
    return output;
}


int main()
{
    string formattedText = formatTextFile("ghost.txt");
    cout << formattedText;
    return 0;
}
