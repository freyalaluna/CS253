#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <locale>
using namespace std;

void censorString(string& input, string targetPhrase){
	
	//This is bad and you should feel bad
	locale loc;	
	string inputLower = input;
	string targetLower = targetPhrase;
	for(size_t i = 0; i < inputLower.size(); i++){
		inputLower[i] = tolower(inputLower[i], loc);
	}
	for(size_t i = 0; i < targetLower.size(); i++){
		targetLower[i] = tolower(targetLower[i], loc);
	}

	size_t runningIndex = 0;
        
	//Finds the nearest instance of the target phrase from the current running index. If that instance is 
	//followed or predicated by another letter, it is skipped over.
	//This replacement is done for both the input string, and the lowercase version of the string in order for the looping condition to properly iterate
	while(inputLower.find(targetLower, runningIndex) != string::npos){
		size_t wordIndex = inputLower.find(targetLower, runningIndex);
		auto previousChar = inputLower[wordIndex - 1];
		auto nextChar = inputLower[wordIndex+targetLower.length()];
		
		if(isalpha(previousChar) || isalpha(nextChar)){
			runningIndex = wordIndex + 1;
			continue;
        	}else{
			input.replace(wordIndex, targetPhrase.length(), "CENSORED");
			inputLower.replace(wordIndex, targetLower.length(), "CENSORED");
			runningIndex = wordIndex;
		}
		
	}
}

void readFromStandard(set<string> toCensor){
	string censoredOutput;
	string inputLine;
       	while(getline(cin, inputLine)){;
		censoredOutput = censoredOutput + inputLine + "\n";
	}
	for(string s : toCensor){
		censorString(censoredOutput, s);
	}

	cout << censoredOutput;
}

bool readFromFiles(set<string> toCensor, set<string> inputFiles){
	string censoredOutput;
	for(string f : inputFiles){
		ifstream inFile(f);
		if(inFile.good()){
			string inputLine;
			while(getline(inFile, inputLine)){
				censoredOutput = censoredOutput + inputLine + "\n";
			}
		} else {
			cerr << "File " << f << " could not be read from by "; //TODO: This is jank. Is there a more elegant way to produce this error?
			return false;
		}
	}
	for(string s : toCensor){
		censorString(censoredOutput, s);
	}
	cout << censoredOutput;
	return true;	
}

int main(int argc, char *argv[]){
	vector<string> allArgs(argv, argv+argc); //Copied argument list to vector of strings for ease of access later.

	//Error checking. Checks if there are too few arguments, and if the mandatory '-' argument isn't present.
	if(argc < 2){
		cerr << argv[0] << " requires additional arguments" << "\n";
		return 1;
	}
	bool isDash = false;
	int dashPosition = 0;
	for(int i = 1; i < argc; i++){ //Checks the argument list for the dash. If it's present, mark its position. Otherwise throw an error. 
		if(allArgs[i] == "-"){
			isDash = true;
			dashPosition = i;
		}
	}
	if(!isDash){
		cerr << "Mandatory dash delimiting censored words from input was not found in argument list for " << argv[0] << "\n";
		return 2;
	}

	//Populate lists of words to censor and files to read from
	set<string> toCensor;
	set<string> inputFiles;
	for(int i = 1; i < dashPosition; i++){ //TODO: Is there a way to slice this? 
		for(char c : allArgs[i]){
			if(!isalpha(c)){
				cerr << argv[i] << " contains nonalphabetical character, and cannot be censored by " << argv[0] << "\n";
				return 3;
			}
		}
		if(toCensor.count(allArgs[i])){
			cerr << argv[i] << " was supplied as an argument to be censored multiple times in " << argv[0] << "\n";
			return 4;
		}
		toCensor.insert(allArgs[i]);
	}
	for(int i = dashPosition+1; i < argc; i++){
		inputFiles.insert(allArgs[i]);
	}

	if(inputFiles.size() == 0){ //If no files were given, read from standard input
		readFromStandard(toCensor);
	}  else {
		if(!readFromFiles(toCensor, inputFiles)){
			cerr << argv[0] << "\n";
			return 5;
		}
	}
	
	return 0;
}
