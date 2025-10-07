// #include "text_formating.h"
#include <iostream> 
#include <string> 
#include <vector>
#include <fstream>
using namespace std;

string formatTextFile(std::string url){
    ifstream inputFile(url); 
    string output = ""; 
    string line;
    while (std::getline(inputFile, line)) {
        output += (line + '\n'); 
    }
    return output;
}



class DecisionPoint {
    public: vector<DecisionPoint> choices; 
    public: string prompt;

    public: DecisionPoint(string prompt, vector<DecisionPoint> choices) {
        this->prompt = prompt;
        this->choices = choices;
    }

    public: DecisionPoint(string prompt) {
        this->prompt = prompt;
        this->choices = vector<DecisionPoint>();
    }

    public: DecisionPoint() {
        this->prompt = "default prompt";
        this->choices = vector<DecisionPoint>();
    }

    public:
    virtual void makeDecision() {
        int userInput;
        cout << prompt << endl;
        cin >> userInput;

        switch(choices.size()){
            case 0:
                cout << "The end" << endl;
                return;
            case 1:
                cout << "You really dont have a choice." << endl;
                choices[0].makeDecision();
                return;
            default:
                if (userInput < 0 || userInput >= choices.size()) {
                    cout << "Invalid choice. Please try again." << endl;
                    makeDecision();
                } else {
                    choices[userInput].makeDecision();
                }
                break;
        }
    }
}; 

class DialogueNode {
    public: string prompt;
    public: vector<string> choices;
    public: vector<float> convincingValues;
    public: vector<string> responses;

    public:
    DialogueNode(string prompt, vector<string> choices, vector<float> convincingValues, vector<string> responses) {
        this->prompt = prompt;
        this->choices = choices;
        this->convincingValues = convincingValues;
        this->responses = responses;
    }
    public: float displayDialogue() {
        cout << prompt << endl;
        for (int i = 0; i < choices.size(); i++) {
            cout << i+1 << ": " << choices[i] << endl;
        }
        int userInput;
        cin >> userInput;
        userInput -= 1; 
        if (userInput < 0 || userInput >= choices.size()) {
            cout << "Invalid choice. Please try again." << endl;
            displayDialogue();
        } else {
            cout << responses[userInput] << endl;
            return convincingValues[userInput];
        }
    }
    
};

class DialogueGame : public DecisionPoint {

    public: vector<DialogueNode> dialogues;
    public: DialogueGame(string start, vector<DialogueNode> nodes, vector<DecisionPoint> choices)  {
        this->prompt = start;
        this->dialogues = nodes;
        this->choices = choices;
    }

    void makeDecision() override {
        cout << prompt << endl;
        float totalConvincingValue = 0.0;

        for (DialogueNode node : dialogues) {
            totalConvincingValue += node.displayDialogue();
        }

        if (totalConvincingValue > 0.0) {
            choices[0].makeDecision();
        } else {
            choices[1].makeDecision();
        }

    }
};


/*
 dialogue game class?
You like get a prompt and a list of choices
and each choice is like a convincing value,
and the guy gives a response
and at the end of like 4 dialogues you get a result
*/

/*
class: dialogue game extends decision point?  <so it can replace the end points> 
list of dialogue nodes
loops through dialogue nodes
each dialogue node returns a float
the floats are summed and based on that sum you get a result
i.e die or live 
*/

int main()
{
    vector<DecisionPoint> choices = {
        DecisionPoint("You have convinced the ghost to let you pass. You win!"),
        DecisionPoint("The ghost is not convinced. You lose!")
    };
    vector<DialogueNode> dialogues = {
        DialogueNode("Am I fat?", {"Yea", "Nah"}, {-1.0, 1.0}, {"How dare you!", "Knew it!"}),
        DialogueNode("Do you like my hat?", {"Yea", "Nah"}, {1.0, -1.0}, {"Thanks!", "Rude!"}),
        DialogueNode("Do you think I'm scary?", {"Yea", "Nah"}, {1.0, -1.0}, {"Boo!", "Oh."})
    };

    DialogueGame game("Start", dialogues, choices);

    string formattedText = formatTextFile("ASCII_ART/ghost.txt");

    game.makeDecision();
    
    cout << formattedText;
    return 0;
}