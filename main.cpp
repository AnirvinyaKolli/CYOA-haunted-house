#include "text_formating.h"
#include <iostream> 
#include <string> 
#include <fstream> 
using namespace std;


int main()
{
    TextFormatter formatter;
    string formattedText = formatter.formatTextFile("ASCII_ART/ghost.txt");
    cout << formattedText;
    return 0;
}
