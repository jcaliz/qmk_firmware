AUDIO_ENABLE = no
RGB_MATRIX_ENABLE = no
RGBLIGHT_ENABLE = no
RGB_MATRIX_CUSTOM_USER = no

ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif
