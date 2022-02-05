import gzip
import shutil
import os

root = '..\data\www'

for subdir, dirs, files in os.walk(root):
    for file in files:
        if not file.endswith('.gz'):
            with open(os.path.join(subdir, file), 'rb') as input_file:
                print('Gzipping ' + os.path.join(subdir, file))
                with gzip.open(os.path.join(subdir, file) + '.gz', 'wb') as output_file:
                    shutil.copyfileobj(input_file, output_file)
            os.remove(os.path.join(subdir, file))