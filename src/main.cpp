#include "DxLib.h"
#include "Image.h"
#include "DxlibImage.h"
#include "DxlibTestBoxAndLineImage.h"

// プログラムは WinMain から始まります
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	if( DxLib_Init() == -1 )		// ＤＸライブラリ初期化処理
	{
		return -1 ;			// エラーが起きたら直ちに終了
	}

	Image *img = new DxlibTestBoxAndLineImage(100, 150, true);

	img->drawImage(50, 100);

	delete img;

	WaitKey() ;				// キー入力待ち

	DxLib_End() ;				// ＤＸライブラリ使用の終了処理

	return 0 ;				// ソフトの終了 
}
