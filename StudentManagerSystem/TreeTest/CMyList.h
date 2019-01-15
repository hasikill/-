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

  //β�����
  void push_back(const T& val);

  //ͷ�����
  void push_front(const T& val);

  //�Ƴ�ͷ��
  void pop_front();

  //�Ƴ�β��
  void pop_back();

  //ȡβ������
  T& back();

  //ȡͷ������
  T& front();

  //��С
  int size() const;

  //�Ƿ�Ϊ��
  bool empty() const;

  //��������
  Iterator<T> insert(Iterator<T> position, const T& val);

  //�Ƴ�����
  Iterator<T> erase(Iterator<T> position);

  //�׵�����
  Iterator<T> begin();

  //β������
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
  //  //��ʱ
  //  Node *pHead = m_pHead;

  //  //�����ͷ�
  //  while (pHead != nullptr)
  //  {
  //    Node *pTmp = pHead->pNodeNext;
  //    delete pHead;
  //    pHead = pTmp;
  //  }

  //  //�淶
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
  //�����½ڵ�
  Node *pNew = new Node(val);

  //��ʱ
  Node *pTmp = m_pHead;

  //Ѱ��β��
  while (pTmp->pNodeNext != nullptr && (pTmp = pTmp->pNodeNext));

  //��ӵ�β��
  pTmp->pNodeNext = pNew;
  pNew->pNodePrev = pTmp;

  //����++
  m_nLength++;

  return;
}

template <typename T>
void CMyList<T>::push_front(const T & val)
{
  //�����½ڵ�
  Node *pNew = new Node(val);

  //��ȡ�ײ����ݽڵ�
  Node *pNext = m_pHead->pNodeNext;

  //ָ����ͷ��
  m_pHead->pNodeNext = pNew;

  //ͷ����ָ��
  pNew->pNodePrev = m_pHead;

  //ͷ����ָ��
  pNew->pNodeNext = pNext;

  //��ͷ���ڵ�ָ��
  if (pNext != nullptr)
  {
    pNext->pNodePrev = pNew;
  }

  //����++
  m_nLength++;

}

template <typename T>
void CMyList<T>::pop_front()
{
  if (m_nLength == 0)
  {
    return;
  }

  //�õ�ͷ��
  Node *pFront = m_pHead->pNodeNext;

  //���
  if (pFront != nullptr)
  {
    //�õ���ͷ��
    Node *pNewFront = pFront->pNodeNext;

    //�޸���ȷ��ͷ��
    m_pHead->pNodeNext = pNewFront;
    if (pNewFront != nullptr)
    {
      pNewFront->pNodePrev = m_pHead;
    }

    //�ͷſռ�
    delete pFront;

    //����--
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

  //β��
  Node *pTail = m_pHead;

  //Ѱ��β��
  while (pTail->pNodeNext != nullptr && (pTail = pTail->pNodeNext));

  //���
  if (pTail != m_pHead && pTail != nullptr)
  {
    //�ÿ�βָ��
    Node *pTmp = pTail->pNodePrev;
    pTmp->pNodeNext = nullptr;

    //�ͷſռ�
    delete pTail;

    //����--
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

  //β��
  Node *pTail = m_pHead;

  //Ѱ��β��
  while (pTail->pNodeNext != nullptr && (pTail = pTail->pNodeNext));

  //����β������
  return pTail->Data;
}

template<typename T>
inline T & CMyList<T>::front()
{
  if (m_nLength == 0)
  {
    throw std::range_error("m_nLength == 0");
  }
  //����ͷ������
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
  //���Ժ�
  if (position.m_Ptr == nullptr)
  {
    return position;
  }

  //�����½ڵ�
  Node *pNew = new Node(val);

  //�ϸ��ڵ�
  Node *pPrev = position.m_Ptr->pNodePrev;

  //�¸��ڵ�
  Node *pCur = position.m_Ptr;

  //�½ڵ�ָ��
  pNew->pNodePrev = pPrev;
  pNew->pNodeNext = pCur;

  //�ڵ��޸�
  pPrev->pNodeNext = pNew;
  pCur->pNodePrev = pNew;

  //����++
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

  //���Ժ�
  assert(position.m_Ptr != nullptr);

  //�ϸ��ڵ�
  Node *pPrev = position.m_Ptr->pNodePrev;

  //�¸��ڵ�
  Node *pNext = position.m_Ptr->pNodeNext;

  //�ڵ��޸�
  if (pPrev != nullptr)
  {
    pPrev->pNodeNext = pNext;
  }
  if (pNext != nullptr)
  {
    pNext->pNodePrev = pPrev;
  }

  //�ͷ���Դ
  delete position.m_Ptr;
  position.m_Ptr = nullptr;

  //����--
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
