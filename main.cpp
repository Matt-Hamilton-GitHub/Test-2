#include <array>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const string filename = "votes.txt";
const int maxCandidates = 8;
struct Candidate
{
    string name = "";
    size_t votes = 0;
    double percent = 0.0;
};


int main()
{
    ifstream inps(filename);
    assert(inps);
    array<Candidate, maxCandidates> candidates;
    size_t nCandidates = 0;
    while (inps.good() && nCandidates < maxCandidates) //validate input
    {
        string name;
        inps >> name;//store each name
        size_t votes;
        inps >> votes;//store number of votes 
        candidates[nCandidates].name = name; ///pass names to the array at a specific index
        candidates[nCandidates].votes = votes;//pass number of votes to the array at a specific index (candidate)
        nCandidates++;
    }
    if (nCandidates > 0)
    {
        size_t namefieldwidth = 12;
        size_t maxvotes = 0;
        size_t maxidx = 0;
        size_t totalvotes = 0;
        for (size_t idx = 0; idx < nCandidates; idx++)
        {
            totalvotes += candidates[idx].votes;
            if (candidates[idx].votes > maxvotes)
            {
                maxvotes = candidates[idx].votes;
                maxidx = idx;
            }
        }
		
        size_t namefieldwith = 16;
        size_t votesfieldwidth = 16;
        size_t percentfieldwidth = 16;
		
        if (totalvotes > 0)
        {
            for (size_t idx = 0; idx < nCandidates; idx++)
                candidates[idx].percent = 100.0 * candidates[idx].votes / static_cast<double>(totalvotes);//set percentage for each candidate 
        }
		
		// -------------------- Check if there is more than one winner ----------------------|
		
		unsigned int max_votes = candidates[maxidx].votes; // stores the max number of votes received during elections
		vector <int> winners_index;//a vector that stores the index of every winner, whether there is only one or more than one winner.
		
		
		for(size_t idx{0}; idx < nCandidates; idx++){//loop through the entire struct 
			if(max_votes == candidates[idx].votes){// find other candidates who have the same amount of votes as the first winner
			  winners_index.push_back(idx); // store the index of a winner to the vector of winners
			  
			}
		}
		
		
		//-------------output the deta -------------|
	cout << "\t**************************************************************************\n";
        cout << fixed << setprecision(2);
        cout << left << setw(namefieldwith) << "Candidate" << ' ' << right << setw(votesfieldwidth) << "Votes Received" << ' ' << right << setw(percentfieldwidth) << setfill(' ') << "% of Total Votes " << endl << endl;
        for (size_t idx = 0; idx < nCandidates; ++idx)
            cout << left << setw(namefieldwith) << candidates[idx].name << ' ' << right << setw(votesfieldwidth) << candidates[idx].votes << ' ' << right << setw(percentfieldwidth) << setfill(' ') << candidates[idx].percent << endl;
        size_t totalvotesfieldwidth = namefieldwidth + votesfieldwidth + 1;
		cout << "---------------------------------------------------------------------------\n";
        cout << "Total:" << setw(totalvotesfieldwidth) <<  totalvotes  << endl << endl;
		 
		 //winners_index.size() basically represents the number of winners in this election
	
		 cout << "Number of winners: " << winners_index.size() << " " << endl;
		 cout << "--------------------\n";
      for(size_t idx{0}; idx < winners_index.size(); idx++){//loop through all the winners in this elections
		  cout << "The winner of the Election is " << candidates[winners_index[idx]].name << endl;
	  }
		cout << "\n\t********************The End of The Elections*********************\n";

    }
	
	
	system("pause");
    return 0;
}
