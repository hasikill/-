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
  //�ۺϹ���
  CIntegratedMgr Mgr;

  //��ʼ��
  bool bInit = Mgr.init();

  //��ʼ���ɹ�
  if (bInit)
  {
    _beginthread(run, 0, &Mgr);
    while (true)
    {
      //��ʾ�˵�
      CIntegratedMgr::emMgrOption emOption = Mgr.Menu();

      //ѡ��
      switch (emOption)
      {
        case CIntegratedMgr::OPTION_STU:
        {
          //ѧ������˵�
          Mgr.m_StudentMgr->Menu();
          break;
        }
        case CIntegratedMgr::OPTION_COURSE:
        {
          //�γ̹���˵�
          Mgr.m_CourseMgr->Menu();
          break;
        }
        case CIntegratedMgr::OPTION_SELE:
        {
          //ѡ�ι���˵�
          Mgr.m_SeleCourseMgr->Menu();
          break;
        }
        case CIntegratedMgr::OPTION_EXIT:
        {
          goto Exit_Point;
          break;
        }
        default:
          printf("û�����ѡ��!\r\n");
          getchar();
          break;
      }
    }
  }
  else
  {
    printf("��ʼ��ʧ��!\r\n");
  }
Exit_Point:

  getchar();
  return 0;
}