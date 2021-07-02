#include <queue>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

using namespace std;

size_t findCaseInsensitive(string data, string toSearch, size_t pos = 0)
{
    transform(data.begin(), data.end(), data.begin(), ::tolower);
    transform(toSearch.begin(), toSearch.end(), toSearch.begin(), ::tolower);
    return data.find(toSearch, pos);
}


// traces parent pointers back from endv to startv

void printPath(int parents[], int size, int startv, int endv, vector <string> citylist) {
    if (endv != startv) {
        printPath(parents, size, startv, parents[endv], citylist);
    }
    else {
        cout << citylist[endv];
        return;
    }
    cout << "-->" << citylist[endv];
}

//       

void bfs(vector<int> alists[], int size, int start, int target, vector <string> citylist) {

    int* parents = new int[size];

    for (int i = 0; i < size; i++) parents[i] = -1;

    parents[start] = start;

    queue<int> q;

    q.push(start);

    bool found = false;

    while (!q.empty() && !found) {

        int v = q.front();

        q.pop();

        if (v == target)

            found = true;

        else for (int i = 0; i < alists[v].size(); i++) {

            int w = alists[v][i];

            if (parents[w] == -1) {

                parents[w] = v;

                q.push(w);

            }

        }

    }

    if (found)

        printPath(parents, size, start, target, citylist);

    else

        cout << "Not found";

    cout << endl;

    delete[] parents;

}


int main() {

    vector <string> citylist;
    vector <int> alists[140];  //becasue the citylist have 140 elements, Adjacency lists for a sample graph

    ifstream in("connections.txt");
    string line;
    bool existcheck = false;
    while (getline(in, line))
    {
        string part1 = line.substr(0, 7);
        string part2 = line.substr(7, string::npos);
        existcheck = false;
        for (auto i = citylist.begin(); i != citylist.end(); i++) {
            if (*i == part2) {
                existcheck = true;
                break;
            }
        }
        if (existcheck == false) citylist.push_back(part2);
    }
    in.close();
    ifstream in2("connections.txt");
    unsigned int i = 0, j = 0;
    while (getline(in2, line))
    {
        string part1 = line.substr(0, 7);
        string part2 = line.substr(7, string::npos);

        if (part1 == "From:  ") {
            for (i = 0; i < citylist.size(); i++) { //find index of "from"
                if (citylist[i] == part2) break;
            }
        }
        else {
            for (j = 0; j < citylist.size(); j++) { //find index of "To"
                if (citylist[j] == part2) break;
            }
            alists[i].push_back(j);
        }
    }
    in2.close();

    bool done = false, searchcheck = false;
    string start, goal;
    while (done == false) {
        searchcheck = false;
        while (searchcheck == false) {
            searchcheck = false;
            cout << "Please enter a departing city name or \"quit\" to exit:" << endl;
            cin >> start;
            if (start.size() < 2) {
                cout << "Please use at least two characters." << endl;
                continue;
            }
            else if (start == "quit") {
                done = true;
                return 0;
            }
            for (unsigned int i = 0; i < citylist.size(); i++) {
                if (findCaseInsensitive(citylist[i], start) != string::npos) {
                    cout << i << ": " << citylist[i] << endl;
                    searchcheck = true;
                }
            }
            if (searchcheck == false) cout << "Found no results. Try again" << endl;
        }

        int Departure = 0;
        searchcheck == false;
        do {
            cout << "Please select a departing city by entering a number from the list above :" << endl;
            cin >> Departure;
            if (Departure > 139 || Departure < 0) {
                cout << "Number out of range, try again" << endl;
            }
            else {
                searchcheck = true;
            }
        } while (searchcheck == false);


        cout << "Selected Departure: " << Departure << "; " << citylist[Departure] << endl << endl;
        searchcheck = false;
        while (searchcheck == false) {
            searchcheck = false;
            cout << "Please enter a destination city or \"quit\" to exit :" << endl;
            cin >> goal;
            if (goal.size() < 2) {
                cout << "Please use at least two characters." << endl;
                continue;
            }
            else if (goal == "quit") {
                done = true;
                return 0;
            }
            for (unsigned int i = 0; i < citylist.size(); i++) {
                if (findCaseInsensitive(citylist[i], goal) != string::npos) {
                    cout << i << ": " << citylist[i] << endl;
                    searchcheck = true;
                }
            }
            if (searchcheck == false) cout << "Found no results. Try again" << endl;
        }


        int Destination = 0;

        searchcheck == false;
        do {
            cout << "Please select a destination city by entering a number from the list above :" << endl;
            cin >> Destination;
            if (Destination > 139 || Destination < 0) {
                cout << "Number out of range, try again" << endl;
            }
            else {
                searchcheck = true;
            }
        } while (searchcheck == false);

        cout << "Selected Destination: " << Destination << "; " << citylist[Destination] << endl;

        cout << "Shortest Route: ";
        bfs(alists, 140, Departure, Destination, citylist);
        string another;
        cout << endl << "Make another search? (\"yes\" or \"no\"):";
        cin >> another;
        if (another == "no") done = true;
    }
    system("pause");
    return 0;
}

