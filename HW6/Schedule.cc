#include "Schedule.h"
#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>



/* ------------------------------------------
                SCHEDULE ITERATOR
   ------------------------------------------ */
    //Schedule::ScheduleIterator::ScheduleIterator(const Schedule::ScheduleIterator& newIt) : place(newIt.place), parent(newIt.parent) {}
    
    Schedule::iterator Schedule::iterator::operator++(){
        place += 1;
        advance();
        return *this;
    }

    Schedule::iterator Schedule::iterator::operator++(int){
        iterator temp = *this;
        ++*this;
        return temp;
    }

    Show Schedule::iterator::operator*() const{
        return (*parent)[place];
    }

    bool Schedule::iterator::operator==(const Schedule::iterator& rhs) const{
        return (place == rhs.place);
    }

    bool Schedule::iterator::operator!=(const Schedule::iterator& rhs) const{
        return !(*this == rhs);
    }

    Schedule::iterator Schedule::begin() const {
        Schedule::iterator setBegin;
        setBegin.parent = this;
	setBegin.place = 0;
        setBegin.advance();
        return setBegin;
    }
    Schedule::iterator Schedule::end() const {
        Schedule::iterator setEnd;
        setEnd.parent = this;
        setEnd.place = this->programPlan.size()-1;
        return setEnd;
    }

    void Schedule::iterator::advance(){
        if(!parent->forAdults){
            if((*parent)[place].adult() && (place+1 != (*parent).programPlan.size())) //TODO: add in boundary checking!!
                ++*this;
        }
    }
/* ------------------------------------------
                    SCHEDULE
   ------------------------------------------ */

Schedule::Schedule(){
    currID = 0;
}

Schedule::Schedule(const Schedule &s): currID(s.currID), programPlan(s.programPlan){}

Schedule::Schedule(std::set<Show, compare> newSchedule){
    programPlan = newSchedule;
    currID = newSchedule.size()+1; //type conversion from size_t to int seems a little iffy
}

Schedule &Schedule::operator=(const Schedule &s){
        currID = s.currID;
        programPlan = s.programPlan;
        return *this;
}

void Schedule::grups(bool flag){
	forAdults = flag;
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
                    OPERATOR OVERLOADING
   -----------------------------------------------------*/
Schedule &Schedule::operator+=(const Show& s){
    if(programPlan.size() != 0){ //If the program plan is empty, no validation needs to be performed
        for(Show p : programPlan){ //Check to see if there are any time conflicts between the show to be added and the shows in the plan  
	    if(!validator(p, s)){
                throw std::runtime_error("Show " + s.name() + " cannot be added to the schedule because of time conflicts with " + p.name() + "\n");
            }
        }
    }

    programPlan.insert(s);
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
        programPlan.insert(p);
    }
    return *this;
}

int Schedule::operator-=(int rhs){
    for(auto p : programPlan){
        if(p.id() == rhs){
	    auto removeIt = programPlan.find(p);
            programPlan.erase(removeIt); //Check for off-by-ones
            return 0;
        }
    }
    throw std::runtime_error("Show with ID " + std::to_string(rhs) + " does not currently exist within schedule\n");
}

//TODO: Make this set-compatible
Show Schedule::operator[](const size_t index) const {
    std::set<Show>::iterator schedIt = programPlan.begin();
    if(index >= programPlan.size()){
        throw std::range_error("Could not retrieve show at index " + std::to_string(index) + " as the max index is currently " + std::to_string(programPlan.size()) + "\n");
    }

    for(size_t i = 0; i < index; i++){
        ++schedIt;
    }
    return *schedIt;
    //return programPlan[index];
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
    std::set <Show, compare> combinedList;
    for(Show s : lhs.getPlan())
	combinedList.insert(s);
    for(Show s : rhs.getPlan())
	combinedList.insert(s);
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
