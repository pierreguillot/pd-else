// Porres 2016

#include "m_pd.h"
#include <math.h>

static t_class *cents2ratio_class;

typedef struct _cents2ratio {
  t_object x_obj;
  t_inlet *x_inlet;
  t_outlet *x_outlet;
} t_cents2ratio;

void *cents2ratio_new(void);
static t_int * cents2ratio_perform(t_int *w);
static void cents2ratio_dsp(t_cents2ratio *x, t_signal **sp);

static t_int * cents2ratio_perform(t_int *w)
{
  t_cents2ratio *x = (t_cents2ratio *)(w[1]); // ???
  int n = (int)(w[2]);
  t_float *in = (t_float *)(w[3]);
  t_float *out = (t_float *)(w[4]);
  while(n--)
*out++ = pow(2, (*in++/1200));
  return (w + 5);
}

static void cents2ratio_dsp(t_cents2ratio *x, t_signal **sp)
{
  dsp_add(cents2ratio_perform, 4, x, sp[0]->s_n, sp[0]->s_vec, sp[1]->s_vec);
}

void *cents2ratio_new(void)
{
  t_cents2ratio *x = (t_cents2ratio *)pd_new(cents2ratio_class); 
  x->x_inlet = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
  x->x_outlet = outlet_new(&x->x_obj, &s_signal);
  return (void *)x;
}

void cents2ratio_tilde_setup(void) {
  cents2ratio_class = class_new(gensym("cents2ratio~"),
    (t_newmethod) cents2ratio_new, 0, sizeof (t_cents2ratio), CLASS_NOINLET, 0);
  class_addmethod(cents2ratio_class, (t_method) cents2ratio_dsp, gensym("dsp"), 0);
}