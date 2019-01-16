#include <string>

struct AlphaStrComp {
  bool operator() (const std::string& lhs, const std::string& rhs)
  { // Uses string's built in operator<
    // to do lexicographic (alphabetical) comparison
    return (lhs < rhs);
  }
};

struct LengthStrComp {
  bool operator()(const std::string& lhs, const std::string& rhs)
  { // Compares strings by size;
    // Breaks ties by lexicographic comparison
    return (   (lhs.size() < rhs.size())
            || (lhs.size() == rhs.size() && lhs < rhs));
  }
};

struct NumStrComp {
  bool operator()(const std::string& lhs, const std::string& rhs)
  { // Compares strings by size;
    int LHS_sum = 0;
    for(unsigned int i = 0; i<lhs.size(); i++)
    {
      int letterVal = (int)(toupper(lhs[i]));
      //if it is a number between 0 and 9
      if(letterVal - (int)'0' >= 0 && letterVal - (int)'0' <= 9)
      {
        LHS_sum += letterVal - (int)'0';
      }
      //if it is a letter between A-Z (case insensitive)
      if(letterVal >= 65 && letterVal <= 90)
      {
        LHS_sum += letterVal - (int)'A' + 10;
      }
    }

    int RHS_sum = 0;
    for(unsigned int i = 0; i<rhs.size(); i++)
    {
      int letterVal = (int)(toupper(rhs[i]));
      //if it is a number between 0 and 9
      if(letterVal - (int)'0' >= 0 && letterVal - (int)'0' <= 9)
      {
        RHS_sum += letterVal - (int)'0';
      }
      //if it is a letter between A-Z (case insensitive)
      if(letterVal >= 65 && letterVal <= 90)
      {
        RHS_sum += letterVal - (int)'A' + 10;
      }
    }
    // Breaks ties by lexicographic comparison
    return ((LHS_sum < RHS_sum) || (LHS_sum == RHS_sum && lhs < rhs));
  }
};