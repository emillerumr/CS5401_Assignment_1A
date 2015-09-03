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



void assign_variables(vector<vector<int> > clauses, 
										vector<bool> variable_assignments)
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
	print_boolean_clauses(boolean_clauses);
	cout<<"Fitness: "<<fitness<<endl;
}

int main()
{
	// ifstream fin;
	// string configuration_filename = "default.cfg";
	// fin.open(configuration_filename.c_str());
	// if(!fin.good())
	// {
	// 	bool valid_file = false;
	// 	cout<<"No default.cfg file! "
	// 		<<"Please enter the name of the desired configuration file: " <<endl;
	// 	while(!valid_file)
	// 	{
	// 		cin>>configuration_filename;
	// 		fin.open(configuration_filename.c_str());
	// 		if(fin.good())
	// 		{
	// 			valid_file = true;
	// 		}
	// 		else
	// 		{
	// 			cout<<"Error! Enter a valid file name:" <<endl;
	// 		}
	// 	}
	// }	

	// string cnf_filename;
	// fin>>cnf_filename;

	// string rand_parameter;
	// fin>>rand_parameter;
	// if(rand_parameter == "random")
	// {
	// 	srand(time(0));
	// }
	// else
	// {
	// 	srand(strtol(rand_parameter.c_str(),NULL,10));
	// }

	// long evaluations;
	// fin>>evaluations;

	// string log_filename;
	// fin>>log_filename;

	// string solution_filename;
	// fin>>solution_filename;
	string cnf_filename;
	string rand_parameter; 
	long evaluations;
	long runs;
	string log_filename;
	string solution_filename;

	getConfigurationVariables(cnf_filename,rand_parameter,evaluations,runs,log_filename,solution_filename);
	ifstream cnf_stream;
	cnf_stream.open(cnf_filename.c_str());

	char start_character;
	string comments;
	string entry;
	string cnf_filler;
	bool in_comments = true;

	cnf_stream>>start_character;
	while(start_character == 'c')
	{
		getline(cnf_stream,entry);
		comments = comments + entry;
		cnf_stream>>start_character;
	}
	cnf_stream>>cnf_filler;

	long num_variables;
	long num_clauses;
	cnf_stream>>num_variables;
	cnf_stream>>num_clauses;

	string end_line;
	long current_var;
	vector< vector<int> > clauses(num_clauses);

	cnf_stream>>current_var;
	for(int k = 0; k < num_clauses; k++)
	{
		while(current_var != 0)
		{
			clauses[k].push_back(current_var);
			cnf_stream>>current_var;
		}
		cnf_stream>>current_var;		
	}
	print_cnf_clauses(clauses);

	vector< bool > variable_assignments(num_variables + 1);
	for(int k = 1; k <= num_variables; k++)
	{
		variable_assignments[k] = rand() % 2;
	}

	print_variable_assignments(variable_assignments);

	assign_variables(clauses, variable_assignments);
	return 0;
}