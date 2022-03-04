# Moonlander keyboard layout from zamazan4ik

My layout for the Moonlander keyboard: https://www.zsa.io/moonlander

This layout is mostly based on the following works:

* https://github.com/optozorax/moonlander
* https://github.com/mersinvald/moonlander

For some deep details about the layout I highly recommend read this article (in Russian): [link](https://optozorax.github.io/p/my-keyboard-layout/)

## How to install

This layout works only with ZSA fork of [QMK firmware](https://github.com/zsa/qmk_firmware). So, before the start you need to install it.

```bash
git clone https://github.com/zsa/qmk_firmware zsa_qmk
cd zsa_qmk
./util/qmk_install.sh
git submodule init
git submodule update
```

Then, you need to create a symbolic link to the directory with your layout. It`s needed for keeping your keyboard outside of QMK internals:

```bash
ln -s /home/optozorax/my/moonlander ~/zsa_qmk/keyboards/moonlander/keymaps/optozorax
```

For installing your layout into the keyboard, execute the following command:
```bash
make moonlander:optozorax:flash
```
