// Porres 2017

// alias of loadbanger

#include "m_pd.h"
#include "g_canvas.h"

typedef struct _lb{
    t_object    x_ob;
    int         x_nouts;
    int         x_banged;
    int         x_next;
    t_outlet  **x_outs;
    t_outlet   *x_outbuf[1];
} t_lb;

static t_class *lb_class;

static void lb_loadbang(t_lb *x, t_float f){
    if((int)f == LB_INIT && !x->x_next){ // == LB_INIT (1) and not "next"
        int i = x->x_nouts;
        while (i--){
            outlet_bang(x->x_outs[i]);
        }
    x->x_banged = 1;
    }
    if((int)f == LB_LOAD && !x->x_banged){ // == LB_LOAD (0) and hasn't banged yet (next)
        int j = x->x_nouts;
        while (j--){
            outlet_bang(x->x_outs[j]);
        }
    x->x_banged = 1;
    }
}

static void lb_click(t_lb *x, t_floatarg xpos, t_floatarg ypos,
                           t_floatarg shift, t_floatarg ctrl, t_floatarg alt)
{
    int i = x->x_nouts;
    while (i--)
        outlet_bang(x->x_outs[i]);
}

static void lb_bang(t_lb *x){
    int i = x->x_nouts;
    while (i--)
        outlet_bang(x->x_outs[i]);
}

static void lb_anything(t_lb *x, t_symbol *s, int ac, t_atom *av){
    int i = x->x_nouts;
    while (i--)
        outlet_bang(x->x_outs[i]);
}

static void lb_free(t_lb *x){
    if (x->x_outs != x->x_outbuf)
        freebytes(x->x_outs, x->x_nouts * sizeof(*x->x_outs));
}

static void *lb_new(t_symbol *s, int argc, t_atom *argv){
    t_lb *x = (t_lb *)pd_new(lb_class);
    int i, nouts = 1;
    x->x_banged = 0;
    t_outlet **outs;
    x->x_next = 0;
    t_float float_flag = 0;
/////////////////////////////////////////////////////////////////////////////////////
    int argnum = 0;
    if(argc <= 2){
        while(argc > 0){
            if(argv->a_type == A_FLOAT && !float_flag){
                nouts = atom_getfloatarg(0, argc, argv);
                argc--;
                argv++;
                float_flag = 1;
            }
            else
                if (argv -> a_type == A_SYMBOL){
                    t_symbol *curarg = atom_getsymbolarg(0, argc, argv);
                    if(strcmp(curarg->s_name, "-next")==0){
                        x->x_next = 1;
                        argc--;
                        argv++;
                    }
                    else
                        goto errstate;
                }
                else
                    goto errstate;
        };
    }
    else
        goto errstate;
/////////////////////////////////////////////////////////////////////////////////////
    if (nouts < 1)
        nouts = 1;
    if (nouts > 64)
        nouts = 64;
    if (nouts > 1){
        if (!(outs = (t_outlet **)getbytes(nouts * sizeof(*outs))))
            return (0);
        }
    else
        outs = 0;
    x->x_nouts = nouts;
    x->x_outs = (outs ? outs : x->x_outbuf);
    for (i = 0; i < nouts; i++)
        x->x_outs[i] = outlet_new((t_object *)x, &s_bang);
    return (x);
errstate:
    pd_error(x, "lb: improper args");
    return NULL;
}

void lb_setup(void){
    lb_class = class_new(gensym("lb"), (t_newmethod)lb_new,
        (t_method)lb_free, sizeof(t_lb), 0, A_GIMME, 0);
    class_addbang(lb_class, lb_bang);
    class_addanything(lb_class, lb_anything);
    class_addmethod(lb_class, (t_method)lb_loadbang, gensym("loadbang"), A_DEFFLOAT, 0);
    class_addmethod(lb_class, (t_method)lb_click, gensym("click"),
                                    A_FLOAT, A_FLOAT, A_FLOAT, A_FLOAT, A_FLOAT,0);
    class_sethelpsymbol(lb_class, gensym("loadbanger"));
}