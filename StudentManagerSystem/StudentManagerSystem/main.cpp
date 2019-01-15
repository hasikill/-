#include <iostream> 
#include <process.h>
#include "CIntegratedMgr.h"

void run(void* p)
{
  CIntegratedMgr* mgr = (CIntegratedMgr*) p;
  while (true)
  {
    mgr->m_StudentMgr->flush();
    mgr->m_SeleCourseMgr->flush();
    _sleep(2000);
  }
}

int main()
{
  //综合管理
  CIntegratedMgr Mgr;

  //初始化
  bool bInit = Mgr.init();

  //初始化成功
  if (bInit)
  {
    _beginthread(run, 0, &Mgr);
    while (true)
    {
      //显示菜单
      CIntegratedMgr::emMgrOption emOption = Mgr.Menu();

      //选择
      switch (emOption)
      {
        case CIntegratedMgr::OPTION_STU:
        {
          //学生管理菜单
          Mgr.m_StudentMgr->Menu();
          break;
        }
        case CIntegratedMgr::OPTION_COURSE:
        {
          //课程管理菜单
          Mgr.m_CourseMgr->Menu();
          break;
        }
        case CIntegratedMgr::OPTION_SELE:
        {
          //选课管理菜单
          Mgr.m_SeleCourseMgr->Menu();
          break;
        }
        case CIntegratedMgr::OPTION_EXIT:
        {
          goto Exit_Point;
          break;
        }
        default:
          printf("没有这个选项!\r\n");
          getchar();
          break;
      }
    }
  }
  else
  {
    printf("初始化失败!\r\n");
  }
Exit_Point:

  getchar();
  return 0;
}