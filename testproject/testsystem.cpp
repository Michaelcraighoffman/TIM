#include <iostream>
#include "tests.h"
#include "system.h"
using namespace std;

void TestSystemH() {
     unsigned short DataHold=0;
     QUEUE(20) queue;
     OSqclear(&queue);
     queue.Size=10;
     OSenqueue(1, &queue);
     OSenqueue(2, &queue);
     OSenqueue(3, &queue);
     OSenqueue(4, &queue);
     OSenqueue(5, &queue);
     OSenqueue(6, &queue);
     OSenqueue(7, &queue);
     OSenqueue(8, &queue);
     OSenqueue(9, &queue);
	for(int i=1; i<10; i++) {
		if(!OSdequeue(&DataHold, &queue)) {
			if(DataHold!=i)
	if(!OSdequeue(&DataHold, &queue))
          cout<<DataHold<<endl;
     if(!OSdequeue(&DataHold, &queue))
          cout<<DataHold<<endl;
     if(!OSdequeue(&DataHold, &queue))
          cout<<DataHold<<endl;
     if(!OSdequeue(&DataHold, &queue))
          cout<<DataHold<<endl;
     if(!OSdequeue(&DataHold, &queue))
          cout<<DataHold<<endl;
     if(!OSdequeue(&DataHold, &queue))
          cout<<DataHold<<endl;
     if(!OSdequeue(&DataHold, &queue))
          cout<<DataHold<<endl;
     //if(!OSdequeue(&DataHold, &queue))
          //cout<<DataHold<<endl;
     //if(!OSdequeue(&DataHold, &queue))
          //cout<<DataHold<<endl;
}
