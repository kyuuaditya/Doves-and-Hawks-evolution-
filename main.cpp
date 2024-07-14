// improving upon the previous approach and defining global variables to keep things a lot simpler.
#include<bits/stdc++.h>
#include<stdio.h>
#include<fstream>
using namespace std;

// * hardcoded max creatures in the system.
int max_count=1000;
int creatures[1000][10]={0};
int temp[5]={0};
/*
what every place in creatures array denotes.
0: creature number;
1: creature nature;
2: creature generation;
3: creature survival;
4: creature reproduction;
5: creature food_number;
6: 
7:
8:
9:
*/

//death counter
int deaths=0;

//number of trees or lets say food available.
int trees_available=300;

//number of generations.
int generations=100;

//number of each type of creatures to start the program with.
int doves=300;
int hawks=150;
int smurfs=100;
int total_creatures=doves+hawks+smurfs;
int current_num=total_creatures;

//current iteration number to keep track of each generation simultaneously.
int itr=0; 

//displays stats of all alive creatures.
void display(int creatures[1000][10]){
    for(int i=0;i<max_count;i++){
        if(creatures[i][0]!=0){
            for(int j=0;j<10;j++){
                cout<<creatures[i][j]<<" ";
            }
            cout<<endl;
        }
    }
}

void display2(int creatures[1000][10]){
    for(int i=0;i<max_count;i++){
        for(int j=0;j<10;j++){
            cout<<creatures[i][j]<<" ";
        }
        cout<<endl;
    }
}

void stats(int creatures[1000][10]){
    int h=0;
    int d=0;
    int s=0;
    for(int i=0;i<max_count;i++){
        if(creatures[i][0]!=0){
            if(creatures[i][1]==0){
                d++;
            }
            if(creatures[i][1]==1){
                h++;
            }
            if(creatures[i][1]==2){
                s++;
            }
        }
    }
    cout<<"doves: "<<d<<" Hawks: "<<h<<" smurmfs: "<<s<<endl;
    // cout<<deaths<<endl;
}


void assign_tree(int creatures[1000][10]){
    int tree_checker[trees_available]={0};
    int creature_checker[max_count]={0};
    int runs;
    runs=total_creatures+1;
    
    int trees_assigned=0;
    //clear previous data
    for(int i=0;i<max_count;i++){
        creatures[i][5]=0;
    }
    //loop
    while(runs!=1){
        int random=rand()%max_count;
        if(creatures[random][0]!=0&&creature_checker[random]<1){
            int random2=rand()%trees_available;
            if(tree_checker[random2]<2){
                creatures[random][5]=random2;
                creature_checker[random]++;
                tree_checker[random2]++;
                runs--;
                trees_assigned++;
            }
        }
    }
    // cout<<"trees assigned: "<<trees_assigned<<endl;
}

//function to calculate foods
void calculate_food(int creatures[1000][10]){

    for(int i=0;i<max_count;i++){
        if(creatures[i][5]==0){
            creatures[i][0]=0;
            creatures[i][1]=0;
            creatures[i][2]=0;
            creatures[i][3]=0;
            creatures[i][4]=0;
        }
    }

    int i1=0,i2=0,i3=0,i4=0,i5=0,i6=0,i7=0,i8=0,i9=0;
    for(int i=0;i<max_count;i++){
        for(int j=0;j<max_count;j++){
            if(creatures[i][5]==creatures[j][5]&&i!=j&&creatures[i][0]!=0&&creatures[j][0]!=0){
                if(creatures[i][1]==0&&creatures[j][1]==0){
                    creatures[i][3]=1;
                    creatures[i][4]=0;
                    i1++;
                    break;
                }
                if(creatures[i][1]==0&&creatures[j][1]==1){
                    creatures[i][3]=(rand() % 100) / 50;
                    creatures[i][4]=0;
                    i2++;
                    break;
                }
                if(creatures[i][1]==0&&creatures[j][1]==2){
                    creatures[i][3]=(rand() % 100) / 50;
                    creatures[i][4]=0;
                    i3++;
                    break;
                }
                if(creatures[i][1]==1&&creatures[j][1]==0){
                    creatures[i][3]=1;
                    creatures[i][4]=(rand() % 100) / 50;
                    i4++;
                    break;
                }
                if(creatures[i][1]==1&&creatures[j][1]==1){
                    creatures[i][3]=0;
                    creatures[i][4]=0;
                    i5++;
                    break;
                }
                if(creatures[i][1]==1&&creatures[j][1]==2){
                    creatures[i][3]=1;
                    creatures[i][4]=(rand() % 100) / 50;
                    i6++;
                    break;
                }
                if(creatures[i][1]==2&&creatures[j][1]==0){
                    creatures[i][3]=1;
                    creatures[i][4]=(rand() % 100) / 50;
                    i7++;
                    break;
                }
                if(creatures[i][1]==2&&creatures[j][1]==1){
                    creatures[i][3]=(rand() % 100) / 50;
                    creatures[i][4]=0;
                    i8++;
                    break;
                }
                if(creatures[i][1]==2&&creatures[j][1]==2){
                    creatures[i][3]=(rand() % 100) / 50;
                    creatures[i][4]=0;
                    i9++;
                    break;
                }
            }else if(creatures[i][0]!=0){
                creatures[i][3]=1;
                creatures[i][4]=1;
            }
        }
    }
    // cout<<i1<<" "<<i2<<" "<<i3<<endl;
    // cout<<i4<<" "<<i5<<" "<<i6<<endl;
    // cout<<i7<<" "<<i8<<" "<<i9<<endl;
}


void reaper(int creatures[1000][10]){
    for (int i = 0; i < max_count; i++) {
        //death
        if (creatures[i][3] == 0) {
            if(creatures[i][0]!=0){
                deaths++;
            } 
            creatures[i][0] = 0;
            creatures[i][1] = 0;
            creatures[i][2] = 0;
            creatures[i][4] = 0;
            creatures[i][5] = 0;
        }
    }

    for(int i=0;i<max_count;i++){
        if(creatures[i][4]==1&&creatures[i][0]!=0){
            int find=0;
            int birth=1;
            while(birth){
                if(creatures[find][0]==0&&creatures[i][4]==1){
                    current_num++;
                    creatures[find][0]=current_num;
                    creatures[find][1]=creatures[i][1];
                    creatures[find][2]=creatures[i][2]+1;
                    creatures[find][3]=0;
                    creatures[find][4]=0;
                    creatures[find][5]=0;
                    birth--;
                }else{
                    find++;
                }
            }
        }
    }

    

    //reset all values
    for(int i=0;i<max_count;i++){
        if(creatures[i][3]==1){
            creatures[i][3]=0;
            creatures[i][4]=0;
            creatures[i][5]=0;
        }
    }
}

//update function.
void update(int creatures[1000][10]){
    hawks=0;
    doves=0;
    smurfs=0;
    for(int i=0;i<1000;i++){
        if(creatures[i][0]!=0&&creatures[i][1]==0){
            doves++;
        }
        if(creatures[i][0]!=0&&creatures[i][1]==1){
            hawks++;
        }
        if(creatures[i][0]!=0&&creatures[i][1]==2){
            smurfs++;
        }
    }

    total_creatures=hawks+smurfs+doves;
}

int main(){
    //resets all the random numbers each time the program is run.
    srand(time(0));

    ofstream myfile;
    myfile.open("file.txt");    

    //assigning doves,hawks and smurfs.
    for(int i=0;i<doves;i++){
        creatures[i][0]=i+1;
        creatures[i][1]=0;
        creatures[i][2]=1;
    }
    for(int i=doves;i<doves+hawks;i++){
        creatures[i][0]=i+1;
        creatures[i][1]=1;
        creatures[i][2]=1;
    }
    for(int i=doves+hawks;i<doves+hawks+smurfs;i++){
        creatures[i][0]=i+1;
        creatures[i][1]=2;
        creatures[i][2]=1;
    }

    //display(creatures);
    //cout<<"gap"<<endl;

    stats(creatures);
    myfile<<doves<<" "<<hawks<<" "<<smurfs<<endl;
    for(int i=0;i<generations;i++){
    //assigns tree numbers to  each creature.
    assign_tree(creatures);
    calculate_food(creatures);
    //display2(creatures);
    reaper(creatures);
    //stats(creatures);
    update(creatures);
    myfile<<doves<<" "<<hawks<<" "<<smurfs<<endl;
    }
    myfile.close();
}   