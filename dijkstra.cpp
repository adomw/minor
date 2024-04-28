#include<cstdio>
#include<cstdlib>

//number of nodes
const int NODES = 8;

//max value of a link between two nodes, ("infinity")
const int INF = 100000;

//note: "visited" means "has been fully analized" rather than "some kind of path has been established"

//define graph
int Graph[NODES][NODES] = {
    {-1, 107, -1, -1, -1, 30, 27, -1},
    {107, -1, 60, 144, -1, -1, -1, 35},
    {-1, 60, -1, -1, -1, -1, 73, -1},
    {-1, 144, 73, -1, 139, -1, 82, -1},
    {-1, -1, -1, 139, -1, 58, 52, -1},
    {30, -1, -1, -1, 58, -1, 45, -1},
    {27, -1, -1, 82, 52, 45, -1, 12},
    {-1, 35, -1, -1, -1, -1, 12, -1}
};

int* dijkstra(int Graph[NODES][NODES], int source){

    //setup
    static int distance[NODES];
    bool visited[NODES];//fully analized
    for(int i = 0; i < NODES; i++){
        distance[i] = INF;
        visited[i] = false;
    }
    distance[source] = 0;
    int remaining = NODES;//remaining unvisited
    int min_node;
    int min_path;

    //calculate
    while(remaining > 0){

        //determine minimum
        min_node = -1;
        min_path = INF;
        for(int i = 0; i < NODES; i++)
            if((!visited[i]) && (distance[i] < min_path)){
                    min_path = distance[i];
                    min_node = i;
                }

        //update all the unvisited neighbours of min_node
        for(int i = 0; i < NODES; i++){
            if((Graph[min_node][i] != -1) && (!visited[i]))
                if(distance[i] > (distance[min_node] + Graph[min_node][i])){
                    distance[i] = distance[min_node] + Graph[min_node][i];
                }
        }
        visited[min_node] = true;
        remaining--;
    }
    return distance;
}

int main(){
    int Start = 7;
    int *G;
    G = dijkstra(Graph, Start);
    for(int i = 0; i < NODES; i++){
        printf("Shortest distance from %d to %d: %d\n",
               //Start + 1, i + 1, //+1 to change the naming of nodes from 0... to 1...
               Start, i,
               *(G+i));
    }
    system("pause");
    return 0;
}
