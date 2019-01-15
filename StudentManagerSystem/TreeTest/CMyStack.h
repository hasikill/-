#pragma once
#include "CMyList.h"

template <typename T>
class CMyStack : protected CMyList<T>
{
public:
  CMyStack()
  {

  }

  ~CMyStack()
  {

  }

  bool empty()
  {
    return __super::empty();
  }

  int size()
  {
    return __super::size();
  }

  void push(T val)
  {
    __super::push_back(val);
  }

  void pop()
  {
    __super::pop_back();
  }

  T top()
  {
    return __super::back();
  }

};

