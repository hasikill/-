#include "CStudentMgr.h"
#include <time.h>
#pragma warning(disable:4996)

const char *xing = {
  "赵钱孙李周吴郑王冯陈褚卫蒋沈韩杨朱秦尤许何吕施张孔曹严华金魏陶姜戚谢邹喻柏水窦章云苏潘葛奚范彭郎鲁韦昌马苗凤花方俞任袁柳酆鲍史唐费廉岑薛雷贺倪汤滕殷罗毕郝邬安常\
乐于时傅皮卞齐康\
伍余元卜顾孟平黄\
和穆萧尹姚邵湛汪\
祁毛禹狄米贝明臧\
计伏成戴谈宋茅庞\
熊纪舒屈项祝董梁\
杜阮蓝闵席季麻强\
贾路娄危江童颜郭\
梅盛林刁钟徐邱骆\
高夏蔡田樊胡凌霍\
虞万支柯昝管卢莫\
经房裘缪干解应宗\
丁宣贲邓郁单杭洪\
包诸左石崔吉钮龚\
程嵇邢滑裴陆荣翁\
荀羊於惠甄曲家封\
芮羿储靳汲邴糜松\
井段富巫乌焦巴弓\
牧隗山谷车侯宓蓬\
全郗班仰秋仲伊宫\
宁仇栾暴甘钭厉戎\
祖武符刘景詹束龙\
叶幸司韶郜黎蓟薄\
印宿白怀蒲邰从鄂\
索咸籍赖卓蔺屠蒙\
池乔阴鬱胥能苍双\
闻莘党翟谭贡劳逄\
姬申扶堵冉宰郦雍\
卻璩桑桂濮牛寿通\
边扈燕冀郏浦尚农\
温别庄晏柴瞿阎充\
慕连茹习宦艾鱼容\
向古易慎戈廖庾终\
暨居衡步都耿满弘\
匡国文寇广禄阙东\
欧殳沃利蔚越夔隆\
师巩厍聂晁勾敖融\
冷訾辛阚那简饶空\
曾毋沙乜养鞠须丰\
巢关蒯相查后荆红\
游竺权逯盖益桓公\
万俟司马上官欧阳\
夏侯诸葛闻人东方\
赫连皇甫尉迟公羊\
澹台公冶宗政濮阳\
淳于单于太叔申屠\
公孙仲孙轩辕令狐\
钟离宇文长孙慕容\
鲜于闾丘司徒司空\
丌官司寇仉督子车\
颛孙端木巫马公西\
漆雕乐正壤驷公良\
拓跋夹谷宰父谷梁\
晋楚闫法汝鄢涂钦\
段干百里东郭南门\
呼延归海羊舌微生\
岳帅缑亢况郈有琴\
梁丘左丘东门西门\
商牟佘佴伯赏南宫\
墨哈谯笪年爱阳佟第五言福"
};

const char* ming[] = 
{
  "一", "二", "三", "四", "五", "六", "七", "八", "九", "十",
  "金豪","金豪","金豪","金豪", "宇", "涛", "丽丽", "爸爸", "爷爷"
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
  //新id
  int nId = STUID_START;
  //查找最大ID
  tagStudentId *tmp = m_StudentIdTree.GetMax();
  if (tmp != nullptr)
  {
    nId = tmp->m_nId + 1;
  }
  //学生对象
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
    //写文件
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

    printf("    学生管理\r\n");
    printf("\r\n");
    printf("      1.增加学生\r\n\r\n");
    printf("      2.删除学生\r\n\r\n");
    printf("      3.查询学生\r\n\r\n");
    printf("      0.返回上一级\r\n\r\n");
    printf("\r\n");
    printf("请输入序号,按回车选择:");

    scanf("%d", &nOption);
    getchar();

    int nId = 0;
    char szName[20] = { 0 };

    switch (nOption)
    {
    case 1:
    {
      printf("请输入学生姓名:");
      scanf("%20s", szName);
      getchar();
      //添加学生
      int nTid = AddStudent(szName);
      if (nTid != 0)
      {
        printf("\r\n%d\t\t%s\r\n", nTid, szName);
        printf("添加成功!\r\n\r\n");
      }
      getchar();
    }
    break;
    case 2:
    {
      printf("请输入学号:");
      scanf("%d", &nId);
      getchar();

      tagStudent *pStu = FindStudent(nId);
      if (pStu != nullptr)
      {
        printf("\r\n%d\t\t%s\r\n", pStu->m_nId, pStu->m_szName);
        if (DelStudent(nId))
        {
          printf("删除成功!");
        }
      }
      else
      {
        printf("没有这个学生!\r\n");
      }
      getchar();
    }
    break;
    case 3:
    {
      system("cls");
      printf("\r\n");
      printf("1.通过学生ID查询学生\r\n\r\n");
      printf("2.通过学生姓名查询学生\r\n\r\n");
      printf("3.查看学生\r\n\r\n");
      printf("0.返回上一级\r\n\r\n");
      printf("\r\n");
      printf("请输入序号,按回车选择:");

      scanf("%d", &nOption);
      getchar();

      switch (nOption)
      {
        case 1:
        {
          printf("请输入学号:");
          scanf("%d", &nId);
          ShowStus(FindStudent(nId));
        }
        break;
        case 2:
        {
          printf("请输入学生姓名:");
          scanf("%20s", szName);
          ShowStus(FindStudent(szName));
        }
        break;
        case 3:
        {
          //显示学生
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

CStudentMgr::tagStudent * CStudentMgr::FindStudent(int nId)
{
  CMyTree<tagStudentId*>::TreeNode *pNode = m_StudentIdTree.Find(&tagStudentId(nId, ""));
  return pNode == nullptr ? nullptr : pNode->data;
}

CMyList<CStudentMgr::tagStudent*> CStudentMgr::FindStudent(const char * szName)
{
  CMyList<CStudentMgr::tagStudent*> StuList;

  CMyTree<tagStudentName*>::TreeNode *pNode = m_StudentNameTree.Find(&tagStudentName(0, szName));

  //遍历
  while (pNode != nullptr)
  {
    StuList.push_back(pNode->data);
    //往下迭代
    pNode = pNode->pNext;
  }
  return StuList;
}

void CStudentMgr::ShowStus(tagStudent * stu)
{
  system("cls");
  printf("\r\n%s\t\t%s\r\n", "学号", "姓名");
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
  printf("按任意键继续...");
  getchar();
}

void CStudentMgr::ShowStus(CMyList<tagStudent*> list)
{
  system("cls");
  printf("\r\n%s\t\t%s\r\n", "学号", "姓名");
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
  printf("按任意键继续...");
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
  //写到文件
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

  //读出大小
  if (fread(&nObjSize, 4, 1, fp) != 1)
  {
    printf("读出数量失败!");
    goto ExitProc;
  }

  //读取
  while (feof(fp) == 0) {
    //临时对象
    tagStudentId *obj = new tagStudentId();

    if (fread(obj, nObjSize, 1, fp) != 1)
    {
      goto ExitProc;
    }

    //读取成功,构建树
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
    //姓
    char tmpBuf[3] = { 0 };
    memcpy(tmpBuf, &xing[(rand() % nXingCount) * 2], 2);
    //名字
    strcpy(szName, tmpBuf);
    strcat(szName, ming[rand() % nMingCount]);
    //插入树
    m_StudentIdTree.insert(new tagStudentId(STUID_START + i, szName));
  }
}
