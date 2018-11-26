from pyzbar.pyzbar import decode
import numpy as np
import imageio


def check(path):
    image = np.array(imageio.imread(path))
    arr = np.zeros(shape=(45, 45), dtype=np.uint8)
    patch_size = 100
    for i in range(image.shape[0] // patch_size):
        for j in range(image.shape[1] // patch_size):
            d = decode(image[i * patch_size : (i + 1) * patch_size, j * patch_size : (j + 1) * patch_size])[0].data
            n = bin(int(d.decode()))[2:]
            n = '0' * (25 - len(n)) + n
            d = np.array([int(c) for c in n])
            d = d.reshape((5, 5))
            arr[i * d.shape[0]: (i + 1) * d.shape[0], j * d.shape[1] : (j + 1) * d.shape[1]] = d

    return decode(np.repeat(np.repeat(arr, 4, axis=0), 4, axis=1) * 255)[0].data

if __name__ == '__main__':
    print(check('../binary/noisy.png').decode())
