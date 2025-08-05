/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include "pqueue.h"
#include <random.h>
using namespace std;

/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */
bool isValidCell(int x, int y, const Grid<double>& world) {
    return x >= 0 && x < world.numRows() && y >= 0 && y < world.numCols();
}
void updateNode(
    Loc curr,
    Loc next,
    double newCost,
    map<Loc, double>& cost,
    map<Loc, Loc>& path,
    map<Loc, Color>& color,
    PriorityQueue<Loc>& pq,
    Loc end,
    Grid<double>& world,
    double heuristic(Loc, Loc, Grid<double>&)) {

    cost[next] = newCost;
    path[next] = curr;
    pq.enqueue(next, newCost + heuristic(next, end, world));
}

Vector<Loc>
shortestPath(Loc start,
             Loc end,
             Grid<double>& world,
             double costFn(Loc from, Loc to, Grid<double>& world),
    double heuristic(Loc start, Loc end, Grid<double>& world)) {
	// TODO: Fill this in!
    PriorityQueue<Loc> pq;
    map<Loc, double> cost;
    map<Loc, Loc> path;
    map<Loc, Color> color;
    color[start] = YELLOW;
    cost[start] = 0;
    pq.enqueue(start, heuristic(start, end, world));
    while (!pq.isEmpty()) {
        Loc curr = pq.dequeue();
        color[curr] = GREEN;
        if (curr == end) {
            Vector<Loc> ans;
            while (curr != start) {
                ans.insert(0, curr);
                curr = path[curr];
            }
            ans.insert(0, start);
            return ans;
        }
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                if (i == 0 && j == 0) {
                    continue;
                }
                int x = curr.row + i;
                int y = curr.col + j;
                if (!isValidCell(x, y, world)) continue;
                Loc next = makeLoc(x, y);
                double stepCost = costFn(curr, next, world);
                double price = cost[curr] + stepCost;
                if (color[next] == GRAY) {
                    color[next] = YELLOW;
                    updateNode(curr, next, price, cost, path, color, pq, end, world, heuristic);
                }
                else if(color[next]==YELLOW && price<cost[next]){
                    updateNode(curr, next, price, cost, path, color, pq, end, world, heuristic);
                }
            }
        }
    }
	
    return{};
}
Loc find(map<Loc, Loc>& world, Loc loc) {
    while (world[loc] != loc) {
        loc = world[loc];
    }
    return loc;
}
void initializeClusters(map<Loc, Loc>& world, int numRows, int numCols) {
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            Loc curr = makeLoc(row, col);
            world[curr] = curr;
        }
    }
}
void enqueueEdge(PriorityQueue<Edge>& edges,Loc& curr, int row, int col) {
    Loc below = makeLoc(row, col);
    Edge down = makeEdge(curr, below);
    edges.enqueue(down, randomReal(0, 1));
}
void buildEdges(PriorityQueue<Edge>& edges, int numRows, int numCols) {
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            Loc curr = makeLoc(row, col);
            if (row + 1 < numRows) {
                enqueueEdge(edges, curr, row+1, col);
            }
            if (col + 1 < numCols) {
                enqueueEdge(edges, curr, row , col+1);
            }
        }
    }
}

Set<Edge> createMaze(int numRows, int numCols) {
	// TODO: Fill this in!
    Set<Edge> res;
    map<Loc, Loc> world;
    initializeClusters(world, numRows, numCols);
    PriorityQueue<Edge> edges;
    buildEdges(edges, numRows, numCols);
    while (!edges.isEmpty() && res.size() < numRows * numCols - 1) {
        Edge e = edges.dequeue();
        Loc root1 = find(world, e.start);
        Loc root2 = find(world, e.end);

        if (root1 != root2) {
            world[root2] = root1;
            res.add(e);
        }
    }
    return res;
}
