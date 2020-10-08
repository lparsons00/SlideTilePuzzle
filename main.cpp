//PUZZLE FOR 1D
#include <bits/stdc++.h>

#include <stdio.h>

using namespace std;

struct Node {
    Node * parent;
    int matrix[7];
    int x;
    int cost;
    int level;
};

//creates new node from struct above
Node * newNode(int matrix[7], int x, int newX, int level, Node * parent) {
    Node * node = new Node;
    node -> parent = parent;
    memcpy(node -> matrix, matrix, sizeof node -> matrix);
    swap(node -> matrix[x], node -> matrix[newX]);
    node -> cost = INT_MAX;
    node -> level = level;
    node -> x = newX;

    return node;
}

// Function to calculate the number of misplaced tiles 
// ie. number of non-blank tiles not in their goal position 
int totalCost(int first[7], int last[7], int distance) {
    int count = distance;
    for (int i = 0; i < 7; i++)
        if (first[i] && first[i] != last[i])
            count++;
    return count;
}

//heap
struct comp {
    bool operator()(const Node * lhs,
        const Node * rhs) const {
        return (lhs -> cost + lhs -> level) > (rhs -> cost + rhs -> level);
    }
};

//simple print code, calls itself to ensure all matrix are printed
void print(int matrix[7]) {
    for (int i = 0; i < 7; i++) {
        if (matrix[i] == 0) {
            printf("_ ");
        } else {
            printf("%d ", matrix[i]);
        }
    //printf("  \n");
    }
}

void printPath(Node * root) {
    if (root == NULL) {
        return;
    }
    printPath(root -> parent);
    print(root -> matrix);
    printf("\n");

}

int inside(int x) {
    return (x >= 0 && x < 7);
}


//set basic default values for 'moving' around the puzzle
int row1[] = {1,-1};
int row2[] = {2, -2};
int row3[] = {3, -3};
int row4[] = {4, -4};
int row5[] = {5, -5};
int row6[] = {6, -6};


void solve(int first[7], int x, int last[7]) {
    priority_queue < Node * , vector < Node * > , comp > que;
    int distance = 0;
    //checks cost of root (checks total distance)
    Node * root = newNode(first, x, x, 0, NULL);
    root -> cost = totalCost(first, last, distance);
    que.push(root);

    while (!que.empty()) {
        Node * bestMatch = que.top();
        //printf("testline1\n");
        //print(bestMatch->matrix);
        //int test = 0;
        //test = bestMatch ->cost;
        //printf("test: %d\n", test);
        distance = 0;
        que.pop();
        if (bestMatch -> cost == 0) {
            printPath(bestMatch);
            break;
        }
        /*
         * for each possible transition (eg move once left, move 6 spots right etc) 
         * attempt and recognize which value is closest to goal (ensuring the cost 
         * is added to the distance travelled as described in assignment brief)
         */
        for (int i = 0; i < 2; i++) {
            if (inside(bestMatch -> x + row1[i])) {
                distance = 0;
                Node * child = newNode(bestMatch -> matrix, bestMatch -> x, bestMatch -> x + row1[i],
                        bestMatch -> level + 1, bestMatch);
                child -> cost = totalCost(child -> matrix, last, distance);
                que.push(child);
            }
            if (inside(bestMatch -> x + row2[i])) {
                distance = 1;
                Node * child = newNode(bestMatch -> matrix, bestMatch -> x, bestMatch -> x + row2[i],
                        bestMatch -> level + 1, bestMatch);
                child -> cost = totalCost(child -> matrix, last, distance);
                que.push(child);
            }
            if (inside(bestMatch -> x + row3[i])) {
                distance = 2;
                Node * child = newNode(bestMatch -> matrix, bestMatch -> x, bestMatch -> x + row3[i],
                        bestMatch -> level + 1, bestMatch);
                child -> cost = totalCost(child -> matrix, last, distance);
                que.push(child);
            }
            if (inside(bestMatch -> x + row4[i])) {
                distance = 3;
                Node * child = newNode(bestMatch -> matrix, bestMatch -> x, bestMatch -> x + row4[i],
                        bestMatch -> level + 1, bestMatch);
                child -> cost = totalCost(child -> matrix, last, distance);
                que.push(child);
            }
            if (inside(bestMatch -> x + row5[i])) {
                distance = 4;
                Node * child = newNode(bestMatch -> matrix, bestMatch -> x, bestMatch -> x + row5[i],
                        bestMatch -> level + 1, bestMatch);
                child -> cost = totalCost(child -> matrix, last, distance);
                que.push(child);
            }
            if (inside(bestMatch -> x + row6[i])) {
                distance = 5;
                Node * child = newNode(bestMatch -> matrix, bestMatch -> x, bestMatch -> x + row6[i],
                        bestMatch -> level + 1, bestMatch);
                child -> cost = totalCost(child -> matrix, last, distance);
                que.push(child);
            }
        }
    }
}

//basic driver code
//sets first array, last array and where the empty value is
int main() {
    int first[7] = {1,1,1,0,2,2,2}; 
    int last[7] = {2,2,2,0,1,1,1};
    int x = 3;

    solve(first, x, last);

    return 0;
}
