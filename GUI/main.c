#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ui.h"



int onClosing(uiWindow *w, void *data)
{
    uiQuit();
    return 1;
}

void exitClicked(uiMenuItem *item, uiWindow *w, void *data)
{
	uiQuit();
}

void openClicked(uiMenuItem *item, uiWindow *w, void *data)
{
	char * f = uiOpenFile(w);
    uiLabelSetText(uiLabel(data), f);
}


void helpClicked(uiMenuItem *item, uiWindow *w, void *data)
{
	uiMsgBox(w,
		"ConvPic帮助",
		"请访问 https://github.com/TaceyWong");
}

void aboutClicked(uiMenuItem *item, uiWindow *w, void *data)
{
	uiMsgBox(w,
		"ConvPic v1.0",
		"图片格式转换工具\n\n©Tacey Wong ，遵循MIT协议 \n\n\r鸣谢:\n\tImageMagick");
}





void onClicked(uiButton *b, void *data)
{
    // char msg[32] = "按钮被点击!";
    // uiLabelSetText(uiLabel(data), msg);
    // puts(msg);
    
}

int main(void)
{
    uiInitOptions o;
    const char *err;
    uiWindow *w;
    uiGrid *g;
    uiLabel *l;
    uiButton *b;

    memset(&o, 0, sizeof(uiInitOptions));
    err = uiInit(&o);
    if (err != NULL) {
        puts(err);
        uiFreeInitError(err);
        return 1;
    }
    l = uiNewLabel("请选择文件");

    // 创建菜单
    uiMenuItem *item;
    uiMenu *menu;
    menu = uiNewMenu("文件");
	item = uiMenuAppendItem(menu, "打开");
    uiMenuItemOnClicked(item,openClicked,l);

	item = uiMenuAppendItem(menu, "保存");
    uiMenuItemDisable(item);
	item = uiMenuAppendItem(menu, "导出");
    uiMenuItemDisable(item);
	uiMenuAppendSeparator(menu);
    item = uiMenuAppendItem(menu, "退出");
    uiMenuItemOnClicked(item,exitClicked,NULL);





	menu = uiNewMenu("帮助");
	item = uiMenuAppendItem(menu, "帮助");
    uiMenuItemOnClicked(item,helpClicked,NULL);
	item = uiMenuAppendItem(menu, "关于");
    uiMenuItemOnClicked(item,aboutClicked,NULL);

    // 创建Window
    w = uiNewWindow("ConvPic —— 图片格式转化器", 640, 320, 1);
    uiWindowSetMargined(w, 1);


    

    // 创建Grid
    g = uiNewGrid();
    uiGridSetPadded(g, 1);
    uiWindowSetChild(w, uiControl(g));

    // 创建Label
    // l = uiNewLabel("我是一个标签.");
    uiGridAppend(g, uiControl(l),
        0, 2, 2, 1,
        1, uiAlignCenter, 1, uiAlignFill);

    // 创建Button，注册按钮点击时的回调函数
    b = uiNewButton("打开文件");
    // uiButtonOnClicked(b, onOpenBtnClicked, l);
    uiGridAppend(g, uiControl(b),
        0, 2, 2, 1,
        1, uiAlignCenter, 1, uiAlignEnd);

    // 注册窗口关闭时的回调函数
    uiWindowOnClosing(w, onClosing, NULL);

    // 显示窗口
    uiControlShow(uiControl(w));

    // 启动主循环
    uiMain();

    return 0;
}