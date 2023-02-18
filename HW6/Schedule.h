#ifndef SCHEDULE_H_INCLUDED
#define SCHEDULE_H_INCLUDED

#include "Show.h"
#include <string>
#include <vector>
#include <iostream>
#include <set>

        //Set Comparison
struct compare{
    bool operator()(Show a, Show b) const {
        return std::pair{a.start(), a.channel()} < std::pair{b.start(), b.channel()};
    }
};


class Schedule{
    public:
        //Constructors
        Schedule();
        //Schedule(std::string, std::string, int, int, bool adult=false);
	Schedule(std::set<Show, compare>);
        Schedule(const Schedule& s);
        Schedule &operator=(const Schedule& s);

	//Accessors
        [[nodiscard]] size_t size() const;
        std::ostream print(std::ostream &os = std::cout) const;
	std::set<Show, compare> getPlan() const {return programPlan;}

	//Mutators
        int add(std::string name, std::string channel, int start, int length, bool adult=false);
        bool erase(int programID);
	void grups(bool flag=true);

        //Operator Overloads
        Schedule &operator+=(const Show& s);
        Schedule &operator+=(const Schedule& rhs);
	int operator-=(int rhs);
        Show operator[](const size_t index) const;
	
	//Iterator
        class iterator{
            public:
                iterator() = default;
		iterator(Schedule* schedP): parent(schedP), place(0){ advance(); }
                iterator operator++();
                iterator operator++(int);
                Show operator*() const;
                bool operator!=(const iterator&) const;
                bool operator==(const iterator&) const;
                iterator &operator=(const iterator&);
       		
		void setParent(const Schedule* newPar){ parent = newPar; }
            
                void advance();
                const Schedule* parent;
                size_t place;
        };
        
        iterator begin() const;
        iterator end() const;

        //Destructor
        ~Schedule() = default;
    private:
	bool forAdults = true;
        size_t currID;
        std::set<Show, compare> programPlan;
};

Schedule operator+(/*const*/ Schedule& lhs, /*const*/ Schedule& rhs);
std::ostream &operator<<(std::ostream& os, const Schedule& toPrint);

#endif /* DIRECTORY_H_INCLUDED */
