#include "CSList.h"

CSList_use(int)

void test_int()
{
    int ar[10];
    CSList(int) list = CSList_new(int);

    list->Add(list,1);
    list->Add(list,2);
    list->Add(list,3);
    list->Add(list,4);
    list->Add(list,5);

    printf("Count:%d\n",list->Count(list));
    printf("Item:%d\n",*list->Item(list,3));
    printf("IndexOf:%d\n",list->IndexOf(list,4));
    printf("IndexOf:%d\n",list->IndexOf(list,0));
    printf("Contains:%d,%d\n",list->Contains(list,1),list->Contains(list,100000));

    printf("-- foreach --\n");
    CSList_foreach(int,item,list){
        printf("%d\n",*item);
    }CSList_foreach_end
    printf("-------------\n");
    
    list->Clear(list);
    printf("-- foreach --\n");
    CSList_foreach(int,item,list){
        printf("%d\n",*item);
    }CSList_foreach_end
    printf("-------------\n");

    list->Add(list,1);
    list->Add(list,2);
    list->Add(list,3);
    list->Add(list,4);
    list->Add(list,5);
    list->RemoveAt(list,0);
    list->RemoveAt(list,3);
    list->Remove(list,3);

    printf("-- foreach --\n");
    CSList_foreach(int,item,list){
        printf("%d\n",*item);
    }CSList_foreach_end
    printf("-------------\n");

    list->CopyTo(list,ar,0);
    printf("%d,%d,%d\n",ar[0],ar[1],ar[2]);
    list->CopyTo(list,ar,3);
    printf("%d,%d,%d,%d\n",ar[2],ar[3],ar[4],ar[5]);

    list->Insert(list,0,100);
    list->Insert(list,2,200);
    list->Insert(list,4,300);

    printf("-- foreach --\n");
    CSList_foreach(int,item,list){
        printf("%d\n",*item);
    }CSList_foreach_end
    printf("-------------\n");

    CSList_delete(list);
}

struct st_deep{
    char* str;
}typedef deep;

struct st_test{
    int number;
    deep* deep;
}typedef test_struct;

CSList_use(test_struct)

void customFree(test_struct* target)
{
    printf("free:%d\n",target->number);
    free(target->deep);
}

int customCompare(const test_struct* arg1,const test_struct* arg2)
{
    return (arg1->number - arg2->number);
}

void customCopy(test_struct* dest,const test_struct* src)
{
    dest->number = src->number;
    strncpy(dest->deep->str,src->deep->str,strlen(src->deep->str));
}

void test_struct_custom()
{
    test_struct ar[3];
    test_struct a,b,c,search;

    CSList(test_struct) list = CSList_new(test_struct);
    list->customFree = customFree;
    list->customCompare = customCompare;
    list->customCopy = customCopy;

    a.number = 0;
    a.deep = (deep*)malloc(sizeof(deep));
    a.deep->str = (char*)malloc(10);
    memset(a.deep->str,0,10);
    strncpy(a.deep->str,"astr",4);
    list->Add(list,a);

    b.number = 1;
    b.deep = (deep*)malloc(sizeof(deep));
    b.deep->str = (char*)malloc(10);
    memset(b.deep->str,0,10);
    strncpy(b.deep->str,"bstr",4);
    list->Add(list,b);

    c.number = 2;
    c.deep = (deep*)malloc(sizeof(deep));
    c.deep->str = (char*)malloc(10);
    memset(c.deep->str,0,10);
    strncpy(c.deep->str,"cstr",4);
    list->Add(list,c);

    search.number = 2;
    search.deep = NULL;
    printf("%d\n",list->IndexOf(list,search));
    search.number = 1000;
    printf("%d\n",list->IndexOf(list,search));

    ar[0].deep = (deep*)malloc(sizeof(deep));
    ar[0].deep->str = (char*)malloc(10);
    ar[1].deep = (deep*)malloc(sizeof(deep));
    ar[1].deep->str = (char*)malloc(10);
    ar[2].deep = (deep*)malloc(sizeof(deep));
    ar[2].deep->str = (char*)malloc(10);

    list->CopyTo(list,ar,0);
    list->Clear(list);
    printf("%d,%d,%d\n",ar[0].number,ar[1].number,ar[2].number);
    printf("%s,%s,%s\n",ar[0].deep->str,ar[1].deep->str,ar[2].deep->str);

    free(ar[0].deep->str);
    free(ar[1].deep->str);
    free(ar[2].deep->str);
    free(ar[0].deep);
    free(ar[1].deep);
    free(ar[2].deep);
}

int main(int argc, char const *argv[])
{
    test_int();
    test_struct_custom();
    return 0;
}