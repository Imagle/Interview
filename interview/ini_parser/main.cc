#include "ini_parser.h"
#include<string.h>
#include <assert.h>

void test1()
{
    const char* ini_text= "a=1\nb=2\n"; 
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "\n", "=")) {
        assert(false);
    }
    //printf("parse is true\n");
    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "");
    printf("test 1 is OK!\n");
}

void test2(){
    qh::INIParser parser;
    std::string ini_text_file("test.ini");
    if (!parser.Parse(ini_text_file)) {
        assert(false);
    }
    const std::string& author = parser.Get("author", NULL);
    assert(author == "ruiqiang");

    std::string name = parser.Get("owner","name", NULL);
    assert(name == "jame");

    const std::string& server = parser.Get("database","server", NULL);
    assert(server == "192.168.0.1");
    
    printf("test 2 is OK!\n");
    
}

int main(int argc, char* argv[])
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好

    test1();
    test2();

    return 0;
}


