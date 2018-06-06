#include <iostream>
#include "KListBox.h"

using std::cout;
using std::endl;

void main()
{
	// Create a vector object of integers
	KListBox<int>   kListBox;

	// Fill the vector with 3 different elements
    for (int i=0; i<20; ++i)
    {
	    kListBox.Insert(i);
    }//for

    int iStart = kListBox.SetDisplayStart( 15 );
    kListBox.SetSelected( 17 );
	// Now loop and print out all the element values
    for(KListBox<int>::VITOR itor = kListBox.BeginDisplay(); itor != kListBox.EndDisplay(); ++itor)
    {
        if ( kListBox.IsSelected(iStart) )
            cout << "* ";
        else
            cout << "  ";
		cout << "element value = " << (*itor) << endl;
        ++iStart;
    }//for
}//main()