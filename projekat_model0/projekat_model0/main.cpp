#include <stdlib.h>
#include <string.h>
#include "WAVheader.h"
#include "iir.c"

#define BLOCK_SIZE 16
#define MAX_NUM_CHANNEL 8
#define N_TAP 4
#define MAX_LENGTH 4000

#define dB_2 0.794328
#define dB_4 0.630957

double sampleBuffer[MAX_NUM_CHANNEL][BLOCK_SIZE];

/*typedef struct  
{
	double* pBuff;
	int bufferLength;
	int writeIndex;
	int readIndex[N_TAP];
	int delay[N_TAP];
	double input_gain;
	double tap_gain[N_TAP];
	int n_tap;
} State;
*/
double coeff[][6]={0};

double x_history7[] = {0, 0, 0, 0, 0, 0};
double y_history7[] = {0, 0, 0, 0, 0, 0};

double XTempHistory[] = {0, 0};	
double YTempHistory[] = {0, 0};

/*void p_init(State* state, double* buffer, const int bufLen, 
	const int delay[], const double input_gain, const  double tap_gain[], const int n_tap)
{
	int i;
	for (i = 0; i < bufLen; i++)
	{
		buffer[i] = 0.0;
	}
	state->pBuff = buffer;
	state->bufferLength = bufLen;
	state->writeIndex = bufLen-1;
	state->input_gain = input_gain;
	state->n_tap = n_tap;
	for(i = 0; i< n_tap; i++)
	{
		state->delay[i] = delay[i];
		state->readIndex[i] = bufLen - 1 - delay[i];
		state->tap_gain[i] = tap_gain[i];
	}
	
}
*/
//left surround 3  ok
//left 0
//center 1
//lfe 7
//right 2
//right surround 4

void p_function(){
	int i;
	double temp[16];
	for(i = 0; i < BLOCK_SIZE; i++)
	{	
		//left
		sampleBuffer[0][i]*=dB_4;

		//right
		sampleBuffer[2][i]*=dB_4;

		//center -not final 
		sampleBuffer[1][i]*=dB_2;

		//left surround
		sampleBuffer[3][i]=sampleBuffer[0][i]*(-1);

		//right surround
		sampleBuffer[4][i] = sampleBuffer[2][i]*(-1);

		//lfe -not final
		sampleBuffer[7][i] = sampleBuffer[2][i]*dB_2;

		//center final
		temp[i] = sampleBuffer[1][i];
		sampleBuffer[1][i] += sampleBuffer[7][i];

		//lfe final
		sampleBuffer[7][i] = temp[i] - sampleBuffer[7][i];
	//	Nth_order_IIR(sampleBuffer[7][i], coeff, x_history7[], y_history7[], 6);

	}

	

};

int main(int argc, char* argv[])
{
	FILE *wav_in=NULL;
	FILE *wav_out=NULL;
	char WavInputName[256];
	char WavOutputName[256];
	WAV_HEADER inputWAVhdr,outputWAVhdr;	


	// Multitap delay state and initialization constants
	//-------------------------------------------------
/*	State state;
	double buffer[MAX_LENGTH];
	const int initial_delay[N_TAP] = {1024, 1536, 2560, 3072};
	const double initial_gain[N_TAP] ={0.25, 0.125, 0.0625, 0.0625};
	const double initial_input_gain = 0.5;
	//-------------------------------------------------
*/
	// Init channel buffers
	for(int i=0; i<MAX_NUM_CHANNEL; i++)
		memset(&sampleBuffer[i],0,BLOCK_SIZE);

	// Open input and output wav files
	//-------------------------------------------------
	strcpy(WavInputName,argv[1]);
	wav_in = OpenWavFileForRead (WavInputName,"rb");
	strcpy(WavOutputName,argv[2]);
	wav_out = OpenWavFileForRead (WavOutputName,"wb");
	//-------------------------------------------------

	// Read input wav header
	//-------------------------------------------------
	ReadWavHeader(wav_in,inputWAVhdr);
	//-------------------------------------------------
	
	// Set up output WAV header
	//-------------------------------------------------	
	outputWAVhdr = inputWAVhdr;
	//outputWAVhdr.fmt.NumChannels = inputWAVhdr.fmt.NumChannels; // change number of channels
	outputWAVhdr.fmt.NumChannels = 6;

	int oneChannelSubChunk2Size = inputWAVhdr.data.SubChunk2Size/inputWAVhdr.fmt.NumChannels;
	int oneChannelByteRate = inputWAVhdr.fmt.ByteRate/inputWAVhdr.fmt.NumChannels;
	int oneChannelBlockAlign = inputWAVhdr.fmt.BlockAlign/inputWAVhdr.fmt.NumChannels;
	
	outputWAVhdr.data.SubChunk2Size = oneChannelSubChunk2Size*outputWAVhdr.fmt.NumChannels;
	outputWAVhdr.fmt.ByteRate = oneChannelByteRate*outputWAVhdr.fmt.NumChannels;
	outputWAVhdr.fmt.BlockAlign = oneChannelBlockAlign*outputWAVhdr.fmt.NumChannels;


	// Write output WAV header to file
	//-------------------------------------------------
	WriteWavHeader(wav_out,outputWAVhdr);

	
	// Initialize echo 
//	p_init(&state, buffer, MAX_LENGTH, initial_delay, initial_input_gain, initial_gain, N_TAP);
    

	// Processing loop
	//-------------------------------------------------	
	{
		int sample;
		int BytesPerSample = inputWAVhdr.fmt.BitsPerSample/8;
		const double SAMPLE_SCALE = -(double)(1 << 31);		//2^31
		int iNumSamples = inputWAVhdr.data.SubChunk2Size/(inputWAVhdr.fmt.NumChannels*inputWAVhdr.fmt.BitsPerSample/8);
		
		// exact file length should be handled correctly...
		for(int i=0; i<iNumSamples/BLOCK_SIZE; i++)
		{	
			for(int j=0; j<BLOCK_SIZE; j++)
			{
				for(int k=0; k<inputWAVhdr.fmt.NumChannels; k++)
				{	
					sample = 0; //debug
					fread(&sample, BytesPerSample, 1, wav_in);
					sample = sample << (32 - inputWAVhdr.fmt.BitsPerSample); // force signextend
					sampleBuffer[k][j] = sample / SAMPLE_SCALE;				// scale sample to 1.0/-1.0 range		
				}
			}
			
			p_function();
	

			for(int j=0; j<BLOCK_SIZE; j++)
			{
				for(int k=0; k<outputWAVhdr.fmt.NumChannels; k++)
				{	
					sample = sampleBuffer[k][j] * SAMPLE_SCALE ;	// crude, non-rounding 			
					sample = sample >> (32 - inputWAVhdr.fmt.BitsPerSample);
					fwrite(&sample, outputWAVhdr.fmt.BitsPerSample/8, 1, wav_out);		
				}
			}		
		}
	}
	
	// Close files
	//-------------------------------------------------	
	fclose(wav_in);
	fclose(wav_out);
	//-------------------------------------------------	

	return 0;
}
