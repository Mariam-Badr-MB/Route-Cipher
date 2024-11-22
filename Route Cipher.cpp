#include <bits/stdc++.h>
using namespace std;

void clear_Input();
string encipher_route(const string& message, int column);
string decipher_route(const string& message, int column);

int main() {
    string choice, message;

    cout << "================ Route Cipher Program ================" << endl;

    while (true) {
        cout << "A) Encipher\nB) Decipher\nC) Exit\n";
        cout << "Choose an option: ";
        getline(cin, choice);

        while (choice != "A" && choice != "a" && choice != "B" && choice != "b" && choice != "C" && choice != "c") {
            clear_Input();
            cout << "Invalid input. Enter a valid choice: ";
            getline(cin, choice);
        }

        if (choice == "C" || choice == "c") {
            cout << "Thank you for using the Route Cipher program!" << endl;
            break;
        }

        cout << "Enter your message: ";
        getline(cin, message);

        int column;
        cout << "Enter the key (column count): ";
        cin >> column;

        while (cin.fail() || column <= 0 || column > (message.size() / 2)) {
            clear_Input();
            cout << "Invalid input. Enter a valid positive integer: ";
            cin >> column;
        }

        if (choice == "A" || choice == "a") {
            cout << "Encrypted message: " << encipher_route(message, column) << endl;
        } else if (choice == "B" || choice == "b") {
            cout << "Decrypted message: " << decipher_route(message, column) << endl;
        }

        clear_Input();
    }
    return 0;
}

// Function to clear input
void clear_Input() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Function to encipher using Route Cipher
string encipher_route(const string& message, int column) {
    string message_t, encipher_message;

    for (char c : message) {
        if (isalpha(c)) {
            message_t += toupper(c);
        }
    }

    int row = (message_t.length() + column - 1) / column;
    char** matrix = new char*[row];
    for (int i = 0; i < row; ++i) {
        matrix[i] = new char[column];
    }

    int index = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            matrix[i][j] = index < message_t.size() ? message_t[index++] : 'X';
        }
    }

    int top = 0, bottom = row - 1, left = 0, right = column - 1;

    while (top <= bottom && left <= right) {
        for (int i = top; i <= bottom; i++) encipher_message += matrix[i][right];
        right--;
        for (int i = right; i >= left; i--) encipher_message += matrix[bottom][i];
        bottom--;
        for (int i = bottom; i >= top; i--) encipher_message += matrix[i][left];
        left++;
        for (int i = left; i <= right; i++) encipher_message += matrix[top][i];
        top++;
    }

    for (int i = 0; i < row; ++i) delete[] matrix[i];
    delete[] matrix;

    return encipher_message;
}

// Function to decipher using Route Cipher
string decipher_route(const string& message, int column) {
    string message_t, decipher_message;

    for (char c : message) {
        if (isalpha(c)) {
            message_t += toupper(c);
        }
    }

    int row = (message_t.length() + column - 1) / column;
    char** matrix = new char*[row];
    for (int i = 0; i < row; ++i) {
        matrix[i] = new char[column];
    }

    int top = 0, bottom = row - 1, left = 0, right = column - 1;
    int index = 0;

    while (top <= bottom && left <= right) {
        for (int i = top; i <= bottom; i++) matrix[i][right] = message_t[index++];
        right--;
        for (int i = right; i >= left; i--) matrix[bottom][i] = message_t[index++];
        bottom--;
        for (int i = bottom; i >= top; i--) matrix[i][left] = message_t[index++];
        left++;
        for (int i = left; i <= right; i++) matrix[top][i] = message_t[index++];
        top++;
    }

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; j++) {
            decipher_message += matrix[i][j];
        }
    }

    for (int i = 0; i < row; ++i) delete[] matrix[i];
    delete[] matrix;

    return decipher_message;
}
