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
  //��ʼ��ѧ��
  printf("��ʼ��ѧ��...\r\n");
  m_StudentMgr = new CStudentMgr();
  if (m_StudentMgr == nullptr)
  {
    return false;
  }
  printf("��ʼ��ѧ���ɹ�!\r\n");

  //��ʼ���γ�
  printf("��ʼ���γ�...\r\n");
  m_CourseMgr = new CCourseMgr();
  if (m_CourseMgr == nullptr)
  {
    return false;
  }
  printf("��ʼ���γ̳ɹ�!\r\n");

  //��ʼ��ѡ�μ�¼
  printf("��ʼ��ѡ�μ�¼...\r\n");
  m_SeleCourseMgr = new CSeleCourseMgr(m_StudentMgr, m_CourseMgr);
  if (m_SeleCourseMgr == nullptr)
  {
    return false;
  }
  printf("��ʼ��ѡ�μ�¼�ɹ�!\r\n");
  //���
  printf("��ʼ�����...");
  return true;
}

CIntegratedMgr::emMgrOption CIntegratedMgr::Menu()
{
  system("cls");

  printf("    �ۺ�ѧ������ϵͳ\r\n");
  printf("\r\n");
  printf("      1.ѧ������\r\n\r\n");
  printf("      2.�γ̹���\r\n\r\n");
  printf("      3.ѡ�ι���\r\n\r\n");
  printf("      0.�˳�\r\n\r\n");
  printf("\r\n");
  printf("���������,���س�ѡ��:");

  int nOption = 0;

  scanf("%d", &nOption);
  
  return (emMgrOption)nOption;
}
