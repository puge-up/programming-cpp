#pragma pack(push)
#pragma pack(1)

//压缩源程序
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define		TRUE		1
#define		FALSE		0

#define		NOT_FOUND	-1

#define		TARGET_FILE_EXT		".Mechuf"

#define		SET_BIT(byte, i)	(byte |= 1 << (7 ^ (i)))  //设置这个字节的指定位为1
#define		CLR_BIT(byte, i)	(byte &= ~(1 << (7 ^ (i)))) //设置这个字节的指定位为0

typedef unsigned char	u8;
typedef u8	boolean;
typedef unsigned int	u32;

typedef struct FREQ{  //统计字符种类及频度
	u8 alpha;  //字符种类,0-255
	u32	freq;  //字符频度
}FREQ;

typedef struct HUFF_TABLE{  //哈夫曼表
	FREQ freq;   //字符种类及频度
	short leftChild;  //左孩子下标
	short rightChild; //右孩子下标
	u8	isVisited;    //是否访问的标记
	char *huffCode;   //哈夫曼编码
}HUFF_TABLE;

typedef struct MECHUF_HEAD{
	char flag[6];				//文件标识
	u8 alphaCount;				//字符种类个数 alphaCount*5 字符及其出现频度的数据块大小
	u32 bitsCount;				//压缩结果范围 
}MECHUF_HEAD;

int getFreq(char *fileName, FREQ **freq);
void showFreq(const FREQ *freq, int alphaCount);
HUFF_TABLE *initHuffTab(FREQ *freq, int alphaCount);  //初始化哈夫曼表(叶子结点)
void destoryHuffTab(HUFF_TABLE **huf, int alphaCount);
void showHuffTab(HUFF_TABLE *huf, int alphaCount);
int findMinFreqIndex(HUFF_TABLE *huf, int count);
void makeHuffTree(HUFF_TABLE *huf, int count);
void makeHuffCode(HUFF_TABLE *huf, int root, char *str, int index);
void getTargetFileName(char *, char *);
void coddingFile(HUFF_TABLE *, FREQ *, int , char *, char *);
void setIndexOfCh(HUFF_TABLE *huf, int alphaCount, short *ar);
void encoddingFile(HUFF_TABLE *huf, int alphaCount, char *tgFile);

void encoddingFile(HUFF_TABLE *huf, int alphaCount, char *tgFile){
	FILE *fp;
	FILE *fpout;
	int ch;
	int root = 2*(alphaCount-1);

	if((fp = fopen(tgFile, "r")) == NULL){
		printf("没有目标文件:%s！\n", tgFile);
		return;
	}
	if((fpout = fopen("zhomecaaa.txt", "w")) == NULL){
		return;
	}

	while(!feof(fp)){
		if(huf[root].leftChild != -1){
			ch = fgetc(fp);
			root = ch == '0' ? huf[root].leftChild : huf[root].rightChild;
		}else{
			fputc(huf[root].freq.alpha & 0x000000FF, fpout);
			root = 2*(alphaCount-1);
		}
	}

	fclose(fp);
	fclose(fpout);
}

void setIndexOfCh(HUFF_TABLE *huf, int alphaCount, short *ar){
	int i;

	for(i = 0; i < alphaCount; i++){
		ar[huf[i].freq.alpha] = i;
	}
}

void coddingFile(HUFF_TABLE *huf, FREQ *freq, int alphaCount, char *scFile, char *tgFile){
	FILE *fpin;
	FILE *fpout;
	int ch;
	short indexOfch[256] = {0};
	MECHUF_HEAD head = {'M','E','C','H','U','F', 0};
	u8 hCode;
	u8 bitIndex = 0;
	u8 huffCodeIndex;
	u32 bitsCount = 0;
		
	setIndexOfCh(huf, alphaCount, indexOfch);
	if((fpin = fopen(scFile, "r")) == NULL){
		printf("%s文件打开失败！！！", scFile);
		return;
	}
	
	if((fpout = fopen(tgFile, "w+b")) == NULL){
		printf("%s文件创建失败！！！", tgFile);
		return;
	}

	fwrite(&head, sizeof(MECHUF_HEAD), 1, fpout);
	fwrite(freq, sizeof(FREQ), alphaCount, fpout);

	ch = fgetc(fpin);
	while(!feof(fpin)){
		for(huffCodeIndex = 0; huf[indexOfch[ch]].huffCode[huffCodeIndex]; huffCodeIndex++){
			if(huf[indexOfch[ch]].huffCode[huffCodeIndex] == '1'){
				SET_BIT(hCode, bitIndex);
			}else{
				CLR_BIT(hCode, bitIndex);
			}
			if(++bitIndex == 8){
				bitIndex = 0;
				fwrite(&hCode, sizeof(u8), 1, fpout);
			}
			bitsCount++;
		}
		ch = fgetc(fpin);
	}

	if(bitIndex){
		fwrite(&hCode, sizeof(u8), 1, fpout);
	}
	
	fseek(fpout, 0, SEEK_SET);

	head.alphaCount = alphaCount;
	head.bitsCount = bitsCount;
	fwrite(&head, sizeof(MECHUF_HEAD), 1, fpout);

	printf("%x, %x\n", head.alphaCount, head.bitsCount);

	fclose(fpout);
	fclose(fpin);
}

void getTargetFileName(char *sourceFileName, char *targetFileName){
	int lastDotIndex = NOT_FOUND;
	int i;
	char sName[80];

	strcpy(sName, sourceFileName);
	for(i = 0; sName[i]; i++){
		if(sName[i] == '.'){
			lastDotIndex = i;
		}
	}

	if(lastDotIndex != NOT_FOUND){
		sName[lastDotIndex] = 0;
	}

	strcpy(targetFileName, sName);
	strcat(targetFileName, TARGET_FILE_EXT);
}


void makeHuffCode(HUFF_TABLE *huf, int root, char *str, int index){
	if(huf[root].leftChild == -1){
		str[index] = 0;
		strcpy(huf[root].huffCode, str);
	}else{
		str[index] = '0';
		makeHuffCode(huf, huf[root].leftChild, str, index+1);

		str[index] = '1';
		makeHuffCode(huf, huf[root].rightChild, str, index+1);
	}
}

void makeHuffTree(HUFF_TABLE *huf, int count){
	short leftChildIndex;
	short rightChildIndex;
	int i;
	int alphaCount = count;


	for(i = 0; i < alphaCount-1; i++){
		leftChildIndex = findMinFreqIndex(huf, count);
		rightChildIndex = findMinFreqIndex(huf, count);
		huf[count].freq.alpha = '#';
		huf[count].freq.freq = huf[leftChildIndex].freq.freq + huf[rightChildIndex].freq.freq;
		huf[count].leftChild = leftChildIndex;
		huf[count].rightChild = rightChildIndex;
		huf[count].isVisited =	FALSE;
		huf[count].huffCode = NULL;
		++count;
	}
}

int findMinFreqIndex(HUFF_TABLE *huf, int count){
	int minIndex = -1;
	int i;

	for(i = 0; i < count; i++){
		if(huf[i].isVisited == FALSE && (minIndex == -1 || huf[minIndex].freq.freq > huf[i].freq.freq)){
			minIndex = i;
		}
	}

	huf[minIndex].isVisited = TRUE;

	return minIndex;
}

void showHuffTab(HUFF_TABLE *huf, int alphaCount){
	int i = 0; 

	printf("%4s %4s %4s %6s %6s %6s %s\n", "下标", "字符", "频度", "左孩子", "右孩子", "访问否", "哈夫曼编码");
	
	for(i = 0; i < alphaCount; i++){
		printf("%4d %4c %4d %6d %6d %6d %s\n", i, huf[i].freq.alpha, huf[i].freq.freq, huf[i].leftChild, huf[i].rightChild, huf[i].isVisited, huf[i].huffCode);
	}
}

void destoryHuffTab(HUFF_TABLE **huf, int alphaCount){
	int i;

	for(i = 0; i < alphaCount; i++){
		free((*huf)[i].huffCode);
	}

	free(*huf);
	*huf = NULL;
}

HUFF_TABLE *initHuffTab(FREQ *freq, int alphaCount){
	HUFF_TABLE *huf = NULL;
	int i;

	huf = (HUFF_TABLE *)calloc(sizeof(HUFF_TABLE), alphaCount*2 - 1);
	for(i = 0; i < alphaCount; i++){
		huf[i].freq.alpha = freq[i].alpha;
		huf[i].freq.freq = freq[i].freq;
		huf[i].leftChild = huf[i].rightChild = -1;
		huf[i].isVisited = FALSE;
		huf[i].huffCode = (char *)calloc(sizeof(char), alphaCount);
	}

	return huf;
}

void showFreq(const FREQ *freq, int alphaCount){
	int i;

	puts("字符\t频度");
	for(i = 0; i < alphaCount; i++){
		printf("%c\t%d\n", freq[i].alpha, freq[i].freq);
	}
}

int getFreq(char *fileName, FREQ **freq){
	int alpha[256] = {0};
	int i;
	int ch;
	int alphaCount = 0;
	int index = 0;
	FILE *fp;

	if((fp = fopen(fileName, "r")) == NULL)
		return 0;
	
	ch = fgetc(fp);
	while(!feof(fp)){
		alpha[ch]++;
		ch = fgetc(fp);
	}
	fclose(fp);

	for(i = 0; i < 256; i++){
		if(alpha[i]){
			alphaCount++;
		}
	}

	*freq = (FREQ *)calloc(sizeof(FREQ), alphaCount);

	for(i = 0; i < 256; i++){
		if(alpha[i]){
			(*freq)[index].alpha = i;
			(*freq)[index++].freq = alpha[i];
		}
	}

	return alphaCount;
}

void main(int argc, char **args){
	FREQ *freq = NULL;
	HUFF_TABLE *huf = NULL;
	u8 alphaCount;
	char *code;
	char targetFileName[80] = "aaaaa.txt";

	if(argc <= 1 || argc > 3){
		puts("用法: textFileHuff <源文件名> [目标文件名]");
		return;
	}

	if(argc == 3){
		strcpy(targetFileName, args[2]);
	}else{
		getTargetFileName(args[1], targetFileName);
	}

	alphaCount = getFreq(args[1], &freq);
	code = (char *)calloc(sizeof(char), alphaCount);
	huf = initHuffTab(freq, alphaCount);
	makeHuffTree(huf, alphaCount);
	makeHuffCode(huf, 2*alphaCount - 2, code, 0);
	showHuffTab(huf, 2*alphaCount - 1);
	coddingFile(huf, freq, alphaCount, args[1], targetFileName);

	destoryHuffTab(&huf, alphaCount);
	free(code);
	free(freq);
}

#pragma pack(pop)
