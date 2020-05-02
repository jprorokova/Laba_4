#include <cstdint>
#include <fstream>
#include <iostream>

class DataWav {
public:
	DataWav(char fileName[]);//чтение входных данных
	~DataWav();
	void writeWav(char fileName[]);//запись выходных данных
	void interpol(double coef);//функция преобразования
private:
	
    int32_t chunkId;    
    int32_t chunkSize;    
    int32_t format; 
    int32_t subchunk1Id;    
    int32_t subchunk1Size; 
    int16_t audioFormat;    
    int16_t numChannels;   
    int32_t sampleRate;
    int32_t byteRate;  
    int16_t blockAlign; 
    int16_t bitsPerSample;  
    int32_t subchunk2Id;  
    int32_t subchunk2Size;  
    int16_t* data;   
    int16_t* newData; 
    int32_t newSize;
};
