/*
MODEL2

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
#include "stdfix_emu.h"
#include "fixed_point_math.h"
#include "common.h"

#define MODE 0
#define BLOCK_SIZE 16
#define MAX_NUM_CHANNEL 8
#define CHANNEL_NUM 6

#define dB_2 FRACT_NUM(0.794328)
#define dB_4 FRACT_NUM(0.630957)


DSPfract sampleBuffer[MAX_NUM_CHANNEL][BLOCK_SIZE];

DSPfract x_history1[] = {FRACT_NUM(0.0), FRACT_NUM(0.0)};
DSPfract y_history1[] = {FRACT_NUM(0.0), FRACT_NUM(0.0)};

DSPfract x_history2[] = {FRACT_NUM(0.0), FRACT_NUM(0.0)};
DSPfract y_history2[] = {FRACT_NUM(0.0), FRACT_NUM(0.0)};

DSPfract x_history3[] = {FRACT_NUM(0.0), FRACT_NUM(0.0)};
DSPfract y_history3[] = {FRACT_NUM(0.0), FRACT_NUM(0.0)};

DSPfract *p;

//LPF 800Hz
DSPfract coefficients[]={
					FRACT_NUM(0.00252752227776842360),
					FRACT_NUM(0.00505504455553684730),
					FRACT_NUM(0.00252752227776842360),
					FRACT_NUM(1.00000000000000000000),
					FRACT_NUM(-1.85214648539593640000),  // Da li treba skalirati????
					FRACT_NUM(0.86234862603008133000)
					};

DSPfract second_order_IIR(DSPfract input, DSPfract* coefficients, DSPfract* x_history, DSPfract* y_history) {
    DSPaccum output = FRACT_NUM(0.0);
	DSPfract tempY = *y_history;
	DSPfract tempX = *x_history;

    output += *(coefficients) *   input;          /* A0 * x(n)   */
    output += *(coefficients++) * *(x_history++); /* A1 * x(n-1) */
    output += *(coefficients++) * *(x_history--); /* A2 * x(n-2) */
    output -= *(coefficients++) * *(y_history++); /* B1 * y(n-1) */
    output -= *coefficients * *(y_history--);     /* B2 * y(n-2) */

	*(++y_history) = tempY;   	/* y(n-2) = y(n-1) */
	*(--y_history) = output;	/* y(n-1) = y(n)   */
	*(++x_history) = tempX;	    /* x(n-2) = x(n-1) */
	*(--x_history) = input;  	/* x(n-1) = x(n)   */

    return FRACT_NUM(output);

}

void p_function(){

	for( p = sampleBuffer[0]; p<sampleBuffer[0]+ BLOCK_SIZE; p++)
	{	
		//first step - input left and right
		*p = (*p) * dB_4;
		*(p+16) = *(p+16) * dB_4;

		//left DONE
		
		//right
		*(p+32) = *(p+16);

		//left surround
		*(p+48) = (*p) * FRACT_NUM(-1.0);

		//right surround
		*(p+64) = *(p+32) * FRACT_NUM(-1.0);

		if(MODE == 1){

			//center -not final 
			*(p+16) = *(p+16) * dB_2;

			//lfe -not final
			*(p+80) = *(p+32) * dB_2;

			//center final
			*(p+16) += *(p+80);

			//lfe final
			*(p+80) = *(p+16) * FRACT_NUM(-1.0);
			second_order_IIR(*(p+80), coefficients, x_history1,  y_history1);
			second_order_IIR(*(p+80), coefficients, x_history2,  y_history2);
			second_order_IIR(*(p+80), coefficients, x_history3,  y_history3);
		}
		else
		{	//delete center and lfe
			*(p+16) = FRACT_NUM(0.0);
			*(p+80) = FRACT_NUM(0.0);
		}
	}

};
DSPint main(DSPint argc, char* argv[])
{
	FILE *wav_in=NULL;
	FILE *wav_out=NULL;
	char WavInputName[256];
	char WavOutputName[256];
	WAV_HEADER inputWAVhdr,outputWAVhdr;	

	// Init channel buffers
	for(DSPint i=0; i<MAX_NUM_CHANNEL; i++)
		for(DSPint j=0; i<BLOCK_SIZE; i++)
			sampleBuffer[i][j]=(0.0);

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

	DSPint oneChannelSubChunk2Size = inputWAVhdr.data.SubChunk2Size/inputWAVhdr.fmt.NumChannels;
	DSPint oneChannelByteRate = inputWAVhdr.fmt.ByteRate/inputWAVhdr.fmt.NumChannels;
	DSPint oneChannelBlockAlign = inputWAVhdr.fmt.BlockAlign/inputWAVhdr.fmt.NumChannels;
	
	outputWAVhdr.data.SubChunk2Size = oneChannelSubChunk2Size*outputWAVhdr.fmt.NumChannels;
	outputWAVhdr.fmt.ByteRate = oneChannelByteRate*outputWAVhdr.fmt.NumChannels;
	outputWAVhdr.fmt.BlockAlign = oneChannelBlockAlign*outputWAVhdr.fmt.NumChannels;


	// Write output WAV header to file
	//-------------------------------------------------
	WriteWavHeader(wav_out,outputWAVhdr);

	// Processing loop
	//-------------------------------------------------	
	{
		long sample;
		DSPint BytesPerSample = inputWAVhdr.fmt.BitsPerSample/8;
		const double SAMPLE_SCALE = -(double)(1 << 31);		//2^31
		DSPint iNumSamples = inputWAVhdr.data.SubChunk2Size/(inputWAVhdr.fmt.NumChannels*inputWAVhdr.fmt.BitsPerSample/8);
		
		// exact file length should be handled correctly...
		for(DSPint i=0; i<iNumSamples/BLOCK_SIZE; i++)
		{	
			for(DSPint j=0; j<BLOCK_SIZE; j++)
			{
				for(DSPint k=0; k<inputWAVhdr.fmt.NumChannels; k++)
				{	
					sample = 0; //debug
					fread(&sample, BytesPerSample, 1, wav_in);
					sample = sample << (32 - inputWAVhdr.fmt.BitsPerSample); // force signextend
					sampleBuffer[k][j] = FRACT_NUM((double)sample / SAMPLE_SCALE);				// scale sample to 1.0/-1.0 range		
				}
			}

			// process function
			//--------------------------
			p_function();
			//--------------------------

			for(DSPint j=0; j<BLOCK_SIZE; j++)
			{
				for(DSPint k=0; k<outputWAVhdr.fmt.NumChannels; k++)
				{	
					sample = sampleBuffer[k][j].toLong() ;	// crude, non-rounding 			
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
