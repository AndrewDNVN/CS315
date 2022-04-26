//AUTHOR: Andrew Donovan
//STID: 7510
//DATE: 20 Oct 2020
//CLASS: CS315-002 Fall 2020
//PROJECT: pa1-510.cc
//COMPILATION: g++ pa1-50.cc (creates a.out)
//SYNOPSIS: BFS using queues and double vecotrs given a grpah input. The input must be from the standard input, with the redirection '<', and can be in string form.
//COMPUTER: VM allocated by the CS department
//ALGORITHM: BFS and Queue
//COMPLEXITY: BFS Run time of O(V+E). Size / Space is O(V). Currnetly implemented via standard library vectors and queues which are FIFO
//BUGS: N/a
//REFERENCES: Geeks for Geeks for queues and pairs <= to get a better understanding, Tau beta Pi for help reading in the file (not used in final program), and Brendon Bultman's comments on BFS that were given in class
//NOTES: For some parts of the loop the values are set to -1. I am unsure why this is needed but if they are set to 0 the program does not work. (denoted by // Notes: refrence)

#include <string>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;


int main (){

	int nodes = -1, edges = -1; 	// V = Vertex :: E = Edges

	int source = -1; 		// Start Vertex 

	//^ all set to -1 to make sure that they update

	cin >> nodes >> edges; // read in first two lines

	cin >> source;

	string hold; // create string to read in lines from input

	// Set up for reading in the file

	vector<vector<int>> graph(nodes, vector<int>(nodes)); // double layer vector to make ease of access
	// and standard lib functions useful
	
	vector<bool> seen(nodes); // used a bool to make better readiblty 
	
	seen[source] = true; // mark source as seen

	char tempChar; // converting inputs from strings

	int tempInt; // holding inputs to be inserted

	int start = -1; // working when start = -1 // unsure of why it needs to be -1 // Notes: refrence

	for(int i = -1; i < nodes; i++){ // working when i = -1 // unsure of why // Notes: refrence

		getline(cin, hold);

		int j = start;

			for(auto it = hold.begin(); it != hold.end(); it++) {

				tempChar = *it; // gooing char by char

				tempInt = tempChar - '0'; // conversion from ASCII to int

				if(tempInt > 0) //checking for newline char's and not includeing them
					graph[i][j] = tempInt;

				j++;
			}

			start ++;

		}

		// Mirroring the graph to make it easier to search

	start = 0; // resettting to clean val to mirror

	for (int i = 0; i < nodes; i++){

		for(int j = start; j < nodes; j++){

			graph[j][i] = graph[i][j];

		}

	start++;

	}	
	//Setting up BFS using queue's

	int neighbor = 0, Max_neighbor = INT_MIN, Min_neighbor = INT_MAX; 
	// set to max / min to make sure that they are updated correctly

	pair<int, int> f(source, 0); 	// location , distance from source

	queue<pair<int, int>> q;		// put source on q

	q.push(f);

	while(!q.empty()){				// loop until no new nodes found

		f = q.front();				// get most recntly found node and search from there

		q.pop();

		int curr = 0;				// set location of neighbors

			for (int i = 0; i < graph[f.first].size(); i++){
											// go across row
				if(graph[f.first][i] == 1){	// if there is an edge mark that 
					curr++;

					if((seen[i] == false) && (f.second < 2)){ // check to see if seen and if it is within range
						seen[i] = true;
						neighbor++; // set node location and distance
						pair<int, int> internal(i, f.second + 1); // create internal pair to keep clean
						q.push(internal);
					}
				
				}
		}	
		
		Max_neighbor = max(Max_neighbor, curr); // setting new max and min
		Min_neighbor = min(Min_neighbor, curr); // outside of the for loop to make sure the edges are explored
		// standard lib functions 

	}

	cout << neighbor << endl; // outputing total num neighbors
	cout << Min_neighbor << " " << Max_neighbor << endl; // in the correct format

	return 0; // clean up

}
