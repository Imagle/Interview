#include <stdio.h>
#include <stdlib.h>
#include "qh_string.h"

int main(int argc, char* argv[])
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好

    char *p = "hello world!";
    qh::string s1(p);
    printf("s1 = [%s]\n", s1.c_str());
    qh::string s2("how are you ?");
    printf("s2 = [%s]\n", s2.data());
    char * q = s2[2];
    printf("q is %c\n", *q);
    *q = 'G';
    printf("s2 = [%s]\n", s2.data());
    qh::string s3;
    printf("%s\n", s3.data());
    qh::string s4(s2);
    printf("s4 = [%s]\n", s4.data());
#ifdef WIN32
    system("pause");
#endif

	return 0;
}

