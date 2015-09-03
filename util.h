#ifndef UTIL_H
#define UTIL_H

using namespace std;

void print_cnf_clauses(vector<vector<int> > clauses)
{
	for(int k = 0; k < clauses.size(); k++)
	{
		for(int j = 0; j < clauses[k].size(); j++)
		{
			cout<<clauses[k][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

void print_boolean_clauses(vector<vector<bool> > clauses)
{
	for(int k = 0; k < clauses.size(); k++)
	{
		for(int j = 0; j < clauses[k].size(); j++)
		{
			cout<<clauses[k][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

void print_variable_assignments(vector<bool> variable_assignments)
{
	for(int k = 1; k <= variable_assignments.size() - 1; k++)
	{
		cout<<variable_assignments[k]<<" ";
	}
	cout<<endl<<endl;
}

void getConfigurationVariables(string &cnf_filename, string &rand_parameter, long &evaluations,
								long &runs, string &log_filename, string &solution_filename)
{
	ifstream fin;
	string configuration_filename = "default.cfg";
	fin.open(configuration_filename.c_str());
	if(!fin.good())
	{
		bool valid_file = false;
		cout<<"No default.cfg file! "
			<<"Please enter the name of the desired configuration file: " <<endl;
		while(!valid_file)
		{
			cin>>configuration_filename;
			fin.open(configuration_filename.c_str());
			if(fin.good())
			{
				valid_file = true;
			}
			else
			{
				cout<<"Error! Enter a valid file name:" <<endl;
			}
		}
	}	

	fin>>cnf_filename;
	fin>>rand_parameter;
	if(rand_parameter == "random")
	{
		srand(time(0));
	}
	else
	{
		srand(strtol(rand_parameter.c_str(),NULL,10));
	}
	fin>>evaluations;
	fin>>runs;
	fin>>log_filename;
	fin>>solution_filename;
}

#endif