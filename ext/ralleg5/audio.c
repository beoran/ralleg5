#include "ralleg5.h"
#include "allegro5/allegro_acodec.h"
#include "allegro5/allegro_audio.h"

VALUE mAudio;
VALUE cSample;
VALUE cSampleId;
VALUE cSampleInstance;
VALUE cAudioStream;
VALUE cMixer;
VALUE cVoice;

VALUE rbal_not_implemented(const char * warning) {     
  warn(warning);
  return Qnil;
}

VALUE rbal_init_acodec_addon(VALUE rself) {
  return RBH_INT_BOOL(al_init_acodec_addon());
}

VALUE rbal_get_allegro_acodec_version(VALUE rself) {
  return RBH_UINT_NUM(al_get_allegro_acodec_version());
}

/* Wraps a sample into a Ruby object, optionally garbage collected. */
VALUE rbal_sample_wrap(ALLEGRO_SAMPLE * ptr, int gc) {
  if(!ptr) return Qnil;
  if (gc) {
    return Data_Wrap_Struct(cSample, 0, al_destroy_sample, ptr);
  } else {
    return Data_Wrap_Struct(cSample, 0, 0, ptr);
  } 
}

/* Unwraps a sample */
ALLEGRO_SAMPLE * rbal_sample_unwrap(VALUE rself) { 
  ALLEGRO_SAMPLE * result;
  if (rself == Qnil) return NULL;
  Data_Get_Struct(rself, ALLEGRO_SAMPLE, result);
  return result;
}

/* Wraps a sample instance into a Ruby object, optionally garbage collected. */
VALUE rbal_sampleinstance_wrap(ALLEGRO_SAMPLE_INSTANCE * ptr, int gc) {
  if(!ptr) return Qnil;
  if (gc) {
    return Data_Wrap_Struct(cSampleInstance, 0, al_destroy_sample_instance, ptr);
  } else {
    return Data_Wrap_Struct(cSampleInstance, 0, 0, ptr);
  } 
}

/* Allocates a sample id. */
ALLEGRO_SAMPLE_ID * rbal_sampleid_alloc() {
  return calloc(sizeof(ALLEGRO_SAMPLE_ID), 1);
}   

/* Frees a sample id. */
void rbal_sampleid_free(ALLEGRO_SAMPLE_ID * ptr)  {
  free(ptr);
}   

/* Wraps a sampleid into a Ruby object, optionally garbage collected. */
VALUE rbal_sampleid_wrap(ALLEGRO_SAMPLE_ID * ptr, int gc) {
  if(!ptr) return Qnil;
  if (gc) {
    return Data_Wrap_Struct(cSampleId, 0, rbal_sampleid_free, ptr);
  } else {
    return Data_Wrap_Struct(cSampleId, 0, 0, ptr);
  } 
}

/* Unwraps a Sample ID */
ALLEGRO_SAMPLE_ID * rbal_sampleid_unwrap(VALUE rself) { 
  ALLEGRO_SAMPLE_ID * result;
  if (rself == Qnil) return NULL;
  Data_Get_Struct(rself, ALLEGRO_SAMPLE_ID, result);
  return result;
}

/* Unwraps a sampleinstance */
ALLEGRO_SAMPLE_INSTANCE * rbal_sampleinstance_unwrap(VALUE rself) { 
  ALLEGRO_SAMPLE_INSTANCE * result;
  if (rself == Qnil) return NULL;
  Data_Get_Struct(rself, ALLEGRO_SAMPLE_INSTANCE, result);
  return result;
}

/* Wraps an audiostream into a Ruby object, optionally garbage collected. */
VALUE rbal_audiostream_wrap(ALLEGRO_AUDIO_STREAM * ptr, int gc) {
  if(!ptr) return Qnil;
  if (gc == RBAL_GC) {
    return Data_Wrap_Struct(cAudioStream, 0, al_destroy_audio_stream, ptr);
  } else {
    return Data_Wrap_Struct(cAudioStream, 0, 0, ptr);
  } 
}

/* Unwraps an audiostream  */
ALLEGRO_AUDIO_STREAM   * rbal_audiostream_unwrap(VALUE rself) { 
  ALLEGRO_AUDIO_STREAM * result;
  if (rself == Qnil) return NULL;
  Data_Get_Struct(rself, ALLEGRO_AUDIO_STREAM, result);
  return result;
}

/* Wraps a mixer into a Ruby object, optionally garbage collected. */
VALUE rbal_mixer_wrap(ALLEGRO_MIXER * ptr, int gc) {
  if(!ptr) return Qnil;
  if (gc == RBAL_GC) {
    return Data_Wrap_Struct(cMixer, 0, al_destroy_mixer, ptr);
  } else {
    return Data_Wrap_Struct(cMixer, 0, 0, ptr);
  } 
}

/* Unwraps a mixer  */
ALLEGRO_MIXER * rbal_mixer_unwrap(VALUE rself) { 
  ALLEGRO_MIXER * result;
  if (rself == Qnil) return NULL;
  Data_Get_Struct(rself, ALLEGRO_MIXER, result);
  return result;
}

/* Wraps a voice into a Ruby object, optionally garbage collected. */ 
VALUE rbal_voice_wrap(ALLEGRO_VOICE * ptr, int gc) {
  if(!ptr) return Qnil;
  if (gc == RBAL_GC) {
    return Data_Wrap_Struct(cVoice, 0, al_destroy_voice, ptr);
  } else {
    return Data_Wrap_Struct(cVoice, 0, 0, ptr);
  } 
}

/* Unwraps a voice from a Ruby object */ 
ALLEGRO_VOICE  * rbal_voice_unwrap(VALUE rself) { 
  ALLEGRO_VOICE * result;
  if (rself == Qnil) return NULL;
  Data_Get_Struct(rself, ALLEGRO_VOICE, result);
  return result;
}


/* NOTE: is al_create_sample too low level to be wrapped? */
VALUE rbal_create_sample(VALUE rself, VALUE rbuf, VALUE rsamples,
                         VALUE rfreq, VALUE rdepth, VALUE rconf) {
  return rbal_not_implemented("al_create_sample not implemented");
}

VALUE rbal_destroy_sample(VALUE rself, VALUE rspl) {   
  al_destroy_sample(rbal_sample_unwrap(rspl));
  return rspl;
}

/* NOTE: is al_create_sample_instance too low level to be wrapped? */
VALUE rbal_create_sample_instance(VALUE rself, VALUE rbuf, VALUE rsamples,
                         VALUE rfreq, VALUE rdepth, VALUE rconf) {
  return rbal_not_implemented("al_create_sample_instance not implemented");  
}

VALUE rbal_destroy_sample_instance(VALUE rself, VALUE rspl) {   
  al_destroy_sample_instance(rbal_sampleinstance_unwrap(rspl));
  return rspl;
}

VALUE rbal_get_sample_frequency(VALUE rself, VALUE rspl) {
  RBH_UINT_NUM(al_get_sample_frequency(rbal_sample_unwrap(rspl)));
}
 
VALUE rbal_get_sample_length(VALUE rself, VALUE rspl) {
  RBH_UINT_NUM(al_get_sample_length(rbal_sample_unwrap(rspl)));
} 

VALUE rbal_get_sample_depth(VALUE rself, VALUE rspl) {
  RBH_UINT_NUM(al_get_sample_depth(rbal_sample_unwrap(rspl)));
} 

VALUE rbal_get_sample_channels(VALUE rself, VALUE rspl) {
  RBH_UINT_NUM(al_get_sample_channels(rbal_sample_unwrap(rspl)));
} 

/* NOTE: too low-level? */ 
VALUE rbal_get_sample_data(VALUE rself, VALUE rspl) {
  return rbal_not_implemented("al_get_sample_data not implemented");
} 

VALUE rbal_get_sample_instance_frequency(VALUE rself, VALUE rspl) {
  ALLEGRO_SAMPLE_INSTANCE * spl = rbal_sampleinstance_unwrap(rspl);
  RBH_UINT_NUM(al_get_sample_instance_frequency(spl));
} 

VALUE rbal_get_sample_instance_length(VALUE rself, VALUE rspl) {
  ALLEGRO_SAMPLE_INSTANCE * spl = rbal_sampleinstance_unwrap(rspl);
  RBH_UINT_NUM(al_get_sample_instance_length(spl));
} 

VALUE rbal_get_sample_instance_position(VALUE rself, VALUE rspl) {
  ALLEGRO_SAMPLE_INSTANCE * spl = rbal_sampleinstance_unwrap(rspl);
  RBH_UINT_NUM(al_get_sample_instance_position(spl));
} 

VALUE rbal_get_sample_instance_speed(VALUE rself, VALUE rspl) {
  ALLEGRO_SAMPLE_INSTANCE * spl = rbal_sampleinstance_unwrap(rspl);
  RBH_FLOAT_NUM(al_get_sample_instance_speed(spl));
} 

VALUE rbal_get_sample_instance_gain(VALUE rself, VALUE rspl) {
  ALLEGRO_SAMPLE_INSTANCE * spl = rbal_sampleinstance_unwrap(rspl);
  RBH_FLOAT_NUM(al_get_sample_instance_gain(spl));
} 

VALUE rbal_get_sample_instance_pan(VALUE rself, VALUE rspl) {
  ALLEGRO_SAMPLE_INSTANCE * spl = rbal_sampleinstance_unwrap(rspl);
  RBH_FLOAT_NUM(al_get_sample_instance_pan(spl));
} 

VALUE rbal_get_sample_instance_time(VALUE rself, VALUE rspl) {
  ALLEGRO_SAMPLE_INSTANCE * spl = rbal_sampleinstance_unwrap(rspl);
  RBH_UINT_NUM(al_get_sample_instance_time(spl));
} 

VALUE rbal_get_sample_instance_depth(VALUE rself, VALUE rspl) {
  ALLEGRO_SAMPLE_INSTANCE * spl = rbal_sampleinstance_unwrap(rspl);
  RBH_UINT_NUM(al_get_sample_instance_depth(spl));
} 

VALUE rbal_get_sample_instance_channels(VALUE rself, VALUE rspl) {
  ALLEGRO_SAMPLE_INSTANCE * spl = rbal_sampleinstance_unwrap(rspl);
  RBH_UINT_NUM(al_get_sample_instance_channels(spl));
} 

VALUE rbal_get_sample_instance_playmode(VALUE rself, VALUE rspl) {
  ALLEGRO_SAMPLE_INSTANCE * spl = rbal_sampleinstance_unwrap(rspl);
  RBH_UINT_NUM(al_get_sample_instance_playmode(spl));
} 

VALUE rbal_get_sample_instance_playing(VALUE rself, VALUE rspl) {
  ALLEGRO_SAMPLE_INSTANCE * spl = rbal_sampleinstance_unwrap(rspl);
  RBH_INT_BOOL(al_get_sample_instance_playing(spl));
} 

VALUE rbal_get_sample_instance_attached(VALUE rself, VALUE rspl) {
  ALLEGRO_SAMPLE_INSTANCE * spl = rbal_sampleinstance_unwrap(rspl);
  RBH_INT_BOOL(al_get_sample_instance_attached(spl));
} 

VALUE rbal_set_sample_instance_position(VALUE r_, VALUE rspl, VALUE ri) {
  ALLEGRO_SAMPLE_INSTANCE * spl = rbal_sampleinstance_unwrap(rspl);
  RBH_INT_BOOL(al_set_sample_instance_position(spl, RBH_UINT(ri)));
}

VALUE rbal_set_sample_instance_length(VALUE r_, VALUE rspl, VALUE ri) {
  ALLEGRO_SAMPLE_INSTANCE * spl = rbal_sampleinstance_unwrap(rspl);
  RBH_INT_BOOL(al_set_sample_instance_length(spl, RBH_UINT(ri)));
}

VALUE rbal_set_sample_instance_speed(VALUE r_, VALUE rspl, VALUE ri) {
  ALLEGRO_SAMPLE_INSTANCE * spl = rbal_sampleinstance_unwrap(rspl);
  RBH_INT_BOOL(al_set_sample_instance_speed(spl, RBH_FLOAT(ri)));
}

VALUE rbal_set_sample_instance_gain(VALUE r_, VALUE rspl, VALUE ri) {
  ALLEGRO_SAMPLE_INSTANCE * spl = rbal_sampleinstance_unwrap(rspl);
  RBH_INT_BOOL(al_set_sample_instance_gain(spl, RBH_FLOAT(ri)));
}

VALUE rbal_set_sample_instance_pan(VALUE r_, VALUE rspl, VALUE ri) {
  ALLEGRO_SAMPLE_INSTANCE * spl = rbal_sampleinstance_unwrap(rspl);
  RBH_INT_BOOL(al_set_sample_instance_pan(spl, RBH_FLOAT(ri)));
}

VALUE rbal_set_sample_instance_playmode(VALUE r_, VALUE rspl, VALUE ri) {
  ALLEGRO_SAMPLE_INSTANCE * spl = rbal_sampleinstance_unwrap(rspl);
  RBH_INT_BOOL(al_set_sample_instance_playmode(spl, RBH_UINT(ri)));
}

VALUE rbal_set_sample_instance_playing(VALUE r_, VALUE rspl, VALUE ri) {
  ALLEGRO_SAMPLE_INSTANCE * spl = rbal_sampleinstance_unwrap(rspl);
  RBH_INT_BOOL(al_set_sample_instance_playing(spl, RBH_BOOL_INT(ri)));
}

VALUE rbal_detach_sample_instance(VALUE r_, VALUE rspl) {
  ALLEGRO_SAMPLE_INSTANCE * spl = rbal_sampleinstance_unwrap(rspl);
  RBH_INT_BOOL(al_detach_sample_instance(spl));
}


/* NOTE: too low level? */
VALUE rbal_set_sample(VALUE r_, VALUE rspl, VALUE ri) {
  ALLEGRO_SAMPLE * spl = rbal_sample_unwrap(rspl);
  void * buf = NULL;
  return rbal_not_implemented("al_set_sample not implemented");
  /* RBH_INT_BOOL(al_set_sample(spl, buf)); */
  return Qnil;
}

VALUE rbal_get_sample(VALUE r_, VALUE rinst) { 
  ALLEGRO_SAMPLE_INSTANCE * inst = rbal_sampleinstance_unwrap(rinst);
  ALLEGRO_SAMPLE          * spl  = al_get_sample(inst);
  return rbal_sample_wrap(spl, RBAL_NO_GC);
}   

VALUE rbal_play_sample_instance(VALUE r_, VALUE rspl) {
  ALLEGRO_SAMPLE_INSTANCE * spl = rbal_sampleinstance_unwrap(rspl);
  RBH_INT_BOOL(al_play_sample_instance(spl));
}

VALUE rbal_stop_sample_instance(VALUE r_, VALUE rspl) {
  ALLEGRO_SAMPLE_INSTANCE * spl = rbal_sampleinstance_unwrap(rspl);
  RBH_INT_BOOL(al_stop_sample_instance(spl));
}

VALUE rbal_create_audio_stream(VALUE r_, VALUE rcount, VALUE rsam, VALUE rfreq,
                                VALUE rdepth, VALUE rconf) {
  ALLEGRO_AUDIO_STREAM * str = NULL;
  str = al_create_audio_stream(rcount, rsam, rfreq, rdepth, rconf); 
  return rbal_audiostream_wrap(str, RBAL_NO_GC);
}

VALUE rbal_destroy_audio_stream(VALUE r_, VALUE rstr) {
  ALLEGRO_AUDIO_STREAM * str = rbal_audiostream_unwrap(rstr);
  al_destroy_audio_stream(str);
  return r_;
}

VALUE rbal_drain_audio_stream(VALUE r_, VALUE rstr) {
  ALLEGRO_AUDIO_STREAM * str = rbal_audiostream_unwrap(rstr);
  al_drain_audio_stream(str);
  return r_;
}

VALUE rbal_get_audio_stream_frequency(VALUE r_, VALUE rstr) {
  ALLEGRO_AUDIO_STREAM * str = rbal_audiostream_unwrap(rstr);
  return RBH_UINT_NUM(al_get_audio_stream_frequency(str));
}

VALUE rbal_get_audio_stream_length(VALUE r_, VALUE rstr) {
  ALLEGRO_AUDIO_STREAM * str = rbal_audiostream_unwrap(rstr);
  return RBH_UINT_NUM(al_get_audio_stream_length(str));
}

VALUE rbal_get_audio_stream_fragments(VALUE r_, VALUE rstr) {
  ALLEGRO_AUDIO_STREAM * str = rbal_audiostream_unwrap(rstr);
  return RBH_UINT_NUM(al_get_audio_stream_fragments(str));
}

VALUE rbal_get_available_audio_stream_fragments(VALUE r_, VALUE rstr) {
  ALLEGRO_AUDIO_STREAM * str = rbal_audiostream_unwrap(rstr);
  return RBH_UINT_NUM(al_get_available_audio_stream_fragments(str));
}

VALUE rbal_get_audio_stream_speed(VALUE r_, VALUE rstr) {
  ALLEGRO_AUDIO_STREAM * str = rbal_audiostream_unwrap(rstr);
  return RBH_FLOAT_NUM(al_get_audio_stream_speed(str));
}

VALUE rbal_get_audio_stream_gain(VALUE r_, VALUE rstr) {
  ALLEGRO_AUDIO_STREAM * str = rbal_audiostream_unwrap(rstr);
  return RBH_FLOAT_NUM(al_get_audio_stream_gain(str));
}

VALUE rbal_get_audio_stream_pan(VALUE r_, VALUE rstr) {
  ALLEGRO_AUDIO_STREAM * str = rbal_audiostream_unwrap(rstr);
  return RBH_FLOAT_NUM(al_get_audio_stream_pan(str));
}

VALUE rbal_get_audio_stream_channels(VALUE r_, VALUE rstr) {
  ALLEGRO_AUDIO_STREAM * str = rbal_audiostream_unwrap(rstr);
  return RBH_UINT_NUM(al_get_audio_stream_channels(str));
}

VALUE rbal_get_audio_stream_depth(VALUE r_, VALUE rstr) {
  ALLEGRO_AUDIO_STREAM * str = rbal_audiostream_unwrap(rstr);
  return RBH_UINT_NUM(al_get_audio_stream_depth(str));
}

VALUE rbal_get_audio_stream_playmode(VALUE r_, VALUE rstr) {
  ALLEGRO_AUDIO_STREAM * str = rbal_audiostream_unwrap(rstr);
  return RBH_UINT_NUM(al_get_audio_stream_playmode(str));
}

VALUE rbal_get_audio_stream_playing(VALUE r_, VALUE rstr) {
  ALLEGRO_AUDIO_STREAM * str = rbal_audiostream_unwrap(rstr);
  return RBH_INT_BOOL(al_get_audio_stream_playing(str));
}

VALUE rbal_get_audio_stream_attached(VALUE r_, VALUE rstr) {
  ALLEGRO_AUDIO_STREAM * str = rbal_audiostream_unwrap(rstr);
  return RBH_INT_BOOL(al_get_audio_stream_attached(str));
}

VALUE rbal_get_audio_stream_fragment(VALUE r_, VALUE rstr) {
  ALLEGRO_AUDIO_STREAM * str = rbal_audiostream_unwrap(rstr);
  return rbal_not_implemented("al_get_audio_stream_fragment not implemented");
}

VALUE rbal_set_audio_stream_speed(VALUE r_, VALUE rstr, VALUE rval) {
  ALLEGRO_AUDIO_STREAM * str = rbal_audiostream_unwrap(rstr);
  return RBH_INT_BOOL(al_set_audio_stream_speed(str, RBH_FLOAT(rval)));
}

VALUE rbal_set_audio_stream_gain(VALUE r_, VALUE rstr, VALUE rval) {
  ALLEGRO_AUDIO_STREAM * str = rbal_audiostream_unwrap(rstr);
  return RBH_INT_BOOL(al_set_audio_stream_gain(str, RBH_FLOAT(rval)));
}

VALUE rbal_set_audio_stream_pan(VALUE r_, VALUE rstr, VALUE rval) {
  ALLEGRO_AUDIO_STREAM * str = rbal_audiostream_unwrap(rstr);
  return RBH_INT_BOOL(al_set_audio_stream_pan(str, RBH_FLOAT(rval)));
}

VALUE rbal_set_audio_stream_playmode(VALUE r_, VALUE rstr, VALUE rval) {
  ALLEGRO_AUDIO_STREAM * str = rbal_audiostream_unwrap(rstr);
  return RBH_INT_BOOL(al_set_audio_stream_playmode(str, RBH_UINT(rval)));
}

VALUE rbal_set_audio_stream_playing(VALUE r_, VALUE rstr, VALUE rval) {
  ALLEGRO_AUDIO_STREAM * str = rbal_audiostream_unwrap(rstr);
  return RBH_INT_BOOL(al_set_audio_stream_playing(str, RBH_BOOL_INT(rval)));
}

VALUE rbal_detach_audio_stream(VALUE r_, VALUE rstr, VALUE rval) {
  ALLEGRO_AUDIO_STREAM * str = rbal_audiostream_unwrap(rstr);
  return RBH_INT_BOOL(al_detach_audio_stream(str));
}

VALUE rbal_set_audio_stream_fragment(VALUE r_, VALUE rstr, VALUE rval) {
  ALLEGRO_AUDIO_STREAM * str = rbal_audiostream_unwrap(rstr);
  return rbal_not_implemented("al_set_audio_stream_fragment not implemented");
}

VALUE rbal_rewind_audio_stream(VALUE r_, VALUE rstr, VALUE rval) {
  ALLEGRO_AUDIO_STREAM * str = rbal_audiostream_unwrap(rstr);
  return RBH_INT_BOOL(al_rewind_audio_stream(str));
}

VALUE rbal_seek_audio_stream_secs(VALUE r_, VALUE rstr, VALUE rtime) {
  ALLEGRO_AUDIO_STREAM * str = rbal_audiostream_unwrap(rstr);
  return RBH_INT_BOOL(al_seek_audio_stream_secs(str, RBH_DOUBLE(rtime)));
}

VALUE rbal_get_audio_stream_position_secs(VALUE r_, VALUE rstr) {
  ALLEGRO_AUDIO_STREAM * str = rbal_audiostream_unwrap(rstr);
  return RBH_DOUBLE_NUM(al_get_audio_stream_position_secs(str));
}

VALUE rbal_get_audio_stream_length_secs(VALUE r_, VALUE rstr) {
  ALLEGRO_AUDIO_STREAM * str = rbal_audiostream_unwrap(rstr);
  return RBH_DOUBLE_NUM(al_get_audio_stream_length_secs(str));
}

VALUE rbal_set_audio_stream_loop_secs(VALUE r_, VALUE rstr, VALUE rs, VALUE re) {
  ALLEGRO_AUDIO_STREAM * str = rbal_audiostream_unwrap(rstr);
  return RBH_DOUBLE_NUM(al_set_audio_stream_loop_secs(str, 
         RBH_DOUBLE(rs), RBH_DOUBLE(re)));
}

/* Mixer functions. */

VALUE rbal_get_audio_stream_event_source(VALUE r_, VALUE rstr) {
  ALLEGRO_AUDIO_STREAM * str = rbal_audiostream_unwrap(rstr);
  rbal_eventstream_wrap_nofree(al_get_audio_stream_event_source(str));
}

VALUE rbal_create_mixer(VALUE r_, VALUE rfreq, VALUE rdepth, VALUE rchan) {
  ALLEGRO_MIXER * mix = NULL;
  mix = al_create_mixer(RBH_UINT(rfreq), RBH_UINT(rdepth), RBH_UINT(rchan));
  return rbal_mixer_wrap(mix, RBAL_NO_GC);  
}

VALUE rbal_destroy_mixer(VALUE r_, VALUE rmix) {
  ALLEGRO_MIXER * mix = rbal_mixer_unwrap(rmix);
  if(!mix) return Qnil;
  al_destroy_mixer(mix);
  return r_;
}

VALUE rbal_attach_sample_instance_to_mixer(VALUE r_, VALUE rsam, VALUE rmix) {
  ALLEGRO_MIXER           * mix = rbal_mixer_unwrap(rmix);
  ALLEGRO_SAMPLE_INSTANCE * sam = rbal_sampleinstance_unwrap(rsam);
  return RBH_INT_BOOL(al_attach_sample_instance_to_mixer(sam, mix));
}

VALUE rbal_attach_audio_stream_to_mixer(VALUE r_, VALUE rstr, VALUE rmix) {
  ALLEGRO_MIXER           * mix = rbal_mixer_unwrap(rmix);
  ALLEGRO_AUDIO_STREAM    * str = rbal_audiostream_unwrap(rstr);
  return RBH_INT_BOOL(al_attach_audio_stream_to_mixer(str, mix));
}

VALUE rbal_attach_mixer_to_mixer(VALUE r_, VALUE rmix2, VALUE rmix) {
  ALLEGRO_MIXER           * mix  = rbal_mixer_unwrap(rmix);
  ALLEGRO_MIXER           * mix2 = rbal_mixer_unwrap(rmix2); 
  return RBH_INT_BOOL(al_attach_audio_mixer_to_mixer(mix, mix));
}

VALUE rbal_set_mixer_postprocess_callback(VALUE r_,  VALUE rmix, VALUE rdata) {
  ALLEGRO_MIXER           * mix = rbal_mixer_unwrap(rmix);
  return rbal_not_implemented("al_set_mixer_postprocess_callback not implemented");
}

VALUE rbal_get_mixer_frequency(VALUE r_,  VALUE rmix) {
  ALLEGRO_MIXER           * mix = rbal_mixer_unwrap(rmix);
  return RBH_INT_NUM(al_get_mixer_frequency(mix));
}  

VALUE rbal_get_mixer_channels(VALUE r_,  VALUE rmix) {
  ALLEGRO_MIXER           * mix = rbal_mixer_unwrap(rmix);
  return RBH_INT_NUM(al_get_mixer_channels(mix));
}  

VALUE rbal_get_mixer_depth(VALUE r_,  VALUE rmix) {
  ALLEGRO_MIXER           * mix = rbal_mixer_unwrap(rmix);
  return RBH_INT_NUM(al_get_mixer_depth(mix));
}  

VALUE rbal_get_mixer_quality(VALUE r_,  VALUE rmix) {
  ALLEGRO_MIXER           * mix = rbal_mixer_unwrap(rmix);
  return RBH_INT_NUM(al_get_mixer_quality(mix));
}  

VALUE rbal_get_mixer_playing(VALUE r_,  VALUE rmix) {
  ALLEGRO_MIXER           * mix = rbal_mixer_unwrap(rmix);
  return RBH_INT_BOOL(al_get_mixer_playing(mix));
}  

VALUE rbal_get_mixer_attached(VALUE r_,  VALUE rmix) {
  ALLEGRO_MIXER           * mix = rbal_mixer_unwrap(rmix);
  return RBH_INT_BOOL(al_get_mixer_attached(mix));
}  

VALUE rbal_set_mixer_frequency(VALUE r_,  VALUE rmix, VALUE rval) {
  ALLEGRO_MIXER           * mix = rbal_mixer_unwrap(rmix);
  return RBH_INT_NUM(al_set_mixer_frequency(mix, RBH_UINT(rval)));
}  

VALUE rbal_set_mixer_quality(VALUE r_,  VALUE rmix, VALUE rval) {
  ALLEGRO_MIXER           * mix = rbal_mixer_unwrap(rmix);
  return RBH_INT_NUM(al_set_mixer_quality(mix, RBH_UINT(rval)));
}  

VALUE rbal_set_mixer_playing(VALUE r_,  VALUE rmix, VALUE rval) {
  ALLEGRO_MIXER           * mix = rbal_mixer_unwrap(rmix);
  return RBH_INT_NUM(al_set_mixer_playing(mix, RBH_BOOL_INT(rval)));
}  

VALUE rbal_detach_mixer(VALUE r_,  VALUE rmix) {
  ALLEGRO_MIXER           * mix = rbal_mixer_unwrap(rmix);
  return RBH_INT_BOOL(al_detach_mixer(mix));
}  

/* Voice functions */

VALUE rbal_create_voice(VALUE r_, VALUE rfreq, VALUE rdepth, VALUE rchan) {
  ALLEGRO_VOICE * voc = NULL;
  voc = al_create_voice(RBH_UINT(rfreq), RBH_UINT(rdepth), RBH_UINT(rchan));
  return rbal_voice_wrap(voc, RBAL_NO_GC);  
}

VALUE rbal_destroy_voice(VALUE r_, VALUE rvoc) {
  ALLEGRO_VOICE * voc = rbal_voice_unwrap(rvoc);
  if(!voc) return Qnil;
  al_destroy_voice(voc);
  return r_;
}

VALUE rbal_attach_sample_instance_to_voice(VALUE r_, VALUE rsam, VALUE rvoc) {
  ALLEGRO_VOICE           * voc = rbal_voice_unwrap(rvoc);
  ALLEGRO_SAMPLE_INSTANCE * sam = rbal_sampleinstance_unwrap(rsam);
  return RBH_INT_BOOL(al_attach_sample_instance_to_voice(sam, voc));
}

VALUE rbal_attach_audio_stream_to_voice(VALUE r_, VALUE rstr, VALUE rvoc) {
  ALLEGRO_VOICE           * voc = rbal_voice_unwrap(rvoc);
  ALLEGRO_AUDIO_STREAM    * str = rbal_audiostream_unwrap(rstr);
  return RBH_INT_BOOL(al_attach_audio_stream_to_voice(str, voc));
}

VALUE rbal_attach_mixer_to_voice(VALUE r_, VALUE rmix, VALUE rvoc) {
  ALLEGRO_VOICE           * voc = rbal_voice_unwrap(rvoc);
  ALLEGRO_MIXER           * mix = rbal_mixer_unwrap(rmix);
  return RBH_INT_BOOL(al_attach_mixer_to_voice(mix, voc));
}


VALUE rbal_detach_voice(VALUE r_,  VALUE rvoc) {  
  ALLEGRO_VOICE           * voc = rbal_voice_unwrap(rvoc);
  al_detach_voice(voc);
  return r_ ;
}  

VALUE rbal_get_voice_frequency(VALUE r_,  VALUE rvoc) {  
  ALLEGRO_VOICE           * voc = rbal_voice_unwrap(rvoc);  
  return RBH_UINT_NUM(al_get_voice_frequency(voc));
}  

VALUE rbal_get_voice_position(VALUE r_,  VALUE rvoc) {  
  ALLEGRO_VOICE           * voc = rbal_voice_unwrap(rvoc);  
  return RBH_UINT_NUM(al_get_voice_position(voc));
}  

VALUE rbal_get_voice_channels(VALUE r_,  VALUE rvoc) {  
  ALLEGRO_VOICE           * voc = rbal_voice_unwrap(rvoc);  
  return RBH_UINT_NUM(al_get_voice_channels(voc));
}  

VALUE rbal_get_voice_depth(VALUE r_,  VALUE rvoc) {  
  ALLEGRO_VOICE           * voc = rbal_voice_unwrap(rvoc);  
  return RBH_UINT_NUM(al_get_voice_depth(voc));
}  

VALUE rbal_get_voice_playing(VALUE r_,  VALUE rvoc) {  
  ALLEGRO_VOICE           * voc = rbal_voice_unwrap(rvoc);  
  return RBH_INT_BOOL(al_get_voice_playing(voc));
}  

VALUE rbal_set_voice_position(VALUE r_,  VALUE rvoc, VALUE rval) {  
  ALLEGRO_VOICE           * voc = rbal_voice_unwrap(rvoc);  
  return RBH_INT_BOOL(al_set_voice_position(voc, RBH_UINT(rval)));
}  

VALUE rbal_set_voice_playing(VALUE r_,  VALUE rvoc, VALUE rval) {  
  ALLEGRO_VOICE           * voc = rbal_voice_unwrap(rvoc);  
  return RBH_INT_BOOL(al_set_voice_playing(voc, RBH_INT_BOOL(rval)));
}
  

/* Misc. audio functions */

VALUE rbal_install_audio(VALUE r_) {
  al_install_audio();
  return r_;
}

VALUE rbal_uninstall_audio(VALUE r_) {
  al_uninstall_audio();
  return r_;
}

VALUE rbal_is_audio_installed(VALUE r_) {
  return RBH_INT_BOOL(al_is_audio_installed());
}

VALUE rbal_get_allegro_audio_version(VALUE r_) {
  return RBH_INT_NUM(al_get_allegro_audio_version());  
}

VALUE rbal_get_channel_count(VALUE r_, VALUE rconf) {
  return RBH_INT_NUM(al_get_channel_count(RBH_UINT(rconf)));  
}

VALUE rbal_get_audio_depth_size(VALUE r_, VALUE rconf) {
  return RBH_INT_NUM(al_get_audio_depth_size(RBH_UINT(rconf)));  
}

/* Simple audio layer */

VALUE rbal_reserve_samples(VALUE r_, VALUE ramount) {
  return RBH_INT_BOOL(al_reserve_samples(RBH_INT(ramount)));  
}

VALUE rbal_get_default_mixer(VALUE r_) {
  return rbal_mixer_wrap(al_get_default_mixer(), RBAL_NO_GC);  
}

VALUE rbal_set_default_mixer(VALUE r_, VALUE rmix) {
  ALLEGRO_MIXER * mix = rbal_mixer_unwrap(rmix);
  if (!mix) return Qnil;
  return RBH_INT_BOOL(al_set_default_mixer(mix));  
}

VALUE rbal_restore_default_mixer(VALUE r_) {
  al_restore_default_mixer();
  return r_;
}

VALUE rbal_create_sample_id(VALUE r_) {
  ALLEGRO_SAMPLE_ID * id = rbal_sampleid_alloc();
  return rbal_sampleid_wrap(id, RBAL_NO_GC);
}

VALUE rbal_destroy_sample_id(VALUE r_, VALUE rid) {
  ALLEGRO_SAMPLE_ID * id = rbal_sampleid_unwrap(rid);
  rbal_sampleid_free(id);
  return r_;
}

VALUE rbal_play_sample(VALUE r_, VALUE rsam, VALUE rgain, VALUE rpan, 
                       VALUE rspeed, VALUE rloop, VALUE rid) {
  ALLEGRO_SAMPLE    * sam = rbal_sample_unwrap(rsam);
  ALLEGRO_SAMPLE_ID * id  = rbal_sampleid_unwrap(rid);
  int ok = 0;
  float gain  = RBH_FLOAT(rgain),
  pan         = RBH_FLOAT(rpan),
  speed       = RBH_FLOAT(rspeed);
  if(!sam) return Qnil;
  id = rbal_sampleid_alloc();
  ok = al_play_sample(sam, gain, pan, speed, RBH_INT(rloop), id);
  if(!ok) { 
    return Qfalse;
  }  
  return Qtrue;    
}

VALUE rbal_stop_sample(VALUE r_, VALUE rid) {
  ALLEGRO_SAMPLE_ID * id = rbal_sampleid_unwrap(rid);
  al_stop_sample(id);
  return r_;
}

VALUE rbal_stop_samples(VALUE r_, VALUE rid) {
  al_stop_samples();
  return r_;
}


/* File type handlers are not wrapped, since those are for 
writing extensions to allegro in C.  */

VALUE rbal_load_sample(VALUE r_, VALUE rfilename) {
  const char *filename    = RBH_CSTR(rfilename);
  
  return rbal_sample_wrap(al_load_sample(filename), RBAL_NO_GC); 
}

VALUE rbal_save_sample(VALUE r_, VALUE rfilename, VALUE rsam) {
  const char *filename    = RBH_CSTR(rfilename);
  ALLEGRO_SAMPLE    * sam = rbal_sample_unwrap(rsam);  
  return RBH_INT_BOOL(al_save_sample(filename, sam)); 
}

VALUE rbal_load_audio_stream(VALUE r_, VALUE rfilename, VALUE rbu, VALUE rsa) {
  const char *filename       = RBH_CSTR(rfilename);
  ALLEGRO_AUDIO_STREAM * str = NULL;
  str = al_load_audio_stream(filename, RBH_UINT(rbu), RBH_INT(rsa));
  return rbal_audiostream_wrap(str, RBAL_NO_GC); 
}

VALUE rbal_load_sample_f(VALUE r_, VALUE rfp, VALUE rident) {
  ALLEGRO_FILE * fp       = rbal_file_unwrap(rfp);
  const char   * ident    = RBH_CSTR(rident);  
  return rbal_sample_wrap(al_load_sample_f(fp, ident), RBAL_NO_GC); 
}

VALUE rbal_save_sample_f(VALUE r_, VALUE rfp, VALUE rident, VALUE rsam) {
  ALLEGRO_FILE * fp       = rbal_file_unwrap(rfp);
  const char   * ident    = RBH_CSTR(rident);
  ALLEGRO_SAMPLE    * sam = rbal_sample_unwrap(rsam);  
  return RBH_INT_BOOL(al_save_sample_f(fp, ident, sam)); 
}

VALUE rbal_load_audio_stream_f(VALUE r_, VALUE rfp, VALUE rident, 
                               VALUE rbu, VALUE rsa) {
  ALLEGRO_FILE * fp       = rbal_file_unwrap(rfp);
  const char   * ident    = RBH_CSTR(rident);
  ALLEGRO_AUDIO_STREAM * str = NULL;
  str = al_load_audio_stream_f(fp, ident, RBH_UINT(rbu), RBH_INT(rsa));
  return rbal_audiostream_wrap(str, RBAL_NO_GC); 
}


/* Useful ruby snippet after running CPP on the allegro header file: 
parts.map { |e| p e; cnt = e.count(',') - 2 ;  i = e.index(",", e.index(",") + 1) ; e[0..i] + " #{cnt})"  }
*/  

void ralleg5_audio_init(VALUE mAl, VALUE mLow) {
  mAudio          = rb_define_module_under(mAl, "Audio");
  cSample         = rb_define_class_under(mAl , "Sample"         , rb_cObject);
  cSampleId       = rb_define_class_under(mAl , "SampleId"       , rb_cObject);  
  cSampleInstance = rb_define_class_under(mAl , "SampleInstance" , rb_cObject);
  cAudioStream    = rb_define_class_under(mAl , "AudioStream"    , rb_cObject);
  cMixer          = rb_define_class_under(mAl , "Mixer"          , rb_cObject);
  cVoice          = rb_define_class_under(mAl , "Voice"          , rb_cObject);
  
  rbal_low_const(mLow, ALLEGRO_AUDIO_DEPTH_INT8);
  rbal_low_const(mLow, ALLEGRO_AUDIO_DEPTH_INT16);
  rbal_low_const(mLow, ALLEGRO_AUDIO_DEPTH_INT24);
  rbal_low_const(mLow, ALLEGRO_AUDIO_DEPTH_FLOAT32);
  rbal_low_const(mLow, ALLEGRO_AUDIO_DEPTH_UNSIGNED);
  rbal_low_const(mLow, ALLEGRO_AUDIO_DEPTH_UINT8);
  rbal_low_const(mLow, ALLEGRO_AUDIO_DEPTH_UINT16);
  rbal_low_const(mLow, ALLEGRO_AUDIO_DEPTH_UINT24);
  rbal_low_const(mLow, ALLEGRO_CHANNEL_CONF_1);
  rbal_low_const(mLow, ALLEGRO_CHANNEL_CONF_2);
  rbal_low_const(mLow, ALLEGRO_CHANNEL_CONF_3);
  rbal_low_const(mLow, ALLEGRO_CHANNEL_CONF_4);
  rbal_low_const(mLow, ALLEGRO_CHANNEL_CONF_5_1);
  rbal_low_const(mLow, ALLEGRO_CHANNEL_CONF_6_1);
  rbal_low_const(mLow, ALLEGRO_CHANNEL_CONF_7_1);
  rbal_low_const(mLow, ALLEGRO_MAX_CHANNELS);
  rbal_low_const(mLow, ALLEGRO_PLAYMODE_ONCE);
  rbal_low_const(mLow, ALLEGRO_PLAYMODE_LOOP);
  rbal_low_const(mLow, ALLEGRO_PLAYMODE_BIDIR);
  rbal_low_const(mLow, ALLEGRO_MIXER_QUALITY_POINT);
  rbal_low_const(mLow, ALLEGRO_MIXER_QUALITY_LINEAR);
  rbal_low_const_float(mLow, ALLEGRO_AUDIO_PAN_NONE);
  
  
  /* Low level API: */
  rbal_low_func(mLow, al_init_acodec_addon            , 0);
  rbal_low_func(mLow, al_get_allegro_acodec_version   , 0);
  /** Automatically generated. */
  rbal_low_func(mLow, al_create_sample, 5);
  rbal_low_func(mLow, al_destroy_sample, 0);
  rbal_low_func(mLow, al_create_sample_instance, 0);
  rbal_low_func(mLow, al_destroy_sample_instance, 0);
  rbal_low_func(mLow, al_get_sample_frequency, 0);
  rbal_low_func(mLow, al_get_sample_length, 0);
  rbal_low_func(mLow, al_get_sample_depth, 0);
  rbal_low_func(mLow, al_get_sample_channels, 0);
  rbal_low_func(mLow, al_get_sample_data, 0);
  rbal_low_func(mLow, al_get_sample_instance_frequency, 0);
  rbal_low_func(mLow, al_get_sample_instance_length, 0);
  rbal_low_func(mLow, al_get_sample_instance_position, 0);
  rbal_low_func(mLow, al_get_sample_instance_speed, 0);
  rbal_low_func(mLow, al_get_sample_instance_gain, 0);
  rbal_low_func(mLow, al_get_sample_instance_pan, 0);
  rbal_low_func(mLow, al_get_sample_instance_time, 0);
  rbal_low_func(mLow, al_get_sample_instance_depth, 0);
  rbal_low_func(mLow, al_get_sample_instance_channels, 0);
  rbal_low_func(mLow, al_get_sample_instance_playmode, 0);
  rbal_low_func(mLow, al_get_sample_instance_playing, 0);
  rbal_low_func(mLow, al_get_sample_instance_attached, 0);
  rbal_low_func(mLow, al_set_sample_instance_position, 1);
  rbal_low_func(mLow, al_set_sample_instance_length, 1);
  rbal_low_func(mLow, al_set_sample_instance_speed, 1);
  rbal_low_func(mLow, al_set_sample_instance_gain, 1);
  rbal_low_func(mLow, al_set_sample_instance_pan, 1);
  rbal_low_func(mLow, al_set_sample_instance_playmode, 1);
  rbal_low_func(mLow, al_set_sample_instance_playing, 1);
  rbal_low_func(mLow, al_detach_sample_instance, 0);
  rbal_low_func(mLow, al_set_sample, 1);
  rbal_low_func(mLow, al_get_sample, 0);
  rbal_low_func(mLow, al_play_sample_instance, 0);
  rbal_low_func(mLow, al_stop_sample_instance, 0);
  rbal_low_func(mLow, al_create_audio_stream, 4);
  rbal_low_func(mLow, al_destroy_audio_stream, 0);
  rbal_low_func(mLow, al_drain_audio_stream, 0);
  rbal_low_func(mLow, al_get_audio_stream_frequency, 0);
  rbal_low_func(mLow, al_get_audio_stream_length, 0);
  rbal_low_func(mLow, al_get_audio_stream_fragments, 0);
  rbal_low_func(mLow, al_get_available_audio_stream_fragments, 0);
  rbal_low_func(mLow, al_get_audio_stream_speed, 0);
  rbal_low_func(mLow, al_get_audio_stream_gain, 0);
  rbal_low_func(mLow, al_get_audio_stream_pan, 0);
  rbal_low_func(mLow, al_get_audio_stream_channels, 0);
  rbal_low_func(mLow, al_get_audio_stream_depth, 0);
  rbal_low_func(mLow, al_get_audio_stream_playmode, 0);
  rbal_low_func(mLow, al_get_audio_stream_playing, 0);
  rbal_low_func(mLow, al_get_audio_stream_attached, 0);
  rbal_low_func(mLow, al_get_audio_stream_fragment, 0);
  rbal_low_func(mLow, al_set_audio_stream_speed, 1);
  rbal_low_func(mLow, al_set_audio_stream_gain, 1);
  rbal_low_func(mLow, al_set_audio_stream_pan, 1);
  rbal_low_func(mLow, al_set_audio_stream_playmode, 1);
  rbal_low_func(mLow, al_set_audio_stream_playing, 1);
  rbal_low_func(mLow, al_detach_audio_stream, 0);
  rbal_low_func(mLow, al_set_audio_stream_fragment, 1);
  rbal_low_func(mLow, al_rewind_audio_stream, 0);
  rbal_low_func(mLow, al_seek_audio_stream_secs, 1);
  rbal_low_func(mLow, al_get_audio_stream_position_secs, 0);
  rbal_low_func(mLow, al_get_audio_stream_length_secs, 0);
  rbal_low_func(mLow, al_set_audio_stream_loop_secs, 2);
  rbal_low_func(mLow, al_get_audio_stream_event_source, 0);
  rbal_low_func(mLow, al_create_mixer, 2);
  rbal_low_func(mLow, al_destroy_mixer, 0);
  rbal_low_func(mLow, al_attach_sample_instance_to_mixer, 1);
  rbal_low_func(mLow, al_attach_audio_stream_to_mixer, 1);
  rbal_low_func(mLow, al_attach_mixer_to_mixer, 1);
  rbal_low_func(mLow, al_set_mixer_postprocess_callback, 4);
  rbal_low_func(mLow, al_get_mixer_frequency, 0);
  rbal_low_func(mLow, al_get_mixer_channels, 0);
  rbal_low_func(mLow, al_get_mixer_depth, 0);
  rbal_low_func(mLow, al_get_mixer_quality, 0);
  rbal_low_func(mLow, al_get_mixer_playing, 0);
  rbal_low_func(mLow, al_get_mixer_attached, 0);
  rbal_low_func(mLow, al_set_mixer_frequency, 1);
  rbal_low_func(mLow, al_set_mixer_quality, 1);
  rbal_low_func(mLow, al_set_mixer_playing, 1);
  rbal_low_func(mLow, al_detach_mixer, 0);
  rbal_low_func(mLow, al_create_voice, 2);
  rbal_low_func(mLow, al_destroy_voice, 0);
  rbal_low_func(mLow, al_attach_sample_instance_to_voice, 1);
  rbal_low_func(mLow, al_attach_audio_stream_to_voice, 1);
  rbal_low_func(mLow, al_attach_mixer_to_voice, 1);
  rbal_low_func(mLow, al_detach_voice, 0);
  rbal_low_func(mLow, al_get_voice_frequency, 0);
  rbal_low_func(mLow, al_get_voice_position, 0);
  rbal_low_func(mLow, al_get_voice_channels, 0);
  rbal_low_func(mLow, al_get_voice_depth, 0);
  rbal_low_func(mLow, al_get_voice_playing, 0);
  rbal_low_func(mLow, al_set_voice_position, 1);
  rbal_low_func(mLow, al_set_voice_playing, 1);
  rbal_low_func(mLow, al_install_audio, 0);
  rbal_low_func(mLow, al_uninstall_audio, 0);
  rbal_low_func(mLow, al_is_audio_installed, 0);
  rbal_low_func(mLow, al_get_allegro_audio_version, 0);
  rbal_low_func(mLow, al_get_channel_count, 0);
  rbal_low_func(mLow, al_get_audio_depth_size, 0);
  rbal_low_func(mLow, al_reserve_samples, 0);
  rbal_low_func(mLow, al_get_default_mixer, 0);
  rbal_low_func(mLow, al_set_default_mixer, 0);
  rbal_low_func(mLow, al_restore_default_mixer, 0);
  rbal_low_func(mLow, al_play_sample, 5);
  rbal_low_func(mLow, al_stop_sample, 0);
  rbal_low_func(mLow, al_stop_samples, 0);
/* These are not supported  
  rbal_low_func(mLow, al_register_sample_loader, 1);
  rbal_low_func(mLow, al_register_sample_saver, 2);
  rbal_low_func(mLow, al_register_audio_stream_loader, 3);
  rbal_low_func(mLow, al_register_sample_loader_f, 1);
  rbal_low_func(mLow, al_register_sample_saver_f, 2);
  rbal_low_func(mLow, al_register_audio_stream_loader_f, 3);
*/  
  rbal_low_func(mLow, al_load_sample, 0);
  rbal_low_func(mLow, al_save_sample, 1);
  rbal_low_func(mLow, al_load_audio_stream, 2);
  rbal_low_func(mLow, al_load_sample_f, 1);
  rbal_low_func(mLow, al_save_sample_f, 2);
  rbal_low_func(mLow, al_load_audio_stream_f, 3);

}



