#pragma once
#include <assert.h>

template <typename T>
class CMyList
{
private:
  struct Node
  {
    Node(T data)
    {
      Data = data;
      pNodePrev = nullptr;
      pNodeNext = nullptr;
    }

    Node()
    {
      memset(&Data, 0, sizeof(Data));
      pNodePrev = nullptr;
      pNodeNext = nullptr;
    }

    Node *pNodePrev;
    Node *pNodeNext;
    T Data;
  };
public:
  template <typename T>
  class Iterator
  {
  public:
    Iterator(Node * ptr)
    {
      m_Ptr = ptr;
    }

    T& operator*()
    {
      assert(m_Ptr != nullptr);
      return m_Ptr->Data;
    }

    T* operator->()
    {
      assert(m_Ptr != nullptr);
      return &m_Ptr->Data;
    }

    Iterator<T>& operator--()
    {
      if (m_Ptr != nullptr)
      {
        m_Ptr = m_Ptr->pNodePrev;
      }
      return *this;
    }

    Iterator<T>& operator++()
    {
      if (m_Ptr != nullptr)
      {
        m_Ptr = m_Ptr->pNodeNext;
      }
      return *this;
    }

    Iterator<T> operator++(int)
    {
      Iterator<T> Tmp = *this;
      if (m_Ptr != nullptr)
      {
        m_Ptr = m_Ptr->pNodeNext;
      }
      return Tmp;
    }

    bool operator!=(Iterator<T>& it)
    {
      return it.m_Ptr != m_Ptr;
    }

    bool operator!=(Iterator<T>&& it)
    {
      return it.m_Ptr != m_Ptr;
    }

    Node * m_Ptr;
  };

public:
  CMyList();
  ~CMyList();

  //尾部添加
  void push_back(const T& val);

  //头部添加
  void push_front(const T& val);

  //移除头部
  void pop_front();

  //移除尾部
  void pop_back();

  //取尾部数据
  T& back();

  //取头部数据
  T& front();

  //大小
  int size() const;

  //是否为空
  bool empty() const;

  //插入数据
  Iterator<T> insert(Iterator<T> position, const T& val);

  //移除数据
  Iterator<T> erase(Iterator<T> position);

  //首迭代器
  Iterator<T> begin();

  //尾迭代器
  Iterator<T> end();

private:
  Node * m_pHead;
  int m_nLength;
};

template <typename T>
CMyList<T>::CMyList()
{
  m_pHead = new Node();
  m_nLength = 0;
}

template <typename T>
CMyList<T>::~CMyList()
{

  //if (m_nLength > 0)
  //{
  //  //临时
  //  Node *pHead = m_pHead;

  //  //遍历释放
  //  while (pHead != nullptr)
  //  {
  //    Node *pTmp = pHead->pNodeNext;
  //    delete pHead;
  //    pHead = pTmp;
  //  }

  //  //规范
  //  m_nLength = 0;
  //  m_pHead = nullptr;
  //}
  //else
  //{
  //  delete m_pHead;
  //  m_nLength = 0;
  //  m_pHead = nullptr;
  //}

}

template <typename T>
void CMyList<T>::push_back(const T & val)
{
  //构建新节点
  Node *pNew = new Node(val);

  //临时
  Node *pTmp = m_pHead;

  //寻找尾部
  while (pTmp->pNodeNext != nullptr && (pTmp = pTmp->pNodeNext));

  //添加到尾部
  pTmp->pNodeNext = pNew;
  pNew->pNodePrev = pTmp;

  //长度++
  m_nLength++;

  return;
}

template <typename T>
void CMyList<T>::push_front(const T & val)
{
  //构建新节点
  Node *pNew = new Node(val);

  //获取首部数据节点
  Node *pNext = m_pHead->pNodeNext;

  //指向新头部
  m_pHead->pNodeNext = pNew;

  //头部上指针
  pNew->pNodePrev = m_pHead;

  //头部下指针
  pNew->pNodeNext = pNext;

  //老头部节点指针
  if (pNext != nullptr)
  {
    pNext->pNodePrev = pNew;
  }

  //长度++
  m_nLength++;

}

template <typename T>
void CMyList<T>::pop_front()
{
  if (m_nLength == 0)
  {
    return;
  }

  //得到头部
  Node *pFront = m_pHead->pNodeNext;

  //检查
  if (pFront != nullptr)
  {
    //得到新头部
    Node *pNewFront = pFront->pNodeNext;

    //修复正确的头部
    m_pHead->pNodeNext = pNewFront;
    if (pNewFront != nullptr)
    {
      pNewFront->pNodePrev = m_pHead;
    }

    //释放空间
    delete pFront;

    //长度--
    m_nLength--;
  }

}

template <typename T>
void CMyList<T>::pop_back()
{
  if (m_nLength == 0)
  {
    return;
  }

  //尾部
  Node *pTail = m_pHead;

  //寻找尾部
  while (pTail->pNodeNext != nullptr && (pTail = pTail->pNodeNext));

  //检查
  if (pTail != m_pHead && pTail != nullptr)
  {
    //置空尾指针
    Node *pTmp = pTail->pNodePrev;
    pTmp->pNodeNext = nullptr;

    //释放空间
    delete pTail;

    //长度--
    m_nLength--;
  }
}

template<typename T>
inline T & CMyList<T>::back()
{
  if (m_nLength == 0)
  {
    throw std::range_error("m_nLength == 0");
  }

  //尾部
  Node *pTail = m_pHead;

  //寻找尾部
  while (pTail->pNodeNext != nullptr && (pTail = pTail->pNodeNext));

  //返回尾部数据
  return pTail->Data;
}

template<typename T>
inline T & CMyList<T>::front()
{
  if (m_nLength == 0)
  {
    throw std::range_error("m_nLength == 0");
  }
  //返回头部数据
  return m_pHead->pNodeNext->Data;
}

template <typename T>
int CMyList<T>::size() const
{
  return m_nLength;
}

template <typename T>
bool CMyList<T>::empty() const
{
  return m_nLength == 0;
}

template <typename T>
CMyList<T>::Iterator<T> CMyList<T>::insert(CMyList<T>::Iterator<T> position, const T & val)
{
  //断言宏
  if (position.m_Ptr == nullptr)
  {
    return position;
  }

  //构建新节点
  Node *pNew = new Node(val);

  //上个节点
  Node *pPrev = position.m_Ptr->pNodePrev;

  //下个节点
  Node *pCur = position.m_Ptr;

  //新节点指针
  pNew->pNodePrev = pPrev;
  pNew->pNodeNext = pCur;

  //节点修复
  pPrev->pNodeNext = pNew;
  pCur->pNodePrev = pNew;

  //计数++
  m_nLength++;

  return position;
}

template <typename T>
CMyList<T>::Iterator<T> CMyList<T>::erase(CMyList<T>::Iterator<T> position)
{
  //check
  if (m_nLength <= 0 || position.m_Ptr == m_pHead)
  {
    return position;
  }

  //断言宏
  assert(position.m_Ptr != nullptr);

  //上个节点
  Node *pPrev = position.m_Ptr->pNodePrev;

  //下个节点
  Node *pNext = position.m_Ptr->pNodeNext;

  //节点修复
  if (pPrev != nullptr)
  {
    pPrev->pNodeNext = pNext;
  }
  if (pNext != nullptr)
  {
    pNext->pNodePrev = pPrev;
  }

  //释放资源
  delete position.m_Ptr;
  position.m_Ptr = nullptr;

  //计数--
  m_nLength--;

  return position;
}

template <typename T>
CMyList<T>::Iterator<T> CMyList<T>::begin()
{
  return Iterator<T>(m_pHead->pNodeNext);
}

template <typename T>
CMyList<T>::Iterator<T> CMyList<T>::end()
{
  return Iterator<T>(nullptr);
}
