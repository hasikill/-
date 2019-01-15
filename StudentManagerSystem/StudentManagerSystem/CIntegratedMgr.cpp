#include "CIntegratedMgr.h"



CIntegratedMgr::CIntegratedMgr()
{
  m_StudentMgr = nullptr;
  m_CourseMgr = nullptr;
  m_SeleCourseMgr = nullptr;
}


CIntegratedMgr::~CIntegratedMgr()
{
  if (m_StudentMgr != nullptr)
  {
    delete m_StudentMgr;
  }
  if (m_CourseMgr != nullptr)
  {
    delete m_CourseMgr;
  }
  if (m_SeleCourseMgr != nullptr)
  {
    delete m_SeleCourseMgr;
  }
}

bool CIntegratedMgr::init()
{
  //初始化学生
  printf("初始化学生...\r\n");
  m_StudentMgr = new CStudentMgr();
  if (m_StudentMgr == nullptr)
  {
    return false;
  }
  printf("初始化学生成功!\r\n");

  //初始化课程
  printf("初始化课程...\r\n");
  m_CourseMgr = new CCourseMgr();
  if (m_CourseMgr == nullptr)
  {
    return false;
  }
  printf("初始化课程成功!\r\n");

  //初始化选课纪录
  printf("初始化选课纪录...\r\n");
  m_SeleCourseMgr = new CSeleCourseMgr(m_StudentMgr, m_CourseMgr);
  if (m_SeleCourseMgr == nullptr)
  {
    return false;
  }
  printf("初始化选课纪录成功!\r\n");
  //完成
  printf("初始化完毕...");
  return true;
}

CIntegratedMgr::emMgrOption CIntegratedMgr::Menu()
{
  system("cls");

  printf("    综合学生管理系统\r\n");
  printf("\r\n");
  printf("      1.学生管理\r\n\r\n");
  printf("      2.课程管理\r\n\r\n");
  printf("      3.选课管理\r\n\r\n");
  printf("      0.退出\r\n\r\n");
  printf("\r\n");
  printf("请输入序号,按回车选择:");

  int nOption = 0;

  scanf("%d", &nOption);
  
  return (emMgrOption)nOption;
}
