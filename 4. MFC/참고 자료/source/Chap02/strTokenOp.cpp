#include <iostream.h>

// #define charit(x) #@x//�� ������ #@�� ���ڰ� ����ϴ� �����Ϸ��� ����
// �� �����϶�(�ñ��ϴٸ�).
#define stringit(x) #x
#define tokencat(x,y) x##y

void main(void)
{
    int i=1,j=2,ij=3;

    cout << stringit(hello) << '\n';
    cout << tokencat(i,j) << '\n';
}