#include "Show.h"
#include <string>
#include <vector>
#include <iostream>

class Schedule{
    public:
        //Constructors
        Schedule();
        //Schedule(std::string, std::string, int, int, bool adult=false);
	Schedule(std::vector<Show>);
        Schedule(const Schedule& s);
        Schedule &operator=(const Schedule& s);

        [[nodiscard]] size_t size() const;
        std::ostream print(std::ostream &os = std::cout) const;

        int add(std::string name, std::string channel, int start, int length, bool adult=false);
        bool erase(int programID);

        //Operator Overloads
        Schedule &operator+=(const Show& s);
        Schedule &operator+=(const Schedule& rhs);
        //Schedule &operator+(const Schedule& rhs) const;
	int operator-=(int rhs);
        Show &operator[](size_t index) /*const*/;

	std::vector<Show> getPlan() const {return programPlan;}	
        //Destructor
        ~Schedule() = default;
    private:
        size_t currID;
        std::vector<Show> programPlan;
};

Schedule operator+(/*const*/ Schedule& lhs, /*const*/ Schedule& rhs);
std::ostream &operator<<(std::ostream& os, const Schedule& toPrint);
