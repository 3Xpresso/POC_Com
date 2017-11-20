#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SERIAL_FILE "serial.bin"
//#define SERIAL_FILE "/dev/ttyAMA0"

typedef struct {
	uint8_t Id;
	uint8_t Length;
	uint8_t Data[128];
}frame_t;

int main(int argc, char* argv[])
{
	int i = 0, j = 0;
	int ch;
	FILE *fp;

	frame_t frame;
	uint8_t buff[128];

	printf("CBot - Com Simulation\r\n");

	// Print parameters
	for (i = 0; i < argc; i++)
		printf("%s\r\n", argv[i]);

	// Check parameters
	if (argc < 3) {
		printf("Not enough params - First param is Id\r\n");
		return -1;
	}
	if ((uint8_t)strtol(argv[2], NULL, 16) != (argc - 3)) {
		printf("Param2 != sizeof(Data) - Second param is Length\r\n");
		return -1;
	}

	// Params to Frame
	frame.Id     = (uint8_t)strtol(argv[1], NULL, 16);
	frame.Length = (uint8_t)strtol(argv[2], NULL, 16);
	for(i = 0; i < frame.Length; i++)
		frame.Data[i] = (uint8_t)strtol(argv[3+i], NULL, 16);

	// Fill up Frame
	i = 0;
	buff[i++] = 0x02;					// STX
	buff[i++] = frame.Id;				// Id
	buff[i++] = frame.Length;			// Length
	for(j = 0; j < frame.Length; j++)	// Data
		buff[i++] = frame.Data[j];
	buff[i++] = 0x00;					// CRC16_1
	buff[i++] = 0x00;					// CRC16_2
	buff[i++] = 0x03;					// ETX

	// Push Frame
	fp = fopen(SERIAL_FILE, "w+");
	fwrite(buff, sizeof(uint8_t), i, fp);
	fclose(fp);


	//ch = getchar();	// Wait end
	return 0;
}

