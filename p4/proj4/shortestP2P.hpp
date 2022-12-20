#include<iostream>
#include<list>
#include<vector>
#include<climits>
// You are not allowed to include additional libraries, either in shortestP2P.hpp or shortestP2P.cc

#define INF INT_MAX

using namespace std;

class ShortestP2P {
  public:
      ShortestP2P() = default;
      ~ShortestP2P(){
          delete [] edges;
          delete [] marked;
          delete [] parent;

          for (int i = 0; i <node_num ; ++i) {
              delete [] map[i];
          }
          delete [] map;
      }

      /* Read the graph from stdin
       * The input has the following format:
       *
       * Firstline: 1 unsigned int, the total number of verticies, X.
       * Secondline: 1 unsigned int, the total number of edges between vertices, Y.
       * A set of Y lines, each line contains tuple of 2 unsigned int and 1 int (not unsigned int!), in the format of: A(point 1, unsigned) B(point 2, unsigned) dist(distance, int)
       *
       * Example:
       * 4
       * 4
       * 0 1 5
       * 1 2 -1
       * 2 3 4
       * 3 1 6
       * 
       * 
       * 
       *
       * Vertices that are not connected have a infinitly large distance. You may use INF (previously defined at the top of this cope snippet) for infinitly large distance.
       * 
       * Special: when the graph is not proper, where there exist any pair of vertices whose minimum distance does not exist, terminate immediately by printing:
       * cout << "Invalid graph. Exiting." << endl;
       *
       * Note: vertex pairs that are not connected, which have infinitely large distances are not considered cases where "minimum distances do not exist".
       */
      void readGraph(){
          // initialize the number of nodes and edges
          cin>>node_num>>edge_num;
          // generate map
          map=new int*[node_num];
          edges=new int[node_num];
          for (int k = 0; k <node_num ; ++k) {
              map[k]=new int[node_num];
          }
          // initialize the map with infinity
          for (int i = 0; i <node_num ; ++i) {
              for (int j = 0; j <node_num ; ++j) {
                  if(i==j) map[i][j]=0;
                  else map[i][j]=INF;
              }
              edges[i]=0;
          }
          // create new edges
          int start_node_ind, end_node_ind, cur_weight;
          for (int j = 0; j <edge_num ; ++j) {
              cin>>start_node_ind>>end_node_ind>>cur_weight;
              map[start_node_ind][end_node_ind]=cur_weight;
              ++edges[start_node_ind];
          }
          // proper or not (check whether exist a loop which has a total negative weight)
          check_valid();
          // use the idea of dp to obtain the distance map for all the nodes
          floyd();
      }

      /* Input: 2 vertices A and B
       * Output: distance between them.
       * cout << dist << endl;
       *
       * When the A and B are not connected print INF:
       * cout << "INF" << endl;
       */
      void distance(unsigned int A, unsigned int B){
          if (map[A][B]==INF){
              cout<<"INF"<<endl;
          }else {
              cout << map[A][B] << endl;
          }
      }

  private:
    // internal data and functions.

    int node_num;
    int edge_num;
    int * edges;
    int * marked;
    int * parent;
    int **map;

    void dfs(int cur_index){
        // mark as visited
        marked[cur_index]=1;
        for (int next_index = 0; next_index <node_num ; ++next_index) {
            if (map[cur_index][next_index]==INF || cur_index==next_index) continue;
            // if the next node is not visited, record the current edge to it and dfs it
            if (marked[next_index]==0){
                parent[next_index]=cur_index;
                dfs(next_index);
            }
            // if the next node is already visited, there exists a loop
            else if(marked[next_index]==1){
                int temp_index=cur_index;
                int sum=0;
                sum+=map[cur_index][next_index];
                while (parent[temp_index]!=next_index){
                    sum+=map[parent[temp_index]][temp_index];
                    temp_index=parent[temp_index];
                }
                sum+=map[parent[temp_index]][temp_index];
                // if the loop is a negative loop, then the shortest path between two nodes may be negative infinity
                if (sum<0) {
                    cout<<"Invalid graph. Exiting."<<endl;
                    exit(0);
                }
                // If exist such situation: 0<=>1<=>2, cannot directly return to the upper case
                if (edges[temp_index]==1) return;
                else continue;
            }
        }
        marked[cur_index]=-1;
    }

    void check_valid(){
        // check whether there exists a loop which has a total negative length
        marked= new int[node_num];
        parent= new int[node_num];
        for (int j = 0; j <node_num ; ++j) {
            marked[j]=0;
        }

        for (int i = 0; i <node_num ; ++i) {
            if (marked[i]!=-1) dfs(i);
        }
    }

    void floyd(){
        // floyd algorithm
        // calculate the distance between nodes
        for (int k = 0; k <node_num ; ++k) {
            for (int i = 0; i < node_num; ++i) {
                // the "if" condition is used to reduce time
                if (map[i][k]<INF && i!=k){
                    for (int j = 0; j < node_num; ++j) {
                        if (j==i || j==k || map[k][j]==INF) continue;

                        if (map[i][j] > map[i][k] + map[k][j]) {
                            map[i][j] = map[i][k] + map[k][j];
                        }
                    }
                }
            }
        }
    }
};
