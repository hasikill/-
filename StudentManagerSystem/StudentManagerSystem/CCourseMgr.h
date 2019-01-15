#pragma once
#include <iostream>
#include "CMystring.h"
#include "CMyList.h"
#include "CMyTree.h"

#define FILE_COURSETREE  "./CourseTree.dat"
#define COURSEID_START   1000

class CCourseMgr
{
public:
  //�ڴ�洢
  struct tagCourse
  {
    tagCourse()
    {
      m_nId = 0;
    }

    tagCourse(int nId, const char* szName)
    {
      m_nId = nId;
      m_strName = szName;
    }

    tagCourse(int nId, CMystring szName)
    {
      m_nId = nId;
      m_strName = szName;
    }

    int m_nId;
    CMystring m_strName;
  };

  struct tagCourseId : public tagCourse
  {
    tagCourseId() { };

    tagCourseId(int nId, const char* szName) : tagCourse(nId, szName) {  }

    tagCourseId(int nId, CMystring szName) : tagCourse(nId, szName) {  }

    bool operator>(tagCourseId& obj)
    {
      return m_nId > obj.m_nId;
    }

    bool operator>(tagCourseId* obj)
    {
      return m_nId > obj->m_nId;
    }

    bool operator<(tagCourseId& obj)
    {
      return m_nId < obj.m_nId;
    }

    bool operator<(tagCourseId* obj)
    {
      return m_nId < obj->m_nId;
    }

    bool operator==(tagCourseId& obj)
    {
      return m_nId == obj.m_nId;
    }

    bool operator==(tagCourseId* obj)
    {
      return m_nId == obj->m_nId;
    }
  };

  //�ļ��洢
  struct tagFileCourse
  {
    tagFileCourse()
    {
      m_nSize = 8;
      m_nId = 0;
      m_szName = nullptr;
    }

    tagFileCourse(tagCourse& course)
    {
      m_nId = course.m_nId;
      m_szName = course.m_strName.GetStr();
      m_nSize = 8 + course.m_strName.GetStrlen();
    }

    tagFileCourse& operator=(tagCourse& course)
    {
      m_nId = course.m_nId;
      m_szName = course.m_strName.GetStr();
      m_nSize = 8 + course.m_strName.GetStrlen();
    }

    int m_nSize;
    int m_nId;
    char *m_szName;
  };

  struct tagCourseName : public tagCourse
  {

    tagCourseName() {}

    tagCourseName(int nId, const char* szName) : tagCourse(nId, szName) {  }

    tagCourseName(int nId, CMystring szName) : tagCourse(nId, szName) {  }

    bool operator>(tagCourseName& obj)
    {
      return m_strName.Cmp(obj.m_strName) > 0;
    }

    bool operator>(tagCourseName* obj)
    {
      return m_strName.Cmp(obj->m_strName) > 0;
    }

    bool operator<(tagCourseName& obj)
    {
      return m_strName.Cmp(obj.m_strName) < 0;;
    }

    bool operator<(tagCourseName* obj)
    {
      return m_strName.Cmp(obj->m_strName) < 0;;
    }

    bool operator==(tagCourseName* obj)
    {
      return m_strName.Cmp(obj->m_strName) == 0 && m_nId == obj->m_nId;;
    }

    bool operator==(tagCourseName& obj)
    {
      return m_strName.Cmp(obj.m_strName) == 0 && m_nId == obj.m_nId;;
    }
  };
public:
  CCourseMgr();
  ~CCourseMgr();

  //���ӿγ�
  int AddCourse(const char* szName);

  //ɾ���γ�
  bool DelCourse(int nId);

  //�γ̹���˵�
  void Menu();

  //���ҿγ� 
  tagCourse* FindCourse(int nId);

  //���ҿγ� 
  CMyList<tagCourse*> FindCourse(const char* szName);

  //��ʾ�����γ�
  void ShowCourses(tagCourse* stu);

  //��ʾ�γ̼���
  void ShowCourses(CMyList<tagCourse*> list);

  //��ʾȫ��
  void ShowCourses();

  //
  void ObjToFileObj(tagCourse *pCourse, tagFileCourse *pFileCourse);

  void flush();

private:
  void write();
  void read();
  void generate();

public:
  //IdΪ����
  CMyTree<tagCourseId*> m_CourseIdTree;
  //����Ϊ����
  CMyTree<tagCourseName*> m_CourseNameTree;
  //�Ƿ��޸�
  bool isChange;
};

