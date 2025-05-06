#!/usr/bin/env python3
"""
png_to_c_with_palette.py: Convert une image PNG en tableaux C pour VGA,
avec quantization automatique pour les modes autres que 'P',
et option de charger une palette externe JASC-PAL ou GIMP-GPL.

Usage:
    python3 png_to_c_with_palette.py [-p PALETTE_FILE] <image.png>

Génère :
  - #define SPRITE_WIDTH  <width>
  - #define SPRITE_HEIGHT <height>
  - unsigned char palette_vga[256][3] = {{...}};
  - unsigned char sprite_data[SPRITE_WIDTH*SPRITE_HEIGHT] = {{...}};
"""
import sys
import re
from PIL import Image
import argparse

def parse_jasc_pal(path):
    """Parse un fichier JASC-PAL (.pal) en liste de 256 tuples RGB."""
    with open(path, 'r') as f:
        lines = f.read().splitlines()
    # Format: JASC-PAL / version / 256 / R G B...
    header = lines[:3]
    count = int(header[2])
    data = []
    for line in lines[3:3+count]:
        parts = line.strip().split()
        if len(parts) >= 3:
            data.append(tuple(map(int, parts[:3])))
    # Complète si <256
    data += [(0,0,0)] * max(0, 256 - len(data))
    return data[:256]


def parse_gimp_gpl(path):
    """Parse un fichier GIMP-GPL (.gpl) en liste de 256 tuples RGB."""
    data = []
    with open(path, 'r') as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith('#') or re.match(r'GIMP Palette', line) or line.startswith('Name:') or line.startswith('Columns:'):
                continue
            parts = line.split()
            if len(parts) >= 3:
                data.append(tuple(map(int, parts[:3])))
    data += [(0,0,0)] * max(0, 256 - len(data))
    return data[:256]


def rgb_to_vga(r, g, b):
    """Convertit RGB 8-bit (0–255) en VGA 6-bit (0–63)."""
    return (r * 63) // 255, (g * 63) // 255, (b * 63) // 255


def build_palette_image(palette):
    """Construit une image PIL mode 'P' 1x256 avec la palette donnée."""
    pal_img = Image.new('P', (1, 1))
    flat = []
    for (r,g,b) in palette:
        flat.extend([r, g, b])
    pal_img.putpalette(flat)
    return pal_img


def png_to_c(path, external_palette=None,
             array_name="sprite_data",
             width_name="SPRITE_WIDTH",
             height_name="SPRITE_HEIGHT",
             palette_name="palette_vga"):
    im = Image.open(path)

    # Chargement et application de la palette externe si fournie
    if external_palette:
        # Parse JASC ou GIMP
        ext = external_palette.lower()
        if ext.endswith('.pal'):
            pal = parse_jasc_pal(external_palette)
        elif ext.endswith('.gpl'):
            pal = parse_gimp_gpl(external_palette)
        else:
            print(f"[!] Format de palette non supporté: {external_palette}", file=sys.stderr)
            sys.exit(1)
        # Quantize l'image sur cette palette
        pal_img = build_palette_image(pal)
        im = im.convert('RGB').quantize(palette=pal_img)
    else:
        # Si pas P, quantize en 256 couleurs automatiques
        if im.mode != 'P':
            print(f"[i] Mode actuel: {im.mode}. Conversion en 256 couleurs indexées via quantize...", file=sys.stderr)
            im = im.convert('RGB').quantize(colors=256)
        # Charge palette depuis l'image
        raw_pal = im.getpalette() or []
        raw_pal = raw_pal[:768] + [0] * max(0, 768 - len(raw_pal))
        pal = [(raw_pal[i], raw_pal[i+1], raw_pal[i+2]) for i in range(0, 768, 3)]

    # Conversion en VGA 6-bit
    vga_pal = [rgb_to_vga(r, g, b) for (r, g, b) in pal]

    # Dimensions et données pixels
    w, h = im.size
    data = list(im.getdata())

    # Génération du code C
    print(f"// Généré par png_to_c_with_palette.py à partir de '{path}'", file=sys.stdout)
    print(f"#define {width_name}  {w}", file=sys.stdout)
    print(f"#define {height_name} {h}\n", file=sys.stdout)

    # Palette VGA
    print(f"unsigned char {palette_name}[256][3] = {{", file=sys.stdout)
    for r, g, b in vga_pal:
        print(f"    {{{r}, {g}, {b}}},", file=sys.stdout)
    print("};\n", file=sys.stdout)

    # Sprite data
    print(f"unsigned char {array_name}[{width_name}*{height_name}] = {{", file=sys.stdout)

    for i, pix in enumerate(data):
        sep = "," if i < len(data)-1 else ""
        end = "\n" if (i % 16 == 15) else " "
        sys.stdout.write(f"{pix:3d}{sep}{end}")
    print("};", file=sys.stdout)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Convert PNG to C arrays for VGA with optional external palette.")
    parser.add_argument('-p', '--palette', help="Fichier de palette externe (.pal ou .gpl)")
    parser.add_argument('image', help="Chemin vers l'image PNG à convertir")
    args = parser.parse_args()
    png_to_c(args.image, external_palette=args.palette)
