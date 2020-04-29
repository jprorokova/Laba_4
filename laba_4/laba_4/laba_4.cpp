#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <iostream>
#include <cstdint>
using namespace std;

typedef struct {
	int32_t chunkId;   // Завжди містить значення 0x52494646 (літери "RIFF")
	int32_t chunkSize; // 36 + розмір другого підрозділу в байтах
					   // Іншими словами 4 + (8 + SubChunk1Size) + (8 + SubChunk2Size)
					   // Це розмір всього файла мінус 8 байтів які займають поля chunkId та chunkSize
	int32_t format; // Для wav-файла це завжди 0x57415645 (літери "WAVE")
	int32_t subchunk1Id;   // Завжди 0x666d7420 – літери "fmt "
	int32_t subchunk1Size; // Завжди 16 для аудіо PCM. Це розмір частини підрозділу, що слідує після цього числа
	int32_t audioFormat;   // PCM = 1
	int16_t numChannels;   // Mono = 1, Stereo = 2
	int32_t sampleRate;    // Наприклад 44100
	int32_t byteRate;      // == SampleRate * NumChannels * BitsPerSample/8
	int32_t blockAlign;    // == NumChannels * BitsPerSample/8
	int16_t bitsPerSample; // 8 bits = 8, 16 bits = 16, etc.
	int32_t subchunk2Id;   // 0x64617461 – літери "data"
	int32_t subchunk2Size; // == NumSamples * NumChannels * BitsPerSample/8, кількість байтів аудіоданих
	        // семпли
} RIFFHEADER;


int _tmain(int argc, _TCHAR* argv[])
{
	FILE* file;
	errno_t err;
	err = fopen_s(&file, "data.wav", "rb");
	if (err)
	{
		cout << "Failed open file, error %d" << err;
		return 0;
	}

	RIFFHEADER header;

	fread_s(&header, sizeof(RIFFHEADER), sizeof(RIFFHEADER), 1, file);

	// Выводим полученные данные
	cout<<"Sample rate: %d\n"<< header.sampleRate;
	cout << "Channels: %d\n"<< header.numChannels;
	cout << "Bits per sample: %d\n"<< header.bitsPerSample;

	// Посчитаем длительность воспроизведения в секундах
	float fDurationSeconds = 1.f * header.subchunk2Size / (header.bitsPerSample / 8) / header.numChannels / header.sampleRate;
	int iDurationMinutes = (int)floor(fDurationSeconds) / 60;
	fDurationSeconds = fDurationSeconds - (iDurationMinutes * 60);
	cout << "Duration: %02d:%02.f\n"<< iDurationMinutes<< fDurationSeconds;

	fclose(file);

	cin.get();
	return 0;
}