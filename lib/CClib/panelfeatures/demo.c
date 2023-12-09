
/**************************************************************************/
/* PANELFEATURES Package    Release:  1.0    Release Date: 1/15/89        */
/*                          Provider: J. D. Iorio  (speedy!jdi)           */
/**************************************************************************/
//////////////////////////////////////////////////////////////////////////////
// (C) Copyright AT&T 1988
//
//  Sample application program employing wavecalc modules to
//  synthesize complex waveforms by adding the component sine
//  waves.
//////////////////////////////////////////////////////////////////////////////

#include <stream.h>
#include <string.h>

#include "pf.h"
#include "wavecalc.h"

///////////////////////////
int Usermode = INTERACTIVE;	 
///////////////////////////

int ampfunc(panelfeature *);
extern void ALMMS_logo();

panelfeature *machine;  	// our sample machine's frontpanel

main(int argc, char *argv[])
{


    ////////////////////////////////////////////
    // check the argument strings for interactive/non-interactive operation
    // and optional commandline setup arguments

	int commandline = 0;

	for (int a = 1; a<argc; a++)
		if (strcmp(argv[a],"-p") == 0)
			Usermode = PROGRAM;	    // -p means non-graphic mode
		else
		{
			commandline = a;	    // flag text str for setup()
		}

	begin_PF();		// graphics initialization


    ////////////////////////////////////////////
    // create a sample machine using 5 wavecalc modules 

	wavecalc base_gen("Base_Freq.");	
	wavecalc gen1("Harmonic_1");	
	wavecalc gen2("Harmonic_2");	
	wavecalc gen3("Harmonic_3");	
	wavecalc gen4("Harmonic_4");	

	VWFLTknob amps("Harmonic_Amplitudes", "Volts", 1.0, -1.0, 1.0,
					 &ampfunc, 5, 5);

	display plot("SUMMED WAVEFORM",
			"Time","uSec", 10000.0, 0.0, 
			"Amplitude", "Volts", 3.0, -3.0,
			180);

	cluster top("WAVEFORM_ADDITION", NULLFUNC, &plot, &amps,
					gen4.frontpanel,
					gen3.frontpanel,
					gen2.frontpanel,
					gen1.frontpanel,
					base_gen.frontpanel);

	machine = new panel("DEMO", &top, NULL);


    ////////////////////////////////////////////
    // some of the possible setup commands that could be performed to
    // deviate from the default setup of the "machine"
    //   this sequence sets up to approx. a square wave.

	machine->setup("Harmonic_Amplitudes = .81 .27 .09 .03 .01;");
	machine->setup("Base_Freq.; FREQUENCY = 1000;");
	machine->setup("Harmonic_1; FREQUENCY = 3000;");
	machine->setup("Harmonic_2; FREQUENCY = 5000;");
	machine->setup("Harmonic_3; FREQUENCY = 7000;");
	machine->setup("Harmonic_4; FREQUENCY = 9000;");


    ////////////////////////////////////////////
    // allow command line modifications from the user
    // to override any default and programmed setups

	if (commandline)
		machine->setup(argv[commandline]);


        // some local variables to work with
	int working;
	float bfreq, time, timestep, cur_time, tot_ampl;
	panelfeature *basefreqknob;

	// get the pointer to the frequency knob from the base generator
	basefreqknob = (base_gen.frontpanel)->find("FREQUENCY");



    ////////////////////////////////////////////
    // the main execution loop of the sample machine

	for(working=0; working == 0; )
	{

	    ////////////////////////////////////////////
    	    // allow interactive mouse setup if not program mode
		if (Usermode == INTERACTIVE)
		{
			/* until interactive EXIT COMMAND */
			working = machine->panel::user_setup();
			if(working != 0)
				break;
		}
		else
		{
			/* in program mode execute loop once only */ 
			working = 1;
		}


	    ////////////////////////////////////////////
    	    // main measurement cycle for this application machine

		*basefreqknob >> bfreq;		// get the base freq.
		time = 1.0 / bfreq * 1E6;	// compute time step
		timestep = time / 36;		// in microseconds

						// erase the display
						// and set time scale
						// according to base freq
		plot.clear();			
		plot.changeaxis(XAXIS,"Time","uSec", 0.0, time);

		// loop over one cycle of the base frequency
		for( cur_time=0.0; cur_time<time; cur_time=cur_time+timestep)
		{
			// get the base generator amplitude
	    		machine->setup( form("Base_Freq.;ELAPSED TIME = %f;",
					cur_time));

			tot_ampl = base_gen.amp_result;

			// add in results for the active waveform generators
			switch(amps.getsize())
			{
			case 5:
	    			machine->setup(
		    			form("Harmonic_4;ELAPSED TIME = %f;",
					cur_time));
				tot_ampl += gen4.amp_result;
			case 4:
	    			machine->setup(
		    			form("Harmonic_3;ELAPSED TIME = %f;",
					cur_time));
				tot_ampl += gen3.amp_result;
			case 3:
	    			machine->setup(
		    			form("Harmonic_2;ELAPSED TIME = %f;",
					cur_time));
				tot_ampl += gen2.amp_result;
			case 2:
	    			machine->setup(
		    			form("Harmonic_1;ELAPSED TIME = %f;",
					cur_time));
				tot_ampl += gen1.amp_result;
			case 1:
				break;
			}

			// display the result
			plot << cur_time << tot_ampl;
		
		}
	}

	end_PF();		// panelfeatures ending
}


/////////////////////////////////////////////////////////////////////////
// the machine's action function(s)
/////////////////////////////////////////////////////////////////////////
//
// FOR KNOB "Harmonic_Amplitude"
// each time the front panel's amplitude knob is changed, modify
// the amplitude knobs of each wavecalc panel and grey out those
// which the user has de-selected.
//

int ampfunc(panelfeature *p)
{

	panelfeature *h1, *h2, *h3, *h4, *base;
	float ampl_vals[5];


    // if during construction, don't try to locate other knobs

	if(p->getparent() == NULL)
		return(SUCCESS);


    // read the amplitude knob's current values
	*p >> ampl_vals;


    //  find the sub-panels to be modified;
	base = machine->find("Base_Freq.");
	h1 = machine->find("Harmonic_1");
	h2 = machine->find("Harmonic_2");
	h3 = machine->find("Harmonic_3");
	h4 = machine->find("Harmonic_4");

    // NOTE: we do not know how many wavecalc modules were
    // greyed out prior to this call, so we must initialize
    // ALL attributes to the desired state here.

    // depending on the current width of the knob
    // grey unused harmonic sup_panels;

	switch(p->getsize())
	{
	case 1:
		h1->set_attribute(A_GREY);
	case 2:
		h2->set_attribute(A_GREY);
	case 3:
		h3->set_attribute(A_GREY);
	case 4:
		h4->set_attribute(A_GREY);
	case 5:
		break;
	}


    // depending on the current width of the knob
    // un-grey the instrument and set the amplitude

	switch(p->getsize())
	{
	case 5:
		h4->clr_attribute(A_GREY);
	    	machine->setup(
		    form("Harmonic_4;PEAK AMPLITUDE = %f;",ampl_vals[4]));
	case 4:
		h3->clr_attribute(A_GREY);
	    	machine->setup(
		    form("Harmonic_3;PEAK AMPLITUDE = %f;",ampl_vals[3]));
	case 3:
		h2->clr_attribute(A_GREY);
	    	machine->setup(
		    form("Harmonic_2;PEAK AMPLITUDE = %f;",ampl_vals[2]));
	case 2:
		h1->clr_attribute(A_GREY);
	    	machine->setup(
		    form("Harmonic_1;PEAK AMPLITUDE = %f;",ampl_vals[1]));
	case 1:
	    	machine->setup(
		    form("Base_Freq.;PEAK AMPLITUDE = %f;",ampl_vals[0]));

	}


	return(SUCCESS);
}
