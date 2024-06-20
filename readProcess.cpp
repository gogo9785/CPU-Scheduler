#include "Scheduler.h"

#include <bits/stdc++.h>
#include <fstream>
using namespace std ;


void readInput(int &algo ,ProcessQueue &queue,string & filename,int &time_quantum,int &time_limit){
    // now here we have to read the 
    ifstream inputFile(filename);
    if (inputFile.is_open()) {
        string line;
        getline(inputFile, line) ;
        algo = (line[0]-'0') ; 
        if(algo!=1 && algo!=2 && algo != 4){
            line.erase(line.begin()) ;line.erase(line.begin()) ;
            time_quantum = stoi(line) ;
        }
        
        if(algo>=8){
            getline(inputFile, line) ;
            time_limit =stoi(line) ;
        }
        getline(inputFile, line) ;
        int no_process = stoi(line) ;

        for(int i =0 ;i<no_process;i++){
            getline(inputFile, line) ;
            string pid ,brusttime , arrivaltime ,priority;
            int n = line.size() ;
            int k=0 ;
            while(k<n && line[k]!=' ')pid+=line[k], k++ ;
            k++;
            while(k<n && line[k]!=' ')arrivaltime+=line[k], k++ ;
            k++ ;
            while(k<n && line[k]!=' ')brusttime+=line[k], k++ ;
            k++ ;
            while(k<n && line[k]!=' ')priority+=line[k], k++ ;
            k++ ;

            char cata = priority[0] ;
            priority.erase(priority.begin()) ;
            Process temp = Process(stoi(pid),stoi(brusttime),stoi(priority),stoi(arrivaltime)) ;
            


            queue.processes.push_back(temp) ; 
            if(cata=='s'){queue.system_Processes.push_back(temp) ; }
            else if (cata=='i'){queue.interactive_Processes.push_back(temp) ; }
            else {queue.background_Processes.push_back(temp) ; }

            // temp.display() ;
        }
        inputFile.close();
    }
    else {
        cerr << "Error opening file: " << filename << std::endl;
    }
}