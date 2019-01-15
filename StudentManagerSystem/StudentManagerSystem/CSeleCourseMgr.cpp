#include "CSeleCourseMgr.h"
#include <time.h>


CSeleCourseMgr::CSeleCourseMgr(CStudentMgr* stumgr, CCourseMgr* coursemgr)
{
  m_StudentMgr = stumgr;
  m_CourseMgr = coursemgr;
  isChange = false;

  FILE *fp = fopen(FILE_SELECOURSETREE, "r");
  if (fp == nullptr)
  {
    generate();
    write();
  }
  else
  {
    read();
    fclose(fp);
  }

}


CSeleCourseMgr::~CSeleCourseMgr()
{
  if (isChange)
  {
    write();
  }
}

int CSeleCourseMgr::AddSeleCourse(int nStuId, int nCourseId, int nGrade)
{
  m_SeleCourseStuIdTree.insert(new tagSeleCourseStuId(nStuId, nCourseId, nGrade));
  m_SeleCourseCourseTree.insert(new tagSeleCourseCourseId(nStuId, nCourseId, nGrade));
  isChange = true;
  return 0;
}

bool CSeleCourseMgr::DelSeleCourse(int nStuId, int nSeleCourseId)
{
  m_SeleCourseStuIdTree.Delete(&tagSeleCourseStuId(nStuId, nSeleCourseId, 0));
  m_SeleCourseCourseTree.Delete(&tagSeleCourseCourseId(nStuId, nSeleCourseId, 0));
  isChange = true;
  return true;
}

void CSeleCourseMgr::Menu()
{
  int nOption = 0;

  while (true)
  {
    system("cls");

    printf("    ѡ�ι���\r\n");
    printf("\r\n");
    printf("      1.����ѡ��\r\n\r\n");
    printf("      2.ɾ��ѡ��\r\n\r\n");
    printf("      3.��ѯѡ��\r\n\r\n");
    printf("      0.������һ��\r\n\r\n");
    printf("\r\n");
    printf("���������,���س�ѡ��:");

    scanf("%d", &nOption);
    getchar();

    int nStuId = 0;
    int nCourseId = 0;
    int nGrade = 0;

    switch (nOption)
    {
    case 1:
    {
      printf("������ѧ��Id:");
      scanf("%d", &nStuId);
      printf("������γ�Id:");
      scanf("%d", &nCourseId);
      printf("������ɼ�:");
      scanf("%d", &nGrade);
      getchar();
      //�����Ч��
      CStudentMgr::tagStudent *pStu = m_StudentMgr->FindStudent(nStuId);
      CCourseMgr::tagCourse *pCourse = m_CourseMgr->FindCourse(nCourseId);
      if (pStu == nullptr)
      {
        printf("û�����ѧ��!\r\n");
      }
      if (pCourse == nullptr)
      {
        printf("û������γ�!\r\n");
      }
      if (pStu != nullptr && pCourse != nullptr)
      {
        //���ѡ��
        int nTid = AddSeleCourse(nStuId, nCourseId, nGrade);
        tagSeleCourse obj(nStuId, nCourseId, nGrade);
        ShowSeleCourses(&obj);
        printf("��ӳɹ�!\r\n\r\n");
      }
      getchar();
    }
    break;
    case 2:
    {
      printf("������ѧ��Id:");
      scanf("%d", &nStuId);
      printf("������γ�Id:");
      scanf("%d", &nCourseId);
      getchar();

      CStudentMgr::tagStudent *pStu = m_StudentMgr->FindStudent(nStuId);
      CCourseMgr::tagCourse *pCourse = m_CourseMgr->FindCourse(nCourseId);
      if (pStu == nullptr)
      {
        printf("û�����ѧ��!\r\n");
      }
      else if (pCourse == nullptr)
      {
        printf("û������γ�!\r\n");
      }
      else
      {
        if (DelSeleCourse(nStuId, nCourseId))
        {

          printf("%s\t%s\r\n", pStu->m_szName, pCourse->m_strName.GetStr());
          printf("ɾ���ɹ�!\r\n");
        }
      }
      getchar();
    }
    break;
    case 3:
    {
      system("cls");
      printf("\r\n");
      printf("1.ͨ��ѧ��ID��ѡ��\r\n\r\n");
      printf("2.ͨ���γ�ID��ѡ��\r\n\r\n");
      printf("3.�鿴ѡ��\r\n\r\n");
      printf("0.������һ��\r\n\r\n");
      printf("\r\n");
      printf("���������,���س�ѡ��:");

      scanf("%d", &nOption);
      getchar();

      switch (nOption)
      {
      case 1:
      {
        printf("������ѧ��Id:");
        scanf("%d", &nStuId);
        ShowSeleCourses(FindSeleCourse(nStuId, 0));
        getchar();
      }
      break;
      case 2:
      {
        printf("������γ�Id:");
        scanf("%d", &nCourseId);
        ShowSeleCourses(FindSeleCourse(0, nCourseId));
        getchar();
      }
      break;
      case 3:
      {
        //��ʾѡ��
        ShowSeleCourses();
      }
      break;
      case 0:
      {
        break;
      }
      }

      
    }
    break;
    case 0:
    {
      //����ѭ��
      goto Exit_Point;
    }
    break;
    default:
      printf("û�����ѡ��!\r\n");
      getchar();
      break;
    }
  }
Exit_Point:
  ;
}

CMyList<CSeleCourseMgr::tagSeleCourse*> CSeleCourseMgr::FindSeleCourse(int nStuId, int nCourseId)
{
  CMyList<CSeleCourseMgr::tagSeleCourse*> CourseList;

  if (nCourseId != 0)
  {
    CMyTree<tagSeleCourseCourseId*>::TreeNode *pNode = m_SeleCourseCourseTree.Find(&tagSeleCourseCourseId(0, nCourseId, 0));
    //����
    while (pNode != nullptr)
    {
      CourseList.push_back(pNode->data);
      //���µ���
      pNode = pNode->pNext;
    }
  }
  else
  {
    CMyTree<tagSeleCourseStuId*>::TreeNode *pNode = m_SeleCourseStuIdTree.Find(&tagSeleCourseStuId(nStuId, 0, 0));
    //����
    while (pNode != nullptr)
    {
      CourseList.push_back(pNode->data);
      //���µ���
      pNode = pNode->pNext;
    }
  }

  return CourseList;
}

void CSeleCourseMgr::ShowSeleCourses(tagSeleCourse * seleCourse)
{
  system("cls");
  printf("\r\nѧ��ID\t\tѧ����\t\t%-20s�ɼ�\r\n", "ѡ����");
  printf("-------------------------------------------------------------\r\n\r\n");
  if (seleCourse != nullptr)
  {
    CStudentMgr::tagStudent* pStu = m_StudentMgr->FindStudent(seleCourse->m_nStuId);
    CCourseMgr::tagCourse* pCourse = m_CourseMgr->FindCourse(seleCourse->m_nCourseId);
    printf("%d\t\t%s\t\t%-20s%d\r\n", pStu->m_nId, pStu->m_szName, pCourse->m_strName.GetStr(), seleCourse->m_nGrade);
  }
  else
  {
    printf("NONE!\r\n");
  }
  printf("\r\n-------------------------------------------------------------\r\n\r\n");
  printf("�����������...");
  getchar();
}

void CSeleCourseMgr::ShowSeleCourses(CMyList<tagSeleCourse*> list)
{
  system("cls");
  printf("\r\nѧ��ID\t\tѧ����\t\t%-20s�ɼ�\r\n", "ѡ����");
  printf("-------------------------------------------------------------\r\n\r\n");
  if (!list.empty())
  {
    for (tagSeleCourse* seleCourse : list)
    {
      CStudentMgr::tagStudent* pStu = m_StudentMgr->FindStudent(seleCourse->m_nStuId);
      CCourseMgr::tagCourse* pCourse = m_CourseMgr->FindCourse(seleCourse->m_nCourseId);
      if (pStu == nullptr || pCourse == nullptr)
      {//˵���Ѿ���Ч����ɾ��
        DelSeleCourse(seleCourse->m_nStuId, seleCourse->m_nCourseId);
      }
      else
      {
        printf("%d\t\t%s\t\t%-20s%d\r\n", pStu->m_nId, pStu->m_szName, pCourse->m_strName.GetStr(), seleCourse->m_nGrade);
      }
    }
  }
  else
  {
    printf("NONE!\r\n");
  }
  printf("\r\n-------------------------------------------------------------\r\n\r\n");
  printf("�����������...");
  getchar();
}

void CSeleCourseMgr::ShowSeleCourses()
{
}

void CSeleCourseMgr::flush()
{
  if (isChange)
  {
    write();
  }
}

void CSeleCourseMgr::write()
{
  //д���ļ�
  m_SeleCourseStuIdTree.layer_file(FILE_SELECOURSETREE);
  isChange = false;
}

void CSeleCourseMgr::read()
{
  int nObjSize = 0;

  FILE *fp = fopen(FILE_SELECOURSETREE, "rb");
  if (fp == nullptr)
  {
    goto ExitProc;
  }

  //������С
  if (fread(&nObjSize, 4, 1, fp) != 1)
  {
    printf("��������ʧ��!");
    goto ExitProc;
  }

  //��ȡ
  while (feof(fp) == 0) {
    //��ʱ����
    tagSeleCourseStuId *obj = new tagSeleCourseStuId();

    if (fread(obj, nObjSize, 1, fp) != 1)
    {
      goto ExitProc;
    }

    //��ȡ�ɹ�,������
    m_SeleCourseStuIdTree.insert(obj);
    m_SeleCourseCourseTree.insert(new tagSeleCourseCourseId(obj->m_nStuId, obj->m_nCourseId, obj->m_nGrade));
  }

ExitProc:
  if (fp != nullptr)
  {
    fclose(fp);
  }
}

void CSeleCourseMgr::generate()
{
  srand((unsigned int)time(NULL));
  CMyQueue<CMyTree<CStudentMgr::tagStudentId *>::TreeNode*> que;
  CStudentMgr::tagStudentId ** pCur = m_StudentMgr->m_StudentIdTree.GetLayer(true, que);
  //����ѧ��
  do
  {
    //ѧ��ID
    int nStuId = (*pCur)->m_nId;
    //
    for (int i = 0; i < 10; i++)
    {
      int nCourseId = (rand() % 1300) + 1000;
      int nGrade = rand() % 100;
      m_SeleCourseStuIdTree.insert(new tagSeleCourseStuId(nStuId, nCourseId, nGrade));
      m_SeleCourseCourseTree.insert(new tagSeleCourseCourseId(nStuId, nCourseId, nGrade));
    }
    
  } while ((pCur = m_StudentMgr->m_StudentIdTree.GetLayer(false, que)) != nullptr);
  
}
