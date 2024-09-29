#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;

class Library {
private:
    vector<string> bookTitles = {
        "to kill a mockingbird", "1984", "the great gatsby", "pride and prejudice", "the catcher in the rye",
        "animal farm", "brave new world", "the lord of the rings", "the chronicles of narnia", "harry potter and the sorcerer's stone",
        // Add more book titles here
        "the road less traveled", "the color purple", "the adventures of sherlock holmes", "the help", "the girl with the dragon tattoo",
        "the alchemist", "the hobbit", "the handmaid's tale", "the lord of the rings", "the secret history",
        "the fault in our stars", "the silent patient", "brave new world", "the night circus", "the goldfinch",
        "the book thief", "the kite runner", "the shining", "jurassic park", "the picture of dorian gray"
    };

    vector<string> authors = {
        "harper lee", "george orwell", "f. scott fitzgerald", "jane austen", "j.d. salinger",
        "george orwell", "aldous huxley", "j.r.r. tolkien", "c.s. lewis", "j.k. rowling",
        // Add authors corresponding to the new book titles here
        "m. scott peck", "alice walker", "arthur conan doyle", "kathryn stockett", "stieg larsson",
        "paulo coelho", "j.r.r. tolkien", "margaret atwood", "j.r.r. tolkien", "donna tartt",
        "john green", "alex michaelides", "aldous huxley", "erin morgenstern", "donna tartt",
        "markus zusak", "khaled hosseini", "stephen king", "michael crichton", "oscar wilde"
    };

    vector<string> genres = {
        "classic", "dystopian", "classic", "romance", "coming-of-age",
        "dystopian", "dystopian", "fantasy", "fantasy", "fantasy",
        // Add genres corresponding to the new book titles here
        "self-help", "literary fiction", "mystery", "historical fiction", "crime fiction",
        "inspirational", "adventure", "speculative fiction", "epic fantasy", "psychological fiction",
        "contemporary", "psychological thriller", "science fiction", "fantasy", "literary fiction",
        "historical fiction", "contemporary", "horror", "science fiction", "gothic"
    };

    vector<string> borrowed;
    vector<string> updatedList;
    unordered_map<string, vector<double>> similarityMatrix;

public:
    Library() {
        updatedList = bookTitles;
        encodeFeatures();
        calculateSimilarityMatrix();
    }

    void displayCatalog() {
        cout << "Catalog:" << endl;
        for (size_t i = 0; i < bookTitles.size(); ++i) {
            cout << i + 1 << ". " << bookTitles[i] << " by " << authors[i] << " - " << genres[i] << endl;
        }
    }

    void displayAvailableBooks() {
        cout << "Available Books:" << endl;
        for (size_t i = 0; i < updatedList.size(); ++i) {
            cout << i + 1 << ". " << updatedList[i] << endl;
        }
    }

    void displayBorrowedBooks() {
        cout << "Borrowed Books:" << endl;
        for (const auto& book : borrowed) {
            cout << "- " << book << endl;
        }
    }

    void handler() {
        cout << "Enter the book name you want to search: ";
        string bookName;
        getline(cin, bookName);

        auto it = find(updatedList.begin(), updatedList.end(), bookName);
        if (it != updatedList.end()) {
            cout << "The book is available." << endl;
            cout << "Press 1 to borrow or 2 to return: ";
            int option;
            cin >> option;
            cin.ignore(); // Clear the newline character from the input buffer
            if (option == 1) {
                borrowBook(bookName);
            } else if (option == 2) {
                returnBook(bookName);
            }
        } else {
            cout << "The book is not available." << endl;
        }
    }

    vector<string> recommendBooksByInput(const string& author, const string& genre) {
        vector<string> recommendedBooks;
        if (find(authors.begin(), authors.end(), author) == authors.end()) {
            cout << "No books found for author '" << author << "'" << endl;
            return recommendedBooks;
        }
        if (find(genres.begin(), genres.end(), genre) == genres.end()) {
            cout << "No books found for genre '" << genre << "'" << endl;
            return recommendedBooks;
        }

        for (size_t i = 0; i < bookTitles.size(); ++i) {
            if (authors[i] != author && genres[i] == genre) {
                recommendedBooks.push_back(bookTitles[i]);
            }
        }

        return recommendedBooks;
    }

private:
    void borrowBook(const string& bookName) {
        borrowed.push_back(bookName);
        updatedList.erase(find(updatedList.begin(), updatedList.end(), bookName));
        cout << "The book has been borrowed." << endl;
    }

    void returnBook(const string& bookName) {
        auto it = find(borrowed.begin(), borrowed.end(), bookName);
        if (it != borrowed.end()) {
            borrowed.erase(it);
            updatedList.push_back(bookName);
            cout << "The book has been returned." << endl;
        } else {
            cout << "The book was not borrowed or is not part of the catalog." << endl;
        }
    }

    void encodeFeatures() {
        // Encoding logic
    }

    double cosineSimilarity(const vector<double>& v1, const vector<double>& v2) {
        // Cosine similarity calculation
    }

    void calculateSimilarityMatrix() {
        // Similarity matrix calculation
    }
};

int main() {
    Library lib;
    string option;
    do {
        cout << "\nWelcome to the Library Management System" << endl;
        cout << "Press 'a' to check the catalog, 'b' to borrow or return a book, or 'c' to get book recommendations." << endl;
        cout << "Enter your choice: ";
        cin >> option;
        cin.ignore(); // Clear the newline character from the input buffer
        if (option == "a") {
            cout << "Choose what you want to see:" << endl;
            cout << "1. Catalog" << endl;
            cout << "2. Available Books" << endl;
            cout << "3. Borrowed Books" << endl;
            cout << "Enter your choice: ";
            cin >> option;
            cin.ignore(); // Clear the newline character from the input buffer
            if (option == "1") {
                lib.displayCatalog();
            } else if (option == "2") {
                lib.displayAvailableBooks();
            } else if (option == "3") {
                lib.displayBorrowedBooks();
            }
        } else if (option == "b") {
            lib.handler();
        } else if (option == "c") { // New condition for recommendations
            string authorInput, genreInput;
            cout << "Enter the author of the book: ";
            getline(cin, authorInput);
            cout << "Enter the genre of the book: ";
            getline(cin, genreInput);
            vector<string> recommendedBooks = lib.recommendBooksByInput(authorInput, genreInput);
            cout << "\nRecommended Books:" << endl;
            for (const string& book : recommendedBooks) {
                cout << "- " << book << endl;
            }
        }
        cout << "Press 'y' to continue or 'n' to exit: ";
        cin >> option;
    } while (option == "y");

    return 0;
}
