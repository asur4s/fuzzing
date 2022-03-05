#include<stdio.h>
#include<libxml/parser.h>
#include<libxml/tree.h>

// question：为什么Harness只是对文件进行初始化后就释放了？
// 攻击面？
int main(int argc, char **argv){
    xmlDocPtr doc = xmlReadFile("test.xml", NULL, 0);
    if(doc != NULL){
        xmlFreeDoc(doc);
        printf("success\n");
    }
}