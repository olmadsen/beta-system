#include <stdio.h>
class foo{
   public:
      void go() {
	printf("go\n");
      }
};
class bar: private foo{

};

int main()
{ foo * R;
   printf("Hello, World!");
   R = new bar();
   R->go();
}
 
