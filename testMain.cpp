
#include <iostream>
#include "smart_pointer.h"

class MyClassXXX
{
public:
    MyClassXXX()
    {
		location_print;
    }
    ~MyClassXXX()
    {
       location_print;
    }
};

int main()
 {

    location_print;

    std::cout << "\n\n\n Hello gargabe collector \n\n";

    MyShared_ptr<MyClassXXX> shrd_ptr_1(new MyClassXXX) ;

    printf("\n shrd_ptr_1.GetManagedPtr()  == %d \n" , shrd_ptr_1.GetManagedPtr() );
   // cout<< "\n shrd_ptr_1.GetManagedPtr()  " << shrd_ptr_1.GetManagedPtr() << endl;

    MyShared_ptr<MyClassXXX> shrd_ptr_2 =  shrd_ptr_1 ;

    //cout<< "\n shrd_ptr_2.GetManagedPtr()  " << shrd_ptr_2.GetManagedPtr() << endl;
	printf("\n shrd_ptr_2.GetManagedPtr()  == %d \n" , shrd_ptr_2.GetManagedPtr() );

	printf("\n shrd_ptr_1.GetCountSharedOwners()  == %d \n" , shrd_ptr_1.GetCountSharedOwners() );
	printf("\n shrd_ptr_2.GetCountSharedOwners()  == %d \n" , shrd_ptr_2.GetCountSharedOwners() );

    //Press_AnyKey_To_Continue;

  return 0;
}



