#pragma once
#include "CMyQueue.h"
#include "CMyStack.h"
#include <new>
#include <iostream>
#include <cmath>
#pragma warning(disable:4996)

int max(int a, int b);

//二叉排序树
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

    //左旋
    TreeNode* LeftRotate();

    //右旋
    TreeNode* RightRotate();

    //获取
    int GetDepath(TreeNode *pNode);

    T data;
    TreeNode *pParent;
    TreeNode *pLeftTreeNode;
    TreeNode *pRightTreeNode;
    TreeNode *pNext;
    TreeNode *pPrev;
    //节点的深度
    //等于max(左子节点深度, 右子节点深度) + 1
    int nDepath;
  };

public:
  CMyTree();
  ~CMyTree();

  //销毁
  void destroy();

  //增
  void insert(T&& val);
  void insert(T& val);

  //删
  bool Delete(T data);

  //查
  TreeNode* Find(T data);

  //取节点深度
  int GetDepath(TreeNode *pNode);

  //自平衡
  void adjustBalance(TreeNode *pNode);

  //层序
  void layer();

  //
  T* GetLayer(bool isRoot, CMyQueue<TreeNode *> &que);

  //层序遍历存文件
  void layer_file(const char *szFileName);

  //前序
  void DLR(TreeNode *root);
  void _DLR(TreeNode *root);

  //中序
  void LDR(TreeNode *root);
  void _LDR(TreeNode *root);

  //后序
  void LRD(TreeNode *root);
  void _LRD(TreeNode *root);

  //逆前序
  void DRL(TreeNode *root);

  //逆中序
  void RDL(TreeNode *root);

  //逆后序
  void RLD(TreeNode *root);

  //获取最大元素
  T GetMax();
  
  //获取最大元素
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
  //跟节点
  TreeNode *m_pRoot;
  //数量
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
  //新节点
  TreeNode *pNew = new TreeNode(val);

  if (pNew == nullptr)
  {
    throw std::bad_alloc();
  }

  //添加到根节点
  if (m_pRoot == nullptr)
  {
    m_pRoot = pNew;
    m_nSize++;
    return;
  }

  //现行节点
  TreeNode *pCur = m_pRoot;

  //
  while (true)
  {
    if (*pNew->data > pCur->data)
    {
      //放右边
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
      //放左边
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
      //遍历尾部
      while (pCur->pNext != nullptr)
      {
        pCur = pCur->pNext;
      }
      //等于
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
  //新节点
  TreeNode *pNew = new TreeNode(val);

  if (pNew == nullptr)
  {
    throw std::bad_alloc();
  }

  //添加到根节点
  if (m_pRoot == nullptr)
  {
    m_pRoot = pNew;
    m_nSize++;
    return;
  }

  //现行节点
  TreeNode *pCur = m_pRoot;

  //
  while (true)
  {
    if (*pNew->data > pCur->data)
    {
      //放右边
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
      //放左边
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
      //遍历尾部
      while (pCur->pNext != nullptr)
      {
        pCur = pCur->pNext;
      }
      //等于
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
  //先找到
  TreeNode *pCur = Find(data);
  if (pCur == nullptr)
  {
    //找不到
    return false;
  }

  //链表中查找
  if (pCur->pNext == nullptr)
  {
    //找到了
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

    //求差值
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

      //开始旋转
      //判断4种情况
      //左单旋
      /*
      pK1
      pK2
      pK3
      */
      if (pK2 == pK1->pRightTreeNode && pK3 == pK2->pRightTreeNode) {
        pNewRoot = pK1->LeftRotate();
      }


      //右单旋
      /*
      pK1
      pK2
      pK3
      */
      if (pK2 == pK1->pLeftTreeNode && pK3 == pK2->pLeftTreeNode) {
        pNewRoot = pK1->RightRotate();
      }

      //右左双旋
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

      //左右双旋
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

//广度搜索 <层序>
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

  //队列
  CMyQueue<TreeNode *> que;

  //加入根节点
  que.push(m_pRoot);

  //遍历
  while (!que.empty())
  {
    //现行节点
    TreeNode *pCur = que.front();

    //输出现行节点
    printf("%d ", pCur->data);

    //左子树判断
    if (pCur->pLeftTreeNode != nullptr)
    {
      que.push(pCur->pLeftTreeNode);
    }

    //右子树判断
    if (pCur->pRightTreeNode != nullptr)
    {
      que.push(pCur->pRightTreeNode);
    }

    //去除队首
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
    //加入根节点
    que.push(m_pRoot);
  }
  

  //遍历
  if (!que.empty())
  {
    //现行节点
    TreeNode *pCur = que.front();

    //拿出数据
    T* tmp = &pCur->data;

    //左子树判断
    if (pCur->pLeftTreeNode != nullptr)
    {
      que.push(pCur->pLeftTreeNode);
    }

    //右子树判断
    if (pCur->pRightTreeNode != nullptr)
    {
      que.push(pCur->pRightTreeNode);
    }

    //去除队首
    que.pop();

    //返回数据
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

  //队列
  CMyQueue<TreeNode *> que;

  //加入根节点
  que.push(m_pRoot);

  //节点大小存前4个空间
  int nDataSize = sizeof(*m_pRoot->data);

  //打开文件
  FILE *fp = fopen(szFileName, "wb+");
  if (fp == nullptr)
  {
    goto ExitProc;
  }

  //写入大小
 if (fwrite(&nDataSize, 4, 1, fp) != 1)
  {
    printf("写入大小失败!\r\n");
    goto ExitProc;
  }

  //遍历
  while (!que.empty())
  {
    //现行节点
    TreeNode *pCur = que.front();

    //链表
    TreeNode *pLink = pCur;

    //遍历
    while (pLink != nullptr)
    {
      //输出现行节点
      if (fwrite(pLink->data, nDataSize, 1, fp) != 1)
      {
        printf("写入数据失败!\r\n");
        goto ExitProc;
      }
      //遍历下个节点
      pLink = pLink->pNext;
    }

    //左子树判断
    if (pCur->pLeftTreeNode != nullptr)
    {
      que.push(pCur->pLeftTreeNode);
    }

    //右子树判断
    if (pCur->pRightTreeNode != nullptr)
    {
      que.push(pCur->pRightTreeNode);
    }

    //去除队首
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
//深度搜索 <前序>
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
//深度搜索 <中序>
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
//深度搜索 <后序>
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
  //根节点
  TreeNode* pCur = m_pRoot;
  
  //空判断
  if (pCur == nullptr)
  {
    return nullptr;
  }

  //遍历到最右节点
  while (pCur->pRightTreeNode != nullptr)
  {
    pCur = pCur->pRightTreeNode;
  }
  
  //取值
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
  //父亲
  TreeNode *pParent = pNode->pParent;
  //左儿子
  TreeNode *pLeft = pNode->pLeftTreeNode;
  //右儿子
  TreeNode *pRight = pNode->pRightTreeNode;
  //链节点
  TreeNode *pNext = pNode->pNext;
 
  //一个儿子都没有
  if (pLeft == nullptr && pRight == nullptr)
  {
    //说明是根节点
    if (pParent == nullptr)
    {
      m_pRoot = nullptr;
    }
    else
    {
      //左儿子置空
      if (pParent->pLeftTreeNode == pNode)
      {
        pParent->pLeftTreeNode = nullptr;
      }
      //右儿子置空
      else
      {
        pParent->pRightTreeNode = nullptr;
      }
    }
  }
  //有两个儿子
  else if (pLeft != nullptr && pRight != nullptr)
  {
    //找最小
    TreeNode *pMin = pRight;

    //遍历
    while (pMin->pLeftTreeNode != nullptr)
    {
      pMin = pMin->pLeftTreeNode;
    }

    //交换
    pNode->data = pMin->data;

    //销毁
    remove(pMin);

    //返回
    return true;
  }
  //只有一个儿子
  else
  {
    //只有左儿子
    if (pLeft != nullptr)
    {
      pLeft->pParent = pParent;
      pParent->pLeftTreeNode = pLeft;
    }

    //只有右儿子
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
  {//首节点
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

  //修正深度
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
  //修正深度
  nDepath = max(GetDepath(pA->pRightTreeNode), GetDepath(pD)) + 1;
  pB->nDepath = max(GetDepath(pA), GetDepath(pC)) + 1;

  return pNewRoot;
}


template<typename T>
inline int CMyTree<T>::TreeNode::GetDepath(TreeNode* pNode)
{
  return pNode == nullptr ? 0 : pNode->nDepath;;
}
