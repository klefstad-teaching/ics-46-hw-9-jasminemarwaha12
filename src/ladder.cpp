#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " for words '" << word1 << "' and '" << word2 << "'" << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    // The test expects identical strings to be within edit distance 1
    if (str1 == str2) {
        return true;
    }
    
    int len1 = str1.length();
    int len2 = str2.length();
    
    // If difference in length is greater than d, edit distance is at least that difference
    if (abs(len1 - len2) > d) {
        return false;
    }
    
    // For Homework 9, we only care about edit distance of 1
    if (d == 1) {
        // If lengths are the same, only one character can differ
        if (len1 == len2) {
            int differences = 0;
            for (int i = 0; i < len1; i++) {
                if (str1[i] != str2[i]) {
                    differences++;
                }
                if (differences > d) {
                    return false;
                }
            }
            return differences <= d; // Changed back to <= d to match test expectation
        } 
        // If lengths differ by 1, check insertion/deletion
        else if (abs(len1 - len2) == 1) {
            const string& shorter = (len1 < len2) ? str1 : str2;
            const string& longer = (len1 < len2) ? str2 : str1;
            
            int j = 0;
            int differences = 0;
            
            for (int i = 0; i < shorter.length() && j < longer.length(); ) {
                if (shorter[i] == longer[j]) {
                    i++;
                    j++;
                } else {
                    differences++;
                    j++;  // Skip one character in the longer string
                    if (differences > d) {
                        return false;
                    }
                }
            }
            
            // If we've gone through the shorter string but not the longer one
            if (j < longer.length()) {
                differences += longer.length() - j;
            }
            
            return differences <= d; // Changed back to <= d to match test expectation
        }
    }
    
    return false;  // Default case
}

bool is_adjacent(const string& word1, const string& word2) {
    // Based on tests, identical words are considered adjacent
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    // If start and end words are the same, return empty vector per test requirements
    if (begin_word == end_word) {
        return {};
    }
    
    // Queue to store partial ladders
    queue<vector<string>> ladder_queue;
    
    // Start with the begin word in the first ladder
    ladder_queue.push({begin_word});
    
    // Keep track of visited words to avoid cycles and redundant paths
    set<string> visited;
    visited.insert(begin_word);
    
    while (!ladder_queue.empty()) {
        // Get the first ladder from the queue
        vector<string> current_ladder = ladder_queue.front();
        ladder_queue.pop();
        
        // Get the last word in the current ladder
        string last_word = current_ladder.back();
        
        // If we've reached the end word, return this ladder
        if (last_word == end_word) {
            return current_ladder;
        }
        
        // Check each word in the dictionary
        for (const string& word : word_list) {
            // Skip words we've already visited
            if (visited.find(word) != visited.end()) {
                continue;
            }
            
            // Check if this word is adjacent to the last word in our ladder
            if (is_adjacent(last_word, word)) {
                // Mark this word as visited
                visited.insert(word);
                
                // Create a new ladder with this word appended
                vector<string> new_ladder = current_ladder;
                new_ladder.push_back(word);
                
                // Add to queue for further processing
                ladder_queue.push(new_ladder);
            }
        }
    }
    
    // If we get here, no ladder was found
    return {};
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    string word;
    
    if (!file) {
        cerr << "Error: Could not open file " << file_name << endl;
        return;
    }
    
    while (file >> word) {
        // Convert to lowercase for consistent comparison
        for (char& c : word) {
            c = tolower(c);
        }
        word_list.insert(word);
    }
    
    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    
    // Format changed to match expected output format in tests
    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); i++) {
        cout << ladder[i];
        if (i < ladder.size() - 1) {
            cout << " ";
        }
    }
    cout << " " << endl;
}

void verify_word_ladder() {
    #define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
    
    set<string> word_list;
    load_words(word_list, "words.txt");
    
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}