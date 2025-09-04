#include "MyList.h"
#include "MyList_Types.h"

int main() {
    MyList* str_list = StringList_Create();
    StringList_Append(str_list, "frc");
    StringList_Append(str_list, "is");
    StringList_Append(str_list, "cool");
    StringList_Print(str_list);

    MyList* int_list = IntList_Create();
    IntList_Append(int_list, 1);
    IntList_Append(int_list, 2);
    IntList_Append(int_list, 3);
    IntList_Print(int_list);

    MyList* char_list = CharList_Create();
    CharList_Append(char_list, 'w');
    CharList_Append(char_list, 'h');
    CharList_Append(char_list, 'y');
    CharList_Print(char_list);

    MyList* double_list = DoubleList_Create();
    DoubleList_Append(double_list, 0.1);
    DoubleList_Append(double_list, 0.7);
    DoubleList_Append(double_list, 9.9E100);
    DoubleList_Print(double_list);

    MyList_Destroy(str_list);
    MyList_Destroy(int_list);
    MyList_Destroy(char_list);
    MyList_Destroy(double_list);

    printf("\n");

    return 0;
}