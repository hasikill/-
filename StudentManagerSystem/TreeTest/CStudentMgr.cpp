#include "CStudentMgr.h"
#include <time.h>
#pragma warning(disable:4996)

const char *xing = {
  "��Ǯ��������֣��������������������������ʩ�ſײ��ϻ���κ�ս���л������ˮ��������˸��ɷ�����³Τ������ﻨ������Ԭ��ۺ��ʷ�Ʒ����Ѧ�׺����������ޱϺ�������\
����ʱ��Ƥ���뿵\
����Ԫ������ƽ��\
��������Ҧ��տ��\
��ë����ױ����\
�Ʒ��ɴ�̸��é��\
�ܼ�������ף����\
��������ϯ����ǿ\
��·¦Σ��ͯ�չ�\
÷ʢ�ֵ���������\
���Ĳ��﷮�����\
����֧���ù�¬Ī\
�������Ѹɽ�Ӧ��\
�����ڵ���������\
������ʯ�޼�ť��\
�����ϻ���½����\
����춻������ҷ�\
���ഢ����������\
���θ����ڽ��͹�\
����ɽ�ȳ������\
ȫۭ������������\
�����ﱩ��������\
���������ղ����\
Ҷ��˾��۬�輻��\
ӡ�ް׻���ۢ�Ӷ�\
���̼���׿������\
�������d���ܲ�˫\
��ݷ����̷������\
�������Ƚ��۪Ӻ\
�s�ɣ���ţ��ͨ\
�����༽ۣ����ũ\
�±�ׯ�̲����ֳ�\
Ľ����ϰ�°�����\
���������������\
�߾Ӻⲽ��������\
����Ŀܹ�»�ڶ�\
ŷ�����εԽ��¡\
ʦ�������˹�����\
���������Ǽ��Ŀ�\
����ɳؿ�������\
���������󾣺�\
����Ȩ�ָ��滸��\
��ٹ˾���Ϲ�ŷ��\
�ĺ�������˶���\
�����ʸ�ξ�ٹ���\
�̨��ұ�������\
���ڵ���̫������\
����������ԯ���\
�������ĳ���Ľ��\
��������˾ͽ˾��\
آ��˾���붽�ӳ�\
����ľ������\
����������ṫ��\
�ذϼй��׸�����\
�����Ʒ���۳Ϳ��\
�θɰ��ﶫ������\
���ӹ麣����΢��\
��˧�ÿ����C����\
��������������\
��Ĳ��٦�����Ϲ�\
ī�������갮��١�����Ը�"
};

const char* ming[] = 
{
  "һ", "��", "��", "��", "��", "��", "��", "��", "��", "ʮ",
  "���","���","���","���", "��", "��", "����", "�ְ�", "үү"
};

CStudentMgr::CStudentMgr()
{
  FILE *fp = fopen(FILE_STUTREE, "r");
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

CStudentMgr::~CStudentMgr()
{
}

int CStudentMgr::AddStudent(const char * szName)
{
  //��id
  int nId = STUID_START;
  //�������ID
  tagStudentId *tmp = m_StudentIdTree.GetMax();
  if (tmp != nullptr)
  {
    nId = tmp->m_nId + 1;
  }
  //ѧ������
  tagStudentId *stu = new tagStudentId(nId, szName);
  if (stu != nullptr)
  {
    m_StudentIdTree.insert(stu);
    m_StudentNameTree.insert(new tagStudentName(nId, szName));
    write();
    return nId;
  }
  return 0;
}

bool CStudentMgr::DelStudent(int nId)
{
  tagStudent *pStu = FindStudent(nId);
  bool bRet = false;
  if (pStu != nullptr)
  {
    bRet = m_StudentIdTree.Delete(&tagStudentId(nId, ""));
    m_StudentNameTree.Delete(&tagStudentName(pStu->m_nId, pStu->m_szName));
  }
  if (bRet != false)
  {
    //д�ļ�
    write();
  }
  return bRet;
}

void CStudentMgr::Menu()
{
  int nOption = 0;

  while (true)
  {
    system("cls");

    printf("    ѧ������\r\n");
    printf("\r\n");
    printf("      1.����ѧ��\r\n\r\n");
    printf("      2.ɾ��ѧ��\r\n\r\n");
    printf("      3.��ѯѧ��\r\n\r\n");
    printf("      0.������һ��\r\n\r\n");
    printf("\r\n");
    printf("���������,���س�ѡ��:");

    scanf("%d", &nOption);
    getchar();

    int nId = 0;
    char szName[20] = { 0 };

    switch (nOption)
    {
    case 1:
    {
      printf("������ѧ������:");
      scanf("%20s", szName);
      getchar();
      //���ѧ��
      int nTid = AddStudent(szName);
      if (nTid != 0)
      {
        printf("\r\n%d\t\t%s\r\n", nTid, szName);
        printf("��ӳɹ�!\r\n\r\n");
      }
      getchar();
    }
    break;
    case 2:
    {
      printf("������ѧ��:");
      scanf("%d", &nId);
      getchar();

      tagStudent *pStu = FindStudent(nId);
      if (pStu != nullptr)
      {
        printf("\r\n%d\t\t%s\r\n", pStu->m_nId, pStu->m_szName);
        if (DelStudent(nId))
        {
          printf("ɾ���ɹ�!");
        }
      }
      else
      {
        printf("û�����ѧ��!\r\n");
      }
      getchar();
    }
    break;
    case 3:
    {
      system("cls");
      printf("\r\n");
      printf("1.ͨ��ѧ��ID��ѯѧ��\r\n\r\n");
      printf("2.ͨ��ѧ��������ѯѧ��\r\n\r\n");
      printf("3.�鿴ѧ��\r\n\r\n");
      printf("0.������һ��\r\n\r\n");
      printf("\r\n");
      printf("���������,���س�ѡ��:");

      scanf("%d", &nOption);
      getchar();

      switch (nOption)
      {
        case 1:
        {
          printf("������ѧ��:");
          scanf("%d", &nId);
          ShowStus(FindStudent(nId));
        }
        break;
        case 2:
        {
          printf("������ѧ������:");
          scanf("%20s", szName);
          ShowStus(FindStudent(szName));
        }
        break;
        case 3:
        {
          //��ʾѧ��
          ShowStus();
        }
        break;
        case 0:
        {
          break;
        }
      }

      getchar();
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

CStudentMgr::tagStudent * CStudentMgr::FindStudent(int nId)
{
  CMyTree<tagStudentId*>::TreeNode *pNode = m_StudentIdTree.Find(&tagStudentId(nId, ""));
  return pNode == nullptr ? nullptr : pNode->data;
}

CMyList<CStudentMgr::tagStudent*> CStudentMgr::FindStudent(const char * szName)
{
  CMyList<CStudentMgr::tagStudent*> StuList;

  CMyTree<tagStudentName*>::TreeNode *pNode = m_StudentNameTree.Find(&tagStudentName(0, szName));

  //����
  while (pNode != nullptr)
  {
    StuList.push_back(pNode->data);
    //���µ���
    pNode = pNode->pNext;
  }
  return StuList;
}

void CStudentMgr::ShowStus(tagStudent * stu)
{
  system("cls");
  printf("\r\n%s\t\t%s\r\n", "ѧ��", "����");
  printf("-------------------------------\r\n\r\n");
  if (stu != nullptr)
  {
    printf("%d\t\t%s\r\n", stu->m_nId, stu->m_szName);
  }
  else
  {
    printf("NONE!\r\n");
  }
  printf("\r\n-------------------------------\r\n\r\n");
  printf("�����������...");
  getchar();
}

void CStudentMgr::ShowStus(CMyList<tagStudent*> list)
{
  system("cls");
  printf("\r\n%s\t\t%s\r\n", "ѧ��", "����");
  printf("-------------------------------\r\n\r\n");
  if (!list.empty())
  {
    for (tagStudent* stu : list)
    {
      printf("%d\t\t%s\r\n", stu->m_nId, stu->m_szName);
    }
  }
  else
  {
    printf("NONE!\r\n");
  }
  printf("\r\n-------------------------------\r\n\r\n");
  printf("�����������...");
  getchar();
}

void CStudentMgr::ShowStus()
{
}

int CStudentMgr::StuCount()
{
  return m_StudentIdTree.size();
}

void CStudentMgr::write()
{
  //д���ļ�
  m_StudentIdTree.layer_file(FILE_STUTREE);
}

void CStudentMgr::read()
{
  int nObjSize = 0;

  FILE *fp = fopen(FILE_STUTREE, "rb");
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
    tagStudentId *obj = new tagStudentId();

    if (fread(obj, nObjSize, 1, fp) != 1)
    {
      goto ExitProc;
    }

    //��ȡ�ɹ�,������
    m_StudentIdTree.insert(obj);
    m_StudentNameTree.insert(new tagStudentName(obj->m_nId, obj->m_szName));
  }

ExitProc:
  if (fp != nullptr)
  {
    fclose(fp);
  }
}

void CStudentMgr::generate()
{
  char szName[20] = { 0 };

  srand((unsigned int)time(NULL));

  int nXingCount = strlen(xing) / 2;
  int nMingCount = sizeof(ming) / 4;

  for (int i = 0; i < 100000; i++)
  {
    //��
    char tmpBuf[3] = { 0 };
    memcpy(tmpBuf, &xing[(rand() % nXingCount) * 2], 2);
    //����
    strcpy(szName, tmpBuf);
    strcat(szName, ming[rand() % nMingCount]);
    //������
    m_StudentIdTree.insert(new tagStudentId(STUID_START + i, szName));
  }
}
