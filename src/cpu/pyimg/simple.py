from PIL import Image

infile = 'SongHyekyo.jpg'
outfile = 'generated-0.jpg'

while(True):
    Image.open(infile).save(outfile)

