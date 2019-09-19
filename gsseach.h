/*
    gssearch.h
    6/7/2019
    Samuel Lamb
    Project 2
*/

#ifndef _GSSEARCH_H
#define _GSSEARCH_H

#include <compare_spy.h>

namespace seq
{
  template <class I, typename T, class P>
  I g_lower_bound (I beg, I end, const T& val, P& cmp)
  {
    while (beg != end)
    {
      if (!cmp(*beg , val)) 
      {
        return beg;
      }
      ++beg;                                              
    }  
    return beg;
  }
  template <class I, typename T, class P>
  I g_upper_bound (I beg, I end, const T& val, P& cmp)
  {
    while (beg != end)
    {
      if (cmp(val, *beg))                
      {
        return beg;
      }            
      ++beg;           
    }
    return end;
  }
} // namespace seq

#endif
