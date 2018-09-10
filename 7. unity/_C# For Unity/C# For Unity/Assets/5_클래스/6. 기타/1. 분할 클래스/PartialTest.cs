/*
    분할 클래스
    
    -   클래스를 2번이상 나눠서 구현하는 클래스.

    -   클래스의 코드량이 길어질 경우 물리적으로 파일을 나눔으로써

        소스 코드관리의 편의를 제공.

    -   partial 키워드 사용.

        예)

            partial class 클래스_이름
            {
                .......
            }
*/ 

using System;

partial class PartialTest
{
    public string Method1()
    {
        return "Method1()";
    }

    public string Method2()
    {
        return "Method2()";
    }
}