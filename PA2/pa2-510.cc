/*
AUTHOR: Andrew Donovan
STID: 7510
DATE: 8 Nov 2020
CLASS: CS315-002 Fall 2020
PROJECT: pa2-510.cc
COMPILATION: g++ pa2-510.cc (creates a.out) The input must be from the standard input, with the redirection ’<’, and can be in string form.
SYNOPSIS:   Given a list of vertexs on a cartesain plane find the min path betweeen the source and destination vertex.
            This was first down by a Prim MST to find the best tree for the graph, not nesscailry needed but shorted the number of seraches.
            During that process each MST edge was added to a vector, this was done to actually find the path to the destination.
            For this DFS was used seeing as all edges it was given were already the local best for the given graph.
            While this is probably not the most elegant way to solve this problem, does work on all provided test cases.


COMPUTER: VM allocated by the CS department
ALGORITHM: Prim and DFS
COMPLEXITY: Prim's {O(ElogV)} + DFS{V_MST^2} <- see notes
BUGS: N/a (sans cout printing an int instead of a double, Test case 9 being output of 3 as opposed to 3.000)
REFERENCES: Geeks for Geeks for queues and pairs <= to get a better understanding, and Geeks for Geeks on Prims <= for explaintiaon diffrent 
            from the book and in class note and in class notes on Prims and DFS

NOTES:      The DFS is only running on the returned MST vertex's so it is a smaller sub problem than the full graph which is handled by Prim's.

*/

#include <bits/stdc++.h>
#include <vector>
using namespace std;

const int GRAPH_SIZE = 100; // allows for easier passing and is already inlcuded in the project standard

void addEdge(vector<int> v[], int x, int y) 
{ 
    v[x].push_back(y); 
    v[y].push_back(x); 
} // Helper to easily add edges into the vector no matter the size of the graph

void findPath(vector<int> stack, double graph_of_dist[GRAPH_SIZE][GRAPH_SIZE]) 
{ 
    double max_min = 0;
    int i, x, y; 
    for (i = 0; i < (int)stack.size() - 1; i++) { 
        x = stack[i];
        y= stack[i+1];

        if(graph_of_dist[x][y] > max_min)
            max_min = graph_of_dist[x][y];

    } 

    cout << setprecision(3) << fixed << max_min << endl;
 
} 

void DFS(vector<int> v[], bool vis[],  int x,  int y, vector<int> stack, double graph_of_dist[GRAPH_SIZE][GRAPH_SIZE]) 
{ 
    stack.push_back(x); 
    if (x == y) { 
  
        // find path and return on 
        // reaching the destination node 
        findPath(stack, graph_of_dist); 
        return; 
        // used to break out of the function
    } 
    
    vis[x] = true; 
  
    // if backtracking is taking place 
    if (!v[x].empty()) { 
        for (int j = 0; j < v[x].size(); j++) { 
            // if the node is not visited 
            if (vis[v[x][j]] == false) {
                
                DFS(v, vis, v[x][j], y, stack, graph_of_dist); 
                // recursively look down each branch

            }
        } 
    } 
  
    stack.pop_back(); 
} 


bool validEdge(int u, int v, vector<bool> inMST){ // checking for legit edges / not already seen

    if (u == v) // same vertex, no edge
       return false; 
   if (inMST[u] == false && inMST[v] == false) 
        return false; 
   else if (inMST[u] == true && inMST[v] == true) // already seen in the MST
        return false; 
   return true; // return true if one vertex edge has not been seen
}


void primMST(double graph_of_dist[GRAPH_SIZE][GRAPH_SIZE], int numHoles){

 vector<bool> inMST(numHoles, false); 
 vector<int> vertex[numHoles], stack; 
  
    // Include first vertex in MST 
    inMST[0] = true; 
  
    // Keep adding edges while number of included 
    // edges does not become V-1. 
    int edge_count = 0;
    
    while (edge_count < numHoles -1) { 
  
        // Find minimum weight valid edge.   
        double min = DBL_MAX;
        
        int curr = -1, next = -1; 
        
        for (int i = 0; i < numHoles; i++) { 
            
            for (int j = 0; j < numHoles; j++) {                
                
                if (graph_of_dist[i][j] < min) { //see if current edge is less than the previously found edge
                    
                    if (validEdge(i, j, inMST)) { // check if its an edge not seen 
                        
                        min = graph_of_dist[i][j]; 
                        curr = i; 
                        next = j; 
                    } 
                } 
            } 
        } 
        
        if (curr != -1 && next != -1) { 
    
            edge_count++;
                   
            inMST[next] = inMST[curr] = true; // Updating vector

            addEdge(vertex, curr, next);  // add for dfs transversal
                                    // This may not be needed but is the only way I could think of the soultion at the time
                                    // of implementation
           
        } 
    }     


    // visited array 
    bool vis[numHoles + 1]; 
  
    memset(vis, false, sizeof(vis)); 
  
    // DFS function call 

    DFS(vertex, vis, 0, 1, stack, graph_of_dist); 
    // based off of the project template
    // 0 is the source node and 1 is the destination
    // that is why it is hard coded as such
    // graph_of_dist is effectavly a lookup table 
    // so that the distances do not have to be  
    // recalculated and can just be looked up
    // vertex is a vecotr to store all edges in of the MST
    // thereby cutting down paths DFS uses 
    // Stack is to store the returned path

} 

 
//Calc Distance ecluidan for two points

double calcDist(int x1, int y1, int x2, int y2){

    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0); 

}


//read in and set
int main()
{
    int numHoles =-1, X = -1, Y = -1, X2 = -1, Y2 =-1; // -1 to make sure it is set correctly

    cin >> numHoles;

    vector< pair<int, int> > map;

    // used to keep easy track of the input pairs

    for(int i = 0; i < numHoles; i++){

        cin >> X >> Y;

        map.push_back( make_pair(X,Y) );
    }
/*
    for (int i=0; i< numHoles; i++) // test code to make sure load in is correct
    { 
        // "first" and "second" are used to access 
        // 1st and 2nd element of pair respectively 
        cout << map[i].first << " " << map[i].second << endl; 
    } 
*/
    double graph_of_dist[GRAPH_SIZE][GRAPH_SIZE]; // store distances for checking

    // enplace pair wise distances into the graph
    // becomes a lookup table so repeat calculations do not have to be redone

    for (int i = 0; i < numHoles; i++){
        for (int j = 0; j < numHoles; j++){

            X = map[i].first;
            Y = map[i].second;
        
            X2 = map[j].first;
            Y2 = map[j].second;

            graph_of_dist[i][j] = calcDist(X, Y, X2, Y2);

        }
    }

/*
    for (int i = 0; i < numHoles; i++){ // test code to make sure graph is correct
        for (int j = 0; j < numHoles; j++){

            cout << right << setw(3) << graph_of_dist[i][j] << " ";
        }
        cout << "\n";
    }
*/

    primMST(graph_of_dist, numHoles);

    /*
        Is used to find the MST of the given graph, the reasoning being that there could be edge cases where a diffrent path may be better.
        Once the MST is found those edges are loaded into another vector to DFS on, therby finding a path from the source to destination.
        The reason for using both was to make sure that the best path was found and returned.
        Nor could I find / think of a better algortyhm that solved this problem better; so I combined two of them. 

    */


    return 0;
}