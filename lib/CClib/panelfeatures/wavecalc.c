
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

// WAVECALC.C
//
//	Copyright (C) ATT 1988
//
// This source file defines the operations of the wave calculator
// demo class.
//
//   History:
//	J. D. Iorio	5/10/88		created

#include "pf.h"
#include "wavecalc.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////////////
						// constructor
wavecalc::wavecalc( char * Iname) 
{
				// ENUM type knob labels and values
	static int waveformval[] = {SINE, COSINE};
	static char *waveformlabel[]  = {"Sine","Cosine"};


    // define the instrument panel

    // input parameter knobs
	freq = new INTknob("FREQUENCY", "Hz",10000, 0, 1000, NULLFUNC);
	ampl = new FLTknob("PEAK AMPLITUDE", "Volts",1.0, -1.0, 0.5, NULLFUNC);
	elapsed_time =
		 new INTknob("ELAPSED TIME","uSec.",10000,0,0,NULLFUNC);
	shape = new ENUMknob("WAVE SHAPE",
		 2, waveformlabel, waveformval, SINE, NULLFUNC);

    // display definition
	dataout = new display("RESULT", "AMPLITUDE", "Volts", 0.0, 1.0, 1);

    // front panel and cluster
	maincluster = new cluster("WAVECALC", &wavecalc::wave_compute,
			 dataout, shape, freq, ampl, elapsed_time);
	frontpanel = new panel(Iname, (cluster *)maincluster, this);

}
/////////////////////////////////////////////////////////////////////////////
						// destructor
wavecalc::~wavecalc()
{

    // delete the instrument panel items allocated by the constructor
	delete freq;
	delete ampl;
	delete elapsed_time;
	delete shape;
	delete dataout;
	delete maincluster;
	delete frontpanel;
	
}
/////////////////////////////////////////////////////////////////////////////
//  						// action function
/////////////////////////////////////////////////////////////////////////////
//
// This function is associated with several knobs in the module
// and is invoked whenever any of them is set to a new value
//

int wavecalc::wave_compute(panelfeature *p)
{
	extern double sin(double);
	extern double cos(double);
	wavecalc *model;
	panelfeature *f, *a, *t, *s, *d;
	float fr, am, et;
	int sh;
	float computed;


    // if during construction phase of this instrument,
    //    we cannot store a result in the class since we cannot 
    //    find the pointer to the class

	if((model = (wavecalc *)p->get_this_module()) == (wavecalc *)NULL)
		return(SUCCESS);

    // find the required parameter knobs to perform the calculation

	f = p->find("FREQUENCY");
	a = p->find("PEAK AMPLITUDE");
	t = p->find("ELAPSED TIME");
	s = p->find("WAVE SHAPE");
	d = p->find("RESULT");


    // read the values and compute the result

	*f >> fr;	// current frequency setting
	*a >> am;	// current amplitude setting
	*t >> et;	// current elapsed time setting
	*s >> sh;	// current wave shape setting

	et /= 1000000.0; 	// convert to uSecs

	if(sh == SINE)
		computed = am * (float)sin((double)(6.2832*fr*et));
	else
		computed = am * (float)cos((double)(6.2832*fr*et));
	

    // place result in display and in the result member of the class

	*d << computed;
	model->amp_result = computed;


	return(SUCCESS);
}
