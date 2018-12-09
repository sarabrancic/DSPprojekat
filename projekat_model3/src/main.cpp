/*
MODEL3

output_mode (default)= 2_2_0 = 0   3_2_1 = 1

l   -> 0
c   -> 1
r   -> 2
ls  -> 3
rs  -> 4
lfe -> 5

*/

#include <stdio.h>
#include <dsplib\wavefile.h>
#include <string.h>
#include <common.h>

#define MODE 1
#define BLOCK_SIZE 16
#define MAX_NUM_CHANNEL 8
#define CHANNEL_NUM 6

#define dB_2 FRACT_NUM(0.794328)
#define dB_4 FRACT_NUM(0.630957)

__memY DSPfract input_gain = dB_4;
__memY DSPfract gain2 =dB_2;

__memX DSPfract sampleBuffer[MAX_NUM_CHANNEL][BLOCK_SIZE];

__memX DSPfract x_history1[] = {FRACT_NUM(0.0), FRACT_NUM(0.0)};
__memY DSPfract y_history1[] = {FRACT_NUM(0.0), FRACT_NUM(0.0)};

__memX DSPfract x_history2[] = {FRACT_NUM(0.0), FRACT_NUM(0.0)};
__memY DSPfract y_history2[] = {FRACT_NUM(0.0), FRACT_NUM(0.0)};

__memX DSPfract x_history3[] = {FRACT_NUM(0.0), FRACT_NUM(0.0)};
__memY DSPfract y_history3[] = {FRACT_NUM(0.0), FRACT_NUM(0.0)};

__memX DSPfract *p;

//LPF 800Hz
__memY DSPfract coefficients[]={
					FRACT_NUM(0.00252752227776842360),
					FRACT_NUM(0.00505504455553684730),
					FRACT_NUM(0.00252752227776842360),
					FRACT_NUM(1.00000000000000000000),
					FRACT_NUM(-0.92607324269796820000),//(-1.85214648539593640000/2),
					FRACT_NUM(0.86234862603008133000)
					};


extern void p_function();

DSPfract second_order_IIR(DSPfract input, __memY DSPfract* coefficients, __memX DSPfract* x_history, __memY DSPfract* y_history) {
    DSPaccum output = 0;
    DSPfract tempY = *y_history;
    DSPfract tempX = *x_history;

    //output += *(coefficients) *   input;          /* A0 * x(n)   */
    asm("x0 = xmem[%1]; %1+=1 \n\t %0+=x0*%2" : "+a"(output) , "+i"(coefficients) : "y"(input));

    //output += *(coefficients++) * *(x_history++); /* A1 * x(n-1) */
    asm("x0 = xmem[%1]; %1+=1 \n\t x1 = xmem[%2]; %2+=1 \n\t %0+=x0*x1" : "+a"(output) , "+i"(coefficients) , "+i"(x_history));

    //output += *(coefficients++) * *(x_history--); /* A2 * x(n-2) */
    asm("x0 = xmem[%1]; %1+=1 \n\t x1 = xmem[%2]; %2-=1 \n\t %0+=x0*x1" : "+a"(output) , "+i"(coefficients) , "+i"(x_history));

    //output -= *(coefficients++) * *(y_history++); /* B1 * y(n-1) */
    asm("x0 = xmem[%1]; %1+=1 \n\t y0 = ymem[%2]; %2+=1 \n\t %0-=x0*y0" : "+a"(output), "+i"(coefficients) , "+i"(y_history));

    //output -= *coefficients * *(y_history);
    asm("x0 = xmem[%1] \n\t y0 = ymem[%2];              \n\t %0-=x0*y0" : "+a"(output), "+i"(coefficients) , "+i"(y_history));

    //output -= *coefficients * *(y_history--);     /* B2 * y(n-2) */
    asm("x0 = xmem[%1] \n\t y0 = ymem[%2]; %2-=1        \n\t %0-=x0*y0" : "+a"(output), "+i"(coefficients) , "+i"(y_history));


	*(++y_history) = tempY;   	/* y(n-2) = y(n-1) */
	*(--y_history) = output;	/* y(n-1) = y(n)   */
	*(++x_history) = tempX;	    /* x(n-2) = x(n-1) */
	*(--x_history) = input;  	/* x(n-1) = x(n)   */

    return (output);

}

int main(int argc, char *argv[])
 {
    WAVREAD_HANDLE *wav_in;
    WAVWRITE_HANDLE *wav_out;

	char WavInputName[256];
	char WavOutputName[256];

    int nChannels;
	int bitsPerSample;
    int sampleRate;
    int iNumSamples;

	// Open input wav file
	//-------------------------------------------------
	strcpy(WavInputName, argv[0]);
	wav_in = cl_wavread_open(WavInputName);
	if(wav_in == NULL)
    {
        printf("Error: Could not open input wavefile.\n");
        return -1;
    }
	//-------------------------------------------------

	// Read input wav header
	//-------------------------------------------------
	nChannels = cl_wavread_getnchannels(wav_in);
    bitsPerSample = cl_wavread_bits_per_sample(wav_in);
    sampleRate = cl_wavread_frame_rate(wav_in);
    iNumSamples =  cl_wavread_number_of_frames(wav_in);
	//-------------------------------------------------

	// Open output wav file
	//-------------------------------------------------
	strcpy(WavOutputName, argv[1]);
	wav_out = cl_wavwrite_open(WavOutputName, bitsPerSample, CHANNEL_NUM, sampleRate);  //izmenjen broj kanala
	if(!wav_out)
    {
        printf("Error: Could not open output wavefile.\n");
        return -1;
    }
	//-------------------------------------------------

	// Processing loop
	//-------------------------------------------------
    {
		int i;
		int j;
		int k;
		int sample;
		int bound = iNumSamples/BLOCK_SIZE;

		for(i=0; i< bound; i++)
		{
			for(j=0; j<BLOCK_SIZE; j++)
			{
				for(k=0; k<nChannels; k++)
				{
					sample = cl_wavread_recvsample(wav_in);
					sampleBuffer[k][j] = rbits(sample);
				}
			}

			// processing...
			//-------------------------------------------------
			p_function();
			//-------------------------------------------------

			for(j=0; j<BLOCK_SIZE; j++)
			{
				for(k=0; k<CHANNEL_NUM; k++)
				{
					sample = bitsr(sampleBuffer[k][j]);
					cl_wavwrite_sendsample(wav_out, sample);
				}
			}
		}
	}

	// Close files
	//-------------------------------------------------
    cl_wavread_close(wav_in);
    cl_wavwrite_close(wav_out);
	//-------------------------------------------------

    return 0;
 }
