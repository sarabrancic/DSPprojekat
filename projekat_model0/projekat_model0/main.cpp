/*MODEL0

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

//LPF 800Hz
double coefficients[]={
					0.00252752227776842360,
					0.00505504455553684730,
					0.00252752227776842360,
					1.00000000000000000000,
					-1.85214648539593640000,
					0.86234862603008133000
					};

double x_history1[] = {0, 0};
double y_history1[] = {0, 0};

double x_history2[] = {0, 0};
double y_history2[] = {0, 0};

double x_history3[] = {0, 0};
double y_history3[] = {0, 0};

double second_order_IIR(double input, double* coefficients, double* x_history, double* y_history) {
    double output = 0;

    output += coefficients[0] * input;        /* A0 * x(n)   */
    output += coefficients[1] * x_history[0]; /* A1 * x(n-1) */
    output += coefficients[2] * x_history[1]; /* A2 * x(n-2) */
    output -= coefficients[4] * y_history[0]; /* B1 * y(n-1) */
    output -= coefficients[5] * y_history[1]; /* B2 * y(n-2) */

    
    y_history[1] = y_history[0];    /* y(n-2) = y(n-1) */
    y_history[0] = output;			/* y(n-1) = y(n)   */
    x_history[1] = x_history[0];    /* x(n-2) = x(n-1) */
    x_history[0] = input;           /* x(n-1) = x(n)   */

    return output;
}

void p_function(){

	int i;

	for(i = 0; i < BLOCK_SIZE; i++)
	{	
		//first step
		sampleBuffer[0][i]*=dB_4;
		sampleBuffer[1][i]*=dB_4;
		
		//left DONE

		//right
		sampleBuffer[2][i] = sampleBuffer[1][i];

		//left surround
		sampleBuffer[3][i]=sampleBuffer[0][i]*(-1);

		//right surround
		sampleBuffer[4][i] = sampleBuffer[2][i]*(-1);
		
		if(MODE == 1){

			//center -not final 
			sampleBuffer[1][i]*=dB_2;

			//lfe -not final
			sampleBuffer[5][i] = sampleBuffer[2][i]*dB_2;

			//center final
			sampleBuffer[1][i] += sampleBuffer[5][i];

			//lfe final
			sampleBuffer[5][i] = sampleBuffer[1][i] * (-1);
			second_order_IIR(sampleBuffer[5][i], coefficients, x_history1,  y_history1);
			second_order_IIR(sampleBuffer[5][i], coefficients, x_history2,  y_history2);
			second_order_IIR(sampleBuffer[5][i], coefficients, x_history3,  y_history3);

		}
		else
		{	//delete center and lfe
			sampleBuffer[1][i] = 0;
			sampleBuffer[5][i] = 0;
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
