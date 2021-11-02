//华氏温度转摄氏温度

#include <stdio.h>
#include <stdlib.h>

#define FREEZING_PT 32.0f
#define SCALE_FACTOR (5.0f / 9.0f)


int main(void)
{
    float f,c;
    printf("请输入华氏温度:");
    scanf("%f",&f);
    c = (f-FREEZING_PT)*SCALE_FACTOR;
    printf("摄氏温度等于:%.1f\n",c);
    return EXIT_SUCCESS;

}