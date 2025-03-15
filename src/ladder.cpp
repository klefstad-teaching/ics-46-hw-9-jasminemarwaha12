#include "ladder.h"
using namespace std;

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " for words: '" << word1 << " and " << word2 << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    int str_length1 = str1.size();
    int str_length2 = str2.size();
    // if (str1 == str2) {
    //     return true;
    // }
    if (abs(str_length1 - str_length2) > d) {
        return false;
    }
    int edit_count_word = 0;
    int i = 0;
    int j = 0;
    while (i < str_length1 && j < str_length2) {
        if (str1[i] != str2[j]) {
            if (edit_count_word == d) {
                return false;
            }
            if (str_length1 > str_length2) {
                i++;
            } else if (str_length1 < str_length2) {
                j++;
            } else {
                i++;
                j++;
            }
            edit_count_word++;
        } else {
        i++;
        j++;
        }
    }
    if (i < str_length1) {
        edit_count_word += (str_length1 - i);
    } else if (j < str_length2) {
        edit_count_word += (str_length2 - j);
    }
    return edit_count_word <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        return {}; //or return begin_word?
    }
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    
    set<string> visited;
    visited.insert(begin_word);
    
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front(); 
        ladder_queue.pop();
        string last_word = ladder.back();
        
        // if (last_word == end_word) {
        //     return current_ladder;
        // }
        
        for (const string& word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    visited.insert(word); 
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    
                    if (word == end_word) {
                        return new_ladder;
                    }
                    
                    ladder_queue.push(new_ladder);
                }
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
        cout << "No word ladder found.\n";
    }
}

void verify_word_ladder() {
    #define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
    
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

    //set<string> word_list;
    //load_words(word_list, "words.txt");
    // string begin_word, end_word;
    
    // cout << "Enter the start word: ";
    // cin >> begin_word;
    // cout << "Enter the end word: ";
    // cin >> end_word;
    
    // if (begin_word == end_word) {
    //     error(begin_word, end_word, "The start and end words are the same!");
    //     return;
    // }
    
    // vector<string> ladder = generate_word_ladder(begin_word, end_word, word_list);
    // print_word_ladder(ladder);
}