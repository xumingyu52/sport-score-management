#ifndef INFORMATION_H
#define INFORMATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROJECT_COUNT 7

struct student {
  char name[20];
  char school_number[20];
  char class_name[20];
  char grade[20];
  float height;
  float weight;
  char sex[10];
  // 体测项目
  char project_name[PROJECT_COUNT][20];
  int project_score[PROJECT_COUNT];
  int total_score;
  // 链表构建
  struct student *next;
};

/**
 * @brief 创建链表节点
 * @param name  学生姓名
 * @param school_number 学号
 * @param class_name 班级
 * @param grade 年级
 * @param height 身高
 * @param weight 体重
 * @param sex 性别
 * @param project_score 体测项目成绩 7个
 * @param total_score 总成绩
 * @return struct student* 返回创建的节点指针
 */
struct student *create_student_node(char *name, char *school_number,
                                    char *class_name, char *grade, float height,
                                    float weight, char *sex, int *project_score,
                                    int total_score) {
  struct student *head = (struct student *)malloc(sizeof(struct student));
  if (head == NULL) {
    printf("内存分配失败！\n");
    return NULL;
  }
  strcpy(head->name, name);
  strcpy(head->school_number, school_number);
  strcpy(head->class_name, class_name);
  strcpy(head->grade, grade);
  head->height = height;
  head->weight = weight;
  strcpy(head->sex, sex);
  for (int i = 0; i < PROJECT_COUNT; i++) {
    head->project_score[i] = project_score[i];
  }

  // 初始化总分
  head->total_score = total_score;

  if (strcmp(sex, "男") == 0) {
    const char *m_names[PROJECT_COUNT] = {"BMI",    "肺活量",   "坐位体前屈",
                                          "50m跑",  "立定跳远", "引体向上",
                                          "1000m跑"};
    for (int i = 0; i < PROJECT_COUNT; i++)
      strcpy(head->project_name[i], m_names[i]);
  } else {
    const char *f_names[PROJECT_COUNT] = {"BMI",   "肺活量",   "坐位体前屈",
                                          "50m跑", "立定跳远", "仰卧起坐",
                                          "800m跑"};
    for (int i = 0; i < PROJECT_COUNT; i++)
      strcpy(head->project_name[i], f_names[i]);
  }

  // 链表部份
  head->next = NULL;
  return head;
}

/**
 * @brief 链表尾插
 *
 * @param head_ref 链表头指针
 * @param new_node 新节点
 */
void insert_student_list_tail(struct student **head_ref,
                              struct student *new_node) {
  if (*head_ref == NULL) {
    *head_ref = new_node;
    return;
  }
  struct student *last = *head_ref;
  while (last->next != NULL) {
    last = last->next;
  }
  last->next = new_node;
}

/**
 * @brief 链表头插
 *
 * @param head_ref 链表头指针
 * @param new_node 新节点
 */
void insert_student_list_head(struct student **head_ref,
                              struct student *new_node) {
  if (*head_ref == NULL) {
    *head_ref = new_node;
    return;
  }
  new_node->next = *head_ref;
  *head_ref = new_node;
}

/**
 * @brief 在链表中插入
 *
 * @param head_ref 链表头指针
 * @param new_node 新节点
 * @param position 插入位置  第n个学生的后面插入
 */
void insert_student_list(struct student **head_ref, struct student *new_node,
                         int position) {
  if (*head_ref == NULL) {
    *head_ref = new_node;
    return;
  }
  struct student *current = *head_ref;
  for (int i = 0; i < position - 1 && current->next != NULL; i++) {
    current = current->next;
  }
  new_node->next = current->next;
  current->next = new_node;
}

/**
 * @brief 链表中任意节点删除
 *
 * @param head_ref 链表头指针
 * @param position 删除位置  第n个学生被删除
 */
void delete_student_list_node(struct student **head_ref, int position) {
  if (*head_ref == NULL || position < 1) {
    return;
  }
  struct student *current = *head_ref;

  if (position == 1) {
    *head_ref = current->next;
    free(current);
    return;
  }
  for (int i = 1; i < position - 1 && current->next != NULL; i++) {
    current = current->next;
  }
  if (current->next == NULL) {
    return;
  }
  struct student *temp = current->next;
  current->next = temp->next;
  free(temp);
}

/**
 * @brief 链表清空
 * @param head_ref 链表头指针
 */
void delete_student_list(struct student **head_ref) {
  struct student *current = *head_ref;
  struct student *next = NULL;
  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }
  *head_ref = NULL;
}

/**
 * @brief 链表查找
 *
 * @param head_ref 链表头指针
 * @param name 学生姓名
 * @return struct student* 返回找到的节点指针
 */
struct student *search_student_list(struct student **head_ref, char *name) {
  struct student *current = *head_ref;
  while (current != NULL) {
    if (strcmp(current->name, name) == 0) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

/**
 * @brief 链表排序
 * @param head_ref 链表头指针
 * @param sort_type 排序类型  1:按总成绩排序  2:按单科成绩排序（输入第几个科目）
 * 3:按体重排序
 * @param sort_index 排序科目
 */
void sort_student_list(struct student **head_ref, int sort_type,
                       int sort_index) {
  // 如果链表为空或只有一个节点，无需排序
  if (*head_ref == NULL || (*head_ref)->next == NULL) {
    return;
  }

  int swapped;
  struct student **curr_ptr_ref;
  struct student *p1, *p2;

  do {
    swapped = 0;
    curr_ptr_ref = head_ref; // 从头指针的地址开始遍历

    // 遍历整个链表进行冒泡排序
    while ((*curr_ptr_ref)->next != NULL) {
      p1 = *curr_ptr_ref; // 当前节点
      p2 = p1->next;      // 下一个节点

      int should_swap = 0;
      // 排序逻辑（降序排列：成绩大的在前）
      if (sort_type == 1) {
        if (p1->total_score < p2->total_score)
          should_swap = 1;
      } else if (sort_type == 2) {
        if (p1->project_score[sort_index - 1] <
            p2->project_score[sort_index - 1])
          should_swap = 1;
      } else if (sort_type == 3) {
        if (p1->weight < p2->weight)
          should_swap = 1;
      }

      if (should_swap) {
        /* 核心逻辑：交换节点的链接 */
        p1->next = p2->next; // 1. 让 p1 指向 p2 之后的节点
        p2->next = p1;       // 2. 让 p2 指向 p1
        *curr_ptr_ref = p2;  // 3. 让“指向 p1 的那个指针”改为指向 p2

        swapped = 1;
      }

      /* 移动到下一个位置 */
      // 无论是否交换，下一次我们要检查的都是“当前这个位置的下一个”
      curr_ptr_ref = &((*curr_ptr_ref)->next);
    }
  } while (swapped); // 如果一轮遍历没有发生交换，说明排序完成
}

/**
 * @brief 个人信息修改
 *
 * @param head_ref 链表头指针
 * @param name 学生姓名
 * @param info_index 需要修改的信息的编号
 * @param new_info 新的信息(传入字符串)
 */
void modify_student_info(struct student **head_ref, char *name, int info_index,
                         char *new_info) {
  struct student *current = *head_ref;
  while (current != NULL) {
    if (strcmp(current->name, name) == 0) {
      if (info_index == 1) {
        strcpy(current->name, new_info); // 姓名
      } else if (info_index == 2) {
        strcpy(current->school_number, new_info); // 学号
      } else if (info_index == 3) {
        strcpy(current->class_name, new_info); // 班级
      } else if (info_index == 4) {
        strcpy(current->grade, new_info); // 年级
      } else if (info_index == 5) {
        strcpy(current->sex, new_info); // 性别
        // --- 修复：修改性别后同步更新项目名称 ---
        if (strcmp(current->sex, "男") == 0) {
          const char *m_names[PROJECT_COUNT] = {
              "BMI",      "肺活量",   "坐位体前屈", "50m跑",
              "立定跳远", "引体向上", "1000m跑"};
          for (int i = 0; i < PROJECT_COUNT; i++)
            strcpy(current->project_name[i], m_names[i]);
        } else {
          const char *f_names[PROJECT_COUNT] = {
              "BMI",      "肺活量",   "坐位体前屈", "50m跑",
              "立定跳远", "仰卧起坐", "800m跑"};
          for (int i = 0; i < PROJECT_COUNT; i++)
            strcpy(current->project_name[i], f_names[i]);
        }
      } else if (info_index == 6) {
        current->height = atof(new_info); // 身高
      } else if (info_index == 7) {
        current->weight = atof(new_info); // 体重
      } else if (info_index >= 8 && info_index < 8 + PROJECT_COUNT) {
        current->project_score[info_index - 8] = atoi(new_info); // 各科目成绩
      } else if (info_index == 8 + PROJECT_COUNT) {
        current->total_score = atoi(new_info); // 总成绩
      }
      return;
    }
    current = current->next;
  }
}

/**
 * @brief 将整个链表保存到文件
 *
 * @param head_ref 链表头指针
 * @param filename 文件名
 */
void save_student_list_to_file(struct student **head_ref, char *filename) {
  FILE *file = fopen(filename, "wb");
  if (file == NULL) {
    printf("无法保存文件\n");
    return;
  }
  struct student *current = *head_ref;
  while (current != NULL) {
    fwrite(current, sizeof(struct student), 1, file);
    current = current->next;
  }
  fclose(file);
}

/**
 * @brief 从文件中读取链表
 *
 * @param head_ref 链表头指针
 * @param filename 文件名
 */
struct student *load_student_list_from_file(char *filename) {
  FILE *file = fopen(filename, "rb");
  if (file == NULL)
    return NULL;

  // 新的头节点
  struct student *head = NULL;
  struct student temp; // 这是一个临时挡箭牌，用来接住从硬盘读出来的东西
  while (fread(&temp, sizeof(struct student), 1, file) == 1) {
    // 关键区别在这里！！
    // 每读到一个学生，我们就给他造一个新的“身体”（分配新内存）
    struct student *new_node = (struct student *)malloc(sizeof(struct student));

    // 把读到的数据拷贝过去
    memcpy(new_node, &temp, sizeof(struct student));

    // 必须清空指针，因为硬盘里的指针是上一次运行时的“破旧地址”，不能用
    new_node->next = NULL;

    // 把这个新同学挂到链表的尾巴上
    insert_student_list_tail(&head, new_node);
  }
  fclose(file);
  return head;
}

/**
 * @brief 将链表信息输出为csv文件
 *
 * @param head_ref 链表头指针
 * @param filename 文件名
 */
void output_csv(struct student **head_ref, char *filename) {
  FILE *file = fopen(filename, "w");
  if (file == NULL) {
    printf("无法保存文件\n");
    return;
  }
  // 写入表头
  fprintf(
      file,
      "姓名,学号,班级,年级,身高,体重,性别,BMI,肺活量,坐位体前屈,50m跑,立定跳远,"
      "引体向上/仰卧起坐,1000m跑/800m跑,总成绩\n");
  struct student *current = *head_ref;
  while (current != NULL) {
    fprintf(file, "%s,%s,%s,%s,%.1f,%.1f,%s,%d,%d,%d,%d,%d,%d,%d,%d\n",
            current->name, current->school_number, current->class_name,
            current->grade, current->height, current->weight, current->sex,
            current->project_score[0], current->project_score[1],
            current->project_score[2], current->project_score[3],
            current->project_score[4], current->project_score[5],
            current->project_score[6], current->total_score);
    current = current->next;
  }
  fclose(file);
}

/**
 * @brief 复制链表
 *
 * @param head_ref 链表头指针
 * @return struct student* 复制后的链表头指针
 */
struct student *copy_student_list(struct student *head_ref) {
  struct student *new_head = NULL;
  struct student *current = head_ref;
  while (current != NULL) {
    // 必须为新节点分配内存
    struct student *new_node = (struct student *)malloc(sizeof(struct student));
    if (new_node == NULL)
      return new_head;

    // 拷贝内容
    memcpy(new_node, current, sizeof(struct student));
    new_node->next = NULL;

    insert_student_list_tail(&new_head, new_node);
    current = current->next;
  }
  return new_head;
}

/**
 * @brief 从这种特定格式的 TXT 文件中导入数据
 * @param head_ref 链表头指针
 * @param filename 文件路径
 * @return int 成功导入的人数
 */
int import_from_custom_txt(struct student **head_ref, char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("无法打开文件：%s\n", filename);
    return 0;
  }

  char line[256];
  int count = 0;

  // 临时存储变量，每次发现新学生时重置
  char name[40] = {0}, sex[10] = {0}, grade[20] = {0}, class_name[20] = {0},
       id[20] = {0};
  float h_val = 0, w_val = 0, total_f = 0;
  int scores[7] = {0};
  int has_active = 0;

  while (fgets(line, sizeof(line), file)) {
    // 发现新的学号行：说明新学生开始
    if (strstr(line, "学号")) {
      // 保存上一个学生
      if (has_active) {
        struct student *node =
            create_student_node(name, id, class_name, grade, h_val, w_val, sex,
                                scores, (int)total_f);
        if (node) {
          insert_student_list_tail(head_ref, node);
          count++;
        }
      }

      // 重置变量
      memset(name, 0, 40);
      memset(sex, 0, 10);
      memset(grade, 0, 20);
      memset(class_name, 0, 20);
      memset(id, 0, 20);
      memset(scores, 0, sizeof(scores));
      h_val = 0;
      w_val = 0;
      total_f = 0;
      has_active = 1;

      char *p = strstr(line, "：");
      if (!p)
        p = strchr(line, ':');
      if (p)
        sscanf(p + (p[0] == ':' ? 1 : 2), "%s", id);
      continue;
    }

    if (!has_active)
      continue;

    // 解析基础属性 (不被分割线阻断)
    char *p_colon = strstr(line, "：");
    if (!p_colon)
      p_colon = strchr(line, ':');
    if (p_colon) {
      char *data = p_colon + (p_colon[0] == ':' ? 1 : 2);
      if (strstr(line, "姓名"))
        sscanf(data, "%s", name);
      else if (strstr(line, "性别"))
        sscanf(data, "%s", sex);
      else if (strstr(line, "年级"))
        sscanf(data, "%s", grade);
      else if (strstr(line, "班级"))
        sscanf(data, "%s", class_name);
      else if (strstr(line, "总分"))
        sscanf(data, "%f", &total_f);
      else if (strstr(line, "身高"))
        sscanf(data, "%f", &h_val);
      else if (strstr(line, "体重"))
        sscanf(data, "%f", &w_val);
    }

    // 解析体测分数 (带有“分”字的行)
    char *p_fen = strstr(line, "分");
    if (p_fen) {
      char *ptr = p_fen - 1;
      while (ptr > line && (*ptr < '0' || *ptr > '9'))
        ptr--; // 越过下划线
      while (ptr > line && (*ptr >= '0' && *ptr <= '9'))
        ptr--; // 找起始
      int val = atoi(ptr + 1);

      if (strstr(line, "BMI"))
        scores[0] = val;
      else if (strstr(line, "肺活量"))
        scores[1] = val;
      else if (strstr(line, "坐位体前屈"))
        scores[2] = val;
      else if (strstr(line, "50米"))
        scores[3] = val;
      else if (strstr(line, "立定跳远"))
        scores[4] = val;
      else if (strstr(line, "引体向上") || strstr(line, "仰卧起坐"))
        scores[5] = val;
      else if (strstr(line, "1000米") || strstr(line, "800米"))
        scores[6] = val;
    }
  }

  // 保存最后一名学生
  if (has_active) {
    struct student *node = create_student_node(
        name, id, class_name, grade, h_val, w_val, sex, scores, (int)total_f);
    if (node) {
      insert_student_list_tail(head_ref, node);
      count++;
    }
  }

  fclose(file);
  return count;
}
#endif

