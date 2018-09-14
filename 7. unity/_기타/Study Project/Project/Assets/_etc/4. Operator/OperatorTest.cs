using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OperatorTest : MonoBehaviour
{
    //------------------------------------------------
	void Start ()
    {
        int num1 = 11, num2 = 3;
        print("num1 = " + num1 + ", " + "num2 = " + num2);
        print("------------------------------");
        //---------------------------------
        /*  부호 연산자 : +,-
        print( "---  부호연산자 ---");
        print(+num1);
        print(-num1);
        //*/
        //---------------------------------
        /* 산술 연산자 : +,-,*,/,%
        print( "---  산술 연산자 ---");

        print(num1 + " + " + num2 + " = " + (num1 + num2));
        print(num1 + " - " + num2 + " = " + (num1 - num2));
        print(num1 + " * " + num2 + " = " + (num1 * num2));
        print(num1 + " / " + num2 + " = " + (num1 / num2));
        print(num1 + " % " + num2 + " = " + (num1 % num2));
        //*/
        //---------------------------------
        /* 비교 연산자 : ==, !=, >=, <=, >,<
        print("---  비교 연산자 ---");

        print("num1 == num2 = " + (num1 == num2));
        print("num1 = num2 = " + (num1 = num2));
        print("num1 != num2 = " + (num1 != num2));
        print("num1 >= num2 = " + (num1 >= num2));
        print("num1 <= num2 = " + (num1 <= num2));
        print("num1 > num2 = " + (num1 > num2));
        print("num1 < num2 = " + (num1 < num2));        
        //*/
        //---------------------------------
        /* 논리 연산자 :  &&, ||, !
        bool a = true, b = false;
        print("---  논리 연산자 ---");
        print("a && b = " + (a && b));
        print("a || b = " + (a || b));
        print("!a = " + (!a));
        print("!b = " + (!b));

        //*/
        //---------------------------------
        /* 증감 연산자( 전치,후치 ) : ++, --
         * print("---  증감 연산자 ---");
        print("num1-- = " + num1++);
        print("++num2 = " + ++num2);
        print("num1-- = " + num1--);
        print("--num2 = " + --num2);

        print("num1++ + 5 = " + (num1++ + 5));
        print("--num2 + 5 = " + (--num2 + 5));
        //*/
        //---------------------------------
        /* 비트 연산자 : &, |, ^, <<,>>
        print("---  비트 연산자 ---");
        byte bit1 = 1;
        byte bit2 = 16;
        print("bit1 = " + GetBinaryNumberString(bit1));
        print("bit2 = " + GetBinaryNumberString(bit2));
        print("bit1 & bit2 = " + GetBinaryNumberString(bit1 & bit2));
        print("bit1 | bit2 = " + GetBinaryNumberString(bit1 | bit2));
        print("bit1 ^ bit2 = " + GetBinaryNumberString(bit1 ^ bit2));
        print("~bit2 = " + GetBinaryNumberString((~bit2)));        
        print("bit1 << 1 = " + GetBinaryNumberString(bit1 << 1));
        print("bit1 >> 1 = " + GetBinaryNumberString(bit1 >> 1));
        print("bit2 << 1 = " + GetBinaryNumberString(bit2 << 1));
        print("bit2 >> 1 = " + GetBinaryNumberString(bit2 >> 1));
        //*/
        //---------------------------------
        /* 대입 연산자 : +=, -=, *=, /=, %=
        print("---  대입 연산자 ---");
        print("num1 += 2 = " + (num1 += 2));
        print("num1 -= 2 = " + (num1 -= 2));
        print("num1 *= 2 = " + (num1 *= 2));
        print("num1 /= 2 = " + (num1 /= 2));
        print("num1 %= 2 = " + (num1 %= 2));
        //*/
        //---------------------------------
        /* 삼항 연산자 : ( 조건 ? 참인경우 : 거짓인 경우 )
        print("num1 == 11 ? "+ (num1 == 11 ? "빙고" : "땡!!") );
        print("num1 > 11 ? " + (num1 > 11 ? "빙고" : "땡!!"));
        print("num1 >= 11 ? " + (num1 >= 11 ? "빙고" : "땡!!"));
        //*/
        //---------------------------------

    }// void Start ()
    //------------------------------------------------
    string GetBinaryNumberString(int num)
    {
        string ret = "0x";
        ret += Convert.ToString(num, 2).PadLeft(8, '0');
        return ret;
    }
    //------------------------------------------------

}// public class OperatorTest : MonoBehaviour
                                             