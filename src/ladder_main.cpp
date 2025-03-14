#include "ladder.h"

int main() {
    // Load dictionary
    set<string> word_list;
    load_words(word_list, "words.txt");
    
    // For testing (uncomment to run tests)
    // verify_word_ladder();
    // return 0;
    
    // Get user input
    string begin_word, end_word;
    cout << "Enter start word: ";
    cin >> begin_word;
    
    cout << "Enter end word: ";
    cin >> end_word;
    
    // Convert to lowercase
    for (char& c : begin_word) c = tolower(c);
    for (char& c : end_word) c = tolower(c);
    
    // Check if they're the same word
    if (begin_word == end_word) {
        error(begin_word, end_word, "Start and end words cannot be the same");
        return 1;
    }
    
    // Generate and print word ladder
    vector<string> ladder = generate_word_ladder(begin_word, end_word, word_list);
    print_word_ladder(ladder);
    
    return 0;
}