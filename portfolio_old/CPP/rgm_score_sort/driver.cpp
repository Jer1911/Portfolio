/**********************************************************************
* Rog-o-matic Score Sorter                                            *
* version 1.0                                                         *
* date: 4/18/2017                                                     *
* author: Jeremy Ecker                                                *
* a program to sort scores output by rogomatic                        *
*                                                                     *
* Notes:                                                              *
* -To use this program, copy the rgmdelta file into this program's    *
*  directory, and rename it to 'rgmdelta_bk'.                         *
* -If a fatal error occured during a rogomatic game, a duplicate      *
*  line number may occur. If this happens, the program will not work  *
*  unless the offending line is removed from the data file.           *
**********************************************************************/

#include<iostream>
#include<string>
#include<fstream>

using namespace std;

// structure representing lines of data:
struct Entry
{
    string month, sep, player;
    string monster, monster2, monster3, exp;
    int day, year, score, level;
    int hp, strength, armor, game_num;
};

// print top ten entries:
void top_ten(Entry entry[], int nol)
{
    cout << "Top ten games:" << endl << endl;
    nol = nol-1;
    for(int k=0; k<10; k++)
    {
        char j=' ';
        cout << entry[nol-k].month << j << entry[nol-k].day 
             << entry[nol-k].sep << j << entry[nol-k].year << j 
             << entry[nol-k].player << j << entry[nol-k].score 
             << j << entry[nol-k].monster << j << entry[nol-k].level 
             << j << entry[nol-k].hp << j << entry[nol-k].strength << j 
             << entry[nol-k].armor << j << entry[nol-k].exp << j 
             << entry[nol-k].game_num << endl;
    }
    cout << endl;
}

// print all entries:
void printer(Entry entry[], int nol)
{
    for(int k=0; k<nol; k++)
    {
        char j=' ';
        cout << entry[k].month << j << entry[k].day << entry[k].sep
             << j << entry[k].year << j << entry[k].player << j 
             << entry[k].score << j << entry[k].monster << j << entry[k].level 
             << j << entry[k].hp << j << entry[k].strength << j 
             << entry[k].armor << j << entry[k].exp << j << entry[k].game_num 
             << endl;
    }
    cout << endl;
}

// ask user what they want to do:
void decider(Entry entry[], int nol)
{
    char choice;
    cout << "What would you like to do?" << endl;
    cout << "1 - Print all entries" << endl;
    cout << "2 - Print top ten entries" << endl;
    cin >> choice;
    cout << endl;
    if((choice == '1') || (choice == '2'))
    {
        if(choice == '1')
            printer(entry, nol);
        if(choice == '2')
            top_ten(entry, nol);
    }
    else
        cout << "You failed to enter a correct input." << endl << endl;
}

// bubble sort, ascending order:
void sorter(Entry entry[], int nol)
{
    bool sorted = false;
    int pass = 1;
    while(!sorted && (pass < nol))
    {
        sorted = true;
        for(int k=0; k<nol-pass; k++)
        {
            int next_index = k+1;
            if(entry[k].score > entry[next_index].score)
            {
                swap(entry[k], entry[next_index]);
                sorted = false;
            }
        }
        pass++;
    }
    decider(entry, nol);
}

// function read_file():
void read_file()
{
    // open file for reading:
    ifstream score_file;
    score_file.open("rgmdelta_bk");

    // check for file error:
    if(!score_file)
    {
        cout << "Error opening score file. " << endl;
        cout << " The score file must be named: 'rgmdelta_bk'" << endl;
    }

    // main program loop:
    else
    {
        // get number of lines in file:
        int nol = 0;
        string line;
        while (getline(score_file, line))
            nol++;
        cout << "Number of entries: " << nol << endl;

        // reset file read location back to beginning:
        score_file.clear();
        score_file.seekg(0, score_file.beg);

        // create and populate structures:
        Entry entry[nol];
        for(int k=0; k<nol; k++)
        {
            score_file >> entry[k].month >> entry[k].day >> entry[k].sep
                       >> entry[k].year >> entry[k].player >> entry[k].score
                       >> entry[k].monster;
            char ch = score_file.peek();
            if(ch == ' ')
            {
                score_file.ignore();
                ch = score_file.peek();
                if(ch > '9')
                {
                    score_file >> entry[k].monster2;
                    ch = score_file.peek();
                    if(ch == ' ')
                    {
                        score_file.ignore();
                        ch = score_file.peek();
                        if(ch > '9')
                            score_file >> entry[k].monster3;
                    }
                }
            }
            score_file >> entry[k].level >> entry[k].hp
                       >> entry[k].strength >> entry[k].armor >> entry[k].exp
                       >> entry[k].game_num;
        }

        // sort the structures by score:
        sorter(entry, nol);

    } // end else
    score_file.close();
} // end read_file()

// function main():
int main()
{
    cout << "Reading data file..." << endl;
    read_file();
    return 0;
}

