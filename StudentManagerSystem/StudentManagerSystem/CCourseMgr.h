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
  //内存存储
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

  //文件存储
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

  //增加课程
  int AddCourse(const char* szName);

  //删除课程
  bool DelCourse(int nId);

  //课程管理菜单
  void Menu();

  //查找课程 
  tagCourse* FindCourse(int nId);

  //查找课程 
  CMyList<tagCourse*> FindCourse(const char* szName);

  //显示单个课程
  void ShowCourses(tagCourse* stu);

  //显示课程集合
  void ShowCourses(CMyList<tagCourse*> list);

  //显示全部
  void ShowCourses();

  //
  void ObjToFileObj(tagCourse *pCourse, tagFileCourse *pFileCourse);

  void flush();

private:
  void write();
  void read();
  void generate();

public:
  //Id为索引
  CMyTree<tagCourseId*> m_CourseIdTree;
  //名字为索引
  CMyTree<tagCourseName*> m_CourseNameTree;
  //是否修改
  bool isChange;
};

