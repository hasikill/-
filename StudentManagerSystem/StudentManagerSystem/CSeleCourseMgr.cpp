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

    printf("    选课管理\r\n");
    printf("\r\n");
    printf("      1.增加选课\r\n\r\n");
    printf("      2.删除选课\r\n\r\n");
    printf("      3.查询选课\r\n\r\n");
    printf("      0.返回上一级\r\n\r\n");
    printf("\r\n");
    printf("请输入序号,按回车选择:");

    scanf("%d", &nOption);
    getchar();

    int nStuId = 0;
    int nCourseId = 0;
    int nGrade = 0;

    switch (nOption)
    {
    case 1:
    {
      printf("请输入学生Id:");
      scanf("%d", &nStuId);
      printf("请输入课程Id:");
      scanf("%d", &nCourseId);
      printf("请输入成绩:");
      scanf("%d", &nGrade);
      getchar();
      //检查有效性
      CStudentMgr::tagStudent *pStu = m_StudentMgr->FindStudent(nStuId);
      CCourseMgr::tagCourse *pCourse = m_CourseMgr->FindCourse(nCourseId);
      if (pStu == nullptr)
      {
        printf("没有这个学生!\r\n");
      }
      if (pCourse == nullptr)
      {
        printf("没有这个课程!\r\n");
      }
      if (pStu != nullptr && pCourse != nullptr)
      {
        //添加选课
        int nTid = AddSeleCourse(nStuId, nCourseId, nGrade);
        tagSeleCourse obj(nStuId, nCourseId, nGrade);
        ShowSeleCourses(&obj);
        printf("添加成功!\r\n\r\n");
      }
      getchar();
    }
    break;
    case 2:
    {
      printf("请输入学生Id:");
      scanf("%d", &nStuId);
      printf("请输入课程Id:");
      scanf("%d", &nCourseId);
      getchar();

      CStudentMgr::tagStudent *pStu = m_StudentMgr->FindStudent(nStuId);
      CCourseMgr::tagCourse *pCourse = m_CourseMgr->FindCourse(nCourseId);
      if (pStu == nullptr)
      {
        printf("没有这个学生!\r\n");
      }
      else if (pCourse == nullptr)
      {
        printf("没有这个课程!\r\n");
      }
      else
      {
        if (DelSeleCourse(nStuId, nCourseId))
        {

          printf("%s\t%s\r\n", pStu->m_szName, pCourse->m_strName.GetStr());
          printf("删除成功!\r\n");
        }
      }
      getchar();
    }
    break;
    case 3:
    {
      system("cls");
      printf("\r\n");
      printf("1.通过学生ID查选课\r\n\r\n");
      printf("2.通过课程ID查选课\r\n\r\n");
      printf("3.查看选课\r\n\r\n");
      printf("0.返回上一级\r\n\r\n");
      printf("\r\n");
      printf("请输入序号,按回车选择:");

      scanf("%d", &nOption);
      getchar();

      switch (nOption)
      {
      case 1:
      {
        printf("请输入学生Id:");
        scanf("%d", &nStuId);
        ShowSeleCourses(FindSeleCourse(nStuId, 0));
        getchar();
      }
      break;
      case 2:
      {
        printf("请输入课程Id:");
        scanf("%d", &nCourseId);
        ShowSeleCourses(FindSeleCourse(0, nCourseId));
        getchar();
      }
      break;
      case 3:
      {
        //显示选课
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
      //跳出循环
      goto Exit_Point;
    }
    break;
    default:
      printf("没有这个选项!\r\n");
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
    //遍历
    while (pNode != nullptr)
    {
      CourseList.push_back(pNode->data);
      //往下迭代
      pNode = pNode->pNext;
    }
  }
  else
  {
    CMyTree<tagSeleCourseStuId*>::TreeNode *pNode = m_SeleCourseStuIdTree.Find(&tagSeleCourseStuId(nStuId, 0, 0));
    //遍历
    while (pNode != nullptr)
    {
      CourseList.push_back(pNode->data);
      //往下迭代
      pNode = pNode->pNext;
    }
  }

  return CourseList;
}

void CSeleCourseMgr::ShowSeleCourses(tagSeleCourse * seleCourse)
{
  system("cls");
  printf("\r\n学生ID\t\t学生名\t\t%-20s成绩\r\n", "选课名");
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
  printf("按任意键继续...");
  getchar();
}

void CSeleCourseMgr::ShowSeleCourses(CMyList<tagSeleCourse*> list)
{
  system("cls");
  printf("\r\n学生ID\t\t学生名\t\t%-20s成绩\r\n", "选课名");
  printf("-------------------------------------------------------------\r\n\r\n");
  if (!list.empty())
  {
    for (tagSeleCourse* seleCourse : list)
    {
      CStudentMgr::tagStudent* pStu = m_StudentMgr->FindStudent(seleCourse->m_nStuId);
      CCourseMgr::tagCourse* pCourse = m_CourseMgr->FindCourse(seleCourse->m_nCourseId);
      if (pStu == nullptr || pCourse == nullptr)
      {//说明已经无效可以删除
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
  printf("按任意键继续...");
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
  //写到文件
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

  //读出大小
  if (fread(&nObjSize, 4, 1, fp) != 1)
  {
    printf("读出数量失败!");
    goto ExitProc;
  }

  //读取
  while (feof(fp) == 0) {
    //临时对象
    tagSeleCourseStuId *obj = new tagSeleCourseStuId();

    if (fread(obj, nObjSize, 1, fp) != 1)
    {
      goto ExitProc;
    }

    //读取成功,构建树
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
  //遍历学生
  do
  {
    //学生ID
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
