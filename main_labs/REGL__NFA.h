// The header file defines the classes and functions used in converting regular expressions to NFAs.

#ifndef REG_TO_NFA_H
#define REG_TO_NFA_H

#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// Represents a state in the NFA graph.
class NFAGraphState
{
public:
NFAGraphState();
NFAGraphState(bool isAccepting);
// A map of string inputs to sets of NFA states reachable from the current state using the input.
unordered_map<std::string, std::unordered_set<NFAGraphState *>> edgeTransitions;
bool isAccepting;
};

// Represents an NFA graph.
class NFAGraph
{
public:
unordered_set<NFAGraphState *> States;
// Set of strings that can be used as inputs to the NFA graph.
unordered_set<string >alphabet;
NFAGraphState *startState;
unordered_set<NFAGraphState *> acceptingStates;
// Returns the set of states reachable from the current state using the given input.
unordered_set<NFAGraphState *> transitionFunction(NFAGraphState *currentState, std::string input);
// Returns the set of states reachable from the current state using epsilon transitions.
unordered_set<NFAGraphState *> epsilonClosure(NFAGraphState *currentState);
// Checks if a given string is valid for the NFA graph.
bool isValidString(string);

string shortest();
};

// A class that converts a regular expression to an NFA graph.
class regToNFAConvertor
{
public:
NFAGraph *mainNFA;
// Returns an NFA graph that accepts a single alphabet symbol.
NFAGraph *getNFAforAlphabet(string alphabet);
// Returns the NFA graph for the star operation.
NFAGraph *getStar(NFAGraph *nfa);
// Returns the NFA graph for the concatenation of two NFA graphs.
NFAGraph *getConcat(NFAGraph *nfa1, NFAGraph *nfa2);
// Returns the NFA graph for the union of two NFA graphs.
NFAGraph *getUnion(NFAGraph *nfa1, NFAGraph *nfa2);
// Converts a regular expression to an NFA graph.
NFAGraph *regToNFA(string reg);
// Returns the precedence of an operator character.
int get_precedence(char c);
// Checks if a character is an operator.
bool is_operator(char c);
// Converts a regular expression to prefix notation.
string regex_to_prefix(string regex);

};

#endif