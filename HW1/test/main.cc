#include <iostream>
#include <string>
#include <vector>

using namespace std;

void censorString(string& input, string targetPhrase){
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
			input.replace(wordIndex, targetPhrase.length(), "CENSORED");
			runningIndex = wordIndex;
		}
		
	}
}


int main(int argc, char **){
	//Error handling - if the user attempts to use the command line to pass input instead of cin, throw an error
	if(argc > 1){
		cerr << "Do not pass a command line argument to this file.\n";
		return 1;
	}

	string censoredOutput = "";
	for(string line; getline(cin, line); ){
		censorString(line, "alpha");
		censorString(line, "beta");
		censorString(line, "delta");
		censorString(line, "gamma");
		censoredOutput = censoredOutput + line + "\n";
	}
	cout << censoredOutput;
	return 0;
}
