#include "Schedule.h"
#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>
Schedule::Schedule(){
    currID = 0;
}

Schedule::Schedule(const Schedule &s): currID(s.currID), programPlan(s.programPlan){}

Schedule::Schedule(std::vector<Show> newSchedule){
    programPlan = newSchedule;
    currID = newSchedule.size()+1; //type conversion from size_t to int seems a little iffy
}

Schedule &Schedule::operator=(const Schedule &s){
        currID = s.currID;
        programPlan = s.programPlan;
        return *this;
}

bool validator(const Show& p, const Show& s){ //Helper function - handles checks for time conflicts between shows
    if(p.channel() == s.channel()){ //TODO: Make this DRYer
        if(p.start() == s.start()){
            return false;
        }
        if((s.start() > p.start()) && (s.start() < (p.start()+p.length()))){
            return false;
        }
         if((p.start() > s.start()) && (p.start() < (s.start()+s.length()))){
            return false;
        }
    }
    return true;
}

/* -----------------------------------------------------
        OPERATOR OVERLOAD SHIT GOES HERE
   -----------------------------------------------------*/
Schedule &Schedule::operator+=(const Show& s){
    if(programPlan.size() != 0){ //If the program plan is empty, no validation needs to be performed
        for(Show p : programPlan){ //Check to see if there are any time conflicts between the show to be added and the shows in the plan  
	    if(!validator(p, s)){
                throw std::runtime_error("Show " + s.name() + " cannot be added to the schedule because of time conflicts with " + p.name() + "\n");
            }
        }
    }

    programPlan.push_back(s);
    return *this;
}

Schedule &Schedule::operator+=(const Schedule& rhs){
    for(Show s: programPlan){ //Check to see if there are any conflicts between right and left operands
        for(Show p : rhs.getPlan()){
            if(!validator(p, s)){
                throw std::runtime_error("Schedules cannot be combined because of time conflicts between " + p.name() + " in the modifying schedule" + 
                " and " + s.name() + " in the schedule to be modefied.");
            }
        }
    }
    for(Show p : rhs.getPlan()){ //If there are no conflicts, copy all shows from right hand operand to left hand operand
        programPlan.push_back(p);
    }
    return *this;
}

int Schedule::operator-=(int rhs){
    for(size_t i = 0; i < programPlan.size(); i++){
        if(programPlan[i].id() == rhs){
            programPlan.erase(programPlan.begin()+i); //Check for off-by-ones
            return 0;
        }
    }
    throw std::runtime_error("Show with ID " + std::to_string(rhs) + " does not currently exist within schedule\n");
    //Will the compiler complain if I don't have a return statement?
}

Show &Schedule::operator[](const size_t index) /*const*/ {
    if(index >= programPlan.size()){
        throw std::range_error("Could not retrieve show at index " + std::to_string(index) + " as the max index is currently " + std::to_string(programPlan.size()) + "\n");
    }
    return programPlan[index];
}

Schedule operator+(/*const*/ Schedule& lhs, /*const*/ Schedule& rhs){
    for(Show s: lhs.getPlan()){ //Check to see if there are any conflicts between right and left operands
        for(Show p : rhs.getPlan()){
            if(!validator(p, s)){
                throw std::runtime_error("Schedules cannot be combined because of time conflicts between " + p.name() + " in the right operand and" + 
                s.name() + "in the left operand.");
            }
        }
    }
    std::vector <Show> combinedList;
    for(Show s : lhs.getPlan())
	combinedList.push_back(s);
    for(Show s : rhs.getPlan())
	combinedList.push_back(s);
    return Schedule(combinedList);
}

std::ostream &operator<<(std::ostream& os, const Schedule& toPrint){
    size_t largestChannel = 0;

    //Find the size of the program with the longest name
    for(Show p : toPrint.getPlan()){
        if(p.channel().size() > largestChannel){
            largestChannel = p.channel().size();
        }
    }

    //Print out each line, with spaces matched according to program name
    for(Show p : toPrint.getPlan()){
	int startInMins = p.start();
	int lengthInMins = p.length(); 
	int startHour = startInMins/60;
	int endHour = (startInMins+lengthInMins)/60;
	int startMin = (startInMins)%60;
	int endMin = (startInMins+lengthInMins)%60;
	
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
        os << p.channel();
        for(size_t i = 0; i < (largestChannel - p.channel().size()); i++){
            os << " ";
        }
        os << " " << p.name();
        if(p.adult()){
            os << "*";
        }

        os << "\n";
    }
    return os;
}

size_t Schedule::size() const {
    return programPlan.size();
}
