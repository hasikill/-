#pragma once
#include "CStudentMgr.h"
#include "CCourseMgr.h"

#define FILE_SELECOURSETREE  "./SelectCourseTree.dat"

class CSeleCourseMgr
{
public:
  struct tagSeleCourse
  {
    tagSeleCourse()
    {
      m_nStuId = 0;
      m_nCourseId = 0;
      m_nGrade = 0;
    }

    tagSeleCourse(int nStuId, int nCourseId, int nGrade)
    {
      m_nStuId = nStuId;
      m_nCourseId = nCourseId;
      m_nGrade = nGrade;
    }

    int m_nStuId;
    int m_nCourseId;
    int m_nGrade;
  };

  struct tagSeleCourseStuId : public tagSeleCourse
  {
    tagSeleCourseStuId() { };

    tagSeleCourseStuId(int nStuId, int nCourseId, int nGrade) : tagSeleCourse(nStuId, nCourseId, nGrade) {  }

    bool operator>(tagSeleCourseStuId& obj)
    {
      return m_nStuId > obj.m_nStuId;
    }

    bool operator>(tagSeleCourseStuId* obj)
    {
      return m_nStuId > obj->m_nStuId;
    }

    bool operator<(tagSeleCourseStuId& obj)
    {
      return m_nStuId < obj.m_nStuId;
    }

    bool operator<(tagSeleCourseStuId* obj)
    {
      return m_nStuId < obj->m_nStuId;
    }

    bool operator==(tagSeleCourseStuId& obj)
    {
      return m_nStuId == obj.m_nStuId && m_nCourseId == obj.m_nCourseId;
    }

    bool operator==(tagSeleCourseStuId* obj)
    {
      return m_nStuId == obj->m_nStuId && m_nCourseId == obj->m_nCourseId;
    }
  };

  struct tagSeleCourseCourseId : public tagSeleCourse
  {
    tagSeleCourseCourseId() { };

    tagSeleCourseCourseId(int nStuId, int nCourseId, int nGrade) : tagSeleCourse(nStuId, nCourseId, nGrade) {  }

    bool operator>(tagSeleCourseCourseId& obj)
    {
      return m_nCourseId > obj.m_nCourseId;
    }

    bool operator>(tagSeleCourseCourseId* obj)
    {
      return m_nCourseId > obj->m_nCourseId;
    }

    bool operator<(tagSeleCourseCourseId& obj)
    {
      return m_nCourseId < obj.m_nCourseId;
    }

    bool operator<(tagSeleCourseCourseId* obj)
    {
      return m_nCourseId < obj->m_nCourseId;
    }

    bool operator==(tagSeleCourseCourseId& obj)
    {
      return m_nStuId == obj.m_nStuId && m_nCourseId == obj.m_nCourseId;
    }

    bool operator==(tagSeleCourseCourseId* obj)
    {
      return m_nStuId == obj->m_nStuId && m_nCourseId == obj->m_nCourseId;
    }
  };

public:
  CSeleCourseMgr(CStudentMgr* stumgr, CCourseMgr* coursemgr);
  ~CSeleCourseMgr();

  //增加选课
  int AddSeleCourse(int nStuId, int nCourseId, int nGrade);

  //删除选课
  bool DelSeleCourse(int nStuId, int nCourseId);

  //选课管理菜单
  void Menu();

  //查找课程 
  CMyList<tagSeleCourse*> FindSeleCourse(int nStuId, int nCourseId);

  //显示单个课程
  void ShowSeleCourses(tagSeleCourse* stu);

  //显示课程集合
  void ShowSeleCourses(CMyList<tagSeleCourse*> list);

  //显示全部
  void ShowSeleCourses();

  void flush();

private:
  void write();
  void read();
  void generate();

private:
  //学生管理
  CStudentMgr* m_StudentMgr;
  //课程管理
  CCourseMgr* m_CourseMgr;
  //学生ID
  CMyTree<tagSeleCourseStuId *> m_SeleCourseStuIdTree;
  //课程ID
  CMyTree<tagSeleCourseCourseId *> m_SeleCourseCourseTree;
  //是否修改
  bool isChange;
};

