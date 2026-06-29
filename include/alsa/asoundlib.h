/*
 * Minimal ALSA shim for cross-compiling the Flow Control GUI renderer.
 *
 * sokol bundles every backend into a single static library (sokol_clib), so
 * sokol_audio.c is always compiled even though flow only ever links
 * sokol_gfx. When cross-compiling we don't have the system ALSA development
 * headers available, so this shim provides just enough declarations for
 * sokol_audio.c to compile. The resulting sokol_audio.o is never referenced
 * and is dropped by the linker, so none of these symbols ever have to resolve
 * or behave correctly at run time.
 */
#ifndef FLOW_SOKOL_SHIM_ALSA_ASOUNDLIB_H
#define FLOW_SOKOL_SHIM_ALSA_ASOUNDLIB_H

#include <stddef.h>
#include <stdint.h>

typedef struct _snd_pcm snd_pcm_t;
typedef struct _snd_pcm_hw_params snd_pcm_hw_params_t;
typedef unsigned long snd_pcm_uframes_t;
typedef long snd_pcm_sframes_t;

typedef enum { SND_PCM_STREAM_PLAYBACK = 0, SND_PCM_STREAM_CAPTURE = 1 } snd_pcm_stream_t;
typedef enum { SND_PCM_ACCESS_RW_INTERLEAVED = 3 } snd_pcm_access_t;
typedef enum { SND_PCM_FORMAT_FLOAT_LE = 14 } snd_pcm_format_t;

extern int snd_pcm_open(snd_pcm_t **pcm, const char *name, snd_pcm_stream_t stream, int mode);
extern int snd_pcm_close(snd_pcm_t *pcm);
extern int snd_pcm_prepare(snd_pcm_t *pcm);
extern int snd_pcm_drain(snd_pcm_t *pcm);
extern snd_pcm_sframes_t snd_pcm_writei(snd_pcm_t *pcm, const void *buffer, snd_pcm_uframes_t size);

extern size_t snd_pcm_hw_params_sizeof(void);
extern int snd_pcm_hw_params_any(snd_pcm_t *pcm, snd_pcm_hw_params_t *params);
extern int snd_pcm_hw_params(snd_pcm_t *pcm, snd_pcm_hw_params_t *params);
extern int snd_pcm_hw_params_set_access(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, snd_pcm_access_t access);
extern int snd_pcm_hw_params_set_format(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, snd_pcm_format_t format);
extern int snd_pcm_hw_params_set_channels(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, unsigned int val);
extern int snd_pcm_hw_params_set_buffer_size(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, snd_pcm_uframes_t val);
extern int snd_pcm_hw_params_set_rate_near(snd_pcm_t *pcm, snd_pcm_hw_params_t *params, unsigned int *val, int *dir);

/* The real macro stack-allocates via alloca(); a no-op assignment is enough
 * to compile the (dead) call site. */
#define snd_pcm_hw_params_alloca(ptr) do { *(ptr) = (snd_pcm_hw_params_t *)0; } while (0)

#endif /* FLOW_SOKOL_SHIM_ALSA_ASOUNDLIB_H */
