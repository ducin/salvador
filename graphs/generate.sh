#!/bin/sh

# głowice
dot -Tpng pointers.dot -o pointers.png

# maszyny
dot -Tpng machines.dot -o machines.png

# obrazy
dot -Tpng images.dot -o images.png

# wirtualna maszyna
dot -Tpng virtual.dot -o virtual.png

# siatka kodu
dot -Tpng codearea.dot -o codearea.png
