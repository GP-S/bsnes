static void dsp_state_save(unsigned char **out, void *in, size_t size) {
  memcpy(*out, in, size);
  *out += size;
}

static void dsp_state_load(unsigned char **in, void *out, size_t size) {
  memcpy(out, *in, size);
  *in += size;
}

void DSP::serialize(serializer &s) {
  s.array(apuram);
  s.array(samplebuffer);
  s.integer(clock);

  unsigned char state[SPC_DSP::state_size];
  unsigned char *p = state;
  memset(&state, 0, SPC_DSP::state_size);
  if(s.mode() == serializer::Save) {
    spc_dsp.copy_state(&p, dsp_state_save);
    s.array(state);
  } else if(s.mode() == serializer::Load) {
    s.array(state);
    spc_dsp.copy_state(&p, dsp_state_load);
  } else {
    s.array(state);
  }
}
