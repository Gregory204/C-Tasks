#include <iostream>
#include <string>
#include <cctype>
using namespace std;

//Modifies profile information
class Profile {
    private:
        string username;
        string displayname;
        // Profile constructor for a user (initializing 
    // private variables username=usrn, displayname=dspn)
    public:
        Profile(string usrn, string dspn){
            username = usrn;
            displayname = dspn;
        }
        // Default Profile constructor (username="", displayname="")
        Profile(){
            username = "";
            displayname = "";
        }
        // Return username
        string getUsername(){
            return username;
        }
        // Return name in the format: "displayname (@username)"
        string getFullName(){
            string display = displayname + " (@" + username + ")";
            return display;
        }
        // Change display name
        void setDisplayName(string dspn){
            displayname = dspn;
        }
};

struct Post{
    string username;
    string message;
};

//Number of users and an array of Profile objects
//Think of this as the whole library of a certain amount of users
class Network {
private:
    static const int MAX_USERS = 20;
    int numUsers;
    Profile profiles[MAX_USERS];

    //findID is used mainly to search for a user by their username
    int findID(string usrn){
    for (int i = 0; i < numUsers; i++) {
        if (profiles[i].getUsername() == usrn) {
            return i;
        }
    }
    return -1;
}
    static const int MAX_POSTS = 100;
    int numPosts; // number of posts 
    Post posts[MAX_POSTS]; // array of all posts

    bool following[MAX_USERS][MAX_USERS]; // friendship matrix:
 // following[id1][id2] == true when id1 is following id2

public:
    // Make 'usrn1' follow 'usrn2' (if both usernames are in the network).
    // return true if success (if both usernames exist), otherwise return false
    bool follow(string usrn1, string usrn2){
        int usrn1_id = findID(usrn1);
        int usrn2_id = findID(usrn2);
        if(usrn1_id == -1 || usrn2_id == -1){
            return false;
        }
        following[usrn1_id][usrn2_id] = true;
        return true;
    }

    // Print Dot file (graphical representation of the network)
    void printDot(){
        cout << "digraph {" << endl;

        for(int i = 0; i < numUsers;i++){
            cout << " \"@" << profiles[i].getUsername() << "\"" << endl;
        }

        for(int i = 0; i < MAX_USERS;i++){
            for(int j = 0;j < MAX_USERS;j++){
                if(following[i][j] == true){
                    cout << " \"@" << profiles[i].getUsername() << "\"->\"@" << profiles[j].getUsername() << "\"" << endl; 
                }
            }
        }
        cout << "}" << endl;
    }

    Network(){
        numUsers = 0;
        for(int i = 0; i < MAX_USERS; i++){
            for(int j = 0;j < MAX_USERS;j++){
                following[i][j] = false;
            }
        }
    }
    // Attempts to sign up a new user with specified username and displayname
// return true if the operation was successful, otherwise return false
bool addUser(string usrn, string dspn) {
    // Check if usrn contains only alphanumeric characters
    for (char c : usrn) {
        if (!(isalpha(c) || isdigit(c))) { //if non-alphanumeric == false
            return false;
        }
    }

    // Check if numUsers is less than MAX_USERS
    if (numUsers >= MAX_USERS) {    //if numUsers is larger
        return false;   //if max of users is reached == false
    }

    // Check if usrn is not an existing username
    if (findID(usrn) == -1) {
        // Create a profile object with the specified parameters
        Profile new_user = Profile(usrn, dspn);
        // Add the new user to the profiles array
        profiles[numUsers] = new_user;
        // Increment the number of users
        numUsers++;
        // Return true to indicate successful registration
        return true;
    }

    // If usrn is an existing username, return false
    return false;
}
    bool writePost(string usrn, string msg){
        if(numPosts >= MAX_POSTS){
            return false;
        }
        if(numPosts < MAX_POSTS){
            posts[numPosts].username = usrn;
            posts[numPosts].message = msg;
            numPosts++;
            return true;
        }
        return false;
    }


bool printTimeline(string usrn){
    int id = findID(usrn);
    if(id == -1){
        return false;
    }
     for (int i = numPosts - 1; i >= 0; i--) {
        // Check whether the username of the current post is a follower of usrn or not
        int id2 = findID(posts[i].username);
        if (following[id][id2] == true || id == id2) {
            cout << profiles[id2].getFullName() << ": " << posts[i].message << endl;
        }
    }
    return true;
}
};
int main() { Network nw;
    // add three users
    nw.addUser("mario", "Mario");
    nw.addUser("luigi", "Luigi");
    nw.addUser("yoshi", "Yoshi");
nw.follow("mario", "luigi");
nw.follow("luigi", "mario");
nw.follow("luigi", "yoshi");
nw.follow("yoshi", "mario");

// write some posts
nw.writePost("mario", "It's a-me, Mario!");
nw.writePost("luigi", "Hey hey!");
nw.writePost("mario", "Hi Luigi!");
nw.writePost("yoshi", "Test 1");
nw.writePost("yoshi", "Test 2");
nw.writePost("luigi", "I just hope this crazy plan of yours works!");
nw.writePost("mario", "My crazy plans always work!");
nw.writePost("yoshi", "Test 3");
nw.writePost("yoshi", "Test 4");
nw.writePost("yoshi", "Test 5");

cout << endl;
cout << "======= Mario's timeline =======" << endl;
nw.printTimeline("mario");
cout << endl;

cout << "======= Yoshi's timeline =======" << endl;
nw.printTimeline("yoshi");
cout << endl;
}
