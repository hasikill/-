#include <iostream>
#include "CStudentMgr.h"

int main()
{
  CStudentMgr mgr;

  mgr.ShowStus(mgr.FindStudent("�Խ��"));

  mgr.m_StudentNameTree.Delete(&CStudentMgr::tagStudentName(7904, "�Խ��"));

  mgr.ShowStus(mgr.FindStudent("�Խ��"));

  mgr.m_StudentNameTree.Delete(&CStudentMgr::tagStudentName(36647, "�Խ��"));

  mgr.ShowStus(mgr.FindStudent("�Խ��"));

  mgr.m_StudentNameTree.Delete(&CStudentMgr::tagStudentName(100314, "�Խ��"));

  mgr.ShowStus(mgr.FindStudent("�Խ��"));

  getchar();
  return 0;
}