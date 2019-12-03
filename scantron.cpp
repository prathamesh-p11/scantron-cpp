#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class scantron
{
private:
    string f_name;  //File Name
    int no_q;   //Number of questions
    int no_stud;    //Number of students

public:
    scantron(); //constructor
    
    void read_ans(string, int, int);
    int calc_score(int a[], int *b, int, int);
    
    //getter setter functions
    void set_no_q(int);
    int get_no_q();
    
    void set_no_stud(int);
    int get_no_stud();

    void set_f_name(string);
    string get_f_name();
};

//init variables
scantron::scantron()
{
    f_name = "";
    no_q = 0;
    no_stud = 0;
}

//getter setter definitions
void scantron::set_f_name(string f_name)
{
    this->f_name = f_name;
}

string scantron::get_f_name()
{
    return this->f_name;
}


void scantron::set_no_q(int no_q)
{
    this->no_q = no_q;
}

int scantron::get_no_q()
{
    return this->no_q;
}


void scantron::set_no_stud(int no_stud)
{
    this->no_stud = no_stud;
}

int scantron::get_no_stud()
{
    return this->no_stud;
}


//calc score for individual student and returns total 
int scantron::calc_score(int *ans_key, int *stud_ans, int no_stud, int no_q)
{
    int marks = 0;
    int total_score =0;
    marks = 100 / no_q; //marks per Q

    //compare answers with keys and assign marks to correct answers
    for(int i=0;i<no_q;i++) 
    {
        if(ans_key[i] == *(stud_ans+i+1))
        {
            total_score = total_score + marks;
        }
    }
    return total_score;
}

//read answer keys(correct answers), student roll numbers and answers and calculate frequency
void scantron::read_ans(string f_name,int no_q,int no_stud)
{
 
    scantron sc;    //scantron object
    int vals;   //read stream
    int i;  //iterator
    string line;   
    int stud_ans[no_stud][no_q+1];  //student roll number and answers array
    ifstream fin;   //file stream to read
    int marksheet[no_stud][2];  //stores student roll and total score for that student   
    int s[no_stud]; //score array
    int v[no_stud]; //frequency array
    int temp,temp2; //temporary variables
    float average;  //average score
    int scores;         //temporary var to get individual stud score


    fin.open(f_name);   //open file
    //init stud_ans matrix and marskheet matrix
    for(int i=0;i<no_stud;i++)
    {
        for(int j=0;j<no_q+1;j++)
        {   
            marksheet[i][0] =0;
            marksheet[i][1] =0;
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

    //read student answers
    for(int i=0;i<no_stud;i++)
    {
        for(int j=0;j<no_q+1;j++)
        {
            fin>>vals;
            stud_ans[i][j] = vals;   
        }
    }
    
    //calculate score for individual stud ans store all in marsheet with roll numbers
    temp =0;
    for(int i=0;i<no_stud;i++)
    {
        marksheet[i][0] = stud_ans[i][0];
        scores = sc.calc_score(ans_key, stud_ans[i], no_stud, no_q);
        marksheet[i][1] = scores;
    }
    

    cout<<"Student ID   Score";
    cout<<"\n=================================\n";
    for(int i=0;i<no_stud;i++)
    {
        cout<<marksheet[i][0]<<"         "<<marksheet[i][1]<<"\n";    
    }
    cout<<"=================================\n";
    cout<<"Tests graded = "<<no_stud;
    cout<<"\n=================================";

    //init score array with score and omit rollnumbers
    for(int i=0;i<no_stud;i++)
    {
        s[i] = marksheet[i][1];
    }
    
    //inti frequency with 1s
    for(int i=0;i<no_stud;i++)
    {
        v[i] = 1;
    }

    //calc frequency
    for(int i=0;i<no_stud;i++)
    {
        for(int j=0;j<=i;j++)
        {
            if( (s[i]==s[j]) && i!=j)
            {
                v[i] = v[i] + 1;
                v[j] = 0;
            }
        }
    }


    //bubble sort frequency
    temp=0;
    temp2=0;
    
    for(int i=0;i<no_stud;i++)
    {
        for(int j=0;j<no_stud-i-1;j++)
        {
            if(s[j]<s[j+1])
            {
                temp = s[j];
                temp2 = v[j];
                
                s[j] = s[j+1];
                v[j] = v[j+1];
                
                s[j+1] = temp;
                v[j+1] = temp2;
            }
        }
    }
    
    

    //print v and s
    temp =0;
    cout<<"\nScore      Frequency";
    cout<<"\n=================================";
    for(int i=0;i<no_stud;i++)
    {
        if(v[i]!=0)
        {
            cout<<"\n"<<s[i]<<"         "<<v[i];
        }

        temp = temp + (s[i] * v[i]);
    }

    cout<<"\n=================================";
    average = temp / no_stud;
    cout<<"\nClass Average = "<<average;

}

int main()
{
    //scantron object to access class functions
    scantron s;

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
    s.set_f_name(f_name);
    fin.open(s.get_f_name());

    if(!fin)
    {
        cout<<"........ Unable to open file! .......";
        exit(1);
    }
    fin>>no_q;
   s.set_no_q(no_q);

    getline(fin,line);
    
   //count number of students
   while (getline(fin,line) && (!fin.eof()))
   {  
       no_stud++;
   }

   s.set_no_stud(no_stud);
   
   s.read_ans(s.get_f_name(),s.get_no_q(),s.get_no_stud());

    return 0;
}