#pragma once
#include "CMyQueue.h"
#include "CMyStack.h"
#include <new>
#include <iostream>
#include <cmath>
#pragma warning(disable:4996)

int max(int a, int b);

//����������
template<typename T>
class CMyTree
{

public:
  struct TreeNode
  {
    TreeNode()
    {
      pParent = nullptr;
      pLeftTreeNode = nullptr;
      pRightTreeNode = nullptr;
      pNext = nullptr;
    }

    TreeNode(T& val)
    {
      data = val;
      pParent = nullptr;
      pLeftTreeNode = nullptr;
      pRightTreeNode = nullptr;
      pNext = nullptr;
      pPrev = nullptr;
      nDepath = 1;
    }

    //����
    TreeNode* LeftRotate();

    //����
    TreeNode* RightRotate();

    //��ȡ
    int GetDepath(TreeNode *pNode);

    T data;
    TreeNode *pParent;
    TreeNode *pLeftTreeNode;
    TreeNode *pRightTreeNode;
    TreeNode *pNext;
    TreeNode *pPrev;
    //�ڵ�����
    //����max(���ӽڵ����, ���ӽڵ����) + 1
    int nDepath;
  };

public:
  CMyTree();
  ~CMyTree();

  //����
  void destroy();

  //��
  void insert(T&& val);
  void insert(T& val);

  //ɾ
  bool Delete(T data);

  //��
  TreeNode* Find(T data);

  //ȡ�ڵ����
  int GetDepath(TreeNode *pNode);

  //��ƽ��
  void adjustBalance(TreeNode *pNode);

  //����
  void layer();

  //
  T* GetLayer(bool isRoot, CMyQueue<TreeNode *> &que);

  //����������ļ�
  void layer_file(const char *szFileName);

  //ǰ��
  void DLR(TreeNode *root);
  void _DLR(TreeNode *root);

  //����
  void LDR(TreeNode *root);
  void _LDR(TreeNode *root);

  //����
  void LRD(TreeNode *root);
  void _LRD(TreeNode *root);

  //��ǰ��
  void DRL(TreeNode *root);

  //������
  void RDL(TreeNode *root);

  //�����
  void RLD(TreeNode *root);

  //��ȡ���Ԫ��
  T GetMax();
  
  //��ȡ���Ԫ��
  T* GetMin();

  int size();

  TreeNode * GetRoot()
  {
    return m_pRoot;
  }
private:
  bool remove(TreeNode * pNode);
  bool removeLink(TreeNode * pNode);

private:
  //���ڵ�
  TreeNode *m_pRoot;
  //����
  int m_nSize;
};

template<typename T>
CMyTree<T>::CMyTree()
{
  m_pRoot = nullptr;
  m_nSize = 0;
}

template<typename T>
CMyTree<T>::~CMyTree()
{
  destroy();
}

template<typename T>
inline void CMyTree<T>::destroy()
{
}

template<typename T>
void CMyTree<T>::insert(T && val)
{
  //�½ڵ�
  TreeNode *pNew = new TreeNode(val);

  if (pNew == nullptr)
  {
    throw std::bad_alloc();
  }

  //��ӵ����ڵ�
  if (m_pRoot == nullptr)
  {
    m_pRoot = pNew;
    m_nSize++;
    return;
  }

  //���нڵ�
  TreeNode *pCur = m_pRoot;

  //
  while (true)
  {
    if (*pNew->data > pCur->data)
    {
      //���ұ�
      if (pCur->pRightTreeNode == nullptr)
      {
        pNew->pParent = pCur;
        pCur->pRightTreeNode = pNew;
        break;
      }
      else
      {
        pCur = pCur->pRightTreeNode;
      }
    }
    else if (*pNew->data < pCur->data)
    {
      //�����
      if (pCur->pLeftTreeNode == nullptr)
      {
        pNew->pParent = pCur;
        pCur->pLeftTreeNode = pNew;
        break;
      }
      else
      {
        pCur = pCur->pLeftTreeNode;
      }
    }
    else
    {
      //����β��
      while (pCur->pNext != nullptr)
      {
        pCur = pCur->pNext;
      }
      //����
      pCur->pNext = pNew;
      pNew->pPrev = pCur;
      break;
    }
  }

  adjustBalance(pCur);
  m_nSize++;
}

template<typename T>
void CMyTree<T>::insert(T & val)
{
  //�½ڵ�
  TreeNode *pNew = new TreeNode(val);

  if (pNew == nullptr)
  {
    throw std::bad_alloc();
  }

  //��ӵ����ڵ�
  if (m_pRoot == nullptr)
  {
    m_pRoot = pNew;
    m_nSize++;
    return;
  }

  //���нڵ�
  TreeNode *pCur = m_pRoot;

  //
  while (true)
  {
    if (*pNew->data > pCur->data)
    {
      //���ұ�
      if (pCur->pRightTreeNode == nullptr)
      {
        pNew->pParent = pCur;
        pCur->pRightTreeNode = pNew;
        break;
      }
      else
      {
        pCur = pCur->pRightTreeNode;
      }
    }
    else if (*pNew->data < pCur->data)
    {
      //�����
      if (pCur->pLeftTreeNode == nullptr)
      {
        pNew->pParent = pCur;
        pCur->pLeftTreeNode = pNew;
        break;
      }
      else
      {
        pCur = pCur->pLeftTreeNode;
      }
    }
    else
    {
      //����β��
      while (pCur->pNext != nullptr)
      {
        pCur = pCur->pNext;
      }
      //����
      pCur->pNext = pNew;
      pNew->pPrev = pCur;
      break;
    }
  }

  adjustBalance(pCur);
  m_nSize++;
}

/*
50
30      70
10  40  60  80
*/
template<typename T>
bool CMyTree<T>::Delete(T data)
{
  //���ҵ�
  TreeNode *pCur = Find(data);
  if (pCur == nullptr)
  {
    //�Ҳ���
    return false;
  }

  //�����в���
  if (pCur->pNext == nullptr)
  {
    //�ҵ���
    return remove(pCur);
  }
  else
  {
    while (pCur != nullptr)
    {
      if (*pCur->data == data)
      {
          return removeLink(pCur);
      }
      pCur = pCur->pNext;
    }
  }
  return false;
}


template<typename T>
typename CMyTree<T>::TreeNode* CMyTree<T>::Find(T data)
{
  TreeNode *pCur = m_pRoot;

  while (pCur != nullptr)
  {
    if (*pCur->data > data)
    {
      pCur = pCur->pLeftTreeNode;
    }
    else if (*pCur->data < data)
    {
      pCur = pCur->pRightTreeNode;
    }
    else 
    {
      return pCur;
    }
  }
  return nullptr;
}

template<typename T>
int CMyTree<T>::GetDepath(TreeNode * pNode)
{
  if (pNode == nullptr)
  {
    return 0;
  }
  return pNode->nDepath;
}

template<typename T>
void CMyTree<T>::adjustBalance(TreeNode * pNode)
{
  TreeNode* pK1 = nullptr;
  TreeNode* pK2 = nullptr;
  TreeNode* pK3 = nullptr;

  while (pNode != nullptr)
  {
    pK1 = pNode;
    pNode->nDepath = max(GetDepath(pNode->pLeftTreeNode), GetDepath(pNode->pRightTreeNode)) + 1;

    //���ֵ
    int nSubHeight = GetDepath(pNode->pLeftTreeNode) - GetDepath(pNode->pRightTreeNode);

    if (std::abs(nSubHeight) > 1) {

      TreeNode* pNewRoot = m_pRoot;

      if (nSubHeight > 1) {
        pK2 = pK1->pLeftTreeNode;
      }
      else {
        pK2 = pK1->pRightTreeNode;
      }

      if (GetDepath(pK2->pLeftTreeNode) - GetDepath(pK2->pRightTreeNode) > 0) {
        pK3 = pK2->pLeftTreeNode;
      }
      else {
        pK3 = pK2->pRightTreeNode;
      }

      //��ʼ��ת
      //�ж�4�����
      //����
      /*
      pK1
      pK2
      pK3
      */
      if (pK2 == pK1->pRightTreeNode && pK3 == pK2->pRightTreeNode) {
        pNewRoot = pK1->LeftRotate();
      }


      //�ҵ���
      /*
      pK1
      pK2
      pK3
      */
      if (pK2 == pK1->pLeftTreeNode && pK3 == pK2->pLeftTreeNode) {
        pNewRoot = pK1->RightRotate();
      }

      //����˫��
      /*
      pK1
      pK2
      pK3
      50
      60
      55
      */
      if (pK2 == pK1->pRightTreeNode && pK3 == pK2->pLeftTreeNode) {
        pNewRoot = pK2->RightRotate();
        pNewRoot = pK1->LeftRotate();
      }

      //����˫��
      /*
      pK1
      pK2
      pK3
      */
      if (pK2 == pK1->pLeftTreeNode && pK3 == pK2->pRightTreeNode) {
        pNewRoot = pK2->LeftRotate();
        pNewRoot = pK1->RightRotate();
      }

      if (pK1 == m_pRoot)
      {
        m_pRoot = pNewRoot;
      }
    }

    pNode = pNode->pParent;
  }

  return;
}

/*
50
30      70
10  40  60  80

//������� <����>
50                50
30 70             50 30
70 10 40          50 30 70
10 40 60 80       50 30 70 10
...               50 30 70 10 40 60 80

*/
template<typename T>
void CMyTree<T>::layer()
{
  if (m_nSize == 0)
  {
    return;
  }

  //����
  CMyQueue<TreeNode *> que;

  //������ڵ�
  que.push(m_pRoot);

  //����
  while (!que.empty())
  {
    //���нڵ�
    TreeNode *pCur = que.front();

    //������нڵ�
    printf("%d ", pCur->data);

    //�������ж�
    if (pCur->pLeftTreeNode != nullptr)
    {
      que.push(pCur->pLeftTreeNode);
    }

    //�������ж�
    if (pCur->pRightTreeNode != nullptr)
    {
      que.push(pCur->pRightTreeNode);
    }

    //ȥ������
    que.pop();
  }
}

template<typename T>
inline T* CMyTree<T>::GetLayer(bool isRoot, CMyQueue<TreeNode *> &que)
{
  if (m_nSize == 0)
  {
    return nullptr;
  }

  if (isRoot)
  {
    //������ڵ�
    que.push(m_pRoot);
  }
  

  //����
  if (!que.empty())
  {
    //���нڵ�
    TreeNode *pCur = que.front();

    //�ó�����
    T* tmp = &pCur->data;

    //�������ж�
    if (pCur->pLeftTreeNode != nullptr)
    {
      que.push(pCur->pLeftTreeNode);
    }

    //�������ж�
    if (pCur->pRightTreeNode != nullptr)
    {
      que.push(pCur->pRightTreeNode);
    }

    //ȥ������
    que.pop();

    //��������
    return tmp;
  }
  return nullptr;
}

template<typename T>
inline void CMyTree<T>::layer_file(const char * szFileName)
{
  if (m_nSize == 0)
  {
    return;
  }

  //����
  CMyQueue<TreeNode *> que;

  //������ڵ�
  que.push(m_pRoot);

  //�ڵ��С��ǰ4���ռ�
  int nDataSize = sizeof(*m_pRoot->data);

  //���ļ�
  FILE *fp = fopen(szFileName, "wb+");
  if (fp == nullptr)
  {
    goto ExitProc;
  }

  //д���С
 if (fwrite(&nDataSize, 4, 1, fp) != 1)
  {
    printf("д���Сʧ��!\r\n");
    goto ExitProc;
  }

  //����
  while (!que.empty())
  {
    //���нڵ�
    TreeNode *pCur = que.front();

    //����
    TreeNode *pLink = pCur;

    //����
    while (pLink != nullptr)
    {
      //������нڵ�
      if (fwrite(pLink->data, nDataSize, 1, fp) != 1)
      {
        printf("д������ʧ��!\r\n");
        goto ExitProc;
      }
      //�����¸��ڵ�
      pLink = pLink->pNext;
    }

    //�������ж�
    if (pCur->pLeftTreeNode != nullptr)
    {
      que.push(pCur->pLeftTreeNode);
    }

    //�������ж�
    if (pCur->pRightTreeNode != nullptr)
    {
      que.push(pCur->pRightTreeNode);
    }

    //ȥ������
    que.pop();
  }

ExitProc:
  if (fp != nullptr)
  {
    fclose(fp);
  }
}

template<typename T>
void CMyTree<T>::DLR(TreeNode * root)
{
  if (root == nullptr)
  {
    return;
  }

  printf("%d ", root->data);
  DLR(root->pLeftTreeNode);
  DLR(root->pRightTreeNode);
}

/*
50
30      70
10  40  60  80

50 30 10 40 70 60 80
//������� <ǰ��>
50                50
70 30             50  30
70 40 10          50  30  10
70 40             50  30  10  40
70                50  30  10  40  70
80 60             50  30  10  40  70  60  80

*/
template<typename T>
void CMyTree<T>::_DLR(TreeNode * root)
{
  if (root == nullptr)
  {
    return;
  }

  CMyStack<TreeNode *> stk;

  stk.push(root);

  while (!stk.empty())
  {
    TreeNode *pCur = stk.top();
    printf("%d ", pCur->data);
    stk.pop();

    if (pCur->pRightTreeNode != nullptr)
    {
      stk.push(pCur->pRightTreeNode);
    }

    if (pCur->pLeftTreeNode != nullptr)
    {
      stk.push(pCur->pLeftTreeNode);
    }

  }


}

template<typename T>
void CMyTree<T>::LDR(TreeNode * root)
{
  if (root == nullptr)
  {
    return;
  }

  LDR(root->pLeftTreeNode);
  printf("%d ", root->data);
  LDR(root->pRightTreeNode);
}

/*
50
30      70
10  40  60  80

10 30 40 50 60 70 80
//������� <����>
50
50 30
50 30 10          10
50 40             10  30
50                10  30  40
70 60             10  30  40  50
70                10  30  40  50  60
80                10  30  40  50  60  70
10  30  40  50  60  70  80
*/
template<typename T>
void CMyTree<T>::_LDR(TreeNode * root)
{
  if (root == nullptr)
  {
    return;
  }

  CMyStack<TreeNode *> stk;

  TreeNode *pLeft = root;

  while (true)
  {
    if (pLeft != nullptr)
    {
      stk.push(pLeft);
      while (pLeft->pLeftTreeNode != nullptr)
      {
        stk.push(pLeft->pLeftTreeNode);
        pLeft = pLeft->pLeftTreeNode;
      }
    }

    if (stk.empty()) break;

    TreeNode *pTop = stk.top();
    printf("%d ", pTop->data);
    stk.pop();

    if (pTop->pRightTreeNode == nullptr)
    {
      pLeft = nullptr;
    }
    else
    {
      pLeft = pTop->pRightTreeNode;
    }

  }

}

template<typename T>
void CMyTree<T>::LRD(TreeNode * root)
{
  if (root == nullptr)
  {
    return;
  }

  LRD(root->pLeftTreeNode);
  LRD(root->pRightTreeNode);
  printf("%d ", root->data);
}

/*
50
30      70
10  40  60  80

10 40 30 60 80 70 50
//������� <����>
50
50 30
50 30 10          10
50 30 40          10 40
50 30             10 40 30
50 70 60          10 40 30 60
50 70 80          10 40 30 60
50 70             10 40 30 60 80
50                10 40 30 60 80 70
10 40 30 60 80 70 50

*/
template<typename T>
void CMyTree<T>::_LRD(TreeNode * root)
{
  if (root == nullptr)
  {
    return;
  }

  CMyStack<TreeNode *> stk;

  TreeNode *pLeft = root;

  TreeNode *pPer = nullptr;

  while (true)
  {
    if (pLeft != nullptr)
    {
      stk.push(pLeft);
      while (pLeft->pLeftTreeNode != nullptr)
      {
        stk.push(pLeft->pLeftTreeNode);
        pLeft = pLeft->pLeftTreeNode;
      }
    }

    if (stk.empty()) break;

    TreeNode *pTop = stk.top();

    if (pTop->pRightTreeNode == pPer || pTop->pRightTreeNode == nullptr)
    {
      printf("%d ", pTop->data);
      pPer = pTop;
      stk.pop();
      pLeft = nullptr;
    }
    else
    {
      pLeft = pTop->pRightTreeNode;
    }
  }
}

template<typename T>
void CMyTree<T>::DRL(TreeNode * root)
{
  if (root == nullptr)
  {
    return;
  }

  printf("%d ", root->data);
  DRL(root->pRightTreeNode);
  DRL(root->pLeftTreeNode);
}

template<typename T>
void CMyTree<T>::RDL(TreeNode * root)
{
  if (root == nullptr)
  {
    return;
  }

  RDL(root->pRightTreeNode);
  printf("%d ", root->data);
  RDL(root->pLeftTreeNode);
}

template<typename T>
void CMyTree<T>::RLD(TreeNode * root)
{
  if (root == nullptr)
  {
    return;
  }

  RLD(root->pRightTreeNode);
  RLD(root->pLeftTreeNode);
  printf("%d ", root->data);
}

template<typename T>
inline T CMyTree<T>::GetMax()
{
  //���ڵ�
  TreeNode* pCur = m_pRoot;
  
  //���ж�
  if (pCur == nullptr)
  {
    return nullptr;
  }

  //���������ҽڵ�
  while (pCur->pRightTreeNode != nullptr)
  {
    pCur = pCur->pRightTreeNode;
  }
  
  //ȡֵ
  return pCur->data;
}

template<typename T>
inline T* CMyTree<T>::GetMin()
{
  return nullptr;
}

template<typename T>
inline int CMyTree<T>::size()
{
  return m_nSize;
}

/*
50
30           70
10    40     60    80
5            55    65
*/
template<typename T>
bool CMyTree<T>::remove(TreeNode * pNode)
{
  //����
  TreeNode *pParent = pNode->pParent;
  //�����
  TreeNode *pLeft = pNode->pLeftTreeNode;
  //�Ҷ���
  TreeNode *pRight = pNode->pRightTreeNode;
  //���ڵ�
  TreeNode *pNext = pNode->pNext;
 
  //һ�����Ӷ�û��
  if (pLeft == nullptr && pRight == nullptr)
  {
    //˵���Ǹ��ڵ�
    if (pParent == nullptr)
    {
      m_pRoot = nullptr;
    }
    else
    {
      //������ÿ�
      if (pParent->pLeftTreeNode == pNode)
      {
        pParent->pLeftTreeNode = nullptr;
      }
      //�Ҷ����ÿ�
      else
      {
        pParent->pRightTreeNode = nullptr;
      }
    }
  }
  //����������
  else if (pLeft != nullptr && pRight != nullptr)
  {
    //����С
    TreeNode *pMin = pRight;

    //����
    while (pMin->pLeftTreeNode != nullptr)
    {
      pMin = pMin->pLeftTreeNode;
    }

    //����
    pNode->data = pMin->data;

    //����
    remove(pMin);

    //����
    return true;
  }
  //ֻ��һ������
  else
  {
    //ֻ�������
    if (pLeft != nullptr)
    {
      pLeft->pParent = pParent;
      pParent->pLeftTreeNode = pLeft;
    }

    //ֻ���Ҷ���
    if (pRight != nullptr)
    {
      pRight->pParent = pParent;
      pParent->pLeftTreeNode = pRight;
    }
  }

  adjustBalance(pNode->pParent);

  if (pNext != nullptr)
  {
    while (pNode != nullptr)
    {
      TreeNode* pTmp = pNode;
      pNode = pNode->pNext;
      delete pTmp;
      m_nSize--;
    }
  }
  else
  {
    delete pNode;
    m_nSize--;
  }

  return true;
}

template<typename T>
bool CMyTree<T>::removeLink(TreeNode * pNode)
{
  if (pNode == nullptr)
  {
    return false;
  }

  TreeNode *pPrev = pNode->pPrev;
  TreeNode *pNext = pNode->pNext;

  if (pPrev == nullptr)
  {//�׽ڵ�
    TreeNode * pCur = pNode;
    while (pCur->pNext != nullptr)
    {
      pCur->data = pCur->pNext->data;
      pCur = pCur->pNext;
    }
    pCur->pPrev->pNext = nullptr;
    pNode = pCur;
  } 
  else
  {
    pPrev->pNext = pNext;
    if (pNext != nullptr)
    {
      pNext->pPrev = pPrev;
    }
  }

  delete pNode;
  m_nSize--;
  return true;
}

/*
50               60
60      =>  50    70
55  70           55

A              B
B           A   C
D C            D
50
55
60
*/
template<typename T>
typename CMyTree<T>::TreeNode* CMyTree<T>::TreeNode::LeftRotate()
{
  TreeNode *pNewRoot = nullptr;
  TreeNode *pP = pParent;
  TreeNode *pA = this;
  TreeNode *pB = pRightTreeNode;
  TreeNode *pC = nullptr;
  TreeNode *pD = nullptr;

  if (pB != nullptr)
  {
    pC = pB->pRightTreeNode;
    pD = pB->pLeftTreeNode;

    pB->pParent = pParent;
    pParent = pB;
    pB->pLeftTreeNode = pA;
    pA->pRightTreeNode = pD;
    if (pD != nullptr)
    {
      pD->pParent = pA;
    }

    if (pP == nullptr)
    {
      pNewRoot = pB;
    }
    else
    {
      if (pP->pLeftTreeNode == pA)
      {
        pP->pLeftTreeNode = pB;
      }
      else
      {
        pP->pRightTreeNode = pB;
      }
    }
  }

  //�������
  pA->nDepath = max(GetDepath(pA->pLeftTreeNode), GetDepath(pD)) + 1;
  pB->nDepath = max(GetDepath(pA), GetDepath(pC)) + 1;

  return pNewRoot;
}


/*
70            60
60        =>  50  70
50  65            65

A             B
B             C   A
C  D              D

D
A    B
B        A

*/
template<typename T>
typename CMyTree<T>::TreeNode* CMyTree<T>::TreeNode::RightRotate()
{
  TreeNode *pNewRoot = nullptr;
  TreeNode *pP = pParent;
  TreeNode *pA = this;
  TreeNode *pB = pLeftTreeNode;
  TreeNode *pC = nullptr;
  TreeNode *pD = nullptr;

  if (pB != nullptr)
  {
    pC = pB->pLeftTreeNode;
    pD = pB->pRightTreeNode;

    pB->pParent = pParent;
    pParent = pB;
    pB->pRightTreeNode = pA;
    pLeftTreeNode = pD;
    if (pD != nullptr)
    {
      pD->pParent = pA;
    }

    if (pP == nullptr)
    {
      pNewRoot = pB;
    }
    else
    {
      if (pP->pLeftTreeNode == pA)
      {
        pP->pLeftTreeNode = pB;
      }
      else
      {
        pP->pRightTreeNode = pB;
      }
    }
  }
  //�������
  nDepath = max(GetDepath(pA->pRightTreeNode), GetDepath(pD)) + 1;
  pB->nDepath = max(GetDepath(pA), GetDepath(pC)) + 1;

  return pNewRoot;
}


template<typename T>
inline int CMyTree<T>::TreeNode::GetDepath(TreeNode* pNode)
{
  return pNode == nullptr ? 0 : pNode->nDepath;;
}
