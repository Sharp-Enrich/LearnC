#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ui.h"
#include "wand/magick_wand.h"

void test_wand(void)
{
	MagickWand *m_wand = NULL;
	
	int width,height;
	
	MagickWandGenesis();
	
	m_wand = NewMagickWand();
	// Read the image - all you need to do is change "logo:" to some other
	// filename to have this resize and, if necessary, convert a different file
	MagickReadImage(m_wand,"logo:");
	
	// Get the image's width and height
	width = MagickGetImageWidth(m_wand);
	height = MagickGetImageHeight(m_wand);
	
	// Cut them in half but make sure they don't underflow
	if((width /= 2) < 1)width = 1;
	if((height /= 2) < 1)height = 1;
	
	// Resize the image using the Lanczos filter
	// The blur factor is a "double", where > 1 is blurry, < 1 is sharp
	// I haven't figured out how you would change the blur parameter of MagickResizeImage
	// on the command line so I have set it to its default of one.
	MagickResizeImage(m_wand,width,height,LanczosFilter,1);
	
	// Set the compression quality to 95 (high quality = low compression)
	MagickSetImageCompressionQuality(m_wand,95);
	
	/* Write the new image */
	MagickWriteImage(m_wand,"logo_resize.jpg");
	
	/* Clean up */
	if(m_wand)m_wand = DestroyMagickWand(m_wand);
	
	MagickWandTerminus();
}

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


