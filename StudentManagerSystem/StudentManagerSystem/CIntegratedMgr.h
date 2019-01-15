#pragma once
#include "CStudentMgr.h"
#include "CCourseMgr.h"
#include "CSeleCourseMgr.h"
class CIntegratedMgr
{
public:
  enum emMgrOption
  {
    OPTION_EXIT,
    OPTION_STU,
    OPTION_COURSE,
    OPTION_SELE
  };
public:
  CIntegratedMgr();
  ~CIntegratedMgr();

  //��ʼ��
  bool init();

  //�˵�
  emMgrOption Menu();

public:
  //ѧ������
  CStudentMgr* m_StudentMgr;
  //�γ̹���
  CCourseMgr* m_CourseMgr;
  //ѡ�ι���
  CSeleCourseMgr* m_SeleCourseMgr;
};