// Porres 2017

#include "m_pd.h"
#include <math.h>
#include <string.h>

#define RESCALE_MININ  -1.
#define RESCALE_MAXIN  1.
#define RESCALE_MINOUT  0.
#define RESCALE_MAXOUT  1.
#define RESCALE_EXPO  1.

typedef struct _rescale
{
    t_object x_obj;
    t_inlet  *x_inlet_1;
    t_inlet  *x_inlet_2;
    t_float expo;
} t_rescale;

static t_class *rescale_class;

void rescale_factor(t_rescale *x, t_floatarg f)
{
    x->expo = f < 0. ? 0. : f;
}

static t_int *rescale_perform(t_int *w)
{
    t_rescale *x = (t_rescale *)(w[1]);
    int nblock = (int)(w[2]);
    t_float *in1 = (t_float *)(w[3]);
    t_float *in2 = (t_float *)(w[4]);
    t_float *in3 = (t_float *)(w[5]);
    t_float *out = (t_float *)(w[6]);
    while (nblock--)
    {
    float in = *in1++;
    float ol = *in2++; // Output LOW
    float oh = *in3++; // Output HIGH
    float p = x->expo; // power (exponential) factor
    float output;
    p = p <= 0 ? 0 : p;
    output = ((in + 1) / 2 == 0) ? ol :
    (in + 1) / 2 > 0 ?
    ol + (oh - ol) * pow((in + 1) / 2, p) :
    ol + (oh - ol) * -(pow(((-in - 1) / 2), p));

    *out++ = output;
    }
    return (w + 7);
}

static void rescale_dsp(t_rescale *x, t_signal **sp)
{
    dsp_add(rescale_perform, 6, x, sp[0]->s_n, sp[0]->s_vec, sp[1]->s_vec,
            sp[2]->s_vec, sp[3]->s_vec);
}

static void *rescale_free(t_rescale *x)
{
		inlet_free(x->x_inlet_1);
        inlet_free(x->x_inlet_2);
        return (void *)x;
}

static void *rescale_new(t_symbol *s, int argc, t_atom *argv)
{
    t_rescale *x = (t_rescale *)pd_new(rescale_class);
    t_float min_in, max_in, min_out, max_out, exp;
    min_in = RESCALE_MININ;
    max_in = RESCALE_MAXIN;
    min_out = RESCALE_MINOUT;
    max_out = RESCALE_MAXOUT;
    exp = RESCALE_EXPO;
    
	int argnum = 0;
	while(argc > 0){
		if(argv -> a_type == A_FLOAT)
        {
			t_float argval = atom_getfloatarg(0,argc,argv);
				switch(argnum){
					case 0:
                        min_out = argval;
                        break;
                    case 1:
                        max_out = argval;
                        break;
                    case 2:
                        exp = argval;
                        break;
					default:
						break;
				};
				argc--;
				argv++;
				argnum++;
        }
    };
    x->expo = exp;
    x->x_inlet_1 = inlet_new((t_object *)x, (t_pd *)x, &s_signal, &s_signal);
    pd_float((t_pd *)x->x_inlet_1, min_out);
    x->x_inlet_2 = inlet_new((t_object *)x, (t_pd *)x, &s_signal, &s_signal);
    pd_float((t_pd *)x->x_inlet_2, max_out);

    outlet_new((t_object *)x, &s_signal);
    
    return (x);
}

void rescale_tilde_setup(void)
{
    rescale_class = class_new(gensym("rescale~"),
				(t_newmethod)rescale_new,
                (t_method)rescale_free,
				sizeof(t_rescale), 0, A_GIMME, 0);
    class_addmethod(rescale_class, nullfn, gensym("signal"), 0);
    class_addmethod(rescale_class, (t_method)rescale_dsp, gensym("dsp"), A_CANT, 0);
    class_addmethod(rescale_class, (t_method)rescale_factor, gensym("factor"), A_FLOAT, 0);
}
