// #include "text_formating.h"
#include <iostream> 
#include <string> 
#include <vector>
#include <fstream>
using namespace std;


vector<string> art;

string formatTextFile(string url){
    ifstream inputFile(url); 
    string output = ""; 
    string line;
    while (getline(inputFile, line)) {
        output += (line + '\n'); 
    }
    return output;
}



class DecisionPoint {
    public: vector<DecisionPoint> choices;
    public: string prompt;
    public: vector<string> choicePrompts;
    public: int artIndex; 

    public: DecisionPoint(string prompt, vector<DecisionPoint> choices, vector<string> choicePrompts, int artIndex) {
        this->prompt = prompt;
        this->choices = choices;
        this->choicePrompts = choicePrompts;
        this->artIndex = artIndex;
    }
    public: DecisionPoint(string prompt, int artIndex) {
        this->prompt = prompt;
        this->choices = vector<DecisionPoint>();
        this->choicePrompts = vector<string>();
        this->artIndex = artIndex;
    }
    
    public: DecisionPoint(string prompt) {
        this->prompt = prompt;
        this->choices = vector<DecisionPoint>();
        this->choicePrompts = vector<string>();
        this->artIndex = 0;
    }

    public: DecisionPoint() {
        this->prompt = "default prompt";
        this->choices = vector<DecisionPoint>();
        this->choicePrompts = vector<string>();
        this->artIndex = 0;
    }

    public:
    virtual void makeDecision() {
        int userInput;
        cout << art[artIndex] << endl;
        cout << "----------------------------------" << endl;
        cout << prompt << endl;
        for (int i = 0; i < choices.size(); i++) {
            cout << i+1 << ": " << choicePrompts[i] << endl;
        }

        cin >> userInput;
        userInput -= 1;

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
    //formatting ascii art 
    vector<string> urls = {"ASCII_ART/boobytrap.txt","ASCII_ART/cave.txt","ASCII_ART/ghost.txt", "ASCII_ART/halberd.txt", "ASCII_ART/temple_entrance.txt"}; 

    for (string url : urls){
        art.push_back(formatTextFile(url)); 
    }

    //Right path
    DecisionPoint endWin1("You have convinced the ghost to let you pass. You win!", 2); //Edit content
    DecisionPoint attackGhostGluttonEnding("You try to attack the ghost. You're not sure why you've chosen this option. The ghost is not impressed. He eats you", 0);
    DecisionPoint failGhostGluttonDialogueEnding("You try to attack the ghost. You're not sure why you've chosen this option. The ghost is not impressed. He eats you", 0);
    DecisionPoint sneakGhostGluttonEnding("You try to sneak past the ghost. You make it! The hallway behind him is a dead end he sneaks up behind you and eats you", 0);
    DecisionPoint ghostGluttonCommunication("You speak with the ghost. He asks you wether you think he is fat.", {endWin1, failGhostGluttonDialogueEnding}, {"You are not obese", "You totally are fat"}, 0);
    DecisionPoint ghostGluttonEncounter("You have encountered a ghostly glutton blocking your path.", {ghostGluttonCommunication, attackGhostGluttonEnding, sneakGhostGluttonEnding}, {"Try to communicate", "Attack the ghost", "Sneak past the ghost"}, 2);

    //Left path
    DecisionPoint endWin2("You win the fight. You have found the treasure! You win!", 3);
    DecisionPoint attackWithKnifeEnding("You try to attack the halberd-wielding ghost with your gleaming and cool knife. It is unimpressed. It kills you.", 0);
    DecisionPoint talkToHalberdGhost("He says: \" Ya the dude in the other room is kinda odd; compliment him and he'll let you win no prob\"", {ghostGluttonEncounter}, {"Go to the next room?"}, 0);
    DecisionPoint halberdGhostEncounter("You have encountered a ghost wielding a halberd blocking your path.", {endWin2, attackWithKnifeEnding, talkToHalberdGhost}, {"Try and suck the ghosts with a vacuum", "Attack the ghost with your knife", "Talk to the ghost"}, 4);

    //Path decision 
    DecisionPoint EmmanuelChosenPath("Emmanuel leads you to the house through a back entrance. He leaves you to explore. There are two paths ahead of you.", {halberdGhostEncounter, ghostGluttonEncounter}, {"Take the left path", "Take the right path"}, 1);
    DecisionPoint FlitchChosenEnding("You follow Flitch to the front entrance of the house. You enter and are immediately pincushioned by an arrow trap. You die.", 0);

    DecisionPoint start("You are standing outside a spooky house. Your friend Emmanuel and your rival Flitch are with you. Who do you follow?", {EmmanuelChosenPath, FlitchChosenEnding}, {"Follow Emmanuel", "Follow Flitch"}, 0);
    start.makeDecision();
    
    return 0;
}