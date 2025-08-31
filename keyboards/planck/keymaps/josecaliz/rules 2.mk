AUDIO_ENABLE = yes
RGB_MATRIX_ENABLE = yes
RGBLIGHT_ENABLE = no
RGB_MATRIX_CUSTOM_USER = yes

ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif
