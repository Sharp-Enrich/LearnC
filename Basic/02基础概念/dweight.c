// 计算盒子空间重量


#include <stdio.h>

int main(void){
    int height,length,width,volume,weight;
    height = 8;
    length = 12;
    width = 10;
    volume = height*length*width;
    weight = (volume+165)/166;
    printf("三维尺寸:%dx%d%d\n",length,width,height);
    printf("体积：%d\n",volume);
    printf("空间重量:%d\n",weight);
    return 0;
}