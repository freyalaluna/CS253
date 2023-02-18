#include "Show.h"
#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>

Show::Show(std::string name, std::string channel, int start, int length, bool adult){
    if(name.length() == 0 || channel.length() == 0){
        throw std::runtime_error("Show name and channel strings must be provided for valid show creation\n");
    }
    if(start < 0 || start > (24*4)){
        throw std::runtime_error("Show start time must be strictly within the bounds of 00:00 and 24:00\n");
    }
    if((start+length) > (24*4)){
        throw std::runtime_error("Show cannot span midnight\n");
    }
    showName = name;
    showChannel = channel;
    startTime = 15*start;
    showLength = 15*length;
    isAdult = adult;
    showIndex = index;
    index++;
}

Show::Show(const Show& s):  showName(s.name()), showChannel(s.channel()), startTime(s.start()), showLength(s.length()), isAdult(s.adult()),
                            showIndex(s.id()) {}

Show &Show::operator=(const Show& s){
    showName = s.name();
    showChannel = s.channel();
    startTime = s.start();
    showLength = s.length();
    isAdult = s.adult();
    showIndex = s.id();
    return *this;
}
