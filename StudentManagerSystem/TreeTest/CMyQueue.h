#pragma once
#include "CMyList.h"
template <typename T>
class CMyQueue : protected CMyList<T>
{
public:
  CMyQueue()
  {

  }

  ~CMyQueue()
  {

  }

  //是否为空
  bool empty()
  {
    return __super::empty();
  }

  //获取大小
  int size()
  {
    return __super::size();
  }

  //获取队头元素
  T& front()
  {
    return __super::front();
  }

  //获取队尾元素
  T& back()
  {
    return __super::back();
  }

  //添加到队尾
  void push(const T& val)
  {
    __super::push_back(val);
  }

  //弹出队首元素
  void pop()
  {
    __super::pop_front();
  }
};

