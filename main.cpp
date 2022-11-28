#include <iostream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>
#include <stack>
#include <climits>

using namespace std;

unsigned long Adjacency_matrix_TT[100][100];
double Adjacency_matrix_TL[100][100];
unsigned long current_TT[100][100];
double current_TL[100][100];


class place_vertex
{
public:
    unsigned long ID;
    string place_name;
    unsigned long PS;
    int state;
    place_vertex(unsigned long ID,string place_name,unsigned long PS);
};
place_vertex::place_vertex(unsigned long ID,string place_name,unsigned long PS)
{
    this->ID=ID;
    this->place_name=place_name;
    this->PS=PS;
    state=1;
}
vector<place_vertex> vertex;


unsigned long place_num;

unsigned long getMin_TIME(unsigned long time[] , bool visited[])
{
    unsigned long key = 0 ;
    unsigned long min_value = LLONG_MAX ;
    for(unsigned long i=0;i < place_num ; i++)
    {
        if(!visited[i] && time[i]<min_value)
        {
            min_value = time[i] ;
            key = i ;
            //cout << "min_value : " << min_value << " ";
            //cout << "key : " << key << endl;
        }
        
    }
    
    //cout << "min_value : " << min_value << " ";
    //cout << "key : " << key << endl;
    return key ;
}

void display(unsigned long time[] , unsigned long par[] , unsigned long end)
{
    stack<unsigned long> sorted;
    unsigned long temp = par[end];
    //cout << "here" << endl;
    while(temp!=-1)
    {
        sorted.push(temp);
        temp = par[temp] ;
    }
    do
    {
        cout << vertex[sorted.top()].place_name << " -> ";
        sorted.pop();
    }while(!sorted.empty());
    cout<< vertex[end].place_name << endl;
}


void dijkstra_time(unsigned long start ,unsigned long num, unsigned long end)
{
    for(int i=0;i<place_num;i++)
    {
        for(int j=0;j<place_num;j++)
        {
            current_TT[i][j]=Adjacency_matrix_TT[i][j];
        }
    }
    for(int k=0;k<place_num;k++)
    {
        if(vertex[k].state==2)
        {
            for(int i=0;i<place_num;i++)
            {
                current_TT[k][i]=LLONG_MAX;
                current_TT[i][k]=LLONG_MAX;
                if(i==k)
                {
                    current_TT[i][k]=0;
                }
            }
        }
    }
    /*for(int i=0;i<place_num;i++)
    {
        for(int j=0;j<place_num;j++)
        {
            cout << current_TT[i][j] << " ";
        }
        cout << endl;
    }*/
    unsigned long par[100];
    unsigned long time[100];
    unsigned long score[100];
    bool visited[100] ={0};
    fill(time,time+place_num,LLONG_MAX);
    //cout << "there" << endl;

    time[start]=0;
    par[start]=-1;
    score[start]=vertex[start].PS;
    //cout << score[start];
    
    for(int g=0;g<num-1;g++)
    {
        unsigned long k = getMin_TIME(time,visited);
        visited[k] = true;
        //cout <<"qoq" << score[k] << endl;
        //cout << "visited[1]" <<  visited[1];
        //cout << "visited[2]" <<  visited[2];
        for(int v=0;v<place_num;v++)
        {
            //cout << v;
            if(!visited[v] && (time[k]+current_TT[k][v])<time[v] && current_TT[k][v]!=LLONG_MAX)
            {
                //cout << v << endl;
                par[v] = k ;
                time[v] = time[k] + current_TT[k][v];
                score[v] = score[k] + vertex[v].PS;
                //cout << "dist[v] : " << dist[v] << endl;
                //cout << "score[v] : " << score[v] << endl;
            }
            else if(!visited[v] && (time[k]+current_TT[k][v])==time[v] && current_TT[k][v]!=LLONG_MAX)
            {
                //cout << "yes" << endl;
                //cout << v << endl;
                //cout << score[k] << endl;
                //cout << score[v] << endl;
                if(score[k]+vertex[v].PS>score[v])
                {
                    par[v] = k ;
                    time[v] = time[k] + current_TT[k][v];
                    score[v] = score[k] + vertex[v].PS;
                    //cout << v << endl;
                    //cout << "dist[v] : " << dist[v] << endl;
                    //cout << "score[v] : " << score[v] << endl;
                }
                else if(score[k]+vertex[v].PS==score[v])
                {
                    //cout << "inside" << endl;
                    unsigned long temp1 = v ;
                    unsigned long temp2 = k ;
                    stack<unsigned long> sorted1;
                    stack<unsigned long> sorted2;
                    //sorted1.push(end);
                    while(temp1!=-1)
                    {
                        sorted1.push(temp1);
                        temp1 = par[temp1];
                    }
                    while(temp2!=-1)
                    {
                        sorted2.push(temp2);
                        temp2 = par[temp2];
                    }
                    /*sorted1.pop();
                    sorted2.pop();
                    if(sorted1.top()>sorted2.top())
                    {
                        par[v] = k ;
                        dist[v] = dist[k] + current_TT[k][v];
                        score[v] = score[k] + vertex[v].PS;
                    }*/
                    do
                    {
                        sorted1.pop();
                        sorted2.pop();
                    }while(sorted1.top()==sorted2.top() && !sorted1.empty() && !sorted2.empty());
                    if(sorted1.top()>sorted2.top())
                    {
                        par[v] = k ;
                        time[v] = time[k] + current_TT[k][v];
                        score[v] = score[k] + vertex[v].PS;
                    }
                    //cout << sorted1.top();
                    //cout << sorted2.top();
                }
            }
        }
    }
    display(time,par,end);
}

unsigned long getMin_FLOW(double flow[] , bool visited[])
{
    unsigned long key = 0 ;
    double min_value = LLONG_MAX ;
    for(int i=0;i < place_num ; i++)
    {   
        if(!visited[i] && flow[i]<min_value)
        {
            min_value = flow[i] ;
            key = i ;
            //cout << "key : " << key;
        }
    }
    return key ;
}

void display(double flow[] , unsigned long par[] , unsigned long end)
{
    stack<unsigned long> sorted;
    unsigned long temp = par[end];
    //cout << "here" << endl;
    //cout << "____" << endl;
    //cout << temp << endl;
    while(temp!=-1)
    {
        sorted.push(temp);
        temp = par[temp];
        //cout << temp << endl;
    }
    //cout << ":::" << endl;
    do
    {
        //cout << sorted.top() << endl;
        cout << vertex[sorted.top()].place_name << " -> ";
        sorted.pop();
    }while(!sorted.empty());
    cout<< vertex[end].place_name << endl;
}

void dijkstra_flow(unsigned long start,unsigned long num,unsigned long end)
{
    for(int i=0;i<place_num;i++)
    {
        for(int j=0;j<place_num;j++)
        {
            current_TL[i][j]=Adjacency_matrix_TL[i][j];
        }
    }
    for(int k=0;k<place_num;k++)
    {
        if(vertex[k].state==2)
        {
            for(int i=0;i<place_num;i++)
            {
                current_TL[k][i]=LLONG_MAX;
                current_TL[i][k]=LLONG_MAX;
                if(i==k)
                {
                    current_TL[i][k]=0;
                }
            }
        }
    }
    /*for(int i=0;i<place_num;i++)
    {
        for(int j=0;j<place_num;j++)
        {
            cout << current_TL[i][j] << " ";
        }
        cout << endl;
    }*/
    unsigned long par[100];
    double flow[100];
    bool visited[100] ={0};
    fill(flow,flow+place_num,LLONG_MAX);

    flow[start]=0;
    par[start]=-1;
    
    for(int g=0;g<num-1;g++)
    {
        unsigned long k = getMin_FLOW(flow,visited);
        visited[k] = true;
        //cout << "visit : " << k << endl;
        for(int v=0;v<place_num;v++)
        {
            //cout << v;
            if(!visited[v] && (flow[k]+fabs(log2(current_TL[k][v]))) <  flow[v] && current_TL[k][v]!=LLONG_MAX)
            {
                //cout << v;
                par[v] = k;
                //cout << "par[" << v << "] : " << par[v] << endl;
                flow[v] = flow[k] + fabs(log2(current_TL[k][v]));
                //cout << "flow[" << v << "] : " << flow[v] << endl;
            }
        }
        //cout << "end" << endl;
    }
    display(flow,par,end);
}



int main ()
{
    cin >> place_num;
    
    unsigned long origin_index=-1;
    
    for (int i=0;i<place_num;i++)
    {
        unsigned long ID,PS;
        string place_name;
        cin >> ID >> place_name >> PS;
        vertex.insert(vertex.end(),place_vertex(ID, place_name, PS));
    }
    
    for(int i = 0 ;i < place_num ; i++)
    {
        for(int j = 0 ; j< place_num ; j++)
        {
            cin>>Adjacency_matrix_TT[i][j];
        }
    }
    
    for(int i = 0 ;i < place_num ; i++)
    {
        for(int j = 0 ; j< place_num ; j++)
        {
            cin>>Adjacency_matrix_TL[i][j];
        }
    }
    
    string command;
    cin >> command;
    do
    {
        if( command == "SET_ORIGIN" )
        {
            int set=1;
            string place;
            cin >> place;
            //SET_ORIGIN ( place );
            for (int i=0;i<place_num;i++)
            {
                if(vertex[i].place_name==place && vertex[i].state==1)
                {
                    origin_index=vertex[i].ID;
                    set=0;
                }
            }
            if (set==0)
            {
                cout << place << " is the new origin" << endl;
            }
            else if (set==1)
            {
                cout << "Fail to reset the origin" << endl;
            }
        }
    
        if( command == "MARK_STATE" )
        {
            string State;
            string place_list;
            cin >> State ;
            getline(cin,place_list);
            
            vector<string> arr;
            string token;
            int c=0;
            istringstream delim(place_list);
            while(getline(delim,token,' '))
            {
                arr.push_back(token);
                c++;
            }
            //cout << c;
            //cout << arr[0] << endl;
            //cout << arr[1] << endl;
            //cout << arr[2] << endl;
            for(int j=1;j<c;j++)
            {
                //cout << i << endl;
                for (int i=0;i<place_num;i++)
                {
                    //cout << j << endl;
                    if(vertex[i].place_name==arr[j] && vertex[i].state==1 && State=="CLOSE" && i!=origin_index)
                    {
                        vertex[i].state=2;
                        //cout << "yes" << endl;
                    }
                    else if(vertex[i].place_name==arr[j] && vertex[i].state==2 && State=="OPEN")
                    {
                        vertex[i].state=1;
                        //cout << "no" << endl;
                    }
                    else if(vertex[i].place_name==arr[j] && vertex[i].state==1 && State=="CLOSE" && i==origin_index)
                    {
                        cout << "Fail to close " << arr[j] << endl;
                    }
                    else if(vertex[i].place_name==arr[j] && vertex[i].state==2 && State=="CLOSE")
                    {
                        cout << "Fail to close " << arr[j] << endl;
                    }
                    else if(vertex[i].place_name==arr[j] && vertex[i].state==1 && State=="OPEN")
                    {
                        cout << "Fail to open " << arr[j] << endl;
                    }
                }
            }
                
        }
    
        if( command == "OPTIMAL_PATH" )
        {
            unsigned long destination_index;
            string place_name;
            string CONSIDERATION;
            cin >> place_name >> CONSIDERATION;
            
            //vector<pass_by> pass;
            
            for (int i=0;i<place_num;i++)
            {
                if(vertex[i].place_name==place_name)
                {
                    destination_index=vertex[i].ID;
                }
            }
            //cout << origin_index << endl;
            //cout << destination_index << endl;
            
            //OPTIMAL_PATH ( place_name , CONSIDERATION);
            if(vertex[destination_index].state==1)
            {
                cout << "Optimal " << CONSIDERATION << " : " ;
                if(CONSIDERATION=="TIME")
                {
                    if(origin_index!=destination_index)
                    {
                        dijkstra_time(origin_index,place_num,destination_index);
                    }
                    else
                    {
                        cout << vertex[origin_index].place_name << endl;
                    }
                }
                if(CONSIDERATION=="FLOW")
                {
                    if(origin_index!=destination_index)
                    {
                        dijkstra_flow(origin_index,place_num,destination_index);
                    }
                    else
                    {
                        cout << vertex[origin_index].place_name << endl;
                    }
                }
            }
            else
            {
                cout << "No such optimal path to " << vertex[destination_index].place_name << endl;

            }
        }
    
        if( command == "LIMITED_PATH" )
        {
            string place_name;
            string CONSIDERATION;
            unsigned long max;
            cin >> place_name >> CONSIDERATION >> max;
            //LIMITED_PATH ( place_name , CONSIDERATION , max);
            
            unsigned long destination_index;
            
            //vector<pass_by> pass;
            for (int i=0;i<place_num;i++)
            {
                if(vertex[i].place_name==place_name)
                {
                    destination_index=vertex[i].ID;
                }
            }
            //OPTIMAL_PATH ( place_name , CONSIDERATION);
            if(vertex[destination_index].state==1)
            {
                cout << "Limited " << CONSIDERATION << " : " ;
                if(CONSIDERATION=="TIME")
                {
                    if(origin_index!=destination_index)
                    {
                        dijkstra_time(origin_index,max,destination_index);
                    }
                    else
                    {
                        cout << vertex[origin_index].place_name << endl;
                    }

                }
                    
                if(CONSIDERATION=="FLOW")
                {
                    if(origin_index!=destination_index)
                    {
                        dijkstra_flow(origin_index,max,destination_index);
                    }
                    else
                    {
                        cout << vertex[origin_index].place_name << endl;
                    }
                }
            }
            else
            {
                cout << "No such limited path to " << vertex[destination_index].place_name << endl;

            }
        }
        
        cin >> command;
    }while(command != "END_OF_INSTRUCTION");
        
    if( command == "END_OF_INSTRUCTION" )
    {
        //END_OF_INSTRUCTION();
        cout << "Stop receiving instructions" << endl;
        return 0;
    }
}


