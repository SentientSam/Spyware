/*
    compare_spy.h
    6/7/2019
    Samuel Lamb
    Project 2
*/

#ifndef _COMPARE_SPY_H
#define _COMPARE_SPY_H

namespace fsu
{
template < typename T >
class LessThanSpy 
{
  public:
    LessThanSpy() : count_(0) //count to 0
    {}
    bool operator () (const T& t1, const T& t2) 
    {
      ++count_;
      return (t1 < t2);
    }
    void Reset() //count reset function
    {
      count_ = 0;
    }
    size_t Count() const //Count() function
    {
      return count_;
    }
  private:
    size_t count_; //Keep the ocunt_ variable private so it cannot be altered 
};

} // namespace fsu
#endif
