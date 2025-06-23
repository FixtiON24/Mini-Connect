#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class User {
private:
    string username;
    string password;
    vector<string> posts;
    vector<string> friends;

public:
    User() {}
    User(string uname, string pwd) {
        username = uname;
        password = pwd;
    }

    string getUsername() {
        return username;
    }

    bool login(string pwd) {
        return pwd == password;
    }

    void postStatus(string status) {
        posts.push_back(status);
        cout << "Status posted!\n";
    }

    void addFriend(string friendName) {
        if (friendName == username) {
            cout << "You can't add yourself.\n";
            return;
        }
        for (string f : friends) {
            if (f == friendName) {
                cout << "Already friends with " << friendName << ".\n";
                return;
            }
        }
        friends.push_back(friendName);
        cout << friendName << " added as friend.\n";
    }

    void viewFriends() {
        cout << "Your friends:\n";
        for (string f : friends) {
            cout << "- " << f << endl;
        }
    }

    void viewPosts() {
        cout << "Your posts:\n";
        for (string p : posts) {
            cout << "- " << p << endl;
        }
    }
};

// Global user storage
unordered_map<string, User> users;

void menu(User& user) {
    int choice;
    do {
        cout << "\n1. Post a status\n2. View my posts\n3. Add friend\n4. View friends\n5. Logout\nChoice: ";
        cin >> choice;
        cin.ignore();
        string input;

        switch (choice) {
            case 1:
                cout << "Enter status: ";
                getline(cin, input);
                user.postStatus(input);
                break;
            case 2:
                user.viewPosts();
                break;
            case 3:
                cout << "Enter friend's username: ";
                getline(cin, input);
                user.addFriend(input);
                break;
            case 4:
                user.viewFriends();
                break;
            case 5:
                cout << "Logged out.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 5);
}

int main() {
    int choice;
    string uname, pwd;

    while (true) {
        cout << "\n=== MiniConnect ===\n";
        cout << "1. Sign Up\n2. Log In\n3. Exit\nChoice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "Choose a username: ";
            getline(cin, uname);
            if (users.find(uname) != users.end()) {
                cout << "Username already taken.\n";
                continue;
            }
            cout << "Choose a password: ";
            getline(cin, pwd);
            users[uname] = User(uname, pwd);
            cout << "Sign up successful!\n";
        } else if (choice == 2) {
            cout << "Username: ";
            getline(cin, uname);
            cout << "Password: ";
            getline(cin, pwd);
            if (users.find(uname) != users.end() && users[uname].login(pwd)) {
                cout << "Login successful!\n";
                menu(users[uname]);
            } else {
                cout << "Invalid credentials.\n";
            }
        } else if (choice == 3) {
            cout << "Exiting...\n";
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
