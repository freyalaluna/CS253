#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <locale>
#include <unistd.h>
using namespace std;

void censorString(string& input, string targetPhrase, string replacement, bool caseIndependent){
	
    //This is bad and you should feel bad
    if(caseIndependent){
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
			input.replace(wordIndex, targetPhrase.length(), replacement);
			inputLower.replace(wordIndex, targetLower.length(), replacement);
			runningIndex = wordIndex;
		}
		
	}
    }else{
        size_t runningIndex = 0;

        //Finds the nearest instance of the target phrase from the current running index. If that instance is
        //followed or predicated by another letter, it is skipped over.
        while(input.find(targetPhrase, runningIndex) != string::npos){
                size_t wordIndex = input.find(targetPhrase, runningIndex);
                auto previousChar = input[wordIndex - 1];
                auto nextChar = input[wordIndex+targetPhrase.length()];

                if(isalpha(previousChar) || isalpha(nextChar)){
                        runningIndex = wordIndex + 1;
                        continue;
                }else{
                        input.replace(wordIndex, targetPhrase.length(), replacement);
                        runningIndex = wordIndex;
                }

        }
	
    }
}

void readFromStandard(set<string> toCensor, string replacement, bool caseIndependent){
	string censoredOutput;
	string inputLine;
       	while(getline(cin, inputLine)){;
		censoredOutput = censoredOutput + inputLine + "\n";
	}
	for(string s : toCensor){
		censorString(censoredOutput, s, replacement, caseIndependent);
	}

	cout << censoredOutput;
}

bool readFromFiles(set<string> toCensor, vector<string> inputFiles, string replacement, bool caseIndependent){
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
		censorString(censoredOutput, s, replacement, caseIndependent);
	}
	cout << censoredOutput;
	return true;	
}

int main(int argc, char *argv[]){
	const string validArgs = "rciv";
	string replacement = "CENSORED";
	set<string> wordsToCensor;
	vector<string> readFiles;
	bool caseIndependent = false;
	bool isVerbose = false;
	bool rGiven = false;
	int opt;
	

	while((opt = getopt(argc, argv, "r:c:iv")) != -1){
		switch(opt){
		    case('r'):
		    {
			if(!rGiven){
				rGiven = true;
				replacement = optarg;
				for(string c : wordsToCensor){
			    		if(c == replacement){
						cerr << "Word to censor, " << c << ", matches the replacement string, " << replacement << " in " << argv[0] << "\n";
						return 1;
			    		}
				}
			} else {
				cerr << "-r given more than once to program " << argv[0] << "\n";
				return 6;
			}
			break;
		    }
		    case('c'):
		    {
			char* p = &optarg[0];
			while(*p != '\0'){
				if(!isalpha(*p)){
					cerr << "Word to censor " << optarg << " is not purely alphabetical in program " << argv[0] << endl;
					return 7;
				}
				p++;
			}
			if(wordsToCensor.count(optarg)){
				cerr << "Word to censor " << optarg << " was listed multiple times as an argument for " << argv[0] << endl;
				return 8;
			}
			wordsToCensor.insert(optarg);
			break;
		    }
		    case('i'):
		    {
			caseIndependent = true;
			break;
		    }
		    case('v'):
		    {
			isVerbose = true;
			break;
		    }
		    default:
		    {
			cerr << "Invalid argument option " << optopt << " given to " << argv[0] << "\n";
			return 2;
		    }
		}
			
	}

	for(int i = optind; i < argc; i++){
		readFiles.push_back(argv[i]);
	}

	if(isVerbose){
		if(readFiles.size() > 0){
		    for(string s : readFiles){
			cout << "Reading " << s << "\n";
		    }
		} else {
		    cout << "Reading standard input\n";
		}
	}

	if(readFiles.size() == 0){ //If no files were given, read from standard input
                readFromStandard(wordsToCensor, replacement, caseIndependent);
        }else{
        	if(!readFromFiles(wordsToCensor, readFiles, replacement, caseIndependent)){
                        cerr << argv[0] << "\n";
                        return 5;
                }
        }

	return 0;
}
