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
        if (u>=start && u<=end){
            graph[u-start].push_back(node_weight);
        }
    }
    myfile.close();
}


int main(int argc, char** argv){
    
    MPI_Init(&argc,&argv);

    MPI_Comm comm;
    comm = MPI_COMM_WORLD;

    int myrank, num_procs, i, graph_number, j, k, l;
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
        cout<<"Finished building graph "<<i<<" by proc "<<myrank<<endl;
    }

    filename = "infected.txt";
    file = &filename[0];

    int *infected_or_not, *quarantined, *infected_day, *quarantined_day;
    infected_or_not = new int[no_vertices];
    quarantined = new int[no_vertices];
    for(i=0; i<no_vertices; i++){
        infected_or_not[i] = 0;
        quarantined[i] = 0;
        // infected_day[i] = 0;
        // quarantined_day[i] =0;
    }
    cout<<"Initialization done"<<myrank<<endl;
    long int *new_infected, **infected;
    long int *old_arraysize, *new_arraysize;
    old_arraysize = new long int[num_procs];
    new_arraysize = new long int[num_procs];
    long int initial_infected=0, current_infected=0, neighbour_size, size=0, new_size=0, totalsize=0, new_infected_size=0;
    

    vector<long int>neighbours;
    infected = new long int*[num_procs];
    new_infected = new long int[100];
    new_infected_size = 100;

    initial_infected = get_no_lines(file);
    current_infected = 0;
    totalsize=initial_infected;

    get_infected(file, initial_infected, infected, myrank);
    for (i=0; i<num_procs; i++){
        if (i==myrank){
            new_arraysize[myrank] = initial_infected;
        }
        else{
            new_arraysize[i] = 0;
        }
    }
    // new_infected[myrank] = new long int[initial_infected];
    for (i=0; i<num_procs; i++){
        for (j=0; j<new_arraysize[i]; j++){
            cout<<infected[i][j]<<"  "<<myrank<<endl;
        // new_infected[myrank][i] = infected[myrank][i];
        }
    }
    // cout<<"reached outside while"<<myrank<<endl;
    while(totalsize){
        // cout<<"Entered while "<<myrank<<endl;
        for (i=0; i<num_procs; i++){
            // cout<<"Entered First for "<<myrank<<endl;
            for (j=0; j<new_arraysize[i]; j++){
                // cout<<"Entered Second for "<<myrank<<endl;
                if ((infected[i][j]>=start) && (infected[i][j]<end)){
                    neighbours = graph[infected[i][j]];
                    // cout<<"reached 1"<<myrank<<endl;
                    for (k=0; k<neighbours.size(); k++){
                        num = (double)((rand()%neighbours.size())) / neighbours.size();
                        if (infected_or_not[neighbours[k]]==0){
                            if (num < 0.5){
                                infected_or_not[neighbours[k]] = 0;
                                quarantined[neighbours[k]] = 1;
                                // cout<<"reached 2"<<myrank<<endl;
                            }
                            else{
                                // cout<<"reached 3"<<myrank<<endl;
                                if (infected_or_not[neighbours[k]]==0){
                                    infected_or_not[neighbours[k]] = 1;
                                    quarantined[neighbours[k]] = 1;
                                    // cout<<"flags assigned after 3"<<myrank<<endl;
                                    // size = (int)(sizeof(new_infected)/sizeof(long int));
                                    // cout<<"Size is "<<size<<endl;
                                    // cout<<"checking size"<<myrank<<endl;
                                    if (current_infected>(new_infected_size)){
                                        // cout<<"reached inside if"<<myrank<<endl;
                                        new_size = new_infected_size+100;
                                        long int *newArr;
                                        newArr = new long int[new_size];
                                        // cout<<"new array assigned"<<myrank<<endl;
                                        // std::copy(new_infected[myrank], new_infected[myrank]+std::min(size, size+100), newArr);
                                        for (l=0; l<new_infected_size; l++){
                                            newArr[l] = new_infected[l];
                                        }
                                        new_infected_size=new_size;
                                        // delete[] new_infected;
                                        // cout<<"array deleted"<<myrank<<endl;
                                        new_infected = newArr;
                                        new_infected[current_infected] = neighbours[k];
                                    }
                                    else{
                                        new_infected[current_infected] = neighbours[k];
                                    }
                                    current_infected++;

                                }
                            }
                        }
                    }
                }
            }
        }
        totalsize=0;
        // cout<<"Reached outside for "<<myrank<<endl;
        // cout<<"number of infected "<<current_infected<<" "<<myrank<<endl;
        MPI_Allgather(&current_infected, 1, MPI_LONG, new_arraysize, 1, MPI_LONG, comm);
        for (l=0; l<num_procs; l++){
            infected[l] = new long int[new_arraysize[l]];
            totalsize+=new_arraysize[l];
        }
        if (myrank==0)
                cout<<myrank<<" : "<<totalsize<<endl;
        // for(l=0; l<new_arraysize[myrank]; l++){
        //     infected[myrank][l] = new_infected[l];
        // }
        infected[myrank] = new_infected;
        // cout<<"the array created by proc "<<myrank<<" is "<<sizeof(infected[myrank])/sizeof(long int)<<endl;
        for (l=0; l<num_procs; l++){
            MPI_Bcast(infected[l], new_arraysize[l], MPI_LONG, l, comm);
        }
        MPI_Barrier(comm);
        for(l=0;l<num_procs;l++){
            for(k=0; k<new_arraysize[l];k++){
                // infected_or_not[infected[l][k]]=1;
                // quarantined[infected[l][k]] = 1;
                // if (myrank==1){
                //     cout<<l<<" "<<k<<" "<<infected[l][k]<<"\t";
                // }
            }
        }
        // cout<<"BCast performed by "<<myrank<<endl;
        MPI_Barrier(comm);
        if (myrank==0){
            // cout<<"Total infected people is "<<totalsize<<endl;
            for (l=0; l<num_procs; l++){
                // cout<<"Size of infected array "<<l<<" is "<<(int)(sizeof(infected[l])/sizeof(long int))<<endl;
            }
        }
        // break;
        current_infected=0;
        new_infected_size=0;
        // delete new_infected;
    }

    MPI_Barrier(comm);

    MPI_Finalize();
}