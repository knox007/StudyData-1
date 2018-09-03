/*
/// 프로퍼티 ///////////////////////////////////////////////////////

----------------------
1.	목적.
----------------------

	1.	일반적으로 클래스의 필드(멤버변수 )는 정보은닉을 목적으로 private로 선언.

       필드에대한 접근용 메소드(멤버 함수) get/set을 만들어 사용해야 했음.

		->	프로퍼티는 필드 접근에 대한 은닉성과 편의성을 제공.

    
    2.  선언

        class 클래스_이름
        {
            데이터타입   필드이름;

            접근제한자   데이터타입   프로퍼티이름
            {
                get
                {
                    return 필드이름;
                }

                set
                {
                    필드이름 = value;
                }
            }
        }

        -   get / set   :   접근자

            value       :   set 접근자의 암묵적 매개변수.

               


     예)
            1)   프로퍼티를 사용하지 않는 필드 접근 방식.

            구현)

                class TestClass
                {
                    int _field;

                    public int GetField()               { return _field; }
                    public void SetField( int value )   { _field = value; }
                }

            사용)

                TestClass test = new TestClass();
                test.SetField( 100 );
                print( test.GetField() );


            2)   프로퍼티를 사용한 필드 접근 방식.

            구현)

                class TestClass
                {
                    int _field;

                    public int _Field
                    {
                        get { return _Field; }
                        set { _Field = value; }
                    }                    
                }

            사용)

                TestClass test = new TestClass();
                test._FieldProperty = 100;
                print( test._FieldProperty );

*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using System;
//*
public class PropertyTest : MonoBehaviour {

    class BirthdayInfo
    {
        string _name;
        DateTime _birthDay;

        public string _Name
        {
            get { return _name; }
            set { _name = value; }
        }

        public DateTime _BirthDay
        {
            get { return _birthDay; }
            set { _birthDay = value; }
        }

        //  읽기 전용 프로퍼티.
        public int _Age
        {
            get { return new DateTime(DateTime.Now.Subtract(_birthDay).Ticks).Year; }
        }

    }

    // Use this for initialization
    void Start() {

        //*
        BirthdayInfo birthday = new BirthdayInfo();
        birthday._Name = "철수";
        birthday._BirthDay = new DateTime(2000, 1, 1);
        //*/

        /*  생성자를 이용한 초기화 방식.
        BirthdayInfo birthday = new BirthdayInfo()
        {
            _Name = "철수",
            _BirthDay = new DateTime(2000, 1, 1)
        };
        //*/

        print("이름 : " + birthday._Name);
        print("생일 : " + birthday._BirthDay);
        print("나이 : " + birthday._Age);
    }
}
//*/


/*
----------------------
2.	자동 구현 프로퍼티.
----------------------
    
    1.  선언

        class TestClass
        {
            public int _Field
            {
                get;set;
            }
         }

----------------------
3.	프로퍼티의 목적.
----------------------

        1.  읽기 전용.

            class TestClass
            {
                int _field;

                public int _Field
                {
                    get { return _Field; }
                    private set { _Field = value; }
                }
            }
   

        2.  필드 관련 데이터 연산후 접근.

            class TestClass
            {
                DateTime _birthDay;

                public int _Age
                {
                    get { return new DateTime(DateTime.Now.Subtract(_birthDay).Ticks).Year; }
                }
            }

    
        3.  예외처리

            class TestClass
            {
                string _name;
                
                get { return _name; }
                
                set
                {
                    if ((value == null))
                        value = "";

                    _name = value;
                }
            }
 */

/*
    quiz)   프로퍼티를 이용하여 
            
            인치정보를 입력하면 센티미터 정보도 얻을 수 있는 클래스를 만든다.

            예)

                CInch   test = new CInch();

                test._Inch = 1;
                print(test.Inch);
                print(test.Centi);
*/

