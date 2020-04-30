#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <bits/stdc++.h> 
#include <stdlib.h>
#include "mpi.h"

using namespace std;

long int get_no_lines(char* filename){

    long int no_vertices = 0;
    string data;

    ifstream myfile;
    myfile.open(filename);

    while(getline(myfile, data)){
        no_vertices++;
    }
    myfile.close();
    return no_vertices;
}

void get_infected(char* filename, long int no_infected, long int **infected, int rank){
    long int u, i=0;
    string data;

    ifstream myfile;

    myfile.open(filename);

    infected[rank] = new long int[no_infected];

    while(myfile>>u){
        infected[rank][i] = u;
        i++;
    }
    myfile.close();
}

void build_graph(char* filename, long int no_vertices, vector< vector<long int> >& graph, long int start, long int end){
    long int u, node_weight;
    string data;

    ifstream myfile;

    myfile.open(filename);

    // if (myfile){
    //     cout<<"file opened"<<endl;
    // }
    // else{
    //     cout<<"file not opened"<<endl;
    // }


    while(myfile>>u>>node_weight){
        if (u>=start && u<= end){
            graph[u-start].push_back(node_weight);
        }
    }
    myfile.close();
}


int main(int argc, char** argv){
    
    MPI_Init(&argc,&argv);

    MPI_Comm comm;
    comm = MPI_COMM_WORLD;

    int myrank, num_procs, i, graph_number, j;
    double num;
    MPI_Comm_rank(comm, &myrank);
    MPI_Comm_size(comm, &num_procs);

    string data, file_number, txt, filename, filename1;

    char* file;
    long int no_vertices=0, per_process, start, end;

    file = "../../../../scratch/graph-inputs_PP/node_weights.txt";
    no_vertices = get_no_lines(file);
    // cout<<"number of vertices "<<no_vertices<<" by proc "<<myrank<<endl;

    per_process = no_vertices/num_procs;
    start = myrank*per_process;

    if (myrank==num_procs-1){
        end = no_vertices;
    }
    else{
        end = start+per_process;
    }
    cout<<"Rank: "<<myrank<<" start: "<<start<<" end: "<<end<<endl;

    vector< vector<long int> > node_weights, graph;
    node_weights.resize(no_vertices);
    graph.resize(end-start);

    filename = "../../../../scratch/graph-inputs_PP/wiki-";
    txt = ".txt";


    for (i=1; i<=10; i++){

        file_number = std::to_string(i);

        filename1 = filename+file_number+txt;

        file = &filename1[0];
        build_graph(file, no_vertices, graph, start, end);
        // cout<<"Finished building graph "<<i<<" by proc "<<myrank<<endl;
    }

    filename = "infected.txt";
    file = &filename[0];

    int infected_or_not[no_vertices], quarantined[no_vertices], infected_day[no_vertices], quarantined_day[no_vertices];
    for(i=0; i<no_vertices; i++){
        infected_or_not[i] = 0;
        quarantined[i] = 0;
        infected_day[i] = 0;
        quarantined_day[i] =0;
    }

    long int **new_infected, **infected;
    long int *old_arraysize, *new_arraysize;
    long int initial_infected=0, current_infected=0, neighbour_size;
    
    vector<long int>neighbours;
    infected = new long int*[num_procs];
    new_infected = new long int*[num_procs];

    initial_infected = get_no_lines(file);

    get_infected(file, initial_infected, infected, myrank);

    // for (i=0; i<initial_inxfected; i++){
    //     cout<<infected[myrank][i]<<"  "<<myrank<<endl;
    // }
    new_infected[myrank] = new long int[initial_infected];
    while(new_infected[myrank]){
        for (i=0; i<num_procs; i++){
            for (j=0; j<(int)(sizeof(infected[i])/sizeof(long int)); j++){
                if (infected[i][j]>=start && infected[i][j]<=end){
                    neighbours = graph[infected[i][j]];
                    for (k=0; k<neighbours.size(); k++){
                        num = (double)((rand()%neighbours.size())) / neighbours.size();
                        if (quarantined[neighbours[k]]==0){
                            if (num < 0.5){
                                infected_or_not[neighbours[k]] = 0;
                                quarantined[neighbours[k]] = 1;
                            }
                            else{
                                infected_or_not[neighbours[k]] = 1; 
                                quarantined[neighbours[k]] = 1;
                                
                            }
                        }
                    }
                }
            }
        }

    }

    MPI_Barrier(comm);

    MPI_Finalize();
}



