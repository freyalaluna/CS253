#include "Schedule.h"
#include <string>
#include <iostream>
#include <vector>

Schedule::Schedule(){
    currID = 0;
}

Schedule::Schedule(std::string name, std::string channel, int start, int length, bool adult){
    currID = 1;

    Program initProgram;
    initProgram.name = name;
    initProgram.channel = channel;
    initProgram.start = start;
    initProgram.length = length;
    initProgram.adult = adult;
    initProgram.id = currID;
    programPlan.push_back(initProgram);
}


void Schedule::print(std::ostream &os) const {
    size_t largestChannel = 0;
    
    //Find the size of the program with the longest name
    for(Program p : programPlan){
        if(p.channel.size() > largestChannel){
            largestChannel = p.channel.size();
        }
    }

    //Print out each line, with spaces matched according to program name
    for(Program p : programPlan){
        int startHour = p.start/4;
        int startMin = (p.start%4) * 15;
        int endHour = (p.start+p.length)/4;
        int endMin = ((p.start+p.length)%4) * 15;
        
        //Prints the time block for the program, prepending zeroes where necessary
        if (startHour < 10){ os << "0"; }
        os << startHour << ":";
        if (startMin < 10){ os << "0"; }
        os << startMin << "-";
        if (endHour < 10){ os << "0"; }
        os << endHour << ":";
        if (endMin < 10){ os << "0"; }
        os << endMin << " ";

        //Prints the name of the program, along with the necessary spaces to make the width universal
        os << p.channel;
        for(size_t i = 0; i < (largestChannel - p.channel.size()); i++){
            os << " ";
        }
        os << " " << p.name;
        if(p.adult){
            os << "*";
        }

        os << "\n";
    }
    return;
}

Schedule::Schedule(const Schedule &s): currID(s.currID), programPlan(s.programPlan){}

Schedule &Schedule::operator=(const Schedule &s){
    	currID = s.currID;
	programPlan = s.programPlan;
	return *this;
}

int Schedule::add(std::string name, std::string channel, int start, int length, bool adult){
    if((start < 0) || (name.length() == 0) || (channel.length() == 0)){
        return -1;
    }

    const int dayInMins = 24*4;
    if(start >= (dayInMins) || ((length) > ((dayInMins)-(start)))){
        return -1;
    }

    Program newProg;
    newProg.name = name;
    newProg.channel = channel;
    newProg.start = start;
    newProg.length = length;
    newProg.adult = adult;

    //No need to check for conflicts if there are no other programs in the plan
    if(currID > 0){
        for(Program p : programPlan){
            //If one program starts while another program is already playing, the new program is invalid
            if(newProg.channel == p.channel){
                if(newProg.start == p.start){ //Is this redundant
                   return -1;
                }
                if((newProg.start > p.start) && (newProg.start < (p.start+p.length))){ //Can these be concatenated?
                    return -1;
                }
                if((p.start > newProg.start) && (p.start < (newProg.start+newProg.length))){
                    return -1;
                }
           }
       }
    }

    //If the new program is valid, increment the ID to be given to the program, and add it to the program plan
    currID++;
    newProg.id = currID;
    programPlan.push_back(newProg);
    return newProg.id;
}

bool Schedule::erase(int id){
    size_t planSize = programPlan.size();
    for(size_t i = 0; i < planSize; i++){
        if(programPlan.at(i).id == id){
            programPlan.erase(programPlan.begin()+i);
            return true;
        }
    }
    return false;
}


int Schedule::getCurrID() const {
    return currID;
}

std::vector<Program> Schedule::getProgramPlan() const {
    return programPlan;
}

size_t Schedule::size() const {
    return programPlan.size();
}
