#include "dna-diff.h"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <fstream>
using std::ifstream;
using std::ofstream;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <iomanip>
using std::setw;
using std::left;
#include <conio.h>

//accept 'u' (uracil) as a base code
//#define ACCEPT_RNA

//use BLAST-style formatting for output_file
#define BLAST

//auto-open output_file
#define AUTO_OPEN

#ifdef ACCEPT_RNA
const enum BASECODE {A, T, U, C, G};
#else
const enum BASECODE {A, T, C, G};
#endif //ACCEPT_RNA

//definition of diff
void diff(string& output_file, string& input_file) {
	//open input_file as ifstream
	ifstream fin(input_file.c_str());
	if (fin.fail()) {	//check 'fin'
		cerr << "Failed to open " << input_file << " for input." << endl;
		cout << "Press any key to continue . . .";
		_getch();
		exit(1);
	}

	//open output_file as ofstream
	ofstream fout(output_file.c_str());
	if (fout.fail()) {	//check 'fout'
		cerr << "Failed to open " << output_file << " for output." << endl;
		cout << "Press any key to continue . . .";
		_getch();
		exit(1);
	}

	//write input_file to the top of output_file
	fout << "Input file: " << input_file << endl << endl;

	//READ STREAMS
	string in1, in2;
	//delimited by newline
	fin >> in1 >> in2;
	bool diff_length = false;
	if (in1.length() != in2.length() ) {
		diff_length = true;
	}

	//FIND DIFFERENCES
	string difference;
	bool invalid = false;
	vector<unsigned int> invalid1, invalid2;
	int diff_count = 0;
	//list nucleotides and their differences
	for (unsigned int i = 0; i < in1.length(); ++i) {
		//the characters to be compared
		BASECODE test1, test2;

		//examine base code in line 1
		switch (tolower(in1[i])) {
		case 'a':	test1 = A;	break;
#ifdef ACCEPT_RNA
		case 'u':	test1 = U;	break;
#endif //ACCEPT_RNA
		case 't':	test1 = T;	break;
		case 'c':	test1 = C;	break;
		case 'g':	test1 = G;	break;
		default:
			invalid1.push_back(i);
			invalid = true;
			break;
		}
		//examine base code in line 2
		switch (tolower(in2[i])) {
		case 'a':	test2 = A;	break;
#ifdef ACCEPT_RNA
		case 'u':	test2 = U;	break;
#endif //ACCEPT_RNA
		case 't':	test2 = T;	break;
		case 'c':	test2 = C;	break;
		case 'g':	test2 = G;	break;
		default:
			invalid2.push_back(i);
			invalid = true;
			break;
		}
		//are the base codes different?
		if (test1 != test2) {
			difference += 'X';
			diff_count++;
		}
		else difference += ' ';
	}

	//REPORT
	if (!invalid && !diff_length) { //no invalid base codes
		//my original formatting
#ifdef BLAST
		//formatting more like BLAST
		unsigned int len = difference.length();
		for (unsigned int r = 0, c; r*60 < len; ++r) {
			//print line 1
			fout << setw(9) << left << "Gen. 1"									//name line
				 << setw(6) << left << r*60 + 1;								//index of first nucleotide on line
			for (c = 0; c < 60 && (r*60 + c) < len; ++c) {
				fout << static_cast<char>(toupper(in1[r*60 + c]));				//nucleotide
			}
			fout << setw(60-c + 1) << " " << "  " << (r * 60) + c << endl;		//index of last nucleotide on line
			
			//print differences
			fout << setw(15) << " ";											//blank space
			for (c = 0; c < 60 && (r*60 + c) < len; ++c) {
				fout << ((difference[r*60 + c] == 'X') ? " " : "|");			//match identical nucleotides with |
			}
			fout << endl;
			
			//print line 2
			fout << setw(9) << left << "Gen. 2"									//name line
				 << setw(6) << left << r*60 + 1;								//index of first nucleotide on line
			for (c = 0; c < 60 && (r*60 + c) < len; ++c) {
				fout << static_cast<char>(toupper(in2[r*60 + c]));				//nucleotide
			}
			fout << setw(60-c + 1) << " " << "  " << (r * 60) + c << endl;		//index of last nucleotide on line
			
			fout << endl;														//extra line break between rows
		}
#else
		fout << "     -1-    -2-    Different?" << endl;
		for (unsigned int i = 0; i < in1.length(); ++i) {
			fout << setw(6) << left << i + 1
				 << setw(7) << left << static_cast<char>(toupper(in1[i]))
				 << setw(8) << left << static_cast<char>(toupper(in2[i]))
				 << static_cast<char>(difference[i]) << endl;
		}
		fout << endl;
#endif //BLAST

		fout << "Length of nitrogenous base sequence: " << in1.length() << endl
			 << "Number of Differences: " << diff_count << endl
			 << "Percent different: " << (double)diff_count/(double)in1.length() * 100 << "%" << endl;
	}
	else  if (diff_length) {	//different input line lengths
		fout << "The input lines are different lengths." << endl
			 << "Line 1: " << in1.length() << endl
			 << "Line 2: " << in2.length() << endl;
	}
	else {	//invalid base codes
#ifdef ACCEPT_RNA
		fout << "Valid base codes: A, T, C, G, U" << endl;
#else
		fout << "Valid base codes: A, T, C, G" << endl;
#endif //ACCEPT_RNA
		fout << "Invalid base codes were found" << endl;
		
		fout << endl
			 << "Sequence 1: " << invalid1.size() << " invalid codes" << endl
			 << "Index    Code" << endl;
		for (unsigned int i = 0; i < invalid1.size(); ++i)
			fout << " " << setw(9) << left << invalid1[i] << in1[invalid1[i]] << endl;
		fout << endl
			 << "Sequence 2: " << invalid2.size() << " invalid codes" << endl
			 << setw(9) << left << "Index" << "Code" << endl;
		for (unsigned int i = 0; i < invalid2.size(); ++i)
			fout << " " << setw(9) << left << invalid2[i] << in2[invalid2[i]] << endl;
		fout << endl;
	}
}
