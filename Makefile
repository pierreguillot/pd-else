############
# Makefile #
############

# library name

lib.name = else

cflags = -Ishared -DHAVE_STRUCT_TIMESPEC

uname := $(shell uname -s)

#########################################################################
# sources
#########################################################################

# GUI:
keyboard.class.sources := classes/keyboard.c

# control:
args.class.sources := classes/args.c
break.class.sources := classes/break.c
cents2ratio.class.sources := classes/cents2ratio.c
changed.class.sources := classes/changed.c
dir.class.sources := classes/dir.c
hz2rad.class.sources := classes/hz2rad.c
lb.class.sources := classes/lb.c
float2bits.class.sources := classes/float2bits.c
loadbanger.class.sources := classes/loadbanger.c
pack2.class.sources := classes/pack2.c
randf.class.sources := classes/randf.c
randi.class.sources := classes/randi.c
rad2hz.class.sources := classes/rad2hz.c
ratio2cents.class.sources := classes/ratio2cents.c
rescale.class.sources := classes/rescale.c
routeall.class.sources := classes/routeall.c
routetype.class.sources := classes/routetype.c
fromany.class.sources := classes/fromany.c
toany.class.sources := classes/toany.c

# signal:
accum~.class.sources := classes/accum~.c
allpass.2nd~.class.sources := classes/allpass.2nd~.c
allpass.rev~.class.sources := classes/allpass.rev~.c
adsr~.class.sources := classes/adsr~.c
asr~.class.sources := classes/asr~.c
autofade~.class.sources := classes/autofade~.c
balance~.class.sources := classes/balance~.c
bandpass~.class.sources := classes/bandpass~.c
bandstop~.class.sources := classes/bandstop~.c
bicoeff.class.sources := classes/bicoeff.c
biquads~.class.sources := classes/biquads~.c
brown~.class.sources := classes/brown~.c
ceil.class.sources := classes/ceil.c
ceil~.class.sources := classes/ceil~.c
cents2ratio~.class.sources := classes/cents2ratio~.c
coin~.class.sources := classes/coin~.c
changed~.class.sources := classes/changed~.c
changed2~.class.sources := classes/changed2~.c
crackle~.class.sources := classes/crackle~.c
cusp~.class.sources := classes/cusp~.c
decay~.class.sources := classes/decay~.c
decay2~.class.sources := classes/decay2~.c
downsample~.class.sources := classes/downsample~.c
dust~.class.sources := classes/dust~.c
dust2~.class.sources := classes/dust2~.c
elapsed~.class.sources := classes/elapsed~.c
# envgen~.class.sources := classes/envgen~.c
eq~.class.sources := classes/eq~.c
fader~.class.sources := classes/fader~.c
fbdelay~.class.sources := classes/fbdelay~.c
fbsine2~.class.sources := classes/fbsine2~.c
floor.class.sources := classes/floor.c
floor~.class.sources := classes/floor~.c
fold.class.sources := classes/fold.c
fold~.class.sources := classes/fold~.c
gbman~.class.sources := classes/gbman~.c
gate2imp~.class.sources := classes/gate2imp~.c
glide~.class.sources := classes/glide~.c
glide2~.class.sources := classes/glide2~.c
gray~.class.sources := classes/gray~.c
henon~.class.sources := classes/henon~.c
highpass~.class.sources := classes/highpass~.c
highshelf~.class.sources := classes/highshelf~.c
hz2rad~.class.sources := classes/hz2rad~.c
ikeda~.class.sources := classes/ikeda~.c
impseq~.class.sources := classes/impseq~.c
lastvalue~.class.sources := classes/lastvalue~.c
latoocarfian~.class.sources := classes/latoocarfian~.c
lorenz~.class.sources := classes/lorenz~.c
lfnoise~.class.sources := classes/lfnoise~.c
lincong~.class.sources := classes/lincong~.c
logistic~.class.sources := classes/logistic~.c
loop.class.sources := classes/loop.c
lowpass~.class.sources := classes/lowpass~.c
lowshelf~.class.sources := classes/lowshelf~.c
match~.class.sources := classes/match~.c
median~.class.sources := classes/median~.c
tempo~.class.sources := classes/tempo~.c
nyquist~.class.sources := classes/nyquist~.c
pan2~.class.sources := classes/pan2~.c
pan4~.class.sources := classes/pan4~.c
peak~.class.sources := classes/peak~.c
pluck~.class.sources := classes/pluck~.c
pmosc~.class.sources := classes/pmosc~.c
pulsecount~.class.sources := classes/pulsecount~.c
pulsediv~.class.sources := classes/pulsediv~.c
quad~.class.sources := classes/quad~.c
rad2hz~.class.sources := classes/rad2hz~.c
ramp~.class.sources := classes/ramp~.c
rampnoise~.class.sources := classes/rampnoise~.c
randf~.class.sources := classes/randf~.c
randi~.class.sources := classes/randi~.c
randpulse~.class.sources := classes/randpulse~.c
ratio2cents~.class.sources := classes/ratio2cents~.c
rescale~.class.sources := classes/rescale~.c
resonant~.class.sources := classes/resonant~.c
resonant2~.class.sources := classes/resonant2~.c
rms~.class.sources := classes/rms~.c
rotate~.class.sources := classes/rotate~.c
sh~.class.sources := classes/sh~.c
stepnoise~.class.sources := classes/stepnoise~.c
step~.class.sources := classes/step~.c
sin~.class.sources := classes/sin~.c
sequencer~.class.sources := classes/sequencer~.c
sr~.class.sources := classes/sr~.c
standard~.class.sources := classes/standard~.c
susloop~.class.sources := classes/susloop~.c
trig.delay~.class.sources := classes/trig.delay~.c
trig.delay2~.class.sources := classes/trig.delay2~.c
timed.gate~.class.sources := classes/timed.gate~.c
toggleff~.class.sources := classes/toggleff~.c
togedge~.class.sources := classes/togedge~.c
trighold~.class.sources := classes/trighold~.c
past~.class.sources := classes/past~.c
vu~.class.sources := classes/vu~.c
xfade~.class.sources := classes/xfade~.c
xgate~.class.sources := classes/xgate~.c
xgate2~.class.sources := classes/xgate2~.c
xmod~.class.sources := classes/xmod~.c
xselect~.class.sources := classes/xselect~.c
xselect2~.class.sources := classes/xselect2~.c
wrap2.class.sources := classes/wrap2.c
wrap2~.class.sources := classes/wrap2~.c
zerocross~.class.sources := classes/zerocross~.c

# dependencies:

magic := shared/magic.c
    sine~.class.sources := classes/sine~.c $(magic)
    cosine~.class.sources := classes/cosine~.c $(magic)
    fbsine~.class.sources := classes/fbsine~.c $(magic)
    imp~.class.sources := classes/imp~.c $(magic)
    impulse~.class.sources := classes/impulse~.c $(magic)
    imp2~.class.sources := classes/imp2~.c $(magic)
    impulse2~.class.sources := classes/impulse2~.c $(magic)
    parabolic~.class.sources := classes/parabolic~.c $(magic)
    pulse~.class.sources := classes/pulse~.c $(magic)
    sawtooth~.class.sources := classes/sawtooth~.c $(magic)
    sawtooth2~.class.sources := classes/sawtooth2~.c $(magic)
    square~.class.sources := classes/square~.c $(magic)
    triangular~.class.sources := classes/triangular~.c $(magic)
    vsaw~.class.sources := classes/vsaw~.c $(magic)
    pimp~.class.sources := classes/pimp~.c $(magic)

gui := shared/gui.c
    window.class.sources := classes/window.c $(gui)


#########################################################################

# extra files

datafiles = \
$(wildcard help/*.pd) \
$(wildcard help/Abstractions/*.pd) \
$(wildcard help/*.wav) \
$(wildcard *.txt) \
else-meta.pd \
README.pdf

#########################################################################

# include Makefile.pdlibbuilder from submodule directory 'pd-lib-builder'
PDLIBBUILDER_DIR=pd-lib-builder/
include $(PDLIBBUILDER_DIR)/Makefile.pdlibbuilder
