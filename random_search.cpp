//Evan Miller
//CS 5401
//September 6 2015

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "util.h"

using namespace std;



void assign_variables(vector<vector<int> > clauses, vector<bool> variable_assignments)
{
	long fitness = 0;
	vector<vector<bool> > boolean_clauses(clauses.size());
	for(int k = 0; k < clauses.size(); k++)
	{
		for(int j = 0; j < clauses[k].size(); j++)
		{
			boolean_clauses[k].push_back(variable_assignments[abs(clauses[k][j])]);
			if(clauses[k][j] < 0)
			{
				boolean_clauses[k][j] = !boolean_clauses[k][j];
 			}
		}
		if (find(boolean_clauses[k].begin(), boolean_clauses[k].end(), true) != boolean_clauses[k].end())
		{
			fitness++;
		}
	}
	if(fitness == clauses.size())
	{
		cout<<"Fitness: "<<fitness<<endl;
	}
}

int main()
{
	string cnf_filename;
	string rand_parameter; 
	long evaluations;
	long runs;
	string log_filename;
	string solution_filename;

	getConfigurationVariables(cnf_filename,rand_parameter,evaluations,runs,log_filename,solution_filename);

	long num_variables;
	vector< vector<int> > clauses = GetCNFInfo(cnf_filename, num_variables);

	for(int i = 0; i < runs; i++)
	{
		for(long k = 0; k < evaluations; k++)
		{
			vector< bool > variable_assignments(num_variables + 1);
			for(int k = 1; k <= num_variables; k++)
			{
				variable_assignments[k] = rand() % 2;
			}
			assign_variables(clauses, variable_assignments);
		}
	}
	return 0;
}