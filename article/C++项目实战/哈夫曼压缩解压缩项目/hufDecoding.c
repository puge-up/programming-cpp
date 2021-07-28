#pragma pack(push)
#pragma pack(1)

//解压缩源程序
#include<stdio.h>
#include<string.h>
#include<malloc.h>

#define TARGET_FILE_EXT		".dhuf"

#define		TRUE		1
#define		FALSE		0

#define		NOT_FOUND	-1
#define		getBit(b, i)	!!((b) & (1 << (7^(i))))

typedef unsigned char	u8;
typedef u8	boolean;
typedef unsigned int	u32;

typedef struct FREQ{
	u8 alpha;
	u32	freq;
}FREQ;

typedef struct HUFF_TABLE{
	FREQ freq;
	short leftChild;
	short rightChild;
	u8	isVisited;
	char *huffCode;
}HUFF_TABLE;

typedef struct MECHUF_HEAD{
	char flag[6];				//文件标识
	u8 alphaCount;				//字符种类个数 alphaCount*5 字符及其出现频度的数据块大小
	u32 bitsCount;				//压缩结果范围 
}MECHUF_HEAD;

void getTargetFileName(char *sourceFileName, char *targetFileName);
boolean getFileHead(char *sourceFileName, MECHUF_HEAD *pHead);
void getAlphaFreq(char *sourceFileName, FREQ **freq, int cnt);
void showFreq(const FREQ *freq, int alphaCount);
HUFF_TABLE *initHuffTab(FREQ *freq, int alphaCount);
void destoryHuffTab(HUFF_TABLE **huf, int alphaCount);
void showHuffTab(HUFF_TABLE *huf, int alphaCount);
int findMinFreqIndex(HUFF_TABLE *huf, int count);
void makeHuffTree(HUFF_TABLE *huf, int count);
void decoding(HUFF_TABLE *huf, MECHUF_HEAD head, char *sourceFileName, char *targetFileName);

void decoding(HUFF_TABLE *huf, MECHUF_HEAD head, char *sourceFileName, char *targetFileName){
	FILE *fpin;
	FILE *fpout;
	int byte = 0;
	int root = 2*(head.alphaCount - 1);
	int bitIndex = 0;
	u32 bitsCount = 0;
	int bitValue = 0;

	if((fpin = fopen(sourceFileName, "rb")) == NULL){
		return;
	}
	
	if((fpout = fopen(targetFileName, "w")) == NULL){
		return;
	}

	fseek(fpin, sizeof(MECHUF_HEAD) + sizeof(FREQ) * head.alphaCount, SEEK_SET);
	fread(&byte, sizeof(char), 1, fpin);
	while(bitsCount <= head.bitsCount){
		if(huf[root].leftChild == -1){
			fputc(huf[root].freq.alpha, fpout);
			root = 2*(head.alphaCount - 1);
		}else{
			bitValue = getBit(byte, bitIndex);
			root = bitValue == 0 ? huf[root].leftChild : huf[root].rightChild;
			bitsCount++;
			if(++bitIndex == 8){
				fread(&byte, sizeof(char), 1, fpin);
				bitIndex = 0;
			}
		}
	}
	
	fclose(fpout);
	fclose(fpin);
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
		printf("%c           %d\n", freq[i].alpha, freq[i].freq);
	}
}

void getAlphaFreq(char *sourceFileName, FREQ **freq, int cnt){
	FILE *fpin;

	if((fpin = fopen(sourceFileName, "rb")) == NULL){
		return;
	}

	*freq = (FREQ *)malloc(sizeof(FREQ) * cnt);

	fseek(fpin, sizeof(MECHUF_HEAD), SEEK_SET);
	fread(*freq, sizeof(FREQ), cnt, fpin);	
	
	fclose(fpin);
}

boolean getFileHead(char *sourceFileName, MECHUF_HEAD *pHead){
	FILE *fpin;

	if((fpin = fopen(sourceFileName, "rb")) == NULL){
		return FALSE;
	}

	fread(pHead, sizeof(MECHUF_HEAD), 1, fpin);

	fclose(fpin);

	return TRUE;
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

void main(int argc, char **argv){
	char sourceFileName[80] = {0};
	char targetFileName[80] = {0};
	MECHUF_HEAD head = {0};
	FREQ *freq = NULL; 
	HUFF_TABLE *huf = NULL;

	if(argc <= 1 || argc > 3){
		puts("Usage : hufDecoding 源文件 [目标文件]");

		return;
	}
	strcpy(sourceFileName, argv[1]);
	if(argc == 3){	// 存在目标文件
		strcpy(targetFileName, argv[2]);
	}else{
		getTargetFileName(sourceFileName, targetFileName);
	}

	getFileHead(sourceFileName, &head);
	getAlphaFreq(sourceFileName, &freq, head.alphaCount);

	huf = initHuffTab(freq, head.alphaCount);
	makeHuffTree(huf, head.alphaCount);
	showHuffTab(huf, 2*head.alphaCount - 1);
	
	decoding(huf, head, sourceFileName, targetFileName);

	destoryHuffTab(&huf, head.alphaCount);
	free(freq);
}

#pragma pack(pop)