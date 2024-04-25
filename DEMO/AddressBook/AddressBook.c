//
// Created by GODӤ�� on 2023/4/21.
//

#include "AddressBook.h"

//����ʵ��
//��ʼ��ͨѶ¼
void Initialize(Contact *ps) {
    ps->data = (PeoInfo *) malloc(DEFAULT_SZ * sizeof(PeoInfo));//�տ�ʼ����Ϊ5
    if (ps->data == NULL) {
        printf("�ڶ��������ڴ�ʧ�ܣ����ٴγ���");
        return;
    }
    ps->count = 0;
    ps->capacity = DEFAULT_SZ;
    //�����ļ���ͨѶ¼�����ݵ�������
    LoadContact(ps);
}

//���ͨѶ¼�Ƿ���Ա
void CheckCapacity(Contact *ps) {
    if (ps->count == ps->capacity) {//���ˣ�capacity���Ӳ���Ա
        //��Ա
        PeoInfo *ptr = realloc(ps->data, (ps->capacity + 2) * sizeof(PeoInfo));
        if (ptr != NULL) {
            ps->data = ptr;
            ps->capacity += INCREASE_SZ;//ÿ������5����
            printf("����Ա,���ݳɹ�\n");
        } else {
            printf("���ڴ����,����ʧ��\n");
        }
    }
}

//��ȡ��ϵ��
void LoadContact(Contact *ps) {
    PeoInfo temp = {0};
    //���ļ�
    FILE *pfRead = fopen("AddressBook.dat", "r");
    //�жϴ����һ
    if (pfRead == NULL) {
        perror("LoadContact");//perror������ȡ������Ϣ
        return;
    }
    //�жϴ������
//    if (pfRead == NULL)
//    {
//        printf("LoadContact::%s\n", strerror(errno));//strerror������ȡ������Ϣ
//        return;
//    }
    //��ȡ�ļ�
    while (fread(&temp, sizeof(PeoInfo), 1, pfRead)) {
        CheckCapacity(ps);
        ps->data[ps->count] = temp;
        ps->count++;
    }
    //�ر��ļ�
    fclose(pfRead);
    pfRead = NULL;
}

//������ϵ��
void Add(Contact *ps) {
    //�ж���Ա�Ƿ�����
    CheckCapacity(ps);
    //û������������
    printf("������������");
    scanf("%s", ps->data[ps->count].name);
    printf("���������䣺");
    scanf("%d", &(ps->data[ps->count].age));
    printf("�������Ա�");
    scanf("%s", ps->data[ps->count].gender);
    printf("������绰��");
    scanf("%s", ps->data[ps->count].telephone);
    printf("�������ַ��");
    scanf("%s", ps->data[ps->count].address);
    ps->count++;
    printf("��ӳɹ�!\n\n");
}

//��ʾ��ϵ�˵���Ϣ
void Show(const Contact *ps) {
    if (ps->count == 0) {
        printf("ͨѶ¼Ϊ��!!\n");
    } else {
        int i = 0;
        printf("%-10s\t%-6s\t%-4s\t%-15s\t%-30s\n", "����", "����", "�Ա�", "�绰", "��ַ");
        for (i = 0; i < ps->count; i++) {
            printf("%-10s\t%-6d\t%-4s\t%-15s\t%-30s\n",
                   ps->data[i].name,
                   ps->data[i].age,
                   ps->data[i].gender,
                   ps->data[i].telephone,
                   ps->data[i].address
            );
        }
        printf("\n");
        printf("\n");
    }
}

//ͨ������������ȷ����Ա�Ƿ����,���ڷ����±�,�����ڷ���-1;
static int FindByName(const Contact *ps, char name[]) {
    int i = 0;
    for (i = 0; i < ps->count; i++) {
        if (0 == strcmp(ps->data[i].name, name)) {
            return i;
        }
    }
    return -1;
}

//ɾ����ϵ��
void Delete(Contact *ps) {
    char name[MAX_NAME];
    int pos = 0;
    printf("������Ҫɾ���˵�����:");
    scanf("%s", name);
    pos = FindByName(ps, name);
    if (pos == -1) {
        printf("Ҫɾ�����˲�����!!\n\n");
    } else {
        int j = 0;
        for (j = pos; j < ps->count - 1; j++) {
            ps->data[j] = ps->data[j + 1];
        }
        ps->count--;
        printf("ɾ���ɹ�!!\n\n");
    }
}

//����ͨѶ¼
void DestroyContact(Contact *ps) {
    free(ps->data);
    ps->data = NULL;
}

//�޸���ϵ�˵���Ϣ
void Modify(Contact *ps) {
    if (ps->count == 0) {
        printf("ͨѶ¼Ϊ��!!!\n\n");
        return;
    }
    char name[MAX_NAME];
    int pos = 0;
    printf("������Ҫ�޸��˵�����:");
    scanf("%s", name);
    pos = FindByName(ps, name);
    if (pos == -1) {
        printf("���޴���,�޸�ʧ��!\n");
    } else {
        printf("�������޸�����:");
        scanf("%s", ps->data[pos].name);
        printf("�������޸�����:");
        scanf("%d", &(ps->data[pos].age));
        printf("�������޸��Ա�:");
        scanf("%s", ps->data[pos].gender);
        printf("�������޸ĵ绰:");
        scanf("%s", ps->data[pos].telephone);
        printf("�������޸ĵ�ַ:");
        scanf("%s", ps->data[ps->count].address);
        printf("�޸ĳɹ�-.-\n");
    }
}

//ֻ�ܲ��ҵ���һ����������������
void Search(Contact *ps) {
    char name[MAX_NAME];
    int pos = 0;
    printf("������Ҫ�����˵�����:");
    scanf("%s", name);
    pos = FindByName(ps, name);
    if (pos == -1) {
        printf("���޴���!!!\n");
    } else {
        printf("%-10s\t%-6s\t%-4s\t%-15s\t%-30s\n", "����", "����", "�Ա�", "�绰", "��ַ");
        printf("%-10s\t%-6d\t%-4s\t%-15s\t%-30s\n",
               ps->data[pos].name,
               ps->data[pos].age,
               ps->data[pos].gender,
               ps->data[pos].telephone,
               ps->data[pos].address
        );
    }
}

//����ͨѶ¼���ݵ��ļ�
void SaveContact(Contact *ps) {
    //���ļ�
    FILE *pfWrite = fopen("AddressBook.dat", "w");
    if (NULL == pfWrite) {
        perror("SaveContact");
        return;
    }
    //д�ļ�
    //��ʽһ:
    int i = 0;
    for (i = 0; i < ps->count; ++i) {
        fwrite(ps->data + i, sizeof(PeoInfo), 1, pfWrite);
    }
    //��ʽ��:
//    fwrite(ps->data,sizeof(PeoInfo),ps->count,pfWrite);
    //�ر��ļ�
    fclose(pfWrite);
    pfWrite = NULL;
}

//����������ͨѶ¼(����ð������)
void SortContact(Contact *ps) {
    if (ps->count == 0 || ps->count == 1) {
        printf("�������򣡣���\n");
        return;
    }
    int i, j;
    int flag = 0;
    PeoInfo temp = {0};
    for (i = 0; i < ps->count - 1; ++i) {
        flag = 1;
        for (j = 0; j < ps->count - 1; j++) {
            if (strcmp((ps->data + j)->name, (ps->data + j + 1)->name) > 0) {
                temp = *(ps->data + j);
                *(ps->data + j) = *(ps->data + j + 1);
                *(ps->data + j + 1) = temp;
                flag = 0;
            }
        }
        if (flag == 1) {
            break;
        }
    }
    printf("������ɣ�����\n");
}





















