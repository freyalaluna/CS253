#ifndef RANGE_H_INCLUDED
#define RANGE_H_INCLUDED

#include <iostream>
#include <ios>
#include <string>
#include <stdexcept>
#include <algorithm>
template <typename T>
class Range{
    public:
		//Constructors - Leave copy and assignment as default
        Range(T val): lowerBound(val), upperBound(val) {}
        Range(T low, T high){
            assign(low, high);
        }
        
        void assign(T low, T high){
            if(low > high){
				std::string err = "Could not create range from values " + std::to_string(low) + " and " + std::to_string(high) + " as the larger value was issued as the first argument.";
                throw std::runtime_error(err);
            }
            lowerBound = low;
            upperBound = high;
        }
        
        //Getters
        [[nodiscard]] T min() const { return lowerBound; }
        [[nodiscard]] T max() const { return upperBound; }

		//Unary Operator Overloads
        Range& operator+=(const Range& rhs){
            lowerBound = lowerBound + rhs.lowerBound;
            upperBound = upperBound + rhs.upperBound;
            return *this;
        }

        Range& operator-=(const Range& rhs){
            lowerBound = lowerBound - rhs.upperBound;
            upperBound = upperBound - rhs.lowerBound;
            return *this;
        }

        Range& operator*=(const Range& rhs){
	    T upperAndUpper = upperBound * rhs.upperBound;
	    T upperAndLower = upperBound * rhs.lowerBound;
	    T lowerAndUpper = lowerBound * rhs.upperBound;
	    T lowerAndLower = lowerBound * rhs.lowerBound;
	    lowerBound = std::min({upperAndUpper, upperAndLower, lowerAndUpper, lowerAndLower});
	    upperBound = std::max({upperAndUpper, upperAndLower, lowerAndUpper, lowerAndLower});
            return *this;
        }
        Range& operator/=(const Range& rhs){
            if(rhs.upperBound - rhs.lowerBound >= rhs.upperBound){
                std::string err = "Could not divide [" + std::to_string(lowerBound) + ", " + std::to_string(upperBound) + "] by " + "[" + std::to_string(rhs.lowerBound) + ", " + std::to_string(rhs.upperBound) + "], as the second range contains 0.";
				throw std::runtime_error(err);
            }
            T upperAndUpper = upperBound / rhs.upperBound;
            T upperAndLower = upperBound / rhs.lowerBound;
            T lowerAndUpper = lowerBound / rhs.upperBound;
            T lowerAndLower = lowerBound / rhs.lowerBound;
            lowerBound = std::min({upperAndUpper, upperAndLower, lowerAndUpper, lowerAndLower});
            upperBound = std::max({upperAndUpper, upperAndLower, lowerAndUpper, lowerAndLower});
            return *this;
        }
	
		[[nodiscard]] bool operator==(const Range& rhs){
			return ((lowerBound == rhs.lowerBound) && (upperBound == rhs.upperBound));
		}
		[[nodiscard]] bool operator!=(const Range& rhs){
			return !(*this == rhs);
		}
    private:
        T lowerBound;
        T upperBound;
};

//Binary Operator Overloads
template <typename T>
Range<T> operator+(const Range<T> lhs, const Range<T> rhs){
    Range<T> sum(lhs);
    return sum += rhs;
}

template <typename T>
Range<T> operator-(const Range<T> lhs, const Range<T> rhs){
    Range<T> diff(lhs);
    return diff -= rhs;
}

template <typename T>
Range<T> operator*(const Range<T> lhs, const Range<T> rhs){
    Range<T> prod(lhs);
    return prod *= rhs;
}

template <typename T>
Range<T> operator/(const Range<T> lhs, const Range<T> rhs){
    Range<T> quot(lhs);
    return quot /= rhs;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Range<T>& toPrint){
    os << "[" << toPrint.min() << "," << toPrint.max() << "]";
    return os;
}

template <typename T>
std::istream& operator>>(std::istream& is, Range<T>& input) {
	char c;
	T a, b;
	if(is>>c && c=='[' && is>>a && is>>c && c==',' && is>>b && is>>c && c==']'){
		input.assign(a, b);
	} else {
		is.setstate(std::ios::failbit);
	}
    return is;
}

#endif /* DIRECTORY_H_INCLUDED */
