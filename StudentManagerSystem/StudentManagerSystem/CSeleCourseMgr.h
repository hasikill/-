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

  //����ѡ��
  int AddSeleCourse(int nStuId, int nCourseId, int nGrade);

  //ɾ��ѡ��
  bool DelSeleCourse(int nStuId, int nCourseId);

  //ѡ�ι���˵�
  void Menu();

  //���ҿγ� 
  CMyList<tagSeleCourse*> FindSeleCourse(int nStuId, int nCourseId);

  //��ʾ�����γ�
  void ShowSeleCourses(tagSeleCourse* stu);

  //��ʾ�γ̼���
  void ShowSeleCourses(CMyList<tagSeleCourse*> list);

  //��ʾȫ��
  void ShowSeleCourses();

  void flush();

private:
  void write();
  void read();
  void generate();

private:
  //ѧ������
  CStudentMgr* m_StudentMgr;
  //�γ̹���
  CCourseMgr* m_CourseMgr;
  //ѧ��ID
  CMyTree<tagSeleCourseStuId *> m_SeleCourseStuIdTree;
  //�γ�ID
  CMyTree<tagSeleCourseCourseId *> m_SeleCourseCourseTree;
  //�Ƿ��޸�
  bool isChange;
};

