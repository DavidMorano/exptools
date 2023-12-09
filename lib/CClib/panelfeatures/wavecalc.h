
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/

// WAVECALC.H
//
//	Copyright (C) ATT 1988
//
// This header file defines the waveform calculator demo class
//    This model will compute the amplitude of a sine or cosine wave 
//    at a specific time given the frequency and peak amplitude.
//
//   History:
//	J. D. Iorio	5/10/88		created


class	wavecalc
{
	enum { SINE, COSINE };

/////////////////////////////////////////////////////////////////////
//  wavecalc action function(s)
/////////////////////////////////////////////////////////////////////
	int	wave_compute(panelfeature *);

/////////////////////////////////////////////////////////////////////
//  wavecalc Front Panel PANELFEATURES
/////////////////////////////////////////////////////////////////////
    // parameter knobs
	panelfeature * elapsed_time;
	panelfeature * freq;
	panelfeature * ampl;
	panelfeature * shape;

    //  result display
	panelfeature * dataout;

    // FRONT PANEL CLUSTER
	panelfeature * maincluster;


//////////////////////////////////////////////////////////////////////////////
public:
/////////////////////////////////////////////////////////////////////
// required public item
/////////////////////////////////////////////////////////////////////

	panelfeature *frontpanel;	// root of panelfeature tree
					// for this model

/////////////////////////////////////////////////////////////////////
// application specific public items
/////////////////////////////////////////////////////////////////////

	float amp_result;		// storage for results of computation


/////////////////////////////////////////////////////////////////////
// constructor / destructor functions
/////////////////////////////////////////////////////////////////////
	wavecalc(char * Iname);
	~wavecalc();
	

};

