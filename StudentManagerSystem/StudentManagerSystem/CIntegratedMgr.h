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

  //初始化
  bool init();

  //菜单
  emMgrOption Menu();

public:
  //学生管理
  CStudentMgr* m_StudentMgr;
  //课程管理
  CCourseMgr* m_CourseMgr;
  //选课管理
  CSeleCourseMgr* m_SeleCourseMgr;
};