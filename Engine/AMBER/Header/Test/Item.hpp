#ifndef __ITEM_LIA__
#define __ITEM_LIA__

#include <iostream>

using namespace std;

namespace lia
{
    class Item
    {
        public:
            Item(string n);
        private:
            string name;            
            float nb;
    };
}

#endif //__ITEM_LIA__
