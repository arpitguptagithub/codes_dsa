// trl 2
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// Define a struct for a node in the NFA
struct Node
{
    int id;
    unordered_map<char, unordered_set<int>> transitions;
    bool acpt;
};

// Define a class for the NFA
class NFA
{
public:
    NFA()
    {
        // Initialize the start and acpt states
        start_state = {0};
        acpt_state = {1};
        // Create the start and acpt nodes
        nodes.push_back(Node{0, {}, false});
        nodes.push_back(Node{1, {}, true});
    }
    // Add a new state to the NFA
    void AddState(int id, bool acpt = false)
    {
        nodes.push_back(Node{id, {}, acpt});
        if (acpt)
        {
            acpt_state.insert(id);
        }
    }
    // Add a transition from state i to state j on symbol c
    void AddTransition(int i, int j, char c)
    {
        nodes[i].transitions[c].insert(j);
    }
    // Get the set of possible next states from the given set of states on the given symbol
    unordered_set<int> NextStates(const unordered_set<int> &states, char c)
    {
        unordered_set<int> next_states;
        for (auto state : states)
        {
            if (nodes[state].transitions.count(c))
            {
                for (auto next_state : nodes[state].transitions[c])
                {
                    next_states.insert(next_state);
                }
            }
        }
        return next_states;
    }
    // Check if the given input string belongs to the language defined by the NFA
    bool Match(const string &input)
    {
        unordered_set<int> current_states = start_state;
        for (auto c : input)
        {
            current_states = EpsilonClosure(NextStates(current_states, c));
        }
        for (auto state : current_states)
        {
            if (acpt_state.count(state))
            {
                return true;
            }
        }
        return false;
    }

public:
    vector<Node> nodes;
    unordered_set<int> start_state;
    unordered_set<int> acpt_state;
    // Compute the ε-closure of the given set of states
    unordered_set<int> EpsilonClosure(const unordered_set<int> &states)
    {
        unordered_set<int> closure = states;
        stack<int> stack;
        for (auto state : states)
        {
            stack.push(state);
        }
        while (!stack.empty())
        {
            int state = stack.top();
            stack.pop();
            if (nodes[state].transitions.count('\0'))
            {
                for (auto next_state : nodes[state].transitions['\0'])
                {
                    if (!closure.count(next_state))
                    {
                        closure.insert(next_state);
                        stack.push(next_state);
                    }
                }
            }
        }
        return closure;
    }
};

// Convert the given regular expression in postfix notation to an NFA
NFA ConvertToNFA(const string &regex)
{
    stack<NFA> stack;
    int id = 1;
    for (auto c : regex)
    {
        if (c == '.')
        {
            auto nfa2 = stack.top();
            stack.pop();
            auto nfa1 = stack.top();
            stack.pop();

            // Add ε-transitions from the acpt states of nfa1 to the start state of nfa2
            for (const auto &state : nfa1.acpt_state)
            {
                nfa1.AddTransition(state, nfa2.start_state, '\0');
            }
            // Create the new NFA from the concatenation of nfa1 and nfa2
            nfa1.acpt_state = nfa2.acpt_state;
            stack.push(nfa1);
        }
        else if (c == '|')
        {
            auto nfa2 = stack.top();
            stack.pop();
            auto nfa1 = stack.top();
            stack.pop();
            // Create a new start state and add ε-transitions to the start states of nfa1 and nfa2
            NFA nfa;
            nfa.AddState(id++);
            nfa.AddTransition(nfa.start_state, nfa1.start_state, '\0');
            nfa.AddTransition(nfa.start_state, nfa2.start_state, '\0');
            // Add ε-transitions from the acpt states of nfa1 and nfa2 to the new acpt state
            for (const auto &state : nfa1.acpt_state)
            {
                nfa.AddTransition(state, nfa.acpt_state.begin(), '\0');
            }
            for (const auto &state : nfa2.acpt_state)
            {
                nfa.AddTransition(state, nfa.acpt_state.begin(), '\0');
            }
            // Push the new NFA onto the stack
            stack.push(nfa);
        }
        else if (c == '*')
        {
            auto nfa1 = stack.top();
            stack.pop();
            // Create a new start state and add ε-transitions to the start state of nfa1 and the new acpt state
            NFA nfa;
            nfa.AddState(id++);
            nfa.AddTransition(nfa.start_state, nfa1.start_state, '\0');
            nfa.AddTransition(nfa.start_state, nfa.acpt_state, '\0');
            // Add ε-transitions from the acpt states of nfa1 to the start state of nfa1 and the new acpt state
            for (const auto &state : nfa1.acpt_state)
            {
                nfa.AddTransition(state, nfa1.start_state, '\0');
                nfa.AddTransition(state, nfa.acpt_state, '\0');
            }
            // Push the new NFA onto the stack
            stack.push(nfa);
        }
        else
        {
            // Create a new NFA for the single symbol
            NFA nfa;
            nfa.AddState(id++);
            nfa.AddState(id++, true);
            nfa.AddTransition(nfa.start_state, nfa.acpt_state, c);
            stack.push(nfa);
        }
    }
    // The final NFA is at the top of the stack
    return stack.top();
}

int main()
{
    // Convert the regular expression (a|b)*abb to an NFA
    auto nfa = ConvertToNFA("ab|*abb.");
    // Check if the input string abb belongs to the language defined by the NFA
    if (nfa.Match("abb"))
    {
        cout << "belong" << endl;
    }
    else
    {
        cout << "not belong" << endl;
    }

    return 0;
}
