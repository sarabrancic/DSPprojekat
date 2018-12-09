/*
MODEL1

output_mode (default)= 2_2_0 = 0   3_2_1 = 1

l   -> 0
c   -> 1
r   -> 2
ls  -> 3
rs  -> 4
lfe -> 5
*/

#include <stdlib.h>
#include <string.h>
#include "WAVheader.h"

#define MODE 0
#define BLOCK_SIZE 16
#define MAX_NUM_CHANNEL 8
#define CHANNEL_NUM 6

#define dB_2 0.794328
#define dB_4 0.630957

double sampleBuffer[MAX_NUM_CHANNEL][BLOCK_SIZE];

double x_history1[] = {0, 0};
double y_history1[] = {0, 0};

double x_history2[] = {0, 0};
double y_history2[] = {0, 0};

double x_history3[] = {0, 0};
double y_history3[] = {0, 0};


double *p;

//LPF 800Hz
double coefficients[]={
					0.00252752227776842360,
					0.00505504455553684730,
					0.00252752227776842360,
					1.00000000000000000000,
					-1.85214648539593640000,
					0.86234862603008133000
					};

double second_order_IIR(double input, double* coefficients, double* x_history, double* y_history) {
    double output = 0;
	double tempY = *y_history;
	double tempX = *x_history;

    output += *(coefficients++) *   input;        /* A0 * x(n)   */
    output += *(coefficients++) * *(x_history++); /* A1 * x(n-1) */
    output += *(coefficients++) * *(x_history--); /* A2 * x(n-2) */
    output -= *(coefficients++) * *(y_history++); /* B1 * y(n-1) */
    output -= *coefficients * *(y_history--);     /* B2 * y(n-2) */

	*(++y_history) = tempY;	  /* y(n-2) = y(n-1) */
	*(--y_history) = output;  /* y(n-1) = y(n)   */
	*(++x_history) = tempX;   /* x(n-2) = x(n-1) */
	*(--x_history) = input;	  /* x(n-1) = x(n)   */

    return output;

}

void p_function(){

	for( p = sampleBuffer[0]; p<sampleBuffer[0]+ BLOCK_SIZE; p++)
	{	
		//first step
		*p *= dB_4;
		*(p+16) *=dB_4;

		//left DONE
		
		//right
		*(p+32) = *(p+16);

		//left surround
		*(p+48) = *p * (-1);

		//right surround
		*(p+64) = *(p+32) *(-1);

		if(MODE == 1){

			//center -not final 
			*(p+16) = *(p+16) * dB_2;

			//lfe -not final
			*(p+80) = *(p+32) * dB_2;

			//center final
			*(p+16) += *(p+80);

			//lfe final
			*(p+80) = *(p+16) * (-1);
			second_order_IIR(*(p+80), coefficients, x_history1,  y_history1);
			second_order_IIR(*(p+80), coefficients, x_history2,  y_history2);
			second_order_IIR(*(p+80), coefficients, x_history3,  y_history3);
		}
		else
		{	//delete center and lfe
			*(p+16) = 0;
			*(p+80) = 0;
		}
	}

};

int main(int argc, char* argv[])
{
	FILE *wav_in=NULL;
	FILE *wav_out=NULL;
	char WavInputName[256];
	char WavOutputName[256];
	WAV_HEADER inputWAVhdr,outputWAVhdr;	

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
	outputWAVhdr.fmt.NumChannels = CHANNEL_NUM;

	int oneChannelSubChunk2Size = inputWAVhdr.data.SubChunk2Size/inputWAVhdr.fmt.NumChannels;
	int oneChannelByteRate = inputWAVhdr.fmt.ByteRate/inputWAVhdr.fmt.NumChannels;
	int oneChannelBlockAlign = inputWAVhdr.fmt.BlockAlign/inputWAVhdr.fmt.NumChannels;
	
	outputWAVhdr.data.SubChunk2Size = oneChannelSubChunk2Size*outputWAVhdr.fmt.NumChannels;
	outputWAVhdr.fmt.ByteRate = oneChannelByteRate*outputWAVhdr.fmt.NumChannels;
	outputWAVhdr.fmt.BlockAlign = oneChannelBlockAlign*outputWAVhdr.fmt.NumChannels;


	// Write output WAV header to file
	//-------------------------------------------------
	WriteWavHeader(wav_out,outputWAVhdr);

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

			// process function
			//--------------------------
			p_function();
			//--------------------------

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
