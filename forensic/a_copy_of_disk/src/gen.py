import numpy as np
import imageio


def main():
    image = np.array(imageio.imread('disk_reshape.png'))
    w, h = 320, 160
    mask_raw = np.array(imageio.imread('mask.png'))[:, :, 0]
    print(image.shape)
    print(mask_raw.shape)
    mask = [mask_raw[:, i * 5: (i + 1) * 5] for i in range(16)]
    zero_mask = mask[9]
    mask[0:8] = mask[1:9]
    mask[0] = zero_mask

    with open('test.img', 'rb') as f:
        data = f.read()
    alpha = np.ones(shape=image.shape[:2], dtype=image.dtype)
    for i, c in enumerate(data):
        d1, d2 = c // 0x10, c % 0x10
        mask_patch = np.concatenate((mask[d1], mask[d2]), axis=1)
        y, x = i //w, i % w
        alpha[y * 10 : (y + 1) * 10, x * 10 : (x + 1) * 10] = mask_patch
    np.place(alpha, alpha == 0, 240)
    result = np.concatenate((image, np.expand_dims(alpha, axis=2)), axis=2)
    print(result.shape)
    print(result.dtype)
    imageio.imwrite('copy.png', result)


if __name__ == '__main__':
    main()
