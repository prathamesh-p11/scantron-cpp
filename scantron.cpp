#include<iostream>
#include<fstream>
#include<string>

using namespace std;


int calc_score(int ans_key[],int *stud_ans, int no_stud,  int no_q)
{
    int marks = 0;
    int total_score =0;
    marks = 100 / no_q;

    for(int i=0;i<no_q;i++)
    {
        if(ans_key[i] == stud_ans[i+1])
        {
            total_score = total_score + marks;
        }
    }

    return total_score;
}


void read_ans(string f_name, int no_q, int no_stud)
{
    int vals;
    int i;
    string line;
    int stud_ans[no_stud][no_q+1];
    ifstream fin;
    int marksheet[no_stud][2];  //stores student roll and total score for that student
    
    fin.open(f_name);


    //init stud_ans matrix and marskheet matrix
    for(int i=0;i<no_stud;i++)
    {
        for(int j=0;j<no_q+1;j++)
        {   
            marksheet[i][1] =0;
            marksheet[i][2] =0;
            stud_ans[i][j]=0;
        }
    }


    fin.seekg(0, ios::beg); //move file pointer to  beginning of file

    //skip first 2 lines
    fin>>vals;
    getline(fin,line);

    //Read answer keys
    i=0;
    int ans_key[no_q];
    do  
    {
        fin>>vals;
        ans_key[i] = vals;
        i++;

    } while (fin.peek()!='\n');

    cout<<"\n";
    for(int k=0;k<no_q;k++)
    {
        cout<<ans_key[k]<<"  ";
    }

    for(int i=0;i<no_stud;i++)
    {
        cout<<"\n";
        for(int j=0;j<no_q+1;j++)
        {
            fin>>vals;
            stud_ans[i][j] = vals;   
            cout<<stud_ans[i][j]<<"  ";
        }
    }

    for(int i=0;i<no_stud;i++)
    {
        marksheet[i][1] = stud_ans[i][0];
        marksheet[i][2] = calc_score(ans_key, &stud_ans[i][0], no_stud, no_q);
    }

    /*
    cout<<"\n\nMarksheet =>\n";
    for(int i=0;i<no_stud;i++)
    {
        cout<<marksheet[i][1]<<"  Scored :"<<marksheet[i][2]<<"\n";    
    }
    */


}

int main()
{
    //variables
    string f_name;
    ifstream fin;
    int vals;
    int no_stud,no_q;
    string line;
    int i;
    //init
    i=0;
    f_name=" ";
    vals =0;
    no_q=0;
    no_stud=0;
    line = " ";

    cout<<"Enter file name:";
    cin>>f_name;
    fin.open(f_name);

    if(!fin)
    {
        cout<<"........ Unable to open file! .......";
        exit(1);
    }
    fin>>no_q;
    cout<<"NO Q :"<<no_q;
    getline(fin,line);
    
   //count number of students
   cout<<"\n";
   while (getline(fin,line) && (!fin.eof()))
   {  
       no_stud++;
   }

    cout<<"\nNumber of students =>"<<no_stud;
   
    read_ans(f_name,no_q,no_stud);

    return 0;
}