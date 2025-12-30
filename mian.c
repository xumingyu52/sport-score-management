#include "information.h"  
#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 

struct student *tou1 = NULL; 

int xitong();
int xitong_xiao();
void zijian();
int gong1(); //1.新增学生信息
int gong2(); //2.删除学生
int gong3(); //3.查询学生信息
void gong4(); //4.显示学生信息
int gong5(); //5.修改学生信息
int gong8(); //8.排序
int gong9();

int main()
{
   
    int chengji[7] = {81,82,83,84,85,86};
    struct student *zhangsan = create_student_node(
    "张三",
    31230,
    "信管4252",
    "2025级",
    170,66,
    "男",
    chengji,
    58
    );
    insert_student_list_tail(&tou1, zhangsan);
    //创建一个学生的信息

    zijian();//判断该使用那种系统使用

    return 0;
}


void zijian() 
{
    
    int xuanze;
    // 自检：检查链表中是否有学生信息
    while (1)
    {
        system("cls");

        if (tou1 == NULL)
        {
            printf("系统自检：未发现已存储的学生信息\n");
            printf("----------------------------------------\n");
            xuanze = xitong_xiao();  // 显示简化菜单（只有新增和退出）
        }

        else
        {
            printf("系统自检：发现已存储的学生信息\n");
            printf("----------------------------------------\n");
            xuanze = xitong();  // 显示完整菜单
        }

    if(xuanze == 0)
    {
        printf("系统已退出,感谢您的使用");
        break;
    }
    
    else if(xuanze == 1)
    {
        gong1();
        continue;
    }

    else if(xuanze == 2)
    {
        gong2();
        continue;
    }


    else if(xuanze == 3)
    {
        gong3();       
        continue;
    }


    else if(xuanze == 4)
    {


    }


    else if(xuanze == 5)
    {
        gong5();
        continue;
    }


    else if(xuanze == 6)
    {


    }


    else if(xuanze == 7)
    {


    }


    else if(xuanze == 8)
    {
        gong8();
        continue;
    }


    else if(xuanze == 9)
    {
        gong9();
        continue;
    }


    else if(xuanze == 10)
    {


    }


    else
    {printf("输入数字无效");}
        

    }
}



int xitong_xiao()
{
int xuanze;

printf("---------------学生成绩管理系统---------\n");

printf("-----------------1.新增学生信息-------------------------------\n");

printf("-----------------0.Quit the System-------------------------\n");

printf("请输入对应数字以使用相应功能");

scanf("%d", &xuanze);
    
return xuanze;
}



int xitong()  
{
    int xuanze;

printf("---------------学生成绩管理系统---------\n");

printf("-----------------1.新增学生信息-------------------------------\n");//

printf("-----------------2.删除学生信息---------------------------\n");//

printf("-----------------3.查询学生信息(姓名)-------------------------------\n");//

printf("-----------------4.显示学生信息--------------------------------\n");

printf("-----------------5.修改学生成绩--------------------------------\n");

printf("-----------------6.统计各项目平均分-----项---数数------------------------\n");

printf("-----------------7.保存----------------------------------\n");

printf("-----------------8.按总成绩排序排序-------------------------------\n");

printf("-----------------9.按单科成绩排序-------------------------------\n");

printf("-----------------10.输出为csv文件-------------------------------\n");

printf("-----------------10.计算单科平均分-------------------------------\n");

printf("-----------------0.Quit the System-------------------------\n");//

printf("请输入对应数字以使用相应功能");

scanf("%d", &xuanze);
    


return xuanze;

}

int gong1()//1.新增学生信息
{
    char xingming[20];
    long int xuehao;
    char banji[10],nianji[10];
    int shengao,tizhong;
    char xingbie[5];
    int chengji[6];
    int zongfen;




    printf("请输入您要添加的学生的姓名,或输入0退出");
    scanf("%s",xingming);

    if(strcmp(xingming, "0") == 0)
    {return 0;}

    printf("请输入您要添加的学生的学号");
    scanf("%ld",&xuehao);

    printf("请输入您要添加的学生的班级");
    scanf("%s",banji);

    printf("请输入您要添加的学生的年级");
    scanf("%s",nianji);

    printf("请输入您要添加的学生的身高");
    scanf("%d",&shengao);

    printf("请输入您要添加的学生的体重");
    scanf("%d",&tizhong);

    printf("请输入您要添加的学生的性别");
    scanf("%s",xingbie);

    printf("请输入您要添加的学生的总分");
    scanf("%d",&zongfen);

    printf("请输入您要添加的学生的BMI的分数");
    scanf("%d",&chengji[0]);

    printf("请输入您要添加的学生的肺活量的分数");
    scanf("%d",&chengji[1]);

    printf("请输入您要添加的学生的50m跑的分数");
    scanf("%d",&chengji[2]);

    printf("请输入您要添加的学生的立定跳远的分数");
    scanf("%d",&chengji[3]);

    printf("请输入您要添加的学生的引体向上的分数");
    scanf("%d",&chengji[4]);

    printf("请输入您要添加的学生的1000m跑的分数");
    scanf("%d",&chengji[5]);


    struct student *xingtianjia = create_student_node(
    xingming,
    xuehao,
    banji,
    nianji,
    shengao,
    tizhong,
    xingbie,
    chengji,
    zongfen
    );

    insert_student_list_tail(&tou1,xingtianjia);
    
    printf("注意:系统不会自动保存,请前往菜单栏手动进行保存");
    printf("添加成功,请按任意键返回");
    getchar();
    getchar();
    return 0;
}

int gong2() //删除学生
{
    char xingming[20];
    int i =1;

    while(1)
    {

        printf("请输入您要删除的学生的姓名,或输入0退出");
        scanf("%s",xingming);

        if(strcmp(xingming, "0") == 0)
        {return 0;}

        //先查找
        struct student *chaxun = search_student_list(&tou1,xingming);

        if(chaxun == NULL)  // 如果没找到
        {
            printf("没有找到这个学生\n");
            continue;
        }

        else  // 如果找到了
        {
            // 需要先知道这个学生是第几个
            int i = 1;
            struct student *temp = tou1;
            
            while(temp != chaxun)  // 遍历，直到找到目标节点
            {
                temp = temp->next;
                i++;
            }
            
            // 删除
            delete_student_list_node(&tou1, i);
            printf("删除成功,请按任意键返回\n");
            getchar();
            getchar();
            return 0;
            }
    }


}

int gong3()//3.查询学生信息(姓名)
{

    char xingming[20];
    int i = 0;

    while (getchar() != '\n');//清空缓冲区

    while(1)
    {
        printf("请输入您要查询的学生的姓名,或输入0退出");
        scanf("%s",xingming);

        if(strcmp(xingming, "0") == 0)
        {return 0;}

        struct student *chadao = search_student_list(&tou1,xingming);

        if(chadao != NULL)
        {
            printf("\n=== 学生信息如下 ===\n");

            printf("\n学生 %s\n学号 %ld\n班级 %s\n年级 %s\n身高 %d\n体重 %d\n总分 %d\n",
            chadao->name,
            chadao->school_number,
            chadao->class_name,
            chadao->grade,
            chadao->height,
            chadao->weight,
            chadao->total_score
            );

            printf("各项目分数分别为\n");
            while(i<6)
            {
                printf("%s---%d分\n",
                    chadao->project_name[i],
                    chadao->project_score[i]
                    );
                i++;
            }

            printf("请输入任意键退出");
            getchar();
            getchar();
            return 0;

        }
        else
        {
            printf("未查找到该学生的个人信息,请输入任意键返回\n");
            getchar();
            getchar();
            continue;
        }
    }
}
/**
* @brief 显示学生信息
* @param 二级头指针
*/
void gong4(struct student **head)
{
    if (*head == NULL)
    printf("当前无信息。\n");
    else{
        printf("\t姓名\t学号\t班级\t年级\t身高\t体重\t性别\tBMI\t肺活量\t50m跑\t立定跳远\t引体向上\\仰卧起坐\t1000米跑\\800米跑\t总分\n");
        struct student* current = *head;
        while (current != NULL)
        {
            //姓名 学号 班级 年级 身高 体重 性别 BMI 肺活量 50 立定 引体 1000
            printf("\t%s\t%ld\t%s\t%s\t%d\t%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
            current->name,current->school_number,current->class_name,
            current->grade,current->height,current->weight,
            current->sex,current->project_score[0],current->project_score[1],
            current->project_score[2],current->project_score[3],current->project_score[4],
            current->project_score[5],current->total_score);
            
            current = current->next;
         
        printf("显示完毕！");
        }
    }
    
}

int gong5()
{
    char xingming[20],xin[20];
    int haoma;

    while(1)
    {

        printf("请输入您要修改的学生的姓名,或输入0退出");
        scanf("%s",xingming);

        if(strcmp(xingming, "0") == 0)
        {return 0;}

        printf("1.姓名\t\t2.学号\t\t3.班级\n");
        printf("4.年级\t\t5.身高\t\t6.体重\n");
        printf("7.性别\t\t8.BMI\t\t9.肺活量\n");
        printf("10.50m跑\t11.立定跳远\t12.引体向上(仰卧起坐)\n");
        printf("13.1000米跑(800米跑)");
        printf("\n请输入您要修改的信息的编号:");
        scanf("%d",&haoma);

        if(haoma > 13 || haoma < 1)
        {
            printf("\n您输入的编号不存在,请重新输入");
            continue;
        }

        printf("\n请输入您修改后的数据:");
        scanf("%s",xin);

        modify_student_info(&tou1,xingming,haoma,xin);

        printf("\n修改成功,请输入任意键退出");
        getchar();
        getchar();
        return 0;
    }
}


int gong8() //排名
{
    int paiming = 1;
    struct student *fuzhi = copy_student_list(tou1);

    sort_student_list(&fuzhi,1,0);
    
    while(1)
    {
        if(fuzhi != NULL)
        {
            printf("%d.%s\t%d\n",paiming,fuzhi->name,fuzhi->total_score);
            fuzhi = fuzhi->next;
            paiming++;
        }
       ar();
    }   
    return 0;
}


int gong9() //单科排序
{
    int paiming = 1,kemu;
    struct student *fuzhi = copy_student_list(tou1);
    printf("请输入您要排序的科目的序号");
    printf("1.BMI\t2.肺活量\n3.50m跑\t4.立定跳远\n5.引体向上(仰卧起坐)\t6.1000米跑(800米跑)\n");
    scanf("%d",&kemu);

    sort_student_list(&fuzhi,2,kemu);
    printf("---------------------------------------------\n");
    printf("  姓名\t科目成绩\n");

    while(1)
    {
        if(fuzhi != NULL)
        {
            printf("%d.%s\t %d\n",paiming,fuzhi->name,fuzhi->project_score[kemu]);
            fuzhi = fuzhi->next;
            paiming++;
        }
        else 
        {break;}
    }

    printf("排序完成,请输入任意键退出");
    getchar();
    getchar();   
    return 0;
}