#include <string>
#include <iostream>

class Show{
  public:
    //Constructors
    Show(std::string name, std::string channel, int start, int length, bool adult=false);
    Show(const Show& s);
    Show &operator=(const Show& s);

    //Getters
    [[nodiscard]] std::string name() const {return showName;}
    [[nodiscard]] std::string channel() const {return showChannel;}
    [[nodiscard]] int start() const {return startTime;}
    [[nodiscard]] int length() const {return showLength;}
    [[nodiscard]] bool adult() const {return isAdult;}
    [[nodiscard]] int id() const {return showIndex;}

  private:
    std::string showName;
    std::string showChannel;
    int startTime;
    int showLength;
    bool isAdult;

    int showIndex;
    static inline int index = 0;
};
