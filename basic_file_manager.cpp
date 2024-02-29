#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>

using namespace std;

void listDirectory(const string& path) {
    string command = "dir /B \"" + path + "\"";
    system(command.c_str());
}

void viewFile(const string& path) {
    ifstream file(path);
    if (file.is_open()) {
        cout << "Content of file " << path << ":" << endl;
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cerr << "Unable to open file: " << path << endl;
    }
}

void createDirectory(const string& path) {
    if (mkdir(path.c_str()) == 0) {
        cout << "Directory created successfully: " << path << endl;
    } else {
        cerr << "Failed to create directory: " << path << endl;
    }
}

void copyFile(const string& source, const string& destination) {
    ifstream src(source, ios::binary);
    ofstream dst(destination, ios::binary);
    dst << src.rdbuf();
    src.close();
    dst.close();
    cout << "File copied successfully from " << source << " to " << destination << endl;
}

void moveFile(const string& source, const string& destination) {
    if (rename(source.c_str(), destination.c_str()) == 0) {
        cout << "File moved successfully from " << source << " to " << destination << endl;
    } else {
        cerr << "Failed to move file" << endl;
    }
}

int main() {
    string command;
    while (true) {
        cout << "\nCommand (ls/view/mkdir/cp/mv/exit): ";
        getline(cin, command);

        if (command == "ls") {
            string path;
            cout << "Enter directory path: ";
            getline(cin, path);
            listDirectory(path);
        } else if (command == "view") {
            string path;
            cout << "Enter file path: ";
            getline(cin, path);
            viewFile(path);
        } else if (command == "mkdir") {
            string path;
            cout << "Enter directory path: ";
            getline(cin, path);
            createDirectory(path);
        } else if (command == "cp") {
            string source, destination;
            cout << "Enter source file path: ";
            getline(cin, source);
            cout << "Enter destination file path: ";
            getline(cin, destination);
            copyFile(source, destination);
        } else if (command == "mv") {
            string source, destination;
            cout << "Enter source file path: ";
            getline(cin, source);
            cout << "Enter destination file path: ";
            getline(cin, destination);
            moveFile(source, destination);
        } else if (command == "exit") {
            break;
        } else {
            cout << "Invalid command. Available commands: ls, view, mkdir, cp, mv, exit" << endl;
        }
    }
    return 0;
}
