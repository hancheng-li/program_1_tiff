#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>

using namespace std;

class Book{
    public: 
        int ISBN;
        string language;
        string type; 
};

ostream& operator<<(ostream& out, vector<Book> v) {
    cout << "{";
    for(int i = 0; i < (int)v.size(); i++) {
        cout << "[" << v.at(i).ISBN << "," << v.at(i).language << "," << v.at(i).type << "]," << endl;
    }
    cout << "}";
    return out;
}

bool operator==(Book lhs, Book rhs) {
    return lhs.ISBN == rhs.ISBN && lhs.language == rhs.language && lhs.type == rhs.type;
}

bool operator<(Book lhs, Book rhs) {
    if(lhs.ISBN == rhs.ISBN) {
        if(lhs.type == rhs.type) {
            if(lhs.language == rhs.language) {
                return false;
            }
            else {
                return lhs.language < rhs.language;
            }
        }
        else {
            int l;
            int r;
            if(lhs.type == "new") {
                l = 1;
            }
            if(lhs.type == "used") {
                l = 2;
            }
            if(lhs.type == "digital") {
                l = 3;
            }
            if(rhs.type == "new") {
                r = 1;
            }
            if(rhs.type == "used") {
                r = 2;
            }
            if(rhs.type == "digital") {
                r = 3;
            }
            return l < r;
        }
    }
    else {
        return lhs.ISBN < rhs. ISBN;
    }
}

int linearSearch(vector<Book> b, vector<Book> v) {
    int count = 0;
    for(int i = 0; i < (int)b.size(); i++){
        for(int j = 0; j < (int)v.size(); j++) {
            if (b.at(i) == v.at(j)) {
                count++;
                break;
            }        
        }
    }
    return count;
}

int iterativeBinarySearch(vector<Book> b, vector<Book> v, int start, int end) {
    sort(v.begin(), v.end()); // sort vector of books
    int count = 0;
    while (end - start >= 1) {
        int middle = (int)v.size() / 2;
        for(int i = 0; i < (int)v.size(); i++){
            if (b.at(i) == v.at(middle)) {
                count++;
                break;
            }

            if (b.at(i) < v.at(middle)) {
                end = middle - 1;
            }
            
            else {
                start = middle + 1;
            }   
        } 
    }
    return count;
}

int recursiveBinarySearch(vector<Book> b, vector<Book> v, int start, int end) {
    sort(v.begin(), v.end()); // sort vector of books
    for(int i = 0; i < (int)v.size(); i++){
        int count = 0;
        if ((int)v.size() >= 1) {
            int middle = v.size() / 2;
            if (b.at(i) == v.at(middle)) {
                count++;
                break;
            }
            
            if (b.at(i) < v.at(middle)) {
                return recursiveBinarySearch(b, v, 0, middle - 1);
            }
            return recursiveBinarySearch(b, v, middle + 1, v.size());
        }
    return count;   
    }
}

int main(int argc, char *argv[]) {
    string newBookFile = argv[1];
    string requestFile = argv[2];
    ifstream file;
    file.open(newBookFile);
    vector<Book> newBooks;
    string line;
    while(getline(file, line)) {
        stringstream ss(line);
        string isbn;
        Book b;
        getline(ss,isbn, ',');
        b.ISBN = stoi(isbn);
        getline(ss,b.language, ',');
        getline(ss,b.type, '\n');
        newBooks.push_back(b);
    }
    file.close();
    
    vector<Book> requestBooks;
    file.open(requestFile);
    while(getline(file, line)) {
        stringstream ss(line);
        string isbn;
        Book b;
        getline(ss,isbn, ',');
        b.ISBN = stoi(isbn);
        getline(ss,b.language, ',');
        getline(ss,b.type, '\n');
        requestBooks.push_back(b);
    }

    cout << "Choice of search method ([l]inear, [b]inary, [r]ecursiveBinary)?" << endl;
    char search = 'l';
    cin >> search;
    std::chrono::high_resolution_clock::time_point start; // Start recording the CPU time
    start = std::chrono::high_resolution_clock::now();
    switch (search) {
        case 'l':
            linearSearch(requestBooks, newBooks);
            break;
        case 'b':
            iterativeBinarySearch(requestBooks, newBooks, 0, newBooks.size()-1);
            break;
        case 'r':
            recursiveBinarySearch(requestBooks, newBooks, 0, newBooks.size()-1);
            break;
        default:
            cout << "Incorrect choice" << endl;
            cout << "Choice of search method ([l]inear, [b]inary, [r]ecursiveBinary)?" << endl;
            // If user didn't choose one of the three search methods, then asking again
    }
    auto end = std::chrono::high_resolution_clock::now(); // Stop recording the CPU time
    double elapsed_us = std::chrono::duration<double, std::micro>(end - start).count();
    cout << "CPU time: " << elapsed_us << " microseconds" << endl; // Print the CPU time
}



