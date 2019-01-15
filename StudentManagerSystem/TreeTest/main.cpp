#include <iostream>
#include "CStudentMgr.h"

int main()
{
  CStudentMgr mgr;

  mgr.ShowStus(mgr.FindStudent("ут╫П╨ю"));

  mgr.m_StudentNameTree.Delete(&CStudentMgr::tagStudentName(7904, "ут╫П╨ю"));

  mgr.ShowStus(mgr.FindStudent("ут╫П╨ю"));

  mgr.m_StudentNameTree.Delete(&CStudentMgr::tagStudentName(36647, "ут╫П╨ю"));

  mgr.ShowStus(mgr.FindStudent("ут╫П╨ю"));

  mgr.m_StudentNameTree.Delete(&CStudentMgr::tagStudentName(100314, "ут╫П╨ю"));

  mgr.ShowStus(mgr.FindStudent("ут╫П╨ю"));

  getchar();
  return 0;
}