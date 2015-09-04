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



long getFitnessValue(vector<vector<int> > clauses, vector<bool> variable_assignments)
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
		if (find(boolean_clauses[k].begin(), boolean_clauses[k].end(), 1) != boolean_clauses[k].end())
		{
			fitness++;
		}
	}

	return fitness;
}

int main(int argc, char* argv[])
{
	string cnf_filename;
	string rand_parameter; 
	long evaluations;
	long runs;
	string log_filename;
	string solution_filename;
	ofstream log_fout;
	ofstream solution_fout;

	ifstream fin;
	if(argc > 1)
	{
		fin.open(argv[1]);
	}
	else
	{
		fin.open("config/default.cfg");
	}
	getConfigurationVariables(fin,cnf_filename,rand_parameter,evaluations,runs,log_filename,solution_filename);

	string log_path = log_filename;
	
	log_fout.open(log_path.c_str());
	log_fout<<"CNF File: "<<cnf_filename<<endl;
	log_fout<<"Random number seed value: "<<rand_parameter<<endl;
	log_fout<<"Number of runs: "<<runs<<endl;
	log_fout<<"Number of fitness evaluations per run: "<<evaluations<<endl<<endl;
	log_fout<<"Result Log"<<endl<<endl;

	long num_variables;
	vector< vector<int> > clauses = GetCNFInfo(cnf_filename, num_variables);

	long overall_max_fitness = 0;
	vector<bool> overall_best_solution(num_variables + 1);
	for(int i = 0; i < runs; i++)
	{
		log_fout<<"Run "<<i+1<<endl;
		long max_fitness = 0;
		vector<bool> run_best_solution(num_variables + 1);
		for(long j = 0; j < evaluations; j++)
		{
			vector<bool> variable_assignments(num_variables + 1);
			for(int k = 1; k <= num_variables; k++)
			{
				variable_assignments[k] = rand() % 2;
			}
			long currnet_fitness = getFitnessValue(clauses, variable_assignments);
			if(currnet_fitness > max_fitness)
			{
				max_fitness = currnet_fitness;
				run_best_solution = variable_assignments;
				log_fout<<j+1<<"\t"<<max_fitness<<endl;
			}
		}
		if(max_fitness > overall_max_fitness)
		{
			overall_max_fitness = max_fitness;
			overall_best_solution = run_best_solution;
		}
		log_fout<<endl;
	}
	solution_fout.open(solution_filename.c_str());
	solution_fout<<"c Solution for: "<<cnf_filename<<endl;
	solution_fout<<"c MAXSAT fitness value: "<<overall_max_fitness<<endl;
	solution_fout<<"v";
	for(int k = 1; k <= num_variables; k++)
	{
		if(overall_best_solution[k] == 1)
		{
			solution_fout<<" "<<k;
		}
		else
		{
			solution_fout<<" "<<-k;
		}
	}
	return 0;
}