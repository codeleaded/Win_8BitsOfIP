#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/ImageFilter.h"
#include "/home/codeleaded/System/Static/Library/RLCamera.h"

float Regler1 = 0.5f;
float Regler2 = 0.5f;
int Mode = 0;
Sprite sp;
RLCamera rlc;

void Setup(AlxWindow* w){
	//sp = Sprite_Load("./data/Dogs_3.jpg");
	//sp = Sprite_Load("./data/Linux.png");

	sp = Sprite_None();
	rlc = RLCamera_New(RLCAMERA_DEVICE,RLCAMERA_WIDTH * 2,RLCAMERA_HEIGHT * 2);
}
void Update(AlxWindow* w){
	if(Stroke(ALX_KEY_0).PRESSED) Mode = 0;
	if(Stroke(ALX_KEY_1).PRESSED) Mode = 1;
	if(Stroke(ALX_KEY_2).PRESSED) Mode = 2;
	if(Stroke(ALX_KEY_3).PRESSED) Mode = 3;
	if(Stroke(ALX_KEY_4).PRESSED) Mode = 4;
	if(Stroke(ALX_KEY_5).PRESSED) Mode = 5;
	if(Stroke(ALX_KEY_6).PRESSED) Mode = 6;
	if(Stroke(ALX_KEY_7).PRESSED) Mode = 7;
	if(Stroke(ALX_KEY_8).PRESSED) Mode = 8;
	if(Stroke(ALX_KEY_9).PRESSED) Mode = 9;
	if(Stroke(ALX_KEY_R).PRESSED) Mode = 10;
	if(Stroke(ALX_KEY_T).PRESSED) Mode = 11;
	if(Stroke(ALX_KEY_Z).PRESSED) Mode = 12;
	if(Stroke(ALX_KEY_U).PRESSED) Mode = 13;
	if(Stroke(ALX_KEY_I).PRESSED) Mode = 14;

	if(Stroke(ALX_KEY_W).DOWN) Regler1 *= 1.01;
	if(Stroke(ALX_KEY_S).DOWN) Regler1 *= 0.99;
	if(Stroke(ALX_KEY_E).DOWN) Regler2 *= 1.01;
	if(Stroke(ALX_KEY_D).DOWN) Regler2 *= 0.99;

	Sprite now = Sprite_None();
    int width = 0,height = 0;
    now.img = RLCamera_Get(&rlc,&width,&height);
    now.w = width;
    now.h = height;
    
    Clear(BLACK);

	//Sprite_Render(WINDOW_STD_ARGS,&sp,0.0f,0.0f);

	if(Mode==0){
		Sprite_Render(WINDOW_STD_ARGS,&sp,0.0f,0.0f);
	}else if(Mode==1){
		Sprite trans = ImageFilter_BW_LRGB(&sp,Regler1);
		Sprite_Render(WINDOW_STD_ARGS,&trans,0.0f,0.0f);
		Sprite_Free(&trans);
	}else if(Mode==2){
		Sprite trans = ImageFilter_BW_LN(&sp,Regler1);
		Sprite_Render(WINDOW_STD_ARGS,&trans,0.0f,0.0f);
		Sprite_Free(&trans);
	}else if(Mode==3){
		Sprite trans = ImageFilter_G(&sp);
		Sprite_Render(WINDOW_STD_ARGS,&trans,0.0f,0.0f);
		Sprite_Free(&trans);
	}else if(Mode==4){
		Sprite trans = ImageFilter_G_ImageKernel3x3(&sp,ImageKernel3x3_Blur());
		Sprite_Render(WINDOW_STD_ARGS,&trans,0.0f,0.0f);
		Sprite_Free(&trans);
	}else if(Mode==5){
		Sprite trans = ImageFilter_G_ImageKernel3x3(&sp,ImageKernel3x3_Sharpen());
		Sprite_Render(WINDOW_STD_ARGS,&trans,0.0f,0.0f);
		Sprite_Free(&trans);
	}else if(Mode==6){
		Sprite trans = ImageFilter_G_ImageKernel3x3(&sp,ImageKernel3x3_Sobel_V());
		Sprite_Render(WINDOW_STD_ARGS,&trans,0.0f,0.0f);
		Sprite_Free(&trans);
	}else if(Mode==7){
		Sprite trans = ImageFilter_G_ImageKernel3x3(&sp,ImageKernel3x3_Sobel_H());
		Sprite_Render(WINDOW_STD_ARGS,&trans,0.0f,0.0f);
		Sprite_Free(&trans);
	}else if(Mode==8){
		Sprite trans = ImageFilter_BW_Morpho_Dilation(&sp,Regler1);
		Sprite_Render(WINDOW_STD_ARGS,&trans,0.0f,0.0f);
		Sprite_Free(&trans);
	}else if(Mode==9){
		Sprite trans = ImageFilter_BW_Morpho_Erosion(&sp,Regler1);
		Sprite_Render(WINDOW_STD_ARGS,&trans,0.0f,0.0f);
		Sprite_Free(&trans);
	}else if(Mode==10){
		Sprite trans = ImageFilter_BW_Morpho_Edge(&sp,Regler1);
		Sprite_Render(WINDOW_STD_ARGS,&trans,0.0f,0.0f);
		Sprite_Free(&trans);
	}else if(Mode==11){
		Sprite trans = ImageFilter_G_Median(&sp);
		Sprite_Render(WINDOW_STD_ARGS,&trans,0.0f,0.0f);
		Sprite_Free(&trans);
	}else if(Mode==12){
		Sprite trans = ImageFilter_G_Adaptive(&sp,Regler1);
		Sprite_Render(WINDOW_STD_ARGS,&trans,0.0f,0.0f);
		Sprite_Free(&trans);
	}else if(Mode==13){
		Sprite trans = ImageFilter_C_Motion(&sp,&now,Regler1);
		Sprite_Render(WINDOW_STD_ARGS,&trans,0.0f,0.0f);
		Sprite_Free(&trans);
	}else if(Mode==14){
		Sprite trans = ImageFilter_G_TemporalRC(&sp,&now,Regler1);
		Sprite_Render(WINDOW_STD_ARGS,&trans,0.0f,0.0f);
		Sprite_Free(&trans);
	}

	String str = String_Format("Info: %d -> %f, %f",Mode,Regler1,Regler2);
	CStr_RenderSizeAlxFont(WINDOW_STD_ARGS,&window.AlxFont,str.Memory,str.size,0.0f,0.0f,RED);
	String_Free(&str);

	Sprite_Free(&sp);
	sp = now;
}
void Delete(AlxWindow* w){
	Sprite_Free(&sp);
	RLCamera_Free(&rlc);
}

int main(){
    if(Create("8Bits of Image Processing",2500,1200,1,1,Setup,Update,Delete))
        Start();
    return 0;
}