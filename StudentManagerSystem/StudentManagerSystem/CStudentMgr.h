#pragma once
#include "CMyTree.h"
#include "CMystring.h"
#include "CMyList.h"

#define FILE_STUTREE  "./StudentTree.dat"
#define STUID_START   1000

class CStudentMgr
{
public:
  struct tagStudent
  {
    tagStudent()
    {
      m_nId = 0;
      memset(m_szName, 0, 20);
    }

    tagStudent(int nId, const char* szName)
    {
      m_nId = nId;
      strcpy(m_szName, szName);
    }

    int m_nId;
    char m_szName[20];
  };

  struct tagStudentId : public tagStudent
  {
    tagStudentId() { };

    tagStudentId(int nId, const char* szName) : tagStudent(nId, szName) {  }

    bool operator>(tagStudentId& obj)
    {
      return m_nId > obj.m_nId;
    }
    
    bool operator>(tagStudentId* obj)
    {
      return m_nId > obj->m_nId;
    }

    bool operator<(tagStudentId& obj)
    {
      return m_nId < obj.m_nId;
    }

    bool operator<(tagStudentId* obj)
    {
      return m_nId < obj->m_nId;
    } 

    bool operator==(tagStudentId& obj)
    {
      return m_nId == obj.m_nId;
    }

    bool operator==(tagStudentId* obj)
    {
      return m_nId == obj->m_nId;
    }
  }; 

  struct tagStudentName : public tagStudent
  {

    tagStudentName() {}

    tagStudentName(int nId, const char* szName) : tagStudent(nId, szName) {  }

    bool operator>(tagStudentName& obj)
    {
      return strcmp(m_szName, obj.m_szName) > 0;
    }

    bool operator>(tagStudentName* obj)
    {
      return strcmp(m_szName, obj->m_szName) > 0;
    }

    bool operator<(tagStudentName& obj)
    {
      return strcmp(m_szName, obj.m_szName) < 0;;
    }

    bool operator<(tagStudentName* obj)
    {
      return strcmp(m_szName, obj->m_szName) < 0;;
    }

    bool operator==(tagStudentName* obj)
    {
      return strcmp(m_szName, obj->m_szName) == 0 && m_nId == obj->m_nId;;
    }

    bool operator==(tagStudentName& obj)
    {
      return strcmp(m_szName, obj.m_szName) == 0 && m_nId == obj.m_nId;;
    }
  };
public:
  CStudentMgr();
  ~CStudentMgr();

  //����ѧ��
  int AddStudent(const char* szName);

  //ɾ��ѧ��
  bool DelStudent(int nId);

  //ѧ������˵�
  void Menu();

  //����ѧ�� 
  tagStudent* FindStudent(int nId);

  //����ѧ�� 
  CMyList<tagStudent*> FindStudent(const char* szName);

  //��ʾ����ѧ��
  void ShowStus(tagStudent* stu);
  
  //��ʾѧ������
  void ShowStus(CMyList<tagStudent*> list);

  //��ʾȫ��
  void ShowStus();

  //ѧ������
  int StuCount();

  void flush();

private:
  void write();
  void read();
  void generate();

public:
  //IdΪ����
  CMyTree<tagStudentId*> m_StudentIdTree;
  //����Ϊ����
  CMyTree<tagStudentName*> m_StudentNameTree;
  //�Ƿ��޸�
  bool isChange;
};

