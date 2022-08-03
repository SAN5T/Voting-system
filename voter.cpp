#include<bits/stdc++.h>
#include<iostream>
#include<stdio.h>
#include<conio.h>
using namespace std;

string pass="mypass";

vector<string> voters_id={"192-35-450","192-35-451","192-35-452","192-35-453","192-35-454","192-35-455","192-35-456",
                            "192-35-457","192-35-458","192-35-459","192-35-460","192-35-461","192-35-462","192-35-463",
                            "192-35-464","192-35-465","192-35-466","192-35-467","192-35-468","192-35-469","192-35-470",
                            "192-35-471","192-35-472","192-35-473","192-35-474","192-35-475","192-35-476","192-35-477",
                            "192-35-478","192-35-479","192-35-480"};

unordered_set<string> all_cand_id;         //this contain all valid voter id
unordered_map<string,int> voter_knows;

int push_candidate(map<int,string> &cand, map<int,int> &cand_vote, int &t){

    cout<<"                                  #Online Voting System From Peak Performers#"<<endl;
    cout<<"                                   -----------------------------------------"<<endl<<endl<<endl;
    cout<<"                               :::::::::::::::::::Admin Panel::::::::::::::::::"<<endl<<endl;
    cout<<"  ####################################################################################################################"<<endl;
    cout<<"  Enter password for authentication :- ";
    string temp;
    cin>>temp;
    bool isSafe=false;
    if(temp==pass){
        isSafe=true;
    }
    int tr=2;

    //if give password is not correct give extra 2 times for correct it else do not allow to vote
    while(tr && !isSafe){
        cout<<"  You have only "<<tr<<" attempts left enter carefully :-";
        string temp1;
        cin>>temp1;
        if(temp1==pass){
            isSafe=true;
            break;
        }
        tr--;

    }
    t=isSafe;

    if(isSafe){
        cout<<"  Admin please enter number of candidates:- ";
        int num;
        cout<<"  ";
        cin>>num;
        cout<<endl;
        cout<<"  Please enter candidate's name"<<endl<<endl;
        int nu=1;
        while(num--){
            cout<<"  Candidate Name "<<nu<<" : ";

            nu++;
            cand_vote[cand.size()+1]=1;
            string name;
            cout<<"  ";
            cin>>name;
            cout<<endl;
            cand[cand.size()+1]=name;
        }
        cand_vote[cand.size()+1]=1;
        cand[cand.size()+1]="NOTA";
        cout<<"  ####################################################################################################################"<<endl;
    }
    else{
        return 0;
    }

}

void Print_participent(map<int,string> &cand){
    for(auto x: cand){
        cout<<"  "<<x.first<<" "<<x.second<<endl;
    }
}

void vote(map<int,int> &cand, unordered_set<string> &done_cand, map<int,string> &c){
    bool isSafe=true;
    if(isSafe){
        cout<<"  Enter your voter-id :- ";
        string voter_id_cand;
        cin>>voter_id_cand;
        bool isdoub=false;

        //if voter id is valid
        if(all_cand_id.find(voter_id_cand)!=all_cand_id.end()){


            //if voter coming second time
            if(done_cand.find(voter_id_cand)!=done_cand.end()){
                isdoub=true;
            }
        }
        else{
            //cout<<"give id is not valid please enter again"<<endl;
            bool istrue=false;
            while(!istrue){
                cout<<"  given ID is not valid please enter again :- ";
                cin>>voter_id_cand;
                cout<<endl;
                if(all_cand_id.find(voter_id_cand)!=all_cand_id.end()){
                    istrue=true;
                    break;
                }

            }
            if(done_cand.find(voter_id_cand)!=done_cand.end()){
                isdoub=true;
            }
        }

        //if voter not coming second time then only execute

        if(!isdoub){
            cout<<"  Choose Your Preferable Candidate"<<endl;
            Print_participent(c);                            //print all registered candidate
            cout<<"  Enter you number according to your preferable candidate :- ";
            int cnd;
            cin>>cnd;
            cout<<endl;
            while(cnd>cand.size()){
                cout<<"Invalid candidate try again"<<endl;
                cin>>cnd;
            }
            cand[cnd]++;
            done_cand.insert(voter_id_cand);
            voter_knows[voter_id_cand]=cnd;
        }
        else{
            cout<<"You already responded"<<endl;
        }
    }
}



int main(){
    int t=1;
    map<int,int> cand_vote;
    map<int,string> cand;

    for(int i=0;i<voters_id.size();i++){
        all_cand_id.insert(voters_id[i]);
    }

    unordered_set<string> vote_done_cand_id;
    push_candidate(cand,cand_vote,t);
    if(!t){
        system("cls");
        cout<<" Authentication error";
        getch();
    }
    if(cand.size()==2){
        system("cls");
        cout<<"                               :::::::::::::::::::Result Panel::::::::::::::::::"<<endl<<endl;
        cout<<cand[1]<<" wins"<<endl<<endl<<endl<<endl;
        getch();
    }
    if(cand.size()==1){
        system("cls");
        cout<<"   voting not possible"<<endl;
        return 0;
    }
    while(t){
        system("cls");
        cout<<"                                  #Online Voting System From Peak Performers#"<<endl;
        cout<<"                                   -----------------------------------------"<<endl<<endl<<endl;
        cout<<"                               :::::::::::::::::::Voting Panel::::::::::::::::::"<<endl<<endl;
        cout<<"  ####################################################################################################################"<<endl;


        vote(cand_vote,vote_done_cand_id,cand);
        int temp;
        cout<<"  If voting is done Admin press 0 or press 1"<<endl;
        cout<<"  ";
        cin>>temp;
        t=temp;
        if(t==0){
            cout<<"  To close voting enter password, to continue press 1:- ";
            string close_pass;
            cin>>close_pass;
            cout<<endl;
            if(close_pass=="1"){
                t=1;
            }
            else if(close_pass!=pass){
                t=1;
            }

        }

    }
    int win,Max_vote=INT_MIN;
    for(auto x: cand_vote){
        if(Max_vote<x.second && x.first!=cand_vote.size()){
            win=x.first;
            Max_vote=x.second;
        }
    }
    system("cls");
    cout<<"                               :::::::::::::::::::Result Panel::::::::::::::::::"<<endl<<endl;
    cout<<endl<<endl;
    cout<<"  Name"<<" :- "<<"     Number of votes"<<endl<<endl;
    for(auto x: cand_vote){
        int spacing=20;
        cout<<" "<<cand[x.first];
        spacing-=cand[x.first].length();
        while(spacing--){
            cout<<" ";
        }

        cout<<x.second-1<<endl<<endl;;
    }
    cout<<cand[win]<<" "<<"wins with"<<" "<<Max_vote-1<<" votes"<<endl<<endl<<endl;
    while(1){
        cout<<"  Enter voter-id for Know which candidate you choosen :- ";
        string vtr_id;
        cin>>vtr_id;
        if(all_cand_id.find(vtr_id)!=all_cand_id.end()){
            if(vote_done_cand_id.find(vtr_id)!=vote_done_cand_id.end()){
                cout<<"  "<<vtr_id<<"     "<<cand[voter_knows[vtr_id]]<<endl;
            }
            else{
                cout<<"  you have not voted"<<endl;
            }
        }
        else{
            cout<<"  Invalid voter-id"<<endl;
        }
        getch();

    }
}
