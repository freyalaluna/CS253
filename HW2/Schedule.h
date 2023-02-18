#include <string>
#include <vector>
#include <iostream>

struct Program{
            std::string name;
            std::string channel;
            int start;
            int length;
            bool adult;
            int id;
};

class Schedule{
    public:
        //Constructors
        Schedule();
        Schedule(std::string, std::string, int, int, bool);
        Schedule(const Schedule& s);
        
	//Getters
        [[nodiscard]] size_t size() const;
        void print(std::ostream &os = std::cout) const;
        int getCurrID() const;
        std::vector<Program> getProgramPlan() const;

        //Setters
        Schedule &operator=(const Schedule& s);
        int add(std::string name, std::string channel, int start, int length, bool adult=false);
        bool erase(int programID);
        
        //Destructor
        ~Schedule() = default;
    private:
        int currID;
        std::vector<Program> programPlan;
};
