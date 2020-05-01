#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <iostream>
#include <cstdint>
#include"Header.h"
using namespace std;

class DataWaw;

void DataWav::writeWav(char filename[])
{
	FILE* in;
	errno_t err;
	err = fopen_s(&in, filename, "rb");
	if (err) {
		cout << "Failed to open input file, error: " << err;
		exit(-1);
	}
	fread(&this->chunkId, sizeof(this->chunkId), 1, in);
	fread(&this->chunkSize, sizeof(this->chunkSize), 1, in);
	fread(&this->format, sizeof(this->format), 1, in);
	fread(&this->subchunk1Id, sizeof(this->subchunk1Id), 1, in);
	fread(&this->subchunk1Size, sizeof(this->subchunk1Size), 1, in);
	fread(&this->audioFormat, sizeof(this->audioFormat), 1, in);
	fread(&this->numChannels, sizeof(this->numChannels), 1, in);
	fread(&this->sampleRate, sizeof(this->sampleRate), 1, in);
	fread(&this->byteRate, sizeof(this->byteRate), 1, in);
	fread(&this->blockAlign, sizeof(this->blockAlign), 1, in);
	fread(&this->bitsPerSample, sizeof(this->bitsPerSample), 1, in);
	fread(&this->subchunk2Id, sizeof(this->subchunk2Id), 1, in);
	fread(&this->subchunk2Size, sizeof(this->subchunk2Size), 1, in);
	this->data = new int16_t[this->subchunk2Size / this->blockAlign];//��������� ��������� �����

	for (int i = 0; i < this->subchunk2Size / this->blockAlign; i++)
	{
		int16_t temp;
		fread(&temp, sizeof(this->blockAlign), 1, in);
		this->data[i] = temp;
	}

	fclose(in);

}

DataWav::~DataWav()
{
	delete[] this-> newData;
	delete[] this->data;
}

void DataWav::interpol(double coef)
{
	this->newSize = this->subchunk2Size * coef;
	this->newData = new int16_t[this->newSize];
	int temp;
	int32_t x0, x1, y0, y1, y, x;
	for (int i = 0; i < this->subchunk2Size / this->blockAlign; i++) { 
		temp = i * coef;
		this->newData[temp] = this->data[i];
	}
	for (int i = 0; i < this->subchunk2Size / this->blockAlign - 1; i++) {
		x0 = i * coef;// �0 - ������� ����� � ����� ������� ������
		x1 = (i + 1) * coef;
		y0 = this->newData[x0];
		y1 = this->newData[x1];
		temp = x1 -1- x0 ; // (x - x0), x0-������� ����� ����������� , �1- ������� ����� ������ ����������
		for (int j = 1; j < temp+1 ; j++) { //����� ���� ����������� 
			y = ((y1 - y0) * j) / (x1 - x0) + y0;// ������� ����������������� ������
			x = x1 - 1;//������� �������� , ������� ����� ����� 
			this->newData[x] = y;
		}
	}
	this->chunkSize += this->newSize - this->subchunk2Size;
	this->subchunk2Size = this->newSize;
}