#include "Scheduler.h"
#include <bits/stdc++.h>
using namespace std ;



void print_stats(vector<Process> & processes, const string &filename){
    std::ofstream outFile(filename, std::ios_base::app);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }

    // Write time units header to the file
    outFile<<"Stats\n\n\n" ;
    outFile << setw(20)<<left<<"process";
    for (const auto &process : processes) {
        outFile << std::setw(8) << std::left << process.processID << " ";
        
    }
    outFile << "\n";
    outFile<<"--------------------" ;
    for(int e=0 ;e<processes.size() ;e++)outFile<<"---------" ;
    outFile << "------\n";

    outFile << setw(20)<<left<<"Priority";
    for (const auto &process : processes) {
        outFile << std::setw(8) << std::left << process.priority << " ";
        
    }
    outFile << "\n";

    outFile << setw(20)<<left<<"Arrival";
    for (const auto &process : processes) {
        outFile << std::setw(8) << std::left << process.arrivalTime << " ";
        
    }
    outFile << "\n";

    outFile << setw(20)<<left<<"Brust time";
    for (const auto &process : processes) {
        outFile << std::setw(8) << std::left << process.burstTime << " ";
        
    }
    outFile << "\n";

    double add =0.00 ;
    outFile << setw(20)<<left<<"Turnaround time";
    for (const auto &process : processes) {
        add+=process.turnaroundTime ;
        outFile << std::setw(8) << std::left << process.turnaroundTime << " ";
    }
    outFile << "\n";

    outFile << setw(20)<<left<<"Finish time";
    for (const auto &process : processes) {
        outFile << std::setw(8) << std::left << process.arrivalTime+process.turnaroundTime << " ";
    }
    outFile << "\n\n\n";


    add/=processes.size() ;

    outFile<<"The mean of TurnAround time is "<<add<<"\n" ;
    outFile.close();
}
void print_trace(const vector<int> &trace, vector<Process> & processes, const string &filename) {
    const int timeUnits = trace.size();
    
    // Open file for writing
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }

    // Write time units header to the file
    outFile<<"process\\time" ;
    for (int i = 0; i <= timeUnits; ++i) {
        // if (i % 10 == 0 && i != 0) {
        //     outFile <<setw(3)<< "|";
        // }
        outFile <<setw(3)<< i % 10;
    }
    outFile<<"\n------------" ;
    for(int e=0 ;e<timeUnits ;e++)outFile<<"---" ;
    outFile << "-----\n";
    


    // Write each process's execution timeline to the file
    for (const auto &process : processes) {
        outFile << std::setw(15) << std::left << process.processID << " ";
        for (int i = 0; i < timeUnits; ++i) {
            if (trace[i] == process.processID) {
                outFile <<setw(3)<< "*";
            } 
            
            else {
                outFile <<setw(3)<< ".";
            }
        }
        outFile << "\n";
    }
    outFile<<"------------" ;
    for(int e=0 ;e<timeUnits ;e++)outFile<<"---" ;
    outFile << "-----\n";

    // Close the file
    outFile << "\n\n\n";
    outFile.close();
    print_stats(processes,filename) ;
}




void sort_brustTime(std::vector<pair<Process,int>>::iterator begin, std::vector<pair<Process,int>>::iterator end) {
    // Sort the processes based on burst time using iterators 'begin' and 'end'
    std::sort(begin, end, [](const pair<Process,int>& a, const pair<Process,int>& b) {
        if(a.first.burstTime == b.first.burstTime)return a.first.priority < b.first.priority ;
        return a.first.burstTime < b.first.burstTime;
    });
}
void sort_arrivalTime(std::vector<Process>::iterator begin, std::vector<Process>::iterator end) {
    // Sort the Processes array based on the process arrivalTime
    sort(begin,end, [](const Process &a, const Process &b) {
        if(a.arrivalTime == b.arrivalTime)return a.priority < b.priority ;
        return a.arrivalTime < b.arrivalTime;
    });
}
void sort_priority(std::vector<pair<Process,int>>::iterator begin, std::vector<pair<Process,int>>::iterator end) {
    // Sort the processes based on priority using iterators 'begin' and 'end'
    std::sort(begin, end, [](const pair<Process,int>& a, const pair<Process,int>& b) {
        return a.first.priority > b.first.priority;
    });
}
void sort_remainingTime(std::vector<pair<Process,int>>::iterator begin, std::vector<pair<Process,int>>::iterator end) {
    // Sort the processes based on burst time using iterators 'begin' and 'end'
    std::sort(begin, end, [](const pair<Process,int>& a, const pair<Process,int>& b) {
        if(a.first.remainingTime == b.first.remainingTime)return a.first.priority < b.first.priority ;
        return a.first.remainingTime < b.first.remainingTime;
    });
}




void FCFS(vector<Process> & processes){
    int total_time =0 ;
    for(auto &it:processes)total_time=max(it.burstTime+it.arrivalTime,total_time+it.burstTime) ;

    auto & tp =processes ;
    sort_arrivalTime(processes.begin(),processes.end()) ;

    vector<int> time ; // time[0] = it will give the name of process which start run at 0sec

    int index =0 ;
    for(int tim =0 ; tim<total_time ; tim++){
        if(tp[index].arrivalTime<=tim){
            tp[index].remainingTime-- ;
            time.push_back(tp[index].processID) ;
            if(tp[index].remainingTime==0){
                tp[index].turnaroundTime = tim -tp[index].arrivalTime ; 
                tp[index].waitingTime = tp[index].turnaroundTime - tp[index].burstTime ;
                index++ ;
            }
        }
        else time.push_back(-1) ;
    }
    print_trace(time,processes,"output/_output_FCFS.txt") ;
}
void SJFNP(vector<Process> & processes){

    int total_time =0 ;
    for(auto &it:processes)total_time=max(it.burstTime+it.arrivalTime,total_time+it.burstTime) ;

    auto & tp =processes ;
    sort_arrivalTime(processes.begin(),processes.end()) ;

    vector<int> time ; // time[0] = it will give the name of process which start run at 0sec

    int index =0 ;

    vector<pair<Process,int>> localq ;
    bool process_completed = true ;
    for(int tim=0 ; tim<total_time ;tim++){
        while(index<tp.size() && tp[index].arrivalTime<=tim){
            localq.push_back({processes[index],index});
            index++;
        }

        if(localq.size()==0){
            time.push_back(-1) ;
            continue ;
        }
        if(process_completed)sort_brustTime(localq.begin() , localq.end()) ;
        process_completed= false ;
        tp[localq.front().second].remainingTime-- ;
        time.push_back(tp[localq.front().second].processID) ;

        if(tp[localq.front().second].remainingTime==0){
            tp[localq.front().second].turnaroundTime = tim-tp[localq.front().second].arrivalTime ;
            tp[localq.front().second].waitingTime=tp[localq.front().second].turnaroundTime-tp[localq.front().second].burstTime ;
            localq.erase(localq.begin()) ;
            process_completed=true ;
        }
    }

    print_trace(time,processes,"output/_output_SJFNP.txt") ;
    
}
void SJFP(vector<Process> & processes,int time_quantum){
    int total_time =0 ;
    for(auto &it:processes)total_time=max(it.burstTime+it.arrivalTime,total_time+it.burstTime) ;

    auto & tp =processes ;
    sort_arrivalTime(processes.begin(),processes.end()) ;

    vector<int> time ; // time[0] = it will give the name of process which start run at 0sec

    int index =0 ;

    vector<pair<Process,int>> localq ;

    for(int tim=0 ; tim<total_time ;tim++){
        while(index<tp.size() && tp[index].arrivalTime<=tim){
            localq.push_back({processes[index],index});
            index++;
        }

        if(localq.size()==0){
            time.push_back(-1) ;
            continue ;
        }
        if(localq.front().first.remainingTime%time_quantum== localq.front().first.burstTime%time_quantum ){
            sort_remainingTime(localq.begin() , localq.end()) ;
        }
        
        tp[localq.front().second].remainingTime-- ;localq.front().first.remainingTime-- ;
        time.push_back(tp[localq.front().second].processID) ;

        if(tp[localq.front().second].remainingTime==0){
            tp[localq.front().second].turnaroundTime = tim-tp[localq.front().second].arrivalTime ;
            tp[localq.front().second].waitingTime=tp[localq.front().second].turnaroundTime-tp[localq.front().second].burstTime ;
            localq.erase(localq.begin()) ;
        
        }
    }

    print_trace(time,processes,"output/_output_SJFP.txt") ;
    
}
void Priority_scheduling_np(vector<Process> & processes){
    int total_time =0 ;
    for(auto &it:processes)total_time=max(it.burstTime+it.arrivalTime,total_time+it.burstTime) ;

    auto & tp =processes ;
    sort_arrivalTime(processes.begin(),processes.end()) ;

    vector<int> time ; // time[0] = it will give the name of process which start run at 0sec

    int index =0 ;

    vector<pair<Process,int>> localq ;
    bool process_completed = true ;
    for(int tim=0 ; tim<total_time ;tim++){
        while(index<tp.size() && tp[index].arrivalTime<=tim){
            localq.push_back({processes[index],index});
            index++;
        }

        if(localq.size()==0){
            time.push_back(-1) ;
            continue ;
        }
        if(process_completed)sort_priority(localq.begin() , localq.end()) ;
        process_completed= false ;
        tp[localq.front().second].remainingTime-- ;
        time.push_back(tp[localq.front().second].processID) ;

        if(tp[localq.front().second].remainingTime==0){
            tp[localq.front().second].turnaroundTime = tim-tp[localq.front().second].arrivalTime ;
            tp[localq.front().second].waitingTime=tp[localq.front().second].turnaroundTime-tp[localq.front().second].burstTime ;
            localq.erase(localq.begin()) ;
            process_completed=true ;
        }
    }

    print_trace(time,processes,"output/_output_PSNP.txt") ;
    
}
void Priority_scheduling_p(vector<Process> & processes,int time_quantum){
    int total_time =0 ;
    for(auto &it:processes)total_time=max(it.burstTime+it.arrivalTime,total_time+it.burstTime) ;

    auto & tp =processes ;
    sort_arrivalTime(processes.begin(),processes.end()) ;

    vector<int> time ; // time[0] = it will give the name of process which start run at 0sec

    int index =0 ;

    vector<pair<Process,int>> localq ;

    for(int tim=0 ; tim<total_time ;tim++){
        while(index<tp.size() && tp[index].arrivalTime<=tim){
            localq.push_back({processes[index],index});
            index++;
        }

        if(localq.size()==0){
            time.push_back(-1) ;
            continue ;
        }

        if(localq.front().first.remainingTime%time_quantum== localq.front().first.burstTime%time_quantum ){
            sort_priority(localq.begin() , localq.end()) ;
        }
        
        tp[localq.front().second].remainingTime-- ;localq.front().first.remainingTime-- ;
        time.push_back(tp[localq.front().second].processID) ;

        if(tp[localq.front().second].remainingTime==0){
            tp[localq.front().second].turnaroundTime = tim-tp[localq.front().second].arrivalTime ;
            tp[localq.front().second].waitingTime=tp[localq.front().second].turnaroundTime-tp[localq.front().second].burstTime ;
            localq.erase(localq.begin()) ;
            
        }
    }

    print_trace(time,processes,"output/_output_PSP.txt") ;
    
}
void RR(vector<Process> & processes,int time_quantum){
    int total_time =0 ;
    for(auto &it:processes)total_time=max(it.burstTime+it.arrivalTime,total_time+it.burstTime) ;

    auto & tp =processes ;
    sort_arrivalTime(processes.begin(),processes.end()) ;

    vector<int> time ; // time[0] = it will give the name of process which start run at 0sec

    int index =0 ;

    vector<pair<Process,int>> localq ;

    for(int tim =0 ; tim<total_time ; tim++){
        while(index<tp.size() && tp[index].arrivalTime<=tim){
            localq.push_back({processes[index],index});
            index++;
        }

        if(localq.size()==0){
            time.push_back(-1) ;
            continue ;
        }

        if(localq.front().first.remainingTime%time_quantum== localq.front().first.burstTime%time_quantum && localq.front().first.remainingTime !=localq.front().first.burstTime){
            localq.front().first.burstTime=localq.front().first.remainingTime  ;
            localq.push_back(localq.front()) ;
            localq.erase(localq.begin()) ;
        }
        // for(auto & v:localq)cout<<v.first.processID<<" ";cout<<endl ;

        tp[localq.front().second].remainingTime-- ;localq.front().first.remainingTime-- ;
        time.push_back(tp[localq.front().second].processID) ;


        if(tp[localq.front().second].remainingTime==0){
            tp[localq.front().second].turnaroundTime = tim-tp[localq.front().second].arrivalTime ;
            tp[localq.front().second].waitingTime=tp[localq.front().second].turnaroundTime-tp[localq.front().second].burstTime ;
            localq.erase(localq.begin()) ;
        }
        
    }
    print_trace(time,processes,"output/_output_RR.txt") ;
}
void MLQ(ProcessQueue &queue,int time_quantum){
    // I have 3 queue 
    // I will use priority scheduling for the system process 
    // round robin for the interactive process
    // FCFS for the background
    auto & tp = queue.processes ;
    auto & sys_arr = queue.system_Processes , inter_arr = queue.interactive_Processes , back_arr = queue.background_Processes ;
    int total_process = tp.size() ;
    
    vector<pair<Process,int>> sys_queue , inter_queue , back_queue ; 

    sort_arrivalTime(sys_arr.begin() , sys_arr.end()) ;
    sort_arrivalTime(inter_arr.begin() , inter_arr.end()) ;
    sort_arrivalTime(back_arr.begin() , back_arr.end()) ;


    vector<int> time_line ;
    int time =0 ;
    int sys_index =0 , inter_index =0 , back_index= 0;
    bool exe_inter = false , exe_back= false ,exe_sys =false;
    while(total_process!=0){// on every iteration I have to increase the time
        // cout<<time<<" "<<total_process<<" "<<sys_queue.size()<<" "<<inter_queue.size()<<" "<<back_queue.size()<<" "<<endl;
        while(sys_index<sys_arr.size() && sys_arr[sys_index].arrivalTime<=time) sys_queue.push_back({sys_arr[sys_index],sys_index}) ,sys_index++ ;
        while(inter_index<inter_arr.size() && inter_arr[inter_index].arrivalTime<=time) inter_queue.push_back({inter_arr[inter_index],inter_index}) ,inter_index++ ;
        while(back_index<back_arr.size() && back_arr[back_index].arrivalTime<=time) back_queue.push_back({back_arr[back_index],back_index}) ,back_index++ ;
        time++ ;
        start :;
        if(!exe_back && !exe_inter && !exe_sys){
            exe_sys = (sys_queue.size()!=0) ;
            // cout<<exe_sys<<endl;
            if(!exe_sys){
                exe_inter = (inter_queue.size()!=0) ;
                // cout<<exe_inter<<endl;
                if(!exe_inter){
                    exe_back = (back_queue.size()!=0) ;
                    // cout<<exe_back<<endl;
                }
            }
        }
        
        if(exe_sys && sys_queue.size()!=0){

            if(sys_queue.front().first.remainingTime%time_quantum==sys_queue.front().first.burstTime%time_quantum ){
                sort_priority(sys_queue.begin() ,sys_queue.end()) ;
            }

            sys_arr[sys_queue.front().second].remainingTime--; sys_queue.front().first.remainingTime-- ;
            time_line.push_back(sys_queue.front().first.processID) ;

            if(sys_arr[sys_queue.front().second].remainingTime==0){
                sys_arr[sys_queue.front().second].turnaroundTime=time - sys_arr[sys_queue.front().second].arrivalTime ;
                sys_arr[sys_queue.front().second].waitingTime = sys_arr[sys_queue.front().second].turnaroundTime-sys_arr[sys_queue.front().second].burstTime ;
                sys_queue.erase(sys_queue.begin()) ;
                total_process-- ;
                exe_sys=false ;
            }
        }
        else if(exe_inter && inter_queue.size()!=0){

            if(inter_queue.front().first.remainingTime%time_quantum==inter_queue.front().first.burstTime%time_quantum){
                if(inter_queue.front().first.remainingTime !=inter_queue.front().first.burstTime){
                    inter_queue.front().first.burstTime=inter_queue.front().first.remainingTime  ;
                    inter_queue.push_back(inter_queue.front()) ;
                    inter_queue.erase(inter_queue.begin()) ;
                    exe_inter = false ;
                    goto start ;
                }
            }

            inter_arr[inter_queue.front().second].remainingTime--; inter_queue.front().first.remainingTime-- ;
            time_line.push_back(inter_queue.front().first.processID) ;

            if(inter_arr[inter_queue.front().second].remainingTime==0){
                inter_arr[inter_queue.front().second].turnaroundTime=time - inter_arr[inter_queue.front().second].arrivalTime ;
                inter_arr[inter_queue.front().second].waitingTime = inter_arr[inter_queue.front().second].turnaroundTime-inter_arr[inter_queue.front().second].burstTime ;
                inter_queue.erase(inter_queue.begin()) ;
                exe_inter = false ;
                total_process-- ;
            }
        }
        else if(exe_back && back_queue.size()!=0){
            back_arr[back_queue.front().second].remainingTime--; back_queue.front().first.remainingTime-- ;
            time_line.push_back(back_queue.front().first.processID) ;

            if(back_arr[back_queue.front().second].remainingTime==0){
                back_arr[back_queue.front().second].turnaroundTime=time - back_arr[back_queue.front().second].arrivalTime ;
                back_arr[back_queue.front().second].waitingTime = back_arr[back_queue.front().second].turnaroundTime-back_arr[back_queue.front().second].burstTime ;
                back_queue.erase(back_queue.begin()) ;
                exe_back = false ;
                total_process-- ;
            }
        }
        else {
            time_line.push_back(-1) ;
        }
        
        // if(time>30)break ;
    }
    // for(auto v: time_line)cout<<v<<" ";cout<<endl ;
    for(auto & v: sys_arr){
        for(int e=0 ;e<tp.size() ;e++){
            if(tp[e].processID==v.processID){tp[e].turnaroundTime = v.turnaroundTime , tp[e].waitingTime= v.waitingTime ;break ;}
        }
    }
    for(auto & v: inter_arr){
        for(int e=0 ;e<tp.size() ;e++){
            if(tp[e].processID==v.processID){tp[e].turnaroundTime = v.turnaroundTime , tp[e].waitingTime= v.waitingTime ;break ;}
        }
    }
    for(auto & v: back_arr){
        for(int e=0 ;e<tp.size() ;e++){
            if(tp[e].processID==v.processID){tp[e].turnaroundTime = v.turnaroundTime , tp[e].waitingTime= v.waitingTime ;break ;}
        }
    }
    print_trace(time_line,queue.processes,"output/_output_MLQ.txt") ;
} 
void MLFQ(ProcessQueue &queue,int time_quantum,int time_limit){
    // I have 3 queue 
    // I will use priority scheduling for the system process 
    // round robin for the interactive process
    // FCFS for the background
    auto & tp = queue.processes ;
    auto & sys_arr = queue.system_Processes , inter_arr = queue.interactive_Processes , back_arr = queue.background_Processes ;
    int total_process = tp.size() ;
    
    vector<pair<Process,int>> sys_queue , inter_queue , back_queue ; 

    sort_arrivalTime(sys_arr.begin() , sys_arr.end()) ;
    sort_arrivalTime(inter_arr.begin() , inter_arr.end()) ;
    sort_arrivalTime(back_arr.begin() , back_arr.end()) ;


    vector<int> time_line ;
    int time =0 ;
    int sys_index =0 , inter_index =0 , back_index= 0;
    bool exe_inter = false , exe_back= false ,exe_sys =false;
    while(total_process!=0){// on every iteration I have to increase the time
        while(sys_index<sys_arr.size() && sys_arr[sys_index].arrivalTime<=time) sys_queue.push_back({sys_arr[sys_index],sys_index}) ,sys_index++ ;
        while(inter_index<inter_arr.size() && inter_arr[inter_index].arrivalTime<=time) inter_queue.push_back({inter_arr[inter_index],inter_index}) ,inter_index++ ;
        while(back_index<back_arr.size() && back_arr[back_index].arrivalTime<=time) back_queue.push_back({back_arr[back_index],back_index}) ,back_index++ ;
        time++ ;
        start :;
        if(!exe_back && !exe_inter && !exe_sys){
            exe_sys = (sys_queue.size()!=0) ;
            if(!exe_sys){
                exe_inter = (inter_queue.size()!=0) ;
                if(!exe_inter){
                    exe_back = (back_queue.size()!=0) ;
                }
            }
        }
        // cout<<total_process<<" ";
        
        if(exe_sys && sys_queue.size()!=0){

            if(sys_queue.front().first.remainingTime%time_quantum==sys_queue.front().first.burstTime%time_quantum ){
                ///////////
                // check if the current system processes run more then the time_limit
                if(sys_queue.front().first.burstTime-sys_queue.front().first.remainingTime>time_limit){
                    inter_queue.push_back(sys_queue.front()) ;
                    sys_queue.erase(sys_queue.begin()) ;
                    time-- ;
                    exe_sys=false ;
                    goto start ;
                }
                
                // //////////
                sort_priority(sys_queue.begin() ,sys_queue.end()) ;

            }

            sys_queue.front().first.remainingTime-- ;
            time_line.push_back(sys_queue.front().first.processID) ;

            if(sys_queue.front().first.remainingTime==0){
                sys_queue.front().first.turnaroundTime=time - sys_queue.front().first.arrivalTime ;
                sys_queue.front().first.waitingTime = sys_queue.front().first.turnaroundTime-sys_queue.front().first.burstTime ;
                sys_queue.erase(sys_queue.begin()) ;
                total_process-- ;
                exe_sys=false ;
            }
        }
        else if(exe_inter && inter_queue.size()!=0){

            if(inter_queue.front().first.remainingTime%time_quantum==inter_queue.front().first.burstTime%time_quantum){
                if(inter_queue.front().first.remainingTime !=inter_queue.front().first.burstTime){
                    inter_queue.front().first.burstTime=inter_queue.front().first.remainingTime  ;
                    inter_queue.push_back(inter_queue.front()) ;
                    inter_queue.erase(inter_queue.begin()) ;
                    exe_inter = false ;
                    goto start ;
                }
            }

            inter_queue.front().first.remainingTime-- ;
            time_line.push_back(inter_queue.front().first.processID) ;

            if(inter_queue.front().first.remainingTime==0){
                inter_queue.front().first.turnaroundTime=time - inter_queue.front().first.arrivalTime ;
                inter_queue.front().first.waitingTime = inter_queue.front().first.turnaroundTime-inter_queue.front().first.burstTime ;
                inter_queue.erase(inter_queue.begin()) ;
                exe_inter = false ;
                total_process-- ;
            }
        }
        else if(exe_back && back_queue.size()!=0){
            back_queue.front().first.remainingTime-- ;
            time_line.push_back(back_queue.front().first.processID) ;

            if(back_queue.front().first.remainingTime==0){
                back_queue.front().first.turnaroundTime=time - back_queue.front().first.arrivalTime ;
                back_queue.front().first.waitingTime = back_queue.front().first.turnaroundTime-back_queue.front().first.burstTime ;
                back_queue.erase(back_queue.begin()) ;
                // check if the process waits for more then the time limit 
                ///////////////
                if(back_queue.size()!=0){
                    for(int e= 0;e<back_queue.size() ; e++){
                        if(time - back_queue[e].first.arrivalTime>time_limit){
                            inter_queue.push_back(back_queue[e]) ;
                            back_queue.erase(back_queue.begin() +e) ;
                            e-- ;
                        }
                    }
                }

                ////////////////////
                exe_back = false ;
                total_process-- ;
            }
        }
        else {
            time_line.push_back(-1) ;
        }
        
    }


    for(int e= time_line.size()-1 ; e>=0 ;e--){
        for(auto &v: tp){
            if(v.processID==time_line[e] && v.turnaroundTime==0){
                v.turnaroundTime = e+1-v.arrivalTime ;
                v.waitingTime = v.turnaroundTime-v.burstTime ;
            }
        }
    }
    print_trace(time_line,queue.processes,"output/_output_MLFQ.txt") ;
} 