#include <bits/stdc++.h>
#include "REGL__NFA.h"
using namespace std;

NFAGraphState::NFAGraphState()
{
    this->edgeTransitions["@"].insert(this);
    this->isAccepting = false;
}

NFAGraphState::NFAGraphState(bool isAccepting)
{ //thus is the constructor for the NFAGraphState
    this->edgeTransitions["@"].insert(this);
    this->isAccepting = isAccepting;
}

unordered_set<NFAGraphState *> NFAGraph::transitionFunction(NFAGraphState *currentState, std::string input)
{
    return currentState->edgeTransitions[input];
}






//checking the epsion closure 
unordered_set<NFAGraphState *> NFAGraph::epsilonClosure(NFAGraphState *currentState)
{
    unordered_set<NFAGraphState *> closure = {currentState};
    stack<NFAGraphState *> stack;
    stack.push(currentState);
    while (!stack.empty())
    {
        NFAGraphState *state = stack.top();
        stack.pop();
        //loop to calculate the epsilon 
        for (NFAGraphState *state2 : state->edgeTransitions["@"])
        {//if the state is not in the closure then insert it
            if (closure.find(state2) == closure.end())
            {
                closure.insert(state2);
                stack.push(state2);
            }//if the state is in the closure then continue
        }
    }
    return closure;
}

bool NFAGraph::isValidString(std::string input)
{
    unordered_set<NFAGraphState *> currentStates = epsilonClosure(startState);
    for (int i = 0; i < input.length(); i++) //loop to check the input
    {
        unordered_set<NFAGraphState *> nextStates = {};
        for (NFAGraphState *state : currentStates) //loop to check the current state
        {
            unordered_set<NFAGraphState *> temp = transitionFunction(state, input.substr(i, 1)); //transition function
            for (NFAGraphState *state2 : temp) //loop to check the state
            {
                unordered_set<NFAGraphState *> temp2 = epsilonClosure(state2); //epsilon closure
                nextStates.insert(temp2.begin(), temp2.end());
            }
        }
        currentStates = nextStates; //set the current state to the next state
    }
    for (NFAGraphState *state : currentStates)
    {
        if (state->isAccepting) //  if the state is accepting then return true
        {
            return true;
        }
    }
    return false;
}

// Returns an NFA graph that accepts a single alphabet symbol.
NFAGraph *regToNFAConvertor::getNFAforAlphabet(string alphabet)
{
// Create a new NFA graph.
NFAGraph *nfa = new NFAGraph();
// Add the given alphabet to the set of valid inputs for the NFA graph.
nfa->alphabet.insert(alphabet);
// Create a start state and an accepting state.
NFAGraphState *startState = new NFAGraphState();
NFAGraphState *acceptingState = new NFAGraphState(true);
// Add a transition from the start state to the accepting state using the given alphabet.
startState->edgeTransitions[alphabet].insert(acceptingState);
// Add the start and accepting states to the NFA graph.
nfa->States.insert(startState);
nfa->States.insert(acceptingState);
// Set the start and accepting states for the NFA graph.
nfa->startState = startState;
nfa->acceptingStates.insert(acceptingState);
return nfa;
}
NFAGraph *regToNFAConvertor::getConcat(NFAGraph *nfa1, NFAGraph *nfa2) // nfa1.nfa2
{
    NFAGraph *nfa = new NFAGraph();
    nfa->alphabet = nfa1->alphabet;
    
    //insert the alphabet of the nfa2 to the nfa
    nfa->alphabet.insert(nfa2->alphabet.begin(), nfa2->alphabet.end());

    //insert the states of the nfa1 to the nfa
    nfa->States = nfa1->States;
    //insert the states of the nfa2 to the nfa
    nfa->States.insert(nfa2->States.begin(), nfa2->States.end());
    nfa->startState = nfa1->startState;
    nfa->acceptingStates = nfa2->acceptingStates;

    // Add epsilon transitions from the accepting states of the first NFA graph to the start state of the second NFA graph.
    for (NFAGraphState *state : nfa1->acceptingStates)
    {
        state->isAccepting = false;
        state->edgeTransitions["@"].insert(nfa2->startState);
    }
    delete nfa1;
    delete nfa2;
    return nfa;
}

NFAGraph *regToNFAConvertor::getUnion(NFAGraph *nfa1, NFAGraph *nfa2)
{
    NFAGraph *nfa = new NFAGraph();
    nfa->alphabet = nfa1->alphabet;
    //insert the alphabet of the nfa2 to the nfa
    nfa->alphabet.insert(nfa2->alphabet.begin(), nfa2->alphabet.end());
    //insert the states of the nfa1 to the nfa
    nfa->States = nfa1->States;

    //insert the states of the nfa2 to the nfa
    nfa->States.insert(nfa2->States.begin(), nfa2->States.end());

   // Create a new start state for the new NFA graph.
nfa->startState = new NFAGraphState();
nfa->States.insert(nfa->startState);
// Add epsilon transitions from the new start state to the start states of the two given NFA graphs.
nfa->startState->edgeTransitions["@"].insert(nfa1->startState);
nfa->startState->edgeTransitions["@"].insert(nfa2->startState);

// Create a new accepting state for the new NFA graph.
NFAGraphState *newState = new NFAGraphState(true);
nfa->States.insert(newState);
nfa->acceptingStates.insert(newState);
// Add epsilon transitions from the accepting states of the two given NFA graphs to the new accepting state.
for (NFAGraphState *state : nfa1->acceptingStates)
{
    state->edgeTransitions["@"].insert(newState);
}
for (NFAGraphState *state : nfa2->acceptingStates)
{
    state->edgeTransitions["@"].insert(newState);
}

// Delete the two given NFA graphs as they are no longer needed.
delete nfa1;
delete nfa2;
return nfa;
}
//same as above but for star 
NFAGraph *regToNFAConvertor::getStar(NFAGraph *nfa)
{
    NFAGraph *newNFA = new NFAGraph();
    newNFA->alphabet = nfa->alphabet;
    
    newNFA->States = nfa->States;
    newNFA->startState = new NFAGraphState(true);
    newNFA->States.insert(newNFA->startState);
    newNFA->acceptingStates.insert(newNFA->startState);
    // Add epsilon transitions from the new start state to the start states of the two given NFA graphs.
    newNFA->startState->edgeTransitions["@"].insert(nfa->startState);
    
    NFAGraphState *newState = new NFAGraphState(true);
    // Create a new accepting state for the new NFA graph.
    newNFA->States.insert(newState);
    // Add epsilon transitions from the accepting states of the two given NFA graphs to the new accepting state.
    newNFA->acceptingStates.insert(newState);


    //  Add epsilon transitions from the accepting states of the first NFA graph to the start state of the second NFA graph.
    for (NFAGraphState *state : nfa->acceptingStates)
    {
        state->edgeTransitions["@"].insert(nfa->startState);
        state->edgeTransitions["@"].insert(newState);
    }
    delete nfa;
    return newNFA;
}


NFAGraph *regToNFAConvertor::regToNFA(string reg)
{
    // Convert the regular expression to start_word notation
    string start_word = regex_to_prefix(reg);

    // Use a stack to keep track of NFAGraphs corresponding to different subexpressions
    stack<NFAGraph *> NFA_stk;

    // Iterate through the start_word notation string from right to left
    for (int i = start_word.length(); i >= 0; i--)
    {
        // If the current character is '*', pop the top NFAGraph from the stack and push its kleene closure
        if (start_word[i] == '*')
        {
            NFAGraph *nfa = NFA_stk.top();
            NFA_stk.pop();
            NFA_stk.push(getStar(nfa));
        }
        // If the current character is '.', pop the top two NFAGraphs from the stack and push their concatenation
        else if (start_word[i] == '.')
        {
            NFAGraph *nfa1 = NFA_stk.top();
            NFA_stk.pop();
            NFAGraph *nfa2 = NFA_stk.top();
            NFA_stk.pop();
            NFA_stk.push(getConcat(nfa1, nfa2));
        }
        // If the current character is '+', pop the top two NFAGraphs from the stack and push their union
        else if (start_word[i] == '+')
        {
            NFAGraph *nfa1 = NFA_stk.top();
            NFA_stk.pop();
            // If the top of the stack is a kleene closure, pop it and push its concatenation with the next NFAGraph
            NFAGraph *nfa2 = NFA_stk.top();
            NFA_stk.pop();
            NFA_stk.push(getUnion(nfa1, nfa2));
        }
        // If the current character is a letter, push a new NFAGraph for that letter onto the stack
        else
        {
            NFA_stk.push(getNFAforAlphabet(string(1, start_word[i])));
        }
    }

    // The final NFAGraph on the stack is the complete NFA corresponding to the regular expression
    mainNFA = NFA_stk.top();
    return NFA_stk.top();
}


int regToNFAConvertor::get_precedence(char c) //just give order 
{
    if (c == '*')
        return 3;
    else if (c == '.')
        return 2;
    else if (c == '+')
        return 1;
    else
        return 0;
}

bool regToNFAConvertor::is_operator(char c) //check if operator or not
{
    if (c == '*' || c == '.' || c == '+' || c == '(' || c == ')')
        return true;
    return false;
}

string regToNFAConvertor::regex_to_prefix(string infix) //convert to prefix
{
    infix = '(' + infix + ')';

    std::reverse(infix.begin(), infix.end());

    int l = infix.size();
    stack<char> char_stack;
    string output;

    for (int i = 0; i < l; i++)
    {

        // If the scanned character is an
        // operand, add it to output.
        if (!is_operator(infix[i]))
            output += infix[i];

        // If the scanned character is an
        // ‘(‘, push it to the stack.
        else if (infix[i] == ')')
            char_stack.push(')');

        // If the scanned character is an
        // ‘)’, pop and output from the stack
        // until an ‘(‘ is encountered.
        else if (infix[i] == '(')
        {
            while (char_stack.top() != ')')
            {
                output += char_stack.top();
                char_stack.pop();
            }

            // Remove '(' from the stack
            char_stack.pop();
        }

        // Operator found
        else
        {
            if (is_operator(char_stack.top()))
            {//if the top of the stack is an operator
                while (
                    get_precedence(infix[i]) < get_precedence(char_stack.top())) //if the precedence of the current operator is less than the top of the stack
                {
                    output += char_stack.top();
                    char_stack.pop(); //pop the top of the stack
                }

                // Push current Operator on stack
                char_stack.push(infix[i]);
            }
        }
    }
    while (!char_stack.empty())
    { //pop the remaining operators from the stack
        output += char_stack.top();
        char_stack.pop();
    }
    std::reverse(output.begin(), output.end());
    return output;
}


string NFAGraph::shortest()
{
    string shortestString = "";
    NFAGraphState *currentState = startState;

    queue<pair<NFAGraphState *, string>> q;
    q.push({currentState, ""});
    while (!q.empty())
    {
        pair<NFAGraphState *, string> current = q.front();
        q.pop();
        currentState = current.first;
        string currentString = current.second;
        if (acceptingStates.find(currentState) != acceptingStates.end())
        {
            shortestString = currentString;
            break;
        }
        for (NFAGraphState *state : currentState->edgeTransitions["@"])
        {
            q.push({state, currentString});
        }
      for (auto transition : currentState->edgeTransitions)
        {
            if (transition.first != "@" && transition.first != "#")
            {
                for (NFAGraphState *state : transition.second)
                {
                    q.push({state, currentString + transition.first});
                }
            }
        }
    }
    return shortestString;
}

int main() //drives the code 
{
    
    regToNFAConvertor *regToNFA = new regToNFAConvertor();
    string reg = "a.b*"
    ;
    NFAGraph *nfa = regToNFA->regToNFA(reg);

    //1 for valid 0 for invalid
    cout << nfa->isValidString("bab") << endl;
    cout << nfa->isValidString("bba") << endl;
    cout << nfa->isValidString("ababa") << endl;


    cout << nfa->shortest() << endl;
}