// Porres 2017

#include "m_pd.h"
#include "math.h"

static t_class *tempo_class;

typedef struct _tempo{
    t_object x_obj;
    double  x_phase;
    int        x_val;
    t_inlet  *x_inlet_bpm;
    t_inlet  *x_inlet_swing;
    t_inlet  *x_inlet_sync;
    t_outlet *x_outlet_dsp_0;
    t_float x_sr;
    t_float x_gate;
    t_float x_deviation;
    t_float x_last_gate;
    t_float x_last_sync;
    t_float x_swing;
} t_tempo;

static void tempo_bang(t_tempo *x){
    x->x_phase = 1;
}

static t_int *tempo_perform(t_int *w){
    t_tempo *x = (t_tempo *)(w[1]);
    int nblock = (t_int)(w[2]);
    t_float *in1 = (t_float *)(w[3]); // gate
    t_float *in2 = (t_float *)(w[4]); // bpm
    t_float *in3 = (t_float *)(w[5]); // swing
    t_float *in4 = (t_float *)(w[6]); // sync
    t_float *out = (t_float *)(w[7]);
    float last_gate = x->x_last_gate; // last gate state
    float last_sync = x->x_last_sync; // last gate state
    double phase = x->x_phase;
    double sr = x->x_sr;
    int val = x->x_val;
    float deviation = x->x_deviation;
    while(nblock--){
        float gate = *in1++;
        double bpm = *in2++;
        float swing = *in3++;
        float sync = *in4++;
        float ratio = (swing/100.) + 1;
        if(bpm < 0)
            bpm = 0;
        else
            bpm *= deviation;
        double hz = bpm / 60.;
        double phase_step = hz / sr; // phase_step
        if(phase_step > 1)
            phase_step = 1;
        if(gate != 0){ // if on
            if(last_gate == 0)
                phase = 1;
            if(sync != 0 && last_sync == 0)
                phase = 1;
            *out++ = phase >= 1.;
            if(phase >= 1.){
                phase = phase - 1; // wrapped phase
// update deviation
                t_float random = ((float)((val & 0x7fffffff) - 0x40000000)) * (float)(1.0 / 0x40000000);
                val = val * 435898247 + 382842987;
                x->x_deviation = exp(log(ratio) * random);
            }
            phase += phase_step; // next phase
        }
        else
            *out++ = 0; // resets phase too
        last_gate = gate;
        last_sync = sync;
        deviation = x->x_deviation;
    }
    x->x_phase = phase;
    x->x_last_gate = last_gate;
    x->x_last_sync = last_sync;
    x->x_val = val;
    return (w + 8);
}

static void tempo_dsp(t_tempo *x, t_signal **sp){
    x->x_sr = sp[0]->s_sr;
    dsp_add(tempo_perform, 7, x, sp[0]->s_n, sp[0]->s_vec,
            sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec);
}

static void *tempo_free(t_tempo *x){
    inlet_free(x->x_inlet_bpm);
    inlet_free(x->x_inlet_swing);
    inlet_free(x->x_inlet_sync);
    outlet_free(x->x_outlet_dsp_0);
    return (void *)x;
}

static void *tempo_new(t_symbol *s, int argc, t_atom *argv){
    t_tempo *x = (t_tempo *)pd_new(tempo_class);
    t_float init_swing = 0;
    t_float init_bpm = 0;
    t_float on = 0;
    static int init_seed = 74599;
    x->x_val = (init_seed *= 1319);
/////////////////////////////////////////////////////////////////////////////////////
    int argnum = 0;
    while(argc > 0){
        if(argv->a_type == A_FLOAT){
            t_float argval = atom_getfloatarg(0, argc, argv);
            switch(argnum){
                case 0:
                    init_bpm = argval;
                    break;
                case 1:
                    init_swing = argval;
                    break;
                default:
                    break;
            };
            argnum++;
            argc--;
            argv++;
        }
        else if (argv -> a_type == A_SYMBOL){
            t_symbol *curarg = atom_getsymbolarg(0, argc, argv);
            if(!strcmp(curarg->s_name, "-on")){
                on = 1;
                argc--;
                argv++;
            }
            else
                goto errstate;
        }
    };
/////////////////////////////////////////////////////////////////////////////////////
    if(init_bpm < 0)
        init_bpm = 0;
    if(init_swing < 0)
        init_swing = 0;
    x->x_last_sync = 0;
    x->x_last_gate = 0;
    x->x_swing = init_swing;
    x->x_gate = on;
    x->x_sr = sys_getsr(); // sample rate
    x->x_phase = 1;
    x->x_inlet_bpm = inlet_new((t_object *)x, (t_pd *)x, &s_signal, &s_signal);
        pd_float((t_pd *)x->x_inlet_bpm, init_bpm);
    x->x_inlet_swing = inlet_new((t_object *)x, (t_pd *)x, &s_signal, &s_signal);
        pd_float((t_pd *)x->x_inlet_swing, init_swing);
    x->x_inlet_sync = inlet_new((t_object *)x, (t_pd *)x, &s_signal, &s_signal);
    x->x_outlet_dsp_0 = outlet_new(&x->x_obj, &s_signal);
    return (x);
errstate:
    pd_error(x, "tempo~: improper args");
    return NULL;
}

void tempo_tilde_setup(void){
    tempo_class = class_new(gensym("tempo~"),(t_newmethod)tempo_new, (t_method)tempo_free,
            sizeof(t_tempo), CLASS_DEFAULT, A_GIMME, 0);
    CLASS_MAINSIGNALIN(tempo_class, t_tempo, x_gate);
    class_addmethod(tempo_class, (t_method)tempo_dsp, gensym("dsp"), A_CANT, 0);
    class_addbang(tempo_class, tempo_bang);
}
