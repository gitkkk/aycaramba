/*
*	smart_pointer.h
*	kashyap.inbox@gmail.com
*
*
*
*/

#ifndef _smart_pointer_h_
#define _smart_pointer_h_


#include <iostream>
#include <vector>
#include <stdio.h>

//#include "common_macro_resources.h"


#define _ENABLE_DEBUG_ 
#ifdef _ENABLE_DEBUG_
#define DebugPrint(x){printf("\n %s  @ %d",x,__LINE__);}
#define DebugPrint_vrbose(x){printf("\n %s  @ %d  %s",x,__LINE__ ,__FUNCTION__);}
#define DebugPrint_vrbose_more(x){printf("\n %s  @ %d \n @ %s \n @ %s",x,__LINE__ ,__FUNCTION__,__FILE__);}
#define location_print {printf("\n\t\033[32m@ line :: \033[33m%d",__LINE__);\
						printf("\t\033[32m@ function :: \033[33m%s",__FUNCTION__);\
						printf("\t\033[32m@ file :: \033[33m%s\n",__FILE__);\
						printf("\033[0m");\
					}
#else
#define DebugPrint(x){}
#define DebugPrint_vrbose(x){}
#define DebugPrint_vrbose_more(x){}
#define location_print {}
#endif
	

template<class T>
class MyShared_ptr
{
    T*  m_ptr;
    int* m_ptrCountOwners;

    void AssignManagedPointer(T* ptr)
    {
        if(ptr)
        {
	        /*
	        we can also take into account if the method is not called for already held pointer .
	        may be we can use simple logical m_ptr == ptr ?  true : false ;
	        NEED TO CHECK THIS
	        */
		    bool Is_PtrSameAsAlreadyHeldPtr = false ;        
        	if( !Is_PtrSameAsAlreadyHeldPtr )
        	{
				GiveUpOwnerShip();
				m_ptr = ptr;

				if( !m_ptrCountOwners )
				{
					m_ptrCountOwners = new int(0);
				}
				int& count_OfOwners = *m_ptrCountOwners;
				count_OfOwners = count_OfOwners + 1 ;
        	}
			else
			{
				 DebugPrint_vrbose("Is_PtrSameAsAlreadyHeldPtr is true ");
	        }      
        }
        else
        {
			DebugPrint_vrbose("ptr is NULL ");
        }
       
    }

    void GiveUpOwnerShip()
    {
        /*
            decrease the ownership count
            delete the managed pointer if count becomes zero
        */
        if(m_ptrCountOwners)
        {
            int& count_OfOwners = *m_ptrCountOwners;
            if( count_OfOwners > 0)
            {
                count_OfOwners = count_OfOwners - 1;
                if(count_OfOwners==0)
                {
                  DeleteManagedPointer();
                }
            }
            else
            {
				DebugPrint_vrbose(" count_OfOwners was less than 0  ");
            }

        }
        else
        {
			DebugPrint_vrbose(" m_ptrCountOwners is NULL  ");
        }
    }

    void DeleteManagedPointer()
    {
    	if(m_ptr)
    	{
    		delete m_ptr;
			m_ptr = NULL ;
    	}
		else
		{
			DebugPrint_vrbose(" m_ptr was NULL  ");
		}

		if(m_ptrCountOwners)
        {
            delete m_ptrCountOwners;
            m_ptrCountOwners = NULL ;
        }
        else
        {
			DebugPrint_vrbose(" m_ptrCountOwners was NULL  ");
        }
    }

public:

    MyShared_ptr():m_ptr(NULL),m_ptrCountOwners(NULL)
    {
    }

    ~MyShared_ptr()
    {
    	GiveUpOwnerShip();
    }

    MyShared_ptr(T* ptr):m_ptr(NULL),m_ptrCountOwners(NULL)
    {
		AssignManagedPointer(ptr);
    }

    MyShared_ptr(const MyShared_ptr& val)
    {
		m_ptr               = val.m_ptr ;
		m_ptrCountOwners    = val.m_ptrCountOwners ;
		int& count_OfOwners = *m_ptrCountOwners;
		count_OfOwners = count_OfOwners + 1 ;
    }

    void operator=(const MyShared_ptr& val )
    {
		m_ptr               = val.m_ptr ;
		m_ptrCountOwners    = val.m_ptrCountOwners ;
		int& count_OfOwners = *m_ptrCountOwners;
		count_OfOwners = count_OfOwners + 1 ;
    }

    T* GetManagedPtr()
    {
        T* ret_ptr = NULL ;
        if(m_ptr)
        {
            ret_ptr = m_ptr ;
        }
        return ret_ptr ;
    }


    int GetCountSharedOwners()
    {
        int Owners = *m_ptrCountOwners;
        return Owners ;
    }
	
	operator bool () 
	{
		bool retVal = false ;
		if(m_ptr)
		{
			retVal = true ;
		}

		return retVal ;
	}
};


#endif


