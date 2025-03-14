#include "ladder.h"
using namespace std;

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " for words: '" << word1 << " and " << word2 << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    int len1 = str1.length(); //todo: length or size
    int len2 = str2.length();

    if (str1 == str2) {
        return true;
    }
    
    if (abs(len1 - len2) > d) {
        return false;
    }
    
    if (d == 1) { //todo: check 
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
            return differences <= d; 
        } 
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
                    j++;  
                    if (differences > d) {
                        return false;
                    }
                }
            }
            
            if (j < longer.length()) {
                differences += longer.length() - j;
            }
            
            return differences <= d; 
        }
    }
    
    return false;  
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        return {};
    }
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    
    set<string> visited = {begin_word};
    
    while (!ladder_queue.empty()) {
        vector<string> current_ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = current_ladder.back();
        
        if (last_word == end_word) {
            return current_ladder;
        }
        
        for (const string& word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                visited.insert(word);
                vector<string> new_ladder = current_ladder;
                new_ladder.push_back(word);
                
                if (word == end_word) {
                return new_ladder;
                }
                
                ladder_queue.push(new_ladder);
            }
        }
    }
    
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
        word_list.insert(word);
    }    
    // file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (!ladder.empty()) {
        cout << "Word ladder found: ";
        for (const auto& word : ladder) {
            cout << word << " ";
        }
        cout << endl;
    } else {
        cout << "No word ladder found";
    }
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

    //set<string> word_list;
    //load_words(word_list, "words.txt");
    string begin_word, end_word;
    
    cout << "Enter the start word: ";
    cin >> begin_word;
    cout << "Enter the end word: ";
    cin >> end_word;
    
    if (begin_word == end_word) {
        error(begin_word, end_word, "The start and end words are the same!");
        return;
    }
    
    vector<string> ladder = generate_word_ladder(begin_word, end_word, word_list);
    print_word_ladder(ladder);
}