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

  //�Ƿ�Ϊ��
  bool empty()
  {
    return __super::empty();
  }

  //��ȡ��С
  int size()
  {
    return __super::size();
  }

  //��ȡ��ͷԪ��
  T& front()
  {
    return __super::front();
  }

  //��ȡ��βԪ��
  T& back()
  {
    return __super::back();
  }

  //��ӵ���β
  void push(const T& val)
  {
    __super::push_back(val);
  }

  //��������Ԫ��
  void pop()
  {
    __super::pop_front();
  }
};

