from PIL import Image

infile = 'SongHyekyo.jpg'
outfile = 'generated-'
extension = '.jpg'

count = 0

while(True):
    print('image process %d' % (count))
    for i in range(1000):
        Image.open(infile).convert('L').save(outfile + str(count) + extension)
    count += 1

