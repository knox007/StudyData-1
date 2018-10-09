/*
	열거형

	-	선언.

		-	enum 열거형이름
			{
				열거형상수1,
				열거형상수2,
				열거형상수3,
				.......
			};



	-	특징.
	
		-   정수형 상수의 일종.

	    -   특별히 값을 정의하지 않아도 자동으로 0부터 1씩 증가하며

    	    값이 적용됨.

	    -   값을 정의하게 되면 다음 상수부터는 그 값을 기준으로

    	    1씩 증가된 값이 적용.

		-	정수형 상수이므로 if, switch, for 등에 적용 가능.

	
*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnumScript : MonoBehaviour {

	public enum eDirection
	{
		East,
		West,
		South,
		North,
	};

	public eDirection _curDir;
    eDirection _preDir;

	void Start () 
	{
		print(_curDir);
		print((int)_curDir);
		
        _preDir = _curDir;
    }

    void Update()
    {
        if( _curDir != _preDir)
        {
            print(_curDir);
			print((int)_curDir);

            _preDir = _curDir;
        }
    }

	eDirection ReverseDirection (eDirection dir)
	{
		if(dir == eDirection.North)
			dir = eDirection.South;
		else if(dir == eDirection.South)
			dir = eDirection.North;
		else if(dir == eDirection.East)
			dir = eDirection.West;
		else if(dir == eDirection.West)
			dir = eDirection.East;

		return dir;     
	}
}
