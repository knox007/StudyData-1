// TEST_orangebox.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include"COrangebox.h"

int main()
{
	COrangebox orangebox;

	orangebox.Init();

	orangebox.Add(10);

	orangebox.Minus(3);

	orangebox.Show();

    return 0;
}

