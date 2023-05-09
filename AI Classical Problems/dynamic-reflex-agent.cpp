#include <iostream>
#include <vector>
using namespace std;

enum Status {Clean, Dirty};
enum Actions {Nothing, MoveLeft, MoveRight, Suck}; // for simplicity, we will work on 1d array only (not 2d)


class Environment {
    vector<int> locations; // use a dynamic array
    int numOfLocations;

public:
    Environment(int n) {
        numOfLocations = n;
        locations.resize(numOfLocations);

        set_environment();
    }

    void set_environment() {
        // set the environment randomly

        cout << "\t \t \t \t ... Environment Setting ..." << "\n\n";

        for (int l = 0; l < numOfLocations; ++l) {
            int random = rand() % 10;
            if (random < 5)
                locations[l] = Clean;
            else
                locations[l] = Dirty;
        }
    }

    int get_status_of_location(int loc) {
        return locations[loc];
    }
    void set_status_of_location(int loc, int status) {
        locations[loc] = status;
    }

    void print_status(int agentLoc) {
        cout << "------------ Environment Status ------------" << endl;
        for (int l = 0; l < numOfLocations; ++l) {
            if (locations[l] == Clean)
                cout << "Location " << (l + 1) << " is Clean\n";
            else
                cout << "Location " << (l + 1) << " is Dirty\n";
        }

        cout << "Vacuum is in location " << (agentLoc + 1) << endl;
    }

    bool are_all_clean() {
        for (int l = 0; l < numOfLocations; ++l) {
            if (locations[l] == Dirty)
                return false;
        }
        return true;
    }
};

class Agent {
    int numOfLocations;

public:
    Agent(int n) {
        numOfLocations = n;
    }
    int vacuum_action(int loc, int status) {
        if (status == Dirty)
            return Suck;
        else if (loc == 0)
            return MoveRight;
        else if (loc == numOfLocations - 1)
            return MoveLeft;
        else {
            // move either left or right, in a random way..
            int random = rand() % 2;
            if (random == 1)
                return MoveRight;
            else
                return MoveLeft;
        }
    }
};

int main() {
    int numOfLocations;
    cout << "Enter number of locations: ";
    cin >> numOfLocations;

    Environment environment(numOfLocations);
    Agent agent(numOfLocations);

    int currentLoc = 0;
    int agentAction;
    for (int counter = 1; counter <= 15; ++counter) {
        environment.print_status(currentLoc);

        if (environment.are_all_clean()) {
            // all are clean => stop the vacuum and start from the init
            cout << "Next action is Nothing\n";
            environment.set_environment();
        }
        else {
            agentAction = agent.vacuum_action(currentLoc, environment.get_status_of_location(currentLoc));
            if (agentAction == Suck) {
                cout << "Next action is: " << "Suck" << endl;
                environment.set_status_of_location(currentLoc, Clean);
            }
            else if (agentAction == MoveRight) {
                cout << "Next action is: " << "Move Right" << endl;
                currentLoc++;
            }
            else {
                cout << "Next action is: " << "Move Left" << endl;
                currentLoc--;
            }
        }
        cout << "\n\n";
    }
    system("pause");
}