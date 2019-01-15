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

  //增加学生
  int AddStudent(const char* szName);

  //删除学生
  bool DelStudent(int nId);

  //学生管理菜单
  void Menu();

  //查找学生 
  tagStudent* FindStudent(int nId);

  //查找学生 
  CMyList<tagStudent*> FindStudent(const char* szName);

  //显示单个学生
  void ShowStus(tagStudent* stu);
  
  //显示学生集合
  void ShowStus(CMyList<tagStudent*> list);

  //显示全部
  void ShowStus();

  //学生数量
  int StuCount();

  void flush();

private:
  void write();
  void read();
  void generate();

public:
  //Id为索引
  CMyTree<tagStudentId*> m_StudentIdTree;
  //名字为索引
  CMyTree<tagStudentName*> m_StudentNameTree;
  //是否修改
  bool isChange;
};

