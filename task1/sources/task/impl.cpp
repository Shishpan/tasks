#include "iface.h"

// Implementation of the task's unit testing
namespace Task
{
    typedef DList<int> List;
    typedef DList<int>::Unit Unit;

    bool uTest( UnitTest *utest_p)
    {
        DList<int> list;
        list.push_back(5);
        list.push_back(10);
        Unit *u = list.first();
        
        UTEST_CHECK( utest_p, u);
        UTEST_CHECK( utest_p, list.size() == 2);

        int& f = u->val();
        f = 15;
        
        int sum = 0;
        for ( Unit* e = list.first (); e!= 0; e = e->next() )
        {
            sum += e->val();
        }

        UTEST_CHECK( utest_p, sum == 25);

        u = list.first();

        UTEST_CHECK( utest_p, u->next() == list.last() );
        UTEST_CHECK( utest_p, u->val() == 15);

        Unit * last = list.erase( u);

        UTEST_CHECK( utest_p, last->next() == 0); 
        UTEST_CHECK( utest_p, last->prev() == 0);
        UTEST_CHECK( utest_p, last == list.first());
        UTEST_CHECK( utest_p, last == list.last());
        
        // Test clear
        list.clear();

        UTEST_CHECK( utest_p, list.size() == 0);
        UTEST_CHECK( utest_p, list.empty() );
        UTEST_CHECK( utest_p, list.first() == 0);
        UTEST_CHECK( utest_p, list.last() == 0);

        //--- Test insert and reverse
        list.push_front( 10);// list: 10
        list.push_front( 20);// list: 20 10
        list.push_front( 40);// list: 40 20 10
        
        u= list.first()->next();
        list.insert( u, 30); // list: 40 30 20 10
        
        list.reverse(); // list: 10 20 30 40

        UTEST_CHECK( utest_p, list.first()->val() == 10);
        UTEST_CHECK( utest_p, list.first()->next()->val() == 20);
        UTEST_CHECK( utest_p, list.first()->next()->next()->val() == 30);
        
        UTEST_CHECK( utest_p, list.last()->val() == 40);


//
		list.clear();
		UTEST_CHECK(utest_p, list.size() == 0);
		UTEST_CHECK(utest_p, list.empty());
		UTEST_CHECK(utest_p, list.first() == 0);
		UTEST_CHECK(utest_p, list.last() == 0);
		for (int i = 0; i < 200; i++)
		{
			list.push_back(i);
			list.push_front(i + 1);
		}
		UTEST_CHECK(utest_p, list.size() == 400);
		UTEST_CHECK(utest_p, list.first()->val() == 200);
		UTEST_CHECK(utest_p, list.first()->next()->val() == 199);
		UTEST_CHECK(utest_p, list.last()->val() == 199);
		for (int i = 0; i < 200; i++)
		{
			list.pop_front();
		}
		UTEST_CHECK(utest_p, list.size() == 200);
		UTEST_CHECK(utest_p, list.first()->val() == 0);
		UTEST_CHECK(utest_p, list.last()->val() == 199);
		list.reverse();
		UTEST_CHECK(utest_p, list.first()->val() == 199);
		UTEST_CHECK(utest_p, list.last()->val() == 0);
		list.erase(list.first()->next());
		UTEST_CHECK(utest_p, list.first()->val() == 0);
		UTEST_CHECK(utest_p, list.first()->next()->val() == 2);
		list.clear();
		UTEST_CHECK(utest_p, list.size() == 0);

        return utest_p->result();
    }

};