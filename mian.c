#include "information.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int xitong();
int xitong_xiao();
int gong1(struct student **tou1); // 2.删除学生
int gong2(struct student **tou1);
int gong3(struct student **tou1); // 3.查询学生信息
void gong4(struct student **head); // 4.显示学生信息
int gong5(struct student **tou1); // 5.修改学生信息
int gong8(struct student **tou1); // 8.按总分排序
int gong9(struct student **tou1); // 9.按单项科目排序
int gong10(struct student **tou1); // 10.将数据输出为csv文件
int gong11(struct student **tou1); // 11.保存数据

//int main() {
//    int chengji[7] = {81, 82, 83, 84, 85, 86};
//    struct student *zhangsan = create_student_node(
//        "张三", 31230, "信管4252", "2025级", 170, 66, "男", chengji, 58);
//    insert_student_list_tail(&tou1, zhangsan);
//    zijian();
//    return 0;
//}

int main() {
    // 检测文件
    struct student *tou1 = NULL;
    tou1 = load_student_list_from_file("students.dat");
    int xuanze;
    while (1) {
        system("cls");
        if (tou1 == NULL) {
            printf("系统自检：未检测到已存储的学生信息\n");
            printf("请确保文件在程序所在文件夹中\n");
            printf("----------------------------------------\n");
            xuanze = xitong_xiao();
        } else {
            printf("系统自检：检测到已存储的学生信息\n");
            printf("----------------------------------------\n");
            xuanze = xitong();
        }
        if (xuanze == 0) {
            printf("系统已退出, 谢谢您的使用\n");
            //清空链表
            delete_student_list(&tou1);
            break;
        } else if (xuanze == 1) {
            gong1(&tou1);
        } else if (xuanze == 2) {
            gong2(&tou1);
        } else if (xuanze == 3) {
            gong3(&tou1);
        } else if (xuanze == 4) {
            gong4(&tou1);
        } else if (xuanze == 5) {
            gong5(&tou1);
        } else if (xuanze == 8) {
            gong8(&tou1);
        } else if (xuanze == 9) {
            gong9(&tou1);
        } else if (xuanze == 10) {
            gong10(&tou1);
        } else if (xuanze == 11) {
            gong11(&tou1);
        } else {
            printf("输入的指令无效\n");
        }
    }
}

int xitong_xiao() {
    int xuanze;
    printf("---------------学生成绩管理系统---------\n");
    printf("-----------------1.录入学生信息-------------------------------\n");
    printf("-----------------0.退出系统-------------------------\n");
    printf("请输入相应的数字以使用相应的功能: ");
    scanf("%d", &xuanze);
    printf("\n");
    return xuanze;
}

int xitong() {
    int xuanze;
    printf("---------------学生成绩管理系统---------\n");
    printf("-----------------1.录入学生信息-------------------------------\n");
    printf("-----------------2.删除学生信息---------------------------\n");
    printf("-----------------3.查询学生信息(姓名)-------------------------------\n");
    printf("-----------------4.显示学生信息--------------------------------\n");
    printf("-----------------5.修改学生成绩--------------------------------\n");
    printf("-----------------8.按总成绩高低排序-------------------------------\n");
    printf("-----------------9.按单项成绩高低排序-------------------------------\n");
    printf("-----------------10.将数据输出为csv文件-------------------------\n");
    printf("-----------------11.保存数据--------------------------------\n");
    printf("-----------------0.退出系统-------------------------\n");
    printf("请输入相应的数字以使用相应的功能: ");
    scanf("%d", &xuanze);
    printf("\n");
    return xuanze;
}

int gong1(struct student **tou1) { // 1.录入学生信息
    printf("请选择你需要的导入方式\n");
    printf("1.从txt中批量导入\n");
    printf("2.逐个导入\n");
    printf("0.返回上一级菜单\n");
    printf("请输入相应的数字以使用相应的功能: ");
    int xuanze;
    scanf("%d", &xuanze);
    if (xuanze == 0) return 0;
    if (xuanze == 1) {
        //从txt中批量导入学生成绩
        int i = 0;
        i = import_from_custom_txt(tou1, "students.txt");
        if (i == 0) {
            printf("未找到对应文件\n");
            return 0;
        } else if (i == 1) {
            printf("导入成功,共导入%d条数据\n", i);
            return 0;
        }
    } else if (xuanze == 2) {
        //逐个导入学生数据
        char xingming[20], xingbie[5], banji[10], nianji[10];
        long int xuehao;
        int shengao, tizhong, zongfen, chengji[6];
        printf("请输入您想录入的学生姓名, 输入0退出: ");
        scanf("%s", xingming);
        if (strcmp(xingming, "0") == 0) return 0;
        printf("学号: "); scanf("%ld", &xuehao);
        printf("班级: "); scanf("%s", banji);
        printf("年级: "); scanf("%s", nianji);
        printf("身高: "); scanf("%d", &shengao);
        printf("体重: "); scanf("%d", &tizhong);
        printf("性别: "); scanf("%s", xingbie);
        printf("总分: "); scanf("%d", &zongfen);
        printf("BMI: "); scanf("%d", &chengji[0]);
        printf("肺活量: "); scanf("%d", &chengji[1]);
        printf("50m跑: "); scanf("%d", &chengji[2]);
        printf("立定跳远: "); scanf("%d", &chengji[3]);
        printf("引体向上: "); scanf("%d", &chengji[4]);
        printf("1000m跑: "); scanf("%d", &chengji[5]);
        struct student *node = create_student_node(xingming, xuehao, banji, nianji, shengao, tizhong, xingbie, chengji, zongfen);
        insert_student_list_tail(tou1, node);
        printf("添加成功！\n");
        getchar();
        getchar();
        return 0;
    }
}

int gong2(struct student **tou1) { // 2.删除学生信息
    char xingming[20];
    printf("请输入您想删除的学生姓名: ");
    scanf("%s", xingming);
    struct student *chaxun = search_student_list(tou1, xingming);
    if (chaxun == NULL) {
        printf("没有找到该学生\n");
    } else {
        int i = 1;
        struct student *temp = *tou1;
        while (temp != chaxun) { temp = temp->next; i++; }
        delete_student_list_node(tou1, i);
        printf("删除成功！\n");
    }
    getchar();
    getchar();
    return 0;
}

int gong3(struct student **tou1) { // 3.查询学生信息
    char xingming[20];
    printf("请输入查询姓名: ");
    scanf("%s", xingming);
    struct student *res = search_student_list(tou1, xingming);
    if (res) {
        //将信息全部输出
        printf("姓名: %s\n 学号: %ld\n 班级: %s\n 年级: %s\n 身高: %d\n 体重: %d\n 性别: %s\n BMI: %d\n 肺活量: %d\n 50m跑: %d\n 立定跳远: %d\n 引体向上: %d\n 1000m跑: %d\n 总分: %d\n", 
    res->name, res->school_number, res->class_name, res->grade, res->height, res->weight, res->sex, res->project_score[0], res->project_score[1], res->project_score[2], res->project_score[3], res->project_score[4], res->project_score[5], res->total_score);
    } else {
        printf("未找到该学生\n");
    }
    getchar();
    getchar();
    return 0;
}

void gong4(struct student **head) { // 4.显示学生信息
    if (*head == NULL) { printf("空列表\n"); return; }
    struct student *curr = *head;
    printf("姓名\t学号\t总分\tBMI\t肺活量\t50m跑\t立定跳远\t引体向上\t1000m跑\t总分\n");
    while (curr) {
        printf("%s\t%ld\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", curr->name, curr->school_number, 
        curr->total_score, curr->project_score[0], curr->project_score[1], curr->project_score[2], 
        curr->project_score[3], curr->project_score[4], curr->project_score[5], curr->total_score);
        curr = curr->next;
    }
    getchar();
    getchar();
}

int gong5(struct student **tou1) { // 5.修改学生成绩
    char xingming[20], xin[20];
    int haoma;
    printf("请输入姓名: "); scanf("%s", xingming);
    printf("修改项编号(1-13): "); scanf("%d", &haoma);
    printf("新值: "); scanf("%s", xin);
    modify_student_info(tou1, xingming, haoma, xin);
    printf("修改成功！\n");
    getchar();
    getchar();
    return 0;
}

int gong8(struct student **tou1) { // 8.按总分排序
    printf("排序结果不会保存。\n");
    struct student *fuzhi = copy_student_list(*tou1);
    sort_student_list(&fuzhi, 1, 0);
    gong4(&fuzhi); // 调用4.显示学生信息
    //排序完成后，释放fuzhi
    delete_student_list(&fuzhi);
    getchar();
    getchar();
    return 0;
}

int gong9(struct student **tou1) { // 9.按单项科目排序
    int kemu;
    printf("排序结果不会保存。\n");
    printf("输入科目编号(1-6): ");
    scanf("%d", &kemu);
    struct student *fuzhi = copy_student_list(*tou1);
    sort_student_list(&fuzhi, 2, kemu);
    gong4(&fuzhi); // 调用4.显示学生信息
    //排序完成后，释放fuzhi
    delete_student_list(&fuzhi);
    getchar();
    getchar();
    return 0;
}

int gong10(struct student **tou1) { // 10.将数据输出为csv文件
    output_csv(tou1, "学生成绩.csv");
    printf("输出成功！数据保存在学生成绩.csv文件中\n");
    getchar();
    getchar();
    return 0;
}

int gong11(struct student **tou1) { // 11.保存数据
    save_student_list_to_file(tou1, "students.dat");
    printf("保存成功！数据保存在students.dat文件中\n");
    getchar();
    getchar();
    return 0;
}
    