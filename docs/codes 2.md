# Codes in general

# location of firmwares
`cd ~/qmk_firmware`

# locations of the keyboards maps
`/Users/jcaliz/qmk_firmware/keyboards/planck/keymaps/josecaliz`
`/Users/jcaliz/qmk_firmware/keyboards/ymdk/ymd40/air40/keymaps/josecaliz`

# create a copy of the default to your own environment
qmk new-keymap -kb planck/rev6_drop
qmk new-keymap -kb <keyboard_name>

# compile a saved keyboard
qmk compile -kb ymdk/ymd40/air40 -km josecaliz
qmk flash -kb ymdk/ymd40/air40 -km josecaliz


qmk compile -kb planck/rev6_drop -km josecaliz
qmk flash -kb planck/rev6_drop -km josecaliz