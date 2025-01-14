
/*
// 实验参考代码
// 题目：一元多项式相加
*/

#include<stdio.h>
#include<stdlib.h>

/*
// 一元多项式结点定义
*/
typedef struct node
{
    int coef, exp;
    struct node* next;
}NODE;

/*
// 尾部插入结点建立含头结点的一元多项式单链表函数，按指数从小到大输入的顺序将系数和指数成对输入
*/
NODE* create_nodes_list()
{
    NODE* H = NULL;
    NODE* s, * r = NULL;
    int coef, exp;
    int ret;
    int exp_pre = -1;
    char exit_flag;

    H = (NODE*)malloc(sizeof(NODE));
    if (H == NULL)
    {
        return NULL;
    }

    /*初始化头结点参数*/
    H->coef = 0;
    H->exp = -1;
    H->next = NULL;

    r = H;  /*尾指针指向头结点*/

    printf("请按指数从小到大的顺序成对输入一元多项式的系数和指数,直接输入q加回车结束创建\n");
    while (1)
    {
        ret = scanf_s("%d%d", &coef, &exp);
        scanf_s("%c", &exit_flag);

        if (ret == 2)
        {
            if (coef == 0 || exp <= exp_pre)
            {
                if (coef == 0)
                {
                    printf("输入系数错误，不能为零\n");
                }

                if (exp <= exp_pre)
                {
                    printf("输入指数错误，须大于等于0，且要求比先前输入系数大\n");
                }
            }
            else
            {
                // TODO（1分）: 待添加功能: 要求首先创建一个新结点，用s指向该结点，并给该结点赋值，然后将s放置在尾指针r的后面，以及更新尾指针r
                s = (NODE*)malloc(sizeof(NODE));
                if (s == NULL)
                {
                    printf("申请内存失败");
                    while (1);
                }
                s->coef = coef;
                s->exp = exp;
                s->next = NULL;                 //确保尾指针->next为NULL
                r->next = s;
                r = r->next;
                /*更新exp_pre*/
                exp_pre = exp;
            }
        }
        else if (exit_flag == 'q')
        {
            printf("创建一元多项式链表结束\n");
            break;
        }
        else
        {
            printf("输入参数错误，请按要求输入数值，结束创建请直接输入q加回车\n");
        }

        fflush(stdin);
    }

    return H;
}


/*
// 遍历打印带头结点的链表中所有一元多项式结点的系数和指数
*/
void print_nodes_list(NODE* H)
{
    // TODO: 待添加功能 （1分）
    if (H == NULL)                                    //判断头节点
    {
        return;
    }
    NODE* p = H->next;
    while (p)                                       //循环输出
    {
        printf("(%d,%d)", p->coef, p->exp);
        p = p->next;
    }
    printf("\n");
    return;
}


/*
// 实现两个用带头结点的单链表表示的一元多项式相加
*/
NODE* add_nodes(NODE* pa_H, NODE* pb_H)
{
    //TODO: 待添加功能（2分）
    if (pa_H == NULL && pb_H != NULL)                   //判断pa，pb其中有一个为NULL是，返回非空的头节点
    {
        return pb_H;
    }
    else if (pb_H == NULL && pa_H != NULL)
    {
        return pa_H;
    }
    else
    {
        ;
    }
    NODE* pc_H = (NODE*)malloc(sizeof(NODE));
    NODE* pa = pa_H->next, * pb = pb_H->next;
    NODE* pc = pc_H, * newnode;

    while (pa && pb)
    {
        newnode = (NODE*)malloc(sizeof(NODE));
        if (newnode == NULL)
        {
            printf("申请内存失败");
            while (1);
        }

        if (pa->exp == pb->exp)                             //判断指数，相等则新节点等于二者之和，或者取小的那个
        {
            newnode->coef = pa->coef + pb->coef;
            newnode->exp = pa->exp;
            pc->next = newnode;
            pc = pc->next;
            pa = pa->next;
            pb = pb->next;
        }
        else if (pa->exp > pb->exp)
        {
            newnode->coef = pb->coef;
            newnode->exp = pb->exp;
            pc->next = newnode;
            pc = pc->next;
            pb = pb->next;
        }
        else if (pa->exp < pb->exp)
        {
            newnode->coef = pa->coef;
            newnode->exp = pa->exp;
            pc->next = newnode;
            pc = pc->next;
            pa = pa->next;
        }
    }

    if (pa != NULL)                                         //判断其中一个提前取完，把未取完的链表复制到新链表中
    {
        while (pa)
        {
            newnode = (NODE*)malloc(sizeof(NODE));
            if (newnode == NULL)
            {
                printf("申请内存失败");
                while (1);
            }
            newnode->coef = pa->coef;
            newnode->exp = pa->exp;
            pc->next = newnode;
            pc = pc->next;
            pa = pa->next;
        }
    }
    else if (pb != NULL)
    {
        while (pb)
        {
            newnode = (NODE*)malloc(sizeof(NODE));
            if (newnode == NULL)
            {
                printf("申请内存失败");
                while (1);
            }
            newnode->coef = pb->coef;
            newnode->exp = pb->exp;
            pc->next = newnode;
            pc = pc->next;
            pb = pb->next;
        }
    }
    else
    {
        ;
    }
    pc->next = NULL;                                                   //确保尾指针next为NULL
    return pc_H;
}

/*
// 销毁带头结点的链表
*/
void destroy_nodes_list(NODE* H)
{
    //TODO: 待添加功能（1分）
    NODE* t, * p;

    if (H == NULL)
    {
        return;
    }

    p = H;

    t = p->next;
    while (t)
    {
        free(p);
        p = t;
        t = p->next;
    }

    return;
}


/*
// 一元多项式相加测试函数
*/
void add_nodes_test()
{
    NODE* pa = NULL;
    NODE* pb = NULL;
    NODE* pc = NULL;

    printf("一元多项式相加函数测试开始\n");

    /*创建链表A*/
    printf("\n");
    printf("创建链表A\n");
    pa = create_nodes_list();

    /*创建链表B*/
    printf("\n");
    printf("创建链表B\n");
    pb = create_nodes_list();

    /*遍历输出列表A和B*/
    printf("\n");
    printf("链表A内容:\n");
    print_nodes_list(pa);

    printf("\n");
    printf("链表B内容:\n");
    print_nodes_list(pb);

    /*两个列表相加*/
    pc = add_nodes(pa, pb);
    if (pc != NULL)
    {
        pa = NULL;
        pb = NULL;
    }

    /*打印输出链表C*/
    printf("\n");
    printf("链表C的结果：\n");
    print_nodes_list(pc);

    /*销毁列表C*/
    destroy_nodes_list(pc);

    printf("一元多项式相加函数测试结束，按任意键结束\n");
    getchar(); /*等待任意按键*/
}

//--------------------------------------------------------------------------------------------------------------------------------------------

/*
// 测试主程序
*/

void main()
{

    add_nodes_test();

}
