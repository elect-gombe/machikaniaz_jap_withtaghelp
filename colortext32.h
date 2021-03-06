#define WIDTH_X	30 // 横方向文字数
#define WIDTH_Y	27 // 縦方向文字数
#define ATTROFFSET	(WIDTH_X*WIDTH_Y) // VRAM上のカラーパレット格納位置

// 入力ボタンのポート、ビット定義
#define KEYPORT PORTB
#define KEYUP 0x0400
#define KEYDOWN 0x0080
#define KEYLEFT 0x0100
#define KEYRIGHT 0x0200
#define KEYSTART 0x0800
#define KEYFIRE 0x4000

extern volatile char drawing;		//　表示期間中は-1
extern volatile unsigned short drawcount;		//　1画面表示終了ごとに1足す。アプリ側で0にする。
							// 最低1回は画面表示したことのチェックと、アプリの処理が何画面期間必要かの確認に利用。
extern unsigned char TVRAM[]; //テキストビデオメモリ

extern const unsigned char FontData[]; //フォントパターン定義
extern unsigned char *cursor;
extern unsigned char cursorcolor;
extern unsigned char *fontp;

void start_composite(void); //カラーコンポジット出力開始
void stop_composite(void); //カラーコンポジット出力停止
void init_composite(void); //カラーコンポジット出力初期化
void clearscreen(void); //画面クリア
void set_palette(unsigned char n,unsigned char b,unsigned char r,unsigned char g); //パレット設定
void set_bgcolor(unsigned char b,unsigned char r,unsigned char g); //バックグランドカラー設定

void vramscroll(void);
	//1行スクロール
void setcursor(unsigned char x,unsigned char y,unsigned char c);
	//カーソル位置とカラーを設定
void setcursorcolor(unsigned char c);
	//カーソル位置そのままでカラー番号をcに設定
void printchar(unsigned char n);
	//カーソル位置にテキストコードnを1文字表示し、カーソルを1文字進める
void printstr(unsigned char *s);
	//カーソル位置に文字列sを表示
void printnum(unsigned int n);
	//カーソル位置に符号なし整数nを10進数表示
void printnum2(unsigned int n,unsigned char e);
	//カーソル位置に符号なし整数nをe桁の10進数表示（前の空き桁部分はスペースで埋める）
void cls(void);
	//画面消去し、カーソルを先頭に移動
void startPCG(unsigned char *p,int a);
	// RAMフォント（PCG）の利用開始、pがフォント格納場所、aが0以外でシステムフォントをコピー
void stopPCG(void);
	// RAMフォント（PCG）の利用停止
