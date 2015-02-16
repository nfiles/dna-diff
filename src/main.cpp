#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::getline;
#include <fstream>
using std::ifstream;
using std::ofstream;
#include <conio.h>

#include "dna_diff.h"

int main (int argc, const char* args[]) {
	ifstream in;
	ofstream out;
	size_t pos;
	string input_file, output_file;
	switch (argc) {
	case 1:	//no command-line arguments
			//retrieve input file name
		//INPUT STREAM
		cout << "Input file: ";
		getline(cin, input_file);
		//remove " from beginning and end of string
		if(input_file[0] == '"')						input_file.erase(0,1);
		if(input_file[input_file.size() - 1] == '"')	input_file.erase(input_file.size()-1,1);
		//OUTPUT STREAM
		pos	= input_file.find(".txt");
		output_file	= input_file.substr(0, pos);
		output_file	+= "_diff.txt";
		
		break;
	case 2:	//one command-line argument
			//input_file is argument and output_file is argument + "_diff"
		//INPUT STREAM
		input_file = args[1];
		//OUTPUT STREAM
		pos			= input_file.find(".txt");
		output_file	= input_file.substr(0, pos);
		output_file	+= "_diff.txt";
		
		break;
	default://two or more command line arguments
			//first is input_file, second is output_file
		//INPUT STREAM
		input_file = args[1];
		//OUTPUT STREAM
		output_file	= args[2];
		
		break;
	}

	//copmute differences
	diff(output_file, input_file);

	//location of results file
	cout << "Results: " << output_file << endl;

	cout << "Press any key to continue . . .";
	_getch();

	//automatically opens results file
#ifdef AUTO_OPEN
	output_file.insert(0, "\"");
	output_file.append("\"");
	string open_output = "start explorer " + output_file + " &";
	system(open_output.c_str());
#endif //AUTO_OPEN

	return 0;
}
